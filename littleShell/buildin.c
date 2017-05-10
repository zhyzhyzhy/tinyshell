//
// Created by zhy on 5/7/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include "buildin.h"
#include "util.h"

/* 把命令用buildin的扫一遍 */
int buildin_judge(char *line)
{
    if (buildin_exit(line)
            || buildin_cd(line)) {
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

/* cd
 *
 * support for cd to home
 *
 * */
int buildin_cd(char *line)
{
    if (!strncmp(line, "cd", 2)) {
        line = trim(line+2);

        /*to handle pure cd */
        if (line[0] == '\0') {
            struct passwd *pw = getpwuid(getuid());
            line = pw->pw_dir;
        }
        if (chdir(line) == -1) {
            perror("cd");
        }
        return 1;
    }
    return  0;
}

