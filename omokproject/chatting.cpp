
#define Chatting
#ifdef Chatting

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <unordered_map>
#include <mutex>

#pragma comment(lib, "ws2_32.lib") // Winsock 라이브러리 링크

using namespace std;

const int SERVER_PORT = 8080;

vector<SOCKET> clients;

void handleClient(SOCKET clientSocket) {
	char buffer[1024];

	//버퍼 초기화
	memset(buffer, 0, sizeof(buffer));

	// 첫 번째 데이터(username) 받기
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived <= 0)
	{
		closesocket(clientSocket);
		return;
	}

	buffer[bytesReceived] = '\0'; //문자열 종료 보장
	string username = buffer;
	cout << "사용자 '" << username << "' 이(가) 연결됨." << endl;

	// 채팅 루프
	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived <= 0) break;
		buffer[bytesReceived] = '\0';//문자열 종료

		cout << "[" << username << "] : " << buffer << endl;

		// 모든 클라이언트에게 메시지 전송(브로드캐스트)

		for (SOCKET client : clients)
		{
			if (client != clientSocket)
			{
				send(client, buffer, bytesReceived, 0);
			}
		}
	}
	
	cout << "사용자 '" << username << "' 이(가) 종료됨." << endl;
	closesocket(clientSocket);
}

int main() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		cerr << "Winsock 초기화 실패!" << endl;
		return 1;
	}
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cerr << "서버 소켓 생성 실패!" << endl;
		WSACleanup();
		return 1;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cerr << "서버 소켓 생성 실패!" << endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cerr << "바인딩 실패!" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
}
#endif // Chatting
