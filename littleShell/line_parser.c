//
// Created by zhy on 5/7/17.
//

#include <stdlib.h>
#include "line_parser.h"
#include "util.h"

/* 初始化line */
void init_line(char *line)
{
    delete_newline_symbol(line);
}

/* 去掉每line最后的'\n'， 不然exec不出来 */
void delete_newline_symbol(char *line)
{
    int i = 0;
    while (line[i] != '\0' && line[i] != '\n') {
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

/*
 * parse a single process to a struct process
 * like ls -al
 */

process* parse_to_a_process(char* line) {
    delete_newline_symbol(line);

    line = trim(line);

    int i = 0;
    int j = 0;

    int break_point[12];
    int count = 0;

    process* process1 = malloc(sizeof(process));

    while (line[i] != '\0') {
        if (line[i] == '\'') {
            while (line[i] != '\0' && line[i] != '\'') {
                i++;
            }
        }
        if (line[i] == ' ') {
            line[i] = '\0';
            break_point[count++] = j;
            j = i + 1;
        }
        i++;
    }
    break_point[count++] = j;
    process1->argv = (char**)malloc(sizeof(char*) * (count + 1));
    process1->argc = count + 1;
    for (int k = 0; k < count; ++k) {
        process1->argv[k] = (line + break_point[k]);
    }
    process1->argv[count] = NULL;
    return process1;
}


/*
 * parse line to a process linkedlist with the symbol '\'
 * for example
 * parse `ls -al | wc -l` to ls -al and wc -l
 *
 */
process* parse_to_processes(char* line) {

    //delete the '\n' in the end if has
    delete_newline_symbol(line);

    process *head = malloc(sizeof(process));
    head->argv = malloc(1);


    process *p = head;
    int i = 0;
    int j = 0;
    while (line[i] != '\0') {

        //to find charac '|' which is sourrended with ' '
        if (line[i] == '|'
                && i - 1 != 0
                && line[i - 1] == ' '
                && line[i+1] != '\0'
                && line[i+1] == ' ') {

            line[i] = '\0';
            p->next = parse_to_a_process(line + j);
            p = p->next;
            j = i + 1;
        }
        i++;
    }
    p->next = parse_to_a_process(line + j);
    p->next->next = NULL;
    return head;
}



