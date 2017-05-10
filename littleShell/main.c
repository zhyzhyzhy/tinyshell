#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "line_parser.h"
#include "buildin.h"
#include "env.h"
#include "process.h"

extern env_path *path;


void shell_init() {
    env_init();
}


int main() {
    //初始化所有
    shell_init();

    int count = 0;
    fprintf(stdout, "[%d] %s ~ : ", count++, get_current_dir_name());

    char line[1024];
    while (fgets(line, 1024, stdin) != 0) {
        //初始化line
        init_line(line);

        //判断是否是内置命令
        if (buildin_judge(line)) {
            fprintf(stdout, "[%d] %s ~ : ", count++, get_current_dir_name());
            continue;
        }

        process *head = parse_to_processes(line);
        job *job1 = malloc(sizeof(job));
        job1->first_process = head;
        launch_job(job1);
        destroy_job(job1);
        fprintf(stdout, "[%d] %s ~ : ", count++, get_current_dir_name());
    }
    return 0;
}

