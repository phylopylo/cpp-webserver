#include <iostream>
#include <memory>
#include <cstring>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define HOSTNAME	INADDR_ANY
#define PORT		8080
#define NUM_THREADS	10

static bool isFinished(0);

std::shared_ptr<std::string> webcontent() {

	std::string content = "Hello, World!";

	std::string headers = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: " + std::to_string(content.size()) + "\r\n"
		"Connection: close\r\n"
		"\r\n";


	std::shared_ptr<std::string> resp =
		std::make_shared<std::string>(
			headers + content
		);

	return resp;
}

int server() {
	std::cout << "web server starting up. opening socket." << std::endl;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		std::cout << "setsockopt failed" << std::endl;
		exit(1);
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = HOSTNAME;

	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(serverSocket, 5);
	return serverSocket;
}

void recieve(int serverSocket) {
	int clientSocket = accept(serverSocket, nullptr, nullptr);
	char buffer[1024] = {0};
	ssize_t n = recv(clientSocket, buffer, sizeof(buffer), 0);

	std::cout << "message from client: " << buffer << std::endl;
	std::cout << "ssize_t n from recv was: " << n << std::endl;

	std::shared_ptr<std::string> resp = webcontent();
	std::cout << "sending message to client: " << resp->c_str() << std::endl;
	ssize_t sent = send(clientSocket, resp->c_str(), resp->size(), 0);

	if (sent < 0) {
		std::cout << "error! didnt send!!!" << std::endl;
	} else {
		std::cout << "sent with code " << sent << std::endl;
	};
	shutdown(clientSocket, SHUT_WR);
	close(clientSocket);
}

void recieveLoop(int serverSocket) {
	while(!isFinished) {
		recieve(serverSocket);
	};
}

int main() {
	int serverSocket = server();
	if(serverSocket < 0) {
		std::cout << "failed to initialize socket with code " << serverSocket << std::endl;
		return 0;
	}

	std::vector<std::thread> threads;
	threads.reserve(NUM_THREADS);

	for (int i(0); i < NUM_THREADS; i++) {
		threads.emplace_back(recieveLoop, serverSocket);
	};


	std::cout << "Accepting new connections on socket " << serverSocket << std::endl;

	for (std::thread& thread : threads)
		thread.join();

	return 0;
}
