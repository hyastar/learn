#ifdef _WIN32
//#include <winsock2.h>
#include <windows.h>
//#include <ws2tcpip.h>

//#pragma comment(lib, "ws2_32.lib")
#else 

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define closesocket close

#endif

#include <stdio.h>

int main(int argc, char* argv[]) {
#ifdef WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
		printf("WSAStartup failed\n");
		return -1 ;
	}
#endif
	for (int i = 0; i < 2000; ++i) {
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == -1) {
			printf("create socket failed\n");
			return -1;
		}
		printf("[%d]" , sock);
		closesocket(sock);
	}
	getchar();
	return 0;
}
