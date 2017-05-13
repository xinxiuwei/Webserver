#include "SocketConnect.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <arpa/inet.h>
#include <sys/socket.h>


const int  LISTENQ = 1024;
void unix_error(char *msg) /* unix-style error */
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}


SocketConnection::SocketConnection() : listenfd(-1), connfd(-1)
{

}

int SocketConnection::initserver(int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;

	/* Create a socket descriptor */
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		unix_error("create socket error");

	/* Eliminates "Address already in use" error from bind. */
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval,
			sizeof(int)) < 0)
		unix_error("create socket error");

	/* Listenfd will be an endpoint for all requests to port
	 on any IP address for this host */
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short) port);
	if (bind(listenfd, (sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
		unix_error("bind error");

	/* Make it a listening socket ready to accept connection requests */
	if (listen(listenfd, LISTENQ) < 0)
		unix_error("listen error");
    printf("listenfd=%d\n",listenfd );
	return listenfd;
	
}

int SocketConnection::Accept(int lisfd)
{
    int listenfd=lisfd;
	struct sockaddr_in clientaddr;
	socklen_t clientlen=sizeof(clientaddr);
	if((connfd = accept(listenfd, (sockaddr *) &clientaddr,  &clientlen))<0)
		unix_error("accept error");
	else
		printf("accept ok\n");
		

	return connfd;
}

void SocketConnection::Close(int cofd)
{
	int connfd=cofd;
	if(close(connfd)<0)
		unix_error("Close error");
}
