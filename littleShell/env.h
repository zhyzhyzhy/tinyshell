//
// Created by zhy on 5/7/17.
//

#ifndef LITTLESHELL_ENV_H
#define LITTLESHELL_ENV_H

#include <stdlib.h>

struct env_var{
    char* env_name;
    char* env_value;
    struct env_var* next;
};
typedef struct env_var env_var;

struct env_path {
    char path[64];
    struct env_path* next;
};
typedef struct env_path env_path;

void env_init();
void set_env(char* line);
env_var* get_env_var(char* env_var_name);
void parse_env_path();
#endif //LITTLESHELL_ENV_H
