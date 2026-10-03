#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>

#define HOSTNAME	INADDR_ANY
#define PORT		8080

int main() {
	std::cout << "web server starting up. opening socket." << std::endl;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = HOSTNAME;

	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(serverSocket, 5);

	int clientSocket = accept(serverSocket, nullptr, nullptr);
	char buffer[1024] = {0};
	ssize_t n = recv(clientSocket, buffer, sizeof(buffer), 0);

	std::cout << "message from client: " << buffer << std::endl;
	std::cout << "ssize_t n from recv was: " << n << std::endl;

	const char* headers =	    "HTTP/1.1 200 OK\r\n"
				    "Content-Type: text/plain\r\n"
				    "Content-Length: %zu\r\n"
				    "Connection: close\r\n"
				    "\r\n";

	const char* message = "Hello, World!";

	char* resp = new char[strlen(headers) + strlen(message) + 1];
	memcpy(resp, headers, strlen(headers));
	memcpy(resp + strlen(headers), message, strlen(message) + 1);
	
	ssize_t sent = send(clientSocket, resp, strlen(resp), 0);
	delete[] resp;

	if (sent < 0) {
		std::cout << "error! didnt send!!!" << std::endl;
	};
	return 0;
}
