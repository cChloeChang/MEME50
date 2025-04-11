#include "client.h"
#include <ctype.h>

int main()
{
    int server_fifo_fd, client_fifo_fd, read_res, write_res;
    struct data_to_pass_st my_data;
    char client_fifo[256];
	
	// 建立連線
    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        exit(EXIT_FAILURE);
    }

    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
    if (mkfifo(client_fifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
        exit(EXIT_FAILURE);
    }


	printf("可以開始輸入訊息囉!\n");
	memset(my_data.some_data, '\0', sizeof(my_data.some_data)); // 初始化some_data

	while(1){
		fgets(my_data.some_data, BUFFER_SIZE, stdin);
		my_data.some_data[strcspn(my_data.some_data, "\n")] = 0; // fgets 會把使用者按下的換行符（\n）也存進 my_data.some_data，這會導致顯示時多一個換行，或者傳給 server 時帶著換行符，所以要移除\n
		printf("client: %s\n", my_data.some_data); // 顯示訊息內容
        write_res = write(server_fifo_fd, &my_data, sizeof(my_data)); // 訊息發給server
		if(write_res == -1){
			fprintf(stderr, "Failed to write to server\n");
			exit(EXIT_FAILURE);
		}
       
		// 讀取資料
		if (strncmp(my_data.some_data, "bye", 3) == 0) {
			break;
		}
		
		client_fifo_fd = open(client_fifo, O_RDONLY);
		if (client_fifo_fd == -1) { // 無法讀取
			fprintf(stderr, "Sorry, can't open client fifo %s\n", client_fifo);
			exit(EXIT_FAILURE);
		}
 
		read_res = read(client_fifo_fd, &my_data, sizeof(my_data));
        if (read_res > 0) {
            printf("server: %s\n", my_data.some_data);
			if (strncmp(my_data.some_data, "bye", 3) == 0) { // 檢查 Server 回覆是否為 "bye"
                close(client_fifo_fd);
                break;
            }
        }else if (read_res == 0) { // server 正常斷線
            printf("Server disconnected\n");
			close(client_fifo_fd);
            break;
        }else{ // read_res < 0，讀取錯誤
			fprintf(stderr, "Error reading from server\n");
			close(client_fifo_fd);
			exit(EXIT_FAILURE);
		}
		
		close(client_fifo_fd); // 每次接收後關閉，下次迴圈重新打開 client_fifo_fd
    }

    close(server_fifo_fd);
    unlink(client_fifo);
    exit(EXIT_SUCCESS);
}
