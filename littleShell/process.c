//
// Created by zhy on 5/9/17.
//

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
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


    /*
     *
     * todo
     * redirect
     *
     *
     * */

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


