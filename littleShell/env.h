//
// Created by zhy on 5/7/17.
//

#ifndef LITTLESHELL_ENV_H
#define LITTLESHELL_ENV_H

#include <stdlib.h>

typedef struct env_var{
    char* env_name;
    char* env_value;
    struct env_var* next;
}env_var;

void env_init();
void set_env(char* line);
env_var* get_env_var(char* env_var_name)
#endif //LITTLESHELL_ENV_H
