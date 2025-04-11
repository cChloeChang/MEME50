#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <signal.h>

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT]; 
};

void cleanup(int signo) {
    int msgid = msgget((key_t)1234, 0666);
    if (msgid != -1) {
        struct my_msg_st disconnect_msg;
        disconnect_msg.my_msg_type = 2; // server 發送給 client 的類型
        strcpy(disconnect_msg.some_text, "\nserver_disconnected");
        msgsnd(msgid, (void *)&disconnect_msg, MAX_TEXT, IPC_NOWAIT); // 非阻塞send
        msgctl(msgid, IPC_RMID, 0); // delete msg queue
    }
    printf("\nserver disconnected\n"); // 換行顯示
    exit(EXIT_SUCCESS);
}

int main() {
    int running = 1;
    int msgid;
    struct my_msg_st send_data, recv_data;
    char buffer[MAX_TEXT];

    // 建立 msg queue，key 固定為 1234
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msg queue 建立失敗: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("等待 client 連線...\n");

    // ctrl+c 清理 msg queue
    signal(SIGINT, cleanup);

    while (running) {
        // 接收 client 的 msg (類型設為 1)
        if (msgrcv(msgid, (void *)&recv_data, MAX_TEXT, 1, 0) == -1) {
            fprintf(stderr, "msg 接收失敗: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        // 檢查是否為 client 斷線
        if (strcmp(recv_data.some_text, "\nclient_disconnected") == 0) {
            printf("\nclient disconnected\n"); // 換行顯示
            running = 0;
            continue;
        }

        printf("client: %s\n", recv_data.some_text);

        // 檢查是否收到 "bye"
        if (strncmp(recv_data.some_text, "bye", 3) == 0) {
            running = 0;
            continue;
        }

        // 輸入回覆 msg
        printf("enter msg: ");
        fgets(buffer, MAX_TEXT, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // 移除\n
        printf("server: %s\n", buffer);

        // 準備發送 msg (類型設為 2)
        send_data.my_msg_type = 2;
        strcpy(send_data.some_text, buffer);

        // 發送 msg 給 client
        if (msgsnd(msgid, (void *)&send_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msg 發送失敗\n");
            exit(EXIT_FAILURE);
        }

        // 檢查是否輸入 "bye"
        if (strncmp(buffer, "bye", 3) == 0) {
            running = 0;
        }
    }

    // 清理 msg queue 並結束
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msg queue 刪除失敗\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
