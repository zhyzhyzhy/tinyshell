//
// Created by zhy on 5/7/17.
//

#include "line_parser.h"

/* 初始化line */
void init_line(char *line)
{
    delete_newline_symbol(line);
}

/* 去掉每line最后的'\n'， 不然exec不出来 */
void delete_newline_symbol(char *line)
{
    int i = 0;
    while (line[i] != '\n') {
        i++;
    }
    line[i] = '\0';
}

/*如 /usr/bin/ls 得到 ls */
void* get_argument(char* line) {
    int i = 0;
    int j = 0;
    do {
        j++;
    }
    while (line[j] != '/');
    do {
        j++;
        if (line[j] == '/') {
            do {
                i++;
            } while(line[i] != '/');
        }
    } while (line[j]);
    do {
        i++;
    } while(line[i] != '/');

    return line + i + 1;
}
