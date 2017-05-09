//
// Created by zhy on 5/9/17.
//

#include <stdlib.h>
#include "process.h"

void destroy_job(job* job1) {
    process* head = job1->first_process;
    process* p = head->next;
    while (p != NULL) {
        free(head->argv);
        free(head);
        head = p;
        p = p->next;
    }
    free(head->argv);
    free(head);
    free(job1);
}


