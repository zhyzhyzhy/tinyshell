//
// Created by zhy on 2/12/17.
//
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

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
void do_get(int connfd, char* file_name) {
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
    sprintf(header,"%sServer:zhy's Server\r\n",header);
    sprintf(header,"%sContent-type:text/html\r\n\r\n",header);
    send(connfd, header, strlen(header), 0);

    int length;
    while ((length = read(fd, buffer, 8192)) > 0) {
        send(connfd, buffer, length, 0);
    }
}
void response(int connfd) {
    char method[24];
    char path[1024];
    char version[24];

    memset(method, 0, 24);
    memset(path, 0, 1024);
    memset(version, 0, 24);

    char request[8192];
    read(connfd, request, 8192);

    sscanf(request, "%s %s %s", method, path, version);
    printf("get connect: \n");
    printf("method : %s\npath : %s\nversion : %s\n\n", method, path, version);

    if (strncmp(method, "GET", 3) == 0) {
        do_get(connfd, path+1);
    }
    close(connfd);
}
