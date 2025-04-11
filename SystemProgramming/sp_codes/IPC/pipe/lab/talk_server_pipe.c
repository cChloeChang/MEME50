#include "client.h"
#include <ctype.h>

int main()
{
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    int read_res;
    char client_fifo[256];

    mkfifo(SERVER_FIFO_NAME, 0777);
	printf("wait for client to connect...\n");
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    if (server_fifo_fd == -1) {
        fprintf(stderr, "Server fifo failure\n");
        exit(EXIT_FAILURE);
    }

	printf("可以開始輸入訊息囉!\n");

    while(1) {
        read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
        if (read_res > 0) {
			printf("client: %s\n", my_data.some_data);
            sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);

            client_fifo_fd = open(client_fifo, O_WRONLY);
			if (client_fifo_fd == -1) {
                fprintf(stderr, "Failed to open client fifo %s\n", client_fifo);
                continue; // 跳過這次迴圈，等待下一次訊息
            }

            fgets(my_data.some_data, BUFFER_SIZE, stdin);
			my_data.some_data[strcspn(my_data.some_data, "\n")] = 0;
            printf("server: %s\n", my_data.some_data);
            write(client_fifo_fd, &my_data, sizeof(my_data));
            close(client_fifo_fd);

			// 如果 server 輸入 "bye"，結束程式
            if (strncmp(my_data.some_data, "bye", 3) == 0) {
				write(client_fifo_fd, &my_data, sizeof(my_data)); // 發送 "bye"
				close(client_fifo_fd);
				close(server_fifo_fd); // 關閉server_fifo_fd的寫入
				unlink(SERVER_FIFO_NAME);
                break;
            }
        }else if (read_res == 0) { // client斷線
            printf("Client disconnected\n");
            break;
		} else { // read_res < 0，讀取錯誤
            fprintf(stderr, "Error reading from client\n");
            exit(EXIT_FAILURE);
        }
    } 
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
    exit(EXIT_SUCCESS);
}
