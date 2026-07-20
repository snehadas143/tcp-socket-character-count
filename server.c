#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, cli_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE]; //to read message from client
    int count;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//or localhost
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    listen(server_fd, 5);
    printf("Server is waiting for connection...\n");

    // Accept connection
    cli_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen);
    if (cli_socket < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");

	for(int i = 0; i < 5; i++) 
	{
		    memset(buffer, 0, sizeof(buffer)); //clear the buffer before receiving a new message.
		    // Receive message
		    recv(cli_socket, buffer, sizeof(buffer), 0);

		    printf("Message %d: %s from client:\n", i + 1, buffer);
		    // Count characters
		    count = strlen(buffer);
		    printf("Character Count = %d\n", count);
		    // Send count back
		    send(cli_socket, &count, sizeof(count), 0);
	}
	printf("Processed 5 messages. Closing connection.\n");

    close(cli_socket);
    close(server_fd);
    return 0;
}
