/*
 *  Created on: 2017年4月18日
 *      Author: xinxiuwei
*/

#include <cstdlib>
#include <sys/epoll.h>
#include "RequestManager.h"
#include <errno.h>
#include <stdio.h> 
#include <unistd.h>　
#include <sys/types.h>
#include "SocketConnect.h"
#include <sys/wait.h>
#include <signal.h>


int getPort(int argc, char *argv[])
{
	if (argc != 2) 
	{  
        fprintf(stderr, "usage: %s <port>\n", argv[0]);  
        exit(0);
    }
	else
    printf("port=%d\n",atoi(argv[1]));
		return atoi(argv[1]);
  
}

void handle_child(int sig)
{
  pid_t pid;
  while(1)
  {
    pid=waitpid(0,NULL,WNOHANG);
  }
}


int main(int argc, char *argv[])
{
	int listenfd;
  
	SocketConnection sockeconnection;
  
	listenfd=sockeconnection.initserver(getPort(argc,argv));
 
  signal(SIGCHLD,handle_child);

	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(listenfd, &rset);
	while(1)
	{
    printf("set select\n");
		int ret=select(listenfd+1, &rset,NULL,NULL,NULL);
    printf("ret=%d\n",ret);
		switch(ret)   
       {   
       case 0:   
           printf("time out/n");   
           break;  
       case -1:   
           printf("select error");   
           exit(1);   
       default:   
           if(FD_ISSET(listenfd,&rset))   
           {
           		pid_t pid;
           		if((pid=fork())==0)
           			{
                  printf("child create ok\n");
           				int connfd=sockeconnection.Accept(listenfd);
                  printf("accept ok\n");
                  RequestManager(connfd).doit();
                  sockeconnection.Close(connfd);
           			}  
           }   
          
      }   

	}

  
	exit(0);

}