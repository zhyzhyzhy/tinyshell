#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "line_parser.h"
#include "buildin.h"
#include "env.h"

extern env_path* path;

void shell_init() {
    env_init();
}


int main()
{

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

        //fork后执行命令
        if (fork() == 0) {
            char read[1024];
            env_path* p = path;


            while (p != NULL) {
                strcpy(read, p->path);
                strcat(read, line);
                FILE* file = fopen(read, "rx");
                if (file) {
                    break;
                } else {
                    p = p->next;
                    memset(read, 0, 1024);
                }
            }
            if (execl(read, line, NULL, NULL) == -1) {
                perror("exec");
            }
        }
        int exitcode;
        wait(&exitcode);
        fprintf(stdout, "[%d]: ", count++);
    }
    return 0;
}