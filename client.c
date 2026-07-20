#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    int count;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

	for(int i = 0; i < 5; i++) 
	{
		// Read message
		printf("Enter a message: ");
		fgets(message, BUFFER_SIZE, stdin);

		// Remove newline
		message[strcspn(message, "\n")] = '\0';

		// Send message
		send(sock, message, strlen(message)+1, 0);

		// Receive count
		recv(sock, &count, sizeof(count), 0);
		printf("Reply from Server\n");
		printf("Total number of characters = %d\n", count);
	}

    close(sock);
    return 0;
}
