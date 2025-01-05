#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
//#include <winsock2.h>
#include <windows.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
#else 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define closesocket close
#endif


int main(int argc, char* argv[]) {
#ifdef _WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
		printf("WSAStartup failed\n");
		return -1 ;
	}
#endif
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("create socket failed\n");
		return -1;
	}
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);
	if (bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		printf("bind port %d failed!\n", port);
		return -2;
	}
	printf("bind port %d success!\n", port);
	listen(sock, 10);

	getchar();
	return 0;
}
