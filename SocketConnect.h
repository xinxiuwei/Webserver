#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

class SocketConnection
{
public:
	SocketConnection();
	int initserver(int port);
	int Accept(int lisfd);
	void Close(int cofd);

private:
	int listenfd;
	int connfd;
};

#endif