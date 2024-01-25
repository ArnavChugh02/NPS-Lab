#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void print_permutations(char *str, int start, int end);

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE] = {0};

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for a string from the client...\n");

    // Receive the string from the client
    if (recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &client_address_len) == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // Print permutations of the received string
    printf("Received string from client: %s\n", buffer);
    printf("All permutations of the string:\n");
    print_permutations(buffer, 0, strlen(buffer) - 1);

    close(server_socket);

    return 0;
}

// Function to print all permutations of a string
void print_permutations(char *str, int start, int end) {
    if (start == end) {
        printf("%s\n", str);
    } else {
        for (int i = start; i <= end; i++) {
            // Swap characters
            char temp = str[start];
            str[start] = str[i];
            str[i] = temp;

            // Recursively call the function for the next character
            print_permutations(str, start + 1, end);

            // Swap back to the original configuration (backtrack)
            temp = str[start];
            str[start] = str[i];
            str[i] = temp;
        }
    }
}

