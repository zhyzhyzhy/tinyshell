#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "line_parser.h"
#include "buildin.h"
#include "env.h"

int main()
{
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
            if (execl(line, get_argument(line), NULL, NULL) == -1) {
                perror("exec");
            }
        }
        int exitcode;
        wait(&exitcode);
        fprintf(stdout, "[%d]: ", count++);
    }
    return 0;
}