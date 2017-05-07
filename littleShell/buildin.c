//
// Created by zhy on 5/7/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "buildin.h"

/* 把命令用buildin的扫一遍 */
void buildin_judge(char *line)
{
    buildin_exit(line);
}


/* exit 退出shell*/
void buildin_exit(char *line)
{
    if (!strncmp(line, "exit",4)) {
        fprintf(stdout, "bye\n");
        exit(0);
    }
}
