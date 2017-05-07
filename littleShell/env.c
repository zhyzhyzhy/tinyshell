//
// Created by zhy on 5/7/17.
//

#include <string.h>
#include "env.h"

//链表形式存放env变量集合的头指针
env_var* env_var_header;

//为了方便设置几个特殊的env
env_var PATH;

void env_init()
{
    env_var_header = malloc(sizeof(env_var));
}

//传进来的应该是 env_var=env_value 形式
void set_env(char* line)
{
    char* env_name;
    char* env_value;

    int i = 0;
    //找等号
    while (line[i] != '\0' && line[i] != '=') {
        i++;
    }

    //没找到等于号，设置变量失败，返回
    if (line[i] == '\0') {
        return;
    }

    //把等号设置为'\0'直接
    line[i] = '\0';
    env_name = line;
    env_value = (char *) line[i + 1];

    env_var* env_var1 = (env_var *) getenv(env_name);
    //如果还没有设置env
    if (env_var1 == NULL) {
        env_var1 = malloc(sizeof(env_var));
        env_var1->env_name = env_name;
        env_var1->env_value = env_value;
        env_var1->next = env_var_header;
        env_var_header = env_var1;
    }//否则更新这个env
    else {
        env_var1->env_value = env_value;
    }
}

/* 找对应的env_name的值 */
env_var* get_env_var(char* env_var_name)
{
    env_var* p = env_var_header;
    while (!p) {
        if (!strcmp(p->env_name, env_var_name)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
