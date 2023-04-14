#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void usage(char* argv0);

extern double multiply(double a, double b); // Declare the assembly routine

int main(int argc, char** argv)
{
    if (argc != 2)
        usage(argv[0]);
    
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    pid_t chdpid = fork();
    if (chdpid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    if (chdpid == 0) {

        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        close(pipefd[1]);

        const char* args[3] = {"/usr/bin/python", argv[1], (char*)NULL};

        if (execv(args[0], (char**)args) < 0) {
            char buffer[13] = "execv error\n";
            write(STDOUT_FILENO, buffer, sizeof(buffer));
            perror("execv error");
            exit(EXIT_FAILURE);
        }
    }
    else {

        close(pipefd[1]);

        char buffer[1024];
        memset(buffer, 0x00, sizeof(buffer));
        int i = 0;
        while (read(pipefd[0], buffer + i, 1) > 0) {
            i++;
        }
        
        close(pipefd[0]);

        printf("%s", buffer);

        double crypto_usd = strtod(buffer, NULL);
        double usd = 215.09;

        double result = multiply(crypto_usd, usd); // Call the assembly routine

        printf("%f\n", result);

    }
}


void usage(char* argv0)
{
    fprintf(stderr, "Usage: %s <string>\n", argv0);
    exit(EXIT_FAILURE);
}