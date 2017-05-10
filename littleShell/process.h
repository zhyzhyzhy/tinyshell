//
// Created by zhy on 5/9/17.
//

#ifndef LITTLESHELL_PROCESS_H
#define LITTLESHELL_PROCESS_H

#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>

/* A process is a single process.  */
typedef struct process
{
    struct process *next;       /* next process in pipeline */
    int argc;
    char **argv;                /* for exec */
    pid_t pid;                  /* process ID */
    int completed;             /* true if process has completed */
    int stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
} process;

/* A job is a pipeline of processes.  */
typedef struct job
{
    struct job *next;           /* next active job */
    char *command;              /* command line, used for messages */
    process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
    int notified;              /* true if user told about stopped job */
    int stdin, stdout, stderr;  /* standard i/o channels */
} job;

void destroy_job(job* job1);
void launch_process (process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground);
void launch_job(job* job1);
#endif //LITTLESHELL_PROCESS_H
