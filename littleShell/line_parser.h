//
// Created by zhy on 5/7/17.
//

#ifndef LITTLESHELL_LINE_PARSER_H
#define LITTLESHELL_LINE_PARSER_H

#include "process.h"

void init_line(char *line);
void delete_newline_symbol(char *line);
void* get_argument(char* line);
process* parse_to_a_process(char* line);
process* parse_to_processes(char* line);
job* parse_to_job(char* line);
#endif //LITTLESHELL_LINE_PARSER_H
