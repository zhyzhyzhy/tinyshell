#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/* 去掉每line最后的'\n'， 不然exec不出来 */
void* parseBack(char *line) {
    int i = 0;
    while (line[i] != '\n') {
        i++;
    }
    line[i] = '\0';
}
/*如 /usr/bin/ls 得到 ls */
void* parse_line(char* line) {
    int i = 0;
    int j = 0;
    do {
        j++;
    }
    while (line[j] != '/');
    do {
        j++;
        if (line[j] == '/') {
            do {
                i++;
            } while(line[i] != '/');
        }
    } while (line[j]);
    do {
        i++;
    } while(line[i] != '/');
    return line + i + 1;
}
int main()
{
    int count = 0;
    fprintf(stdout, "[%d]: ", count++);

    char line[1024];
    while (fgets(line, 1024, stdin) != 0) {
        parseBack(line);
        if (fork() == 0) {
            if (execl(line, parse_line(line), NULL, NULL) == -1) {
                perror("exec: ");
            }
        }
        int exitcode;
        wait(&exitcode);
        fprintf(stdout, "[%d]: ", count++);
    }
    return 0;
}