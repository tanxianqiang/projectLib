#include "txqlocalclient.h"
#include "txqcom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/mysocket.sock"
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    START_APP(argv[0]);
    // 创建本地套接字
    int sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("创建套接字失败");
        return -1;
    }

    // 连接服务端
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("绑定套接字失败");
        close(sock_fd);
        return -1;
    }
    if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("连接服务端失败");
        close(sock_fd);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    while (1) {
        // 从标准输入获取要发送的数据
       // fgets(buffer, sizeof(buffer), stdin);
        snprintf(buffer, sizeof(buffer), "local client test");

        if (strlen(buffer) == 1) {
            continue;
        }
        buffer[strlen(buffer) - 1] = '\0';

        // 发送数据给服务端
        ssize_t bytes_written = write(sock_fd, buffer, strlen(buffer));
        if (bytes_written == -1) {
            perror("发送数据给服务端失败");
            break;
        }

        // 接收服务端回显的数据
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = read(sock_fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("读取服务端回显数据失败");
            break;
        } else if (bytes_read == 0) {
            printf("服务端关闭连接\n");
            break;
        }
        printf("服务端回显: %s\n", buffer);
        break;
    }

    close(sock_fd);
    END_APP(argv[0]);
    return 0;
}