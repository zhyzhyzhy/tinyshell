//
// Created by zhy on 5/9/17.
//

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "process.h"
#include "env.h"

extern env_path *path;

void launch_job(job *job1) {
    process *process1 = job1->first_process;
    process1 = process1->next;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int fd[2];
    int flag = 0;
    for (process *p = process1; p; p = p->next) {
        if (p->next) {
            flag = 1;
            if (pipe(fd) == -1) {
                perror("pipe");
            }
            outfile = fd[1];
        } else {
        }
        if (fork() == 0) {
            launch_process(p, 0, infile, outfile, 0, 0);
        } else {
            infile = fd[0];
            if (flag == 1) {
                close(fd[1]);
                flag = 0;
            }
            outfile = STDOUT_FILENO;
            int waitd;
            wait(&waitd);
        }
    }

}
void
launch_process(process *p, pid_t pgid,
               int infile, int outfile, int errfile,
               int foreground) {
    dup2(infile, STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    char read[1024];
    env_path *path1 = path;

    int outfd = -1;
    int infd = -1;

    for (int i = 0; p->argv[i] != NULL ; ++i) {
        if ((p->argv[i])[0] == '>') {
            if (p->argv[i][1] == '>') {
                outfd = open(p->argv[i+1], O_RDWR | O_APPEND);
            }
            else {
                outfd = open(p->argv[i+1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
            }
            if (outfd == -1) {
                perror(p->argv[i+1]);
            }
            p->argv[i] = NULL;
        }
        else if ((p->argv[i])[0] == '<') {
            infd = open(p->argv[i+1], O_RDONLY);
            if (infd == -1) {
                perror(p->argv[i+1]);
            }
            p->argv[i] = NULL;
        }
    }
    if (outfd != -1) {
        dup2(outfd, STDOUT_FILENO);
    }
    if (infd != -1) {
        dup2(infd, STDIN_FILENO);
    }
    while (p != NULL) {
        strcpy(read, path->path);
        strcat(read, p->argv[0]);
        FILE *file = fopen(read, "rx");
        if (file) {
            break;
        } else {
            p = p->next;
            memset(read, 0, 1024);
        }
    }
    if (execv(read, p->argv) == -1) {
        perror("exec");
    }

    if (outfd != -1) {
        close(outfd);
    }
    if (infd != -1) {
        close(infd);
    }
}

void destroy_job(job *job1) {
    process *head = job1->first_process;
    process *p = head->next;
    while (p != NULL) {
        free(head->argv);
        free(head);
        head = p;
        p = p->next;
    }
    free(head->argv);
    free(head);
    free(job1);
}


