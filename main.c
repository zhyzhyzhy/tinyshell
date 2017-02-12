/**
	File Name: main.c
	Author: zhy
	Created Time: 2017/02/11 - 13:12:22
*/

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "helper.h"

#define BACKLOG 1024

int main(int argc, char *argv[])
{
	int server_fd, conn_fd;
	unsigned short port;
	struct sockaddr_in addr_c;

	if (argc != 3) {
		fprintf(stderr, "usage: simpleserver Host port");
		exit(1);
	}

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		perror("socket :");
		exit(1);
	}

    //get port
	char *temp;
	port = (unsigned short) strtol(argv[2], &temp, 0);

    memset(&addr_c, 0, sizeof(addr_c));
	addr_c.sin_family = AF_INET;
    addr_c.sin_addr.s_addr = inet_addr(argv[1]);
    addr_c.sin_port = htons(port);

	int ret = bind(server_fd, (struct sockaddr*)&addr_c, sizeof(addr_c));
	if(ret == -1) {
		perror("bind :");
		exit(1);
	}


	int addr_clen = sizeof(addr_c);
	while(1) {
		listen(server_fd, BACKLOG);
		conn_fd = accept(server_fd, (struct sockaddr*)&addr_c, (socklen_t *) &addr_clen);
		if(fork() == 0) {
			close(server_fd);
            response(conn_fd);
			return 0;
		}
		else {
			close(conn_fd);
		}
	}
	return 0;
}
