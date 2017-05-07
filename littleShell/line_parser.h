//
// Created by zhy on 5/7/17.
//

#ifndef LITTLESHELL_LINE_PARSER_H
#define LITTLESHELL_LINE_PARSER_H
void init_line(char *line);
void delete_newline_symbol(char *line);
void* get_argument(char* line);
#endif //LITTLESHELL_LINE_PARSER_H
