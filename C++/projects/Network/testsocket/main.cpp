#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
//#include <winsock2.h>
#include <windows.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
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
	
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len);
	printf("accpet client %d\n", client);
	char* ip = inet_ntoa(caddr.sin_addr);
	unsigned short cport = ntohs(caddr.sin_port);
	printf("client ip is %s, port is %d\n", ip, cport);
	char buf[1024];
	for (;;) {
		int recvlen = recv(client, buf, sizeof(buf) - 1, 0);
		if (recvlen <= 0) break;
		buf[recvlen] = '\0';
		if (strstr(buf, "quit") != NULL) break;
		printf("recv %s\n", buf);
	}
	closesocket(client);

	getchar();

	return 0;
}
