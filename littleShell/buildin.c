//
// Created by zhy on 5/7/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "buildin.h"

/* 把命令用buildin的扫一遍 */
int buildin_judge(char *line)
{
    if (buildin_exit(line)) {
        return 1;
    }
    return 0;
}


/* exit 退出shell*/
int buildin_exit(char *line)
{
    if (!strncmp(line, "exit",4)) {
        fprintf(stdout, "bye\n");
        exit(0);
    }
    return 0;
}
