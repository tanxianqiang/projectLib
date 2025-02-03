
#include "txqcom.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/msg.h>
 #include <sys/sem.h>

#define SHM_SIZE 1024

int ipcsMem() {
    key_t key;
    int shmid;
    char *shm, *s;

    // 创建一个唯一的键值
    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(1);
    }

    // 创建共享内存段
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // 将共享内存段连接到进程地址空间
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // 父进程写入数据
    if (fork() == 0) {
        s = shm;
        for (int i = 0; i < 10; i++) {
            sprintf(s, "This is a test %d\n", i);
            s += strlen(s);
        }
        // 分离共享内存段
        if (shmdt(shm) == -1) {
            perror("shmdt in child");
            exit(1);
        }
    } else {
        // 父进程等待子进程完成写入
        wait(NULL);
        s = shm;
        while (*s) {
            printf("%s", s);
            s += strlen(s);
        }
        // 分离共享内存段
        if (shmdt(shm) == -1) {
            perror("shmdt in parent");
            exit(1);
        }
        // 删除共享内存段
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }
    return 0;
}

#define MSG_SIZE 128

// 定义消息结构
typedef struct msgbuff {
    long mtype;
    char mtext[MSG_SIZE];
} message_buf;

int ipcsMsg() {
    key_t key;
    int msgid;
    message_buf msg;

    // 创建一个唯一的键值
    if ((key = ftok(".", 'b')) == -1) {
        perror("ftok");
        exit(1);
    }

    // 创建消息队列
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    // 父进程发送消息
    if (fork() == 0) {
        msg.mtype = 1;
        strcpy(msg.mtext, "Hello from child!");
        if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    } else {
        // 父进程接收消息
        if (msgrcv(msgid, &msg, MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Received: %s\n", msg.mtext);
        // 删除消息队列
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }
    return 0;
}

// 定义信号量操作函数
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void semaphore_p(int semid) {
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = SEM_UNDO;
    if (semop(semid, &sops, 1) == -1) {
        perror("semaphore_p");
        exit(1);
    }
}

void semaphore_v(int semid) {
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = SEM_UNDO;
    if (semop(semid, &sops, 1) == -1) {
        perror("semaphore_v");
        exit(1);
    }
}

int ipcsSem() {
    key_t key;
    int semid;
    union semun arg;

    // 创建一个唯一的键值
    if ((key = ftok(".", 'c')) == -1) {
        perror("ftok");
        exit(1);
    }

    // 创建信号量
    if ((semid = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // 初始化信号量
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    // 父进程和子进程通过信号量同步
    if (fork() == 0) {
        semaphore_p(semid);
        printf("Child process has entered critical section.\n");
        sleep(2);
        printf("Child process is leaving critical section.\n");
        semaphore_v(semid);
    } else {
        semaphore_p(semid);
        printf("Parent process has entered critical section.\n");
        sleep(2);
        printf("Parent process is leaving critical section.\n");
        semaphore_v(semid);
        // 删除信号量
        if (semctl(semid, 0, IPC_RMID, arg) == -1) {
            perror("semctl");
            exit(1);
        }
    }
    return 0;
}



int main(int argc, char* argv[]) {
   START_APP(argv[0]);
   ipcsMem();
   ipcsMsg();
   ipcsSem();
   END_APP(argv[0]);
   return 0;
}
