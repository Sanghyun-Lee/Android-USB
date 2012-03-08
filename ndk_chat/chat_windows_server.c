
#include <winsock2.h>   
#include <WinSock.h>
#include <stdio.h>   


#define MAXLINE 1024  
#define PORT 3600   
#define MAX_THREADS 1

DWORD WINAPI MyThreadFunction(LPVOID lpParam);


int main()   
{   
	WSADATA wsaData;   
	int status;   
	int SockLen;   
	int Readn,Writen;   
	SOCKET EndpointSocket, ClientSocket;   
	struct sockaddr_in SockInfo, ClientSockInfo;   
	char ReadBuffer[MAXLINE];   
	DWORD dwThreadIdArray[MAX_THREADS];

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!= 0)   
	{   
		printf("error\r\n");   
		return 0;   
	}   

	EndpointSocket = socket( AF_INET, SOCK_STREAM, 0 );   
	if( EndpointSocket == INVALID_SOCKET )   
		return 1;   

	printf("Success socket create\r\n");   
	ZeroMemory(&SockInfo, sizeof( struct sockaddr_in ));   

	SockInfo.sin_family = AF_INET;   
	SockInfo.sin_port = htons( PORT );   
	SockInfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   

	status = bind( EndpointSocket, (struct sockaddr*)&SockInfo, sizeof( struct sockaddr_in) );   
	if( status == SOCKET_ERROR)    
	{   
		printf("Bind Error\n");   
		return 0;   
	}   
	if( SOCKET_ERROR == listen( EndpointSocket, 5 ))   
	{   
		printf("listen Error\n");   
		return 0;   
	}   

	ZeroMemory( &ClientSockInfo, sizeof( struct sockaddr_in ) );   
	SockLen = sizeof(struct sockaddr_in);   
	ClientSocket = accept( EndpointSocket, (struct sockaddr*)&ClientSockInfo, &SockLen );   
	if(ClientSocket == INVALID_SOCKET)   
	{   
		printf("Accept Error\n");   
		closesocket(EndpointSocket);   
		WSACleanup();   
		return 1;   
	}   
	printf("Accept Client\n"); 


	CreateThread(
		NULL,
		0,
		MyThreadFunction,
		(LPVOID)&ClientSocket,
		0,
		&dwThreadIdArray[0]
	);

	while(1)   
	{   
		memset(ReadBuffer, 0x00, MAXLINE);
		Readn = recv(ClientSocket, ReadBuffer, MAXLINE, 0);
		if(Readn <=0)
		{
			printf("Recv error\n");
			return 1;
		}
		printf("Client: %s", ReadBuffer);
		
	}
	closesocket(ClientSocket);
	closesocket(EndpointSocket);    
	WSACleanup();   
	return 0;   

}   

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{

	SOCKET sockfd = *(SOCKET *)lpParam;
	char buf[MAXLINE];
	printf("connect success\n");
	while(1)
	{
		gets(buf);
		send(sockfd, buf, MAXLINE, 0);
	}
}