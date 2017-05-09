//
// Created by zhy on 5/7/17.
//

#include <string.h>
#include <stdio.h>
#include "env.h"

//链表形式存放env变量集合的头指针
env_var *env_var_header;

//为了方便单独设置PATH变量
env_var PATH;
env_path *path;

void env_init() {
    env_var_header = malloc(sizeof(env_var));
    /* parse shellrc file*/
    FILE *file = fopen("./shellrc", "r");
    if (file) {
        while (!feof(file)) {
            char item[1024];
            fgets(item, 1024, file);
            set_env(item);
        }
        parse_env_path();
    }

}

//传进来的应该是 env_var=env_value 形式
void set_env(char *line) {
    char *env_name;
    char *env_value;

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
    env_value = (char *) (line + i + 1);


    if (!strncmp(env_name, "PATH", 4)) {
        PATH.env_value = env_value;
    }

    env_var *env_var1 = (env_var *) getenv(env_name);
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
env_var *get_env_var(char *env_var_name) {
    env_var *p = env_var_header;
    while (!p) {
        if (!strcmp(p->env_name, env_var_name)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//把PATH的值分分号传到path链表里
void parse_env_path() {
    char *p = PATH.env_value;
    env_path **q = &path;
    int i = 0;
    int j = 0;
    while (p[j] != '\0') {
        if (p[j] == ';') {
            p[j] = '\0';
            *q = malloc(sizeof(env_path));
            strcpy((*q)->path, p + i);
            q = &(*q)->next;
            i = j + 1;
        }
        j++;
    }
    *q = malloc(sizeof(env_path));
    strcpy((*q)->path, p + i);
}