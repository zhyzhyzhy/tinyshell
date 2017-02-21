//
// Created by zhy on 2/21/17.
//

#include "handle.h"
#include "mysocket.h"
#include <stdio.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void do_get(int connfd, char* file_name, char* file_type) {
    char buffer[8192];
    int fd;
    if(strncmp(file_name, "", strlen(file_name)) == 0) {
        fd = open("index.html", O_RDONLY);
    } else {
        fd = open(file_name, O_RDONLY);
    }
    if (fd == -1) {
        server_error(connfd, 400, "file not found");
        return;
    }
    char header[1024];
    sprintf(header,"HTTP/1.1 200 ok\r\n");
    sprintf(header,"%sServer: zhy's Server\r\n",header);
    sprintf(header,"%sContent-type: %s\r\n\r\n",header, file_type);
    send(connfd, header, strlen(header), 0);

    int length;
    while ((length = read(fd, buffer, 8192)) > 0) {
        send(connfd, buffer, length, 0);
    }
    close(fd);
}
void response(int connfd) {
    char method[24];
    char path[1024];
    char version[24];

    memset(method, 0, 24);
    memset(path, 0, 1024);
    memset(version, 0, 24);

    char request[8192];

    while(recv(connfd, request, 8192, 0) > 0) {
        struct sockaddr_in client = get_conn_info(connfd);
        sscanf(request, "%s %s %s", method, path, version);
        printf("get connect from :  %s\n", inet_ntoa(client.sin_addr));
        printf("method : %s\npath : %s\nversion : %s\n", method, path, version);
        printf("response fd = %d\n\n", connfd);
        if (strncmp(method, "GET", 3) == 0) {
            if (strstr(path, ".html") != NULL || strncmp(path+1, "", strlen(path)-1) == 0) {
                do_get(connfd, path+1, "text/html");
            } else if(strstr(path, ".js") != NULL) {
                do_get(connfd, path+1, "text/js");
            } else if(strstr(path, ".css") != NULL) {
                do_get(connfd, path+1, "text/css");
            } else if(strstr(path, ".xml") != NULL) {
                do_get(connfd, path+1, "text/xml");
            } else if(strstr(path, ".xhtml") != NULL) {
                do_get(connfd, path+1, "application/xhtml+xml");
            } else if(strstr(path, ".png") != NULL) {
                do_get(connfd, path+1, "image/png");
            } else if(strstr(path, ".gif") != NULL) {
                do_get(connfd, path+1, "image/gif");
            } else if(strstr(path, ".jpg") != NULL) {
                do_get(connfd, path+1, "image/jpg");
            } else if(strstr(path, ".jpeg") != NULL) {
                do_get(connfd, path+1, "image/jpeg");
            } else if(strstr(path, ".jpeg") != NULL) {
                do_get(connfd, path+1, "image/jpeg");
            } else if(strstr(path, ".woff") || strstr(path, ".ttf")){
                do_get(connfd, path+1, "application/octet-stream");
            } else
                do_get(connfd, path+1, "text/plain");
        }
    }
    close(connfd);
}
void server_error(int connfd, int status, char *error_message) {
    char header[1024];
    memset(header, 0, 1024);
    char *status_message;
    switch (status) {
        case 400:
            status_message = "Bad Request";
            break;
    }
    sprintf(header,"HTTP/1.1 %d %s\r\n", status, status_message);
    sprintf(header,"%sServer:zhy's Server\r\n",header);
    sprintf(header,"%sContent-type:text/html\r\n\r\n",header);

    send(connfd, header, strlen(header), 0);
    send(connfd, error_message, strlen(error_message), 0);
}
