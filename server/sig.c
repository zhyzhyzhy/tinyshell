//
// Created by zhy on 2/21/17.
//

#include "sig.h"
#include <stdio.h>
#include <stdlib.h>
void sig_int(int sig) {
    printf("\nbye\n");
    exit(0);
}
