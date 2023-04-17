#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void usage(char* argv0);                     // Help msg
extern double multiply(double a, double b);  // Assembly routine

/**
 * @brief routine to get cryptocurrency value in ARS.
*/
int main(int argc, char** argv)
{

    if (argc != 5 || !(!strcmp(argv[3], "USDT") || !strcmp(argv[3], "EUR")))
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

        const char* args[5] = {"/usr/bin/python", argv[1] ,argv[2], argv[3],(char*)NULL};

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

        printf("%s %s: %s", argv[2], argv[3], buffer);

        double crypto_usd = strtod(buffer, NULL);
        double currency_ars = strtod(argv[4], NULL);

        double result = multiply(crypto_usd, currency_ars); // Call the assembly routine

        printf("%s ARS: %f\n", argv[2], result);

    }
}

/**
 * @brief Help msg.
 * @param argv0 Name of the programm.
*/
void usage(char* argv0)
{
    fprintf(stderr, "Usage: %s currencies.py crypto currency currency_to_ARS\n", argv0);
    fprintf(stderr, "    currency.py:     python script for Binance API calling\n");
    fprintf(stderr, "    crypto:          cryptocurrency to convert\n");
    fprintf(stderr, "    currency:        currency of conversion\n");
    fprintf(stderr, "    currency_to_ARS: value of currency in ARS\n");
    exit(EXIT_FAILURE);
}