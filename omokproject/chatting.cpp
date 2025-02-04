
#define Chatting
#ifdef Chatting

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <unordered_map>
#include <mutex>

#pragma comment(lib, "ws2_32.lib") // Winsock ���̺귯�� ��ũ

using namespace std;

const int SERVER_PORT = 8080;

vector<SOCKET> clients;

void handleClient(SOCKET clientSocket) {
	char buffer[1024];

	//���� �ʱ�ȭ
	memset(buffer, 0, sizeof(buffer));

	// ù ��° ������(username) �ޱ�
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived <= 0)
	{
		closesocket(clientSocket);
		return;
	}

	buffer[bytesReceived] = '\0'; //���ڿ� ���� ����
	string username = buffer;
	cout << "����� '" << username << "' ��(��) �����." << endl;

	// ä�� ����
	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived <= 0) break;
		buffer[bytesReceived] = '\0';//���ڿ� ����

		cout << "[" << username << "] : " << buffer << endl;

		// ��� Ŭ���̾�Ʈ���� �޽��� ����(��ε�ĳ��Ʈ)

		for (SOCKET client : clients)
		{
			if (client != clientSocket)
			{
				send(client, buffer, bytesReceived, 0);
			}
		}
	}
	
	cout << "����� '" << username << "' ��(��) �����." << endl;
	closesocket(clientSocket);
}

int main() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		cerr << "Winsock �ʱ�ȭ ����!" << endl;
		return 1;
	}
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cerr << "���� ���� ���� ����!" << endl;
		WSACleanup();
		return 1;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cerr << "���� ���� ���� ����!" << endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cerr << "���ε� ����!" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
}
#endif // Chatting
