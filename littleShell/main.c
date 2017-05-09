#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "line_parser.h"
#include "buildin.h"
#include "env.h"
#include "process.h"

extern env_path *path;

void shell_init() {
    env_init();
}


int main() {

    //初始化所有
    shell_init();

    int count = 0;
    fprintf(stdout, "[%d]: ", count++);

    char line[1024];
    while (fgets(line, 1024, stdin) != 0) {

        //初始化line
        init_line(line);

        //判断是否是内置命令
        buildin_judge(line);

        process *head = parse_to_processes(line);
        job* job1 = malloc(sizeof(job));
        job1->first_process = head;

//        fork后执行命令
        head = head->next;
        int fd[2];
        if (pipe(fd) == -1) {
            perror("pipe");
        }
        while (head != NULL) {
            if (fork() == 0) {
                if (head->next) {
                    close(STDOUT_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                } else {
                    close(STDIN_FILENO);
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[1]);
                }
                char read[1024];
                env_path *p = path;
                while (p != NULL) {
                    strcpy(read, p->path);
                    strcat(read, head->argv[0]);
                    FILE *file = fopen(read, "rx");
                    if (file) {
                        break;
                    } else {
                        p = p->next;
                        memset(read, 0, 1024);
                    }
                }
                if (execv(read, head->argv) == -1) {
                    perror("exec");
                }
                return 0;
            }
            else {
//              close(fd[0]);
              close(fd[1]);
            }
            int exitcode;
            wait(&exitcode);
            head = head->next;
        }
        close(fd[0]);
        close(fd[1]);
        destroy_job(job1);
        fprintf(stdout, "[%d]: ", count++);
    }
    return 0;
}