//
// Created by zhy on 5/7/17.
//
#include <stdio.h>
#include "util.h"

char* trim(char *string) {
    //delete ' ' in head
    int begin = 0;
    if (string[0] == ' ') {
        while (string[begin] != '\0' && string[begin] == ' ') {
            begin++;
        }
    }
    //delete ' ' in the tail
    int i = begin;
    int j = begin;
    int flag = 0;
    while (string[i] != '\0') {
        while (string[i] != '\0' && string[i] == ' ') {
            flag = 1;
            i++;
        }
        if (flag == 1) {
            if (string[i] == '\0') {
                while (j < i) {
                    if (string[j] == ' ') {
                        string[j] = '\0';
                    }
                    j++;
                }
                break;
            } else {
                j = i;
            }
            flag = 0;
        }
        i++;
    }
//    printf("%s\n", string + begin);
    return string + begin;
}

