#include "txqlocalserver.h"
#include "txqcom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/mysocket.sock"
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    bool exitFlagSingle = false;
    START_APP(argv[0]);
    // 1. 创建本地套接字
    int listen_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("创建套接字失败");
        return -1;
    }

    // 绑定套接字到本地文件
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    unlink(SOCKET_PATH);
    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("绑定套接字失败");
        close(listen_fd);
        return -1;
    }

    // 监听套接字
    if (listen(listen_fd, 5) == -1) {
        perror("监听套接字失败");
        close(listen_fd);
        return -1;
    }

    // 创建epoll实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("创建epoll实例失败");
        close(listen_fd);
        return -1;
    }

    // 将监听套接字添加到epoll关注列表
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
        perror("添加监听套接字到epoll失败");
        close(epoll_fd);
        close(listen_fd);
        return -1;
    }

    struct epoll_event events[MAX_EVENTS];
    while (1) {
        // 等待事件发生
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("epoll等待事件失败");
            break;
        }

        for (int i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;
            if (fd == listen_fd) {
                // 有新连接到来
                int client_fd = accept(listen_fd, NULL, NULL);
                if (client_fd == -1) {
                    perror("接受新连接失败");
                    continue;
                }
                // 将新连接添加到epoll关注列表
                struct epoll_event client_event;
                memset(&client_event, 0, sizeof(client_event));
                client_event.events = EPOLLIN;
                client_event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
                    perror("添加客户端连接到epoll失败");
                    close(client_fd);
                    continue;
                }
            } else {
                // 处理客户端发来的数据以及对端关闭连接情况
                struct epoll_event client_event;
                memset(&client_event, 0, sizeof(client_event));
                client_event.events = EPOLLIN | EPOLLRDHUP;
                client_event.data.fd = fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &client_event) == -1) {
                    perror("修改客户端事件设置失败");
                    continue;
                }

                char buffer[BUFFER_SIZE];
                memset(buffer, 0, sizeof(buffer));
                ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
                if (bytes_read == -1) {
                    perror("读取客户端数据失败");
                    continue;
                } else if (bytes_read == 0) {
                    // 客户端关闭连接，检测是否是半关闭状态（EPOLLRDHUP）
                    if (events[i].events & EPOLLRDHUP) {
                        printf("客户端半关闭连接\n");
                    } else {
                        printf("客户端完全关闭连接\n");
                    }
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1) {
                        perror("从epoll移除客户端连接失败");
                    }
                    close(fd);
                    exitFlagSingle = true;
                    break;
                } else {
                    // 回显数据给客户端
                    write(fd, buffer, bytes_read);
                }
            }
        }
        if (exitFlagSingle == true) {
            break;
        }
    }

    close(epoll_fd);
    close(listen_fd);
    unlink(SOCKET_PATH);
    END_APP(argv[0]);
    return 0;
}