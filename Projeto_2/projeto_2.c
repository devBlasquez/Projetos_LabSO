#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

void exec();

int main()
{

    char comando[MAX];
    char *tokens[MAX / 2];
    char *input = NULL;
    char *output = NULL;
    int pid;

    while (1)
    {
        printf("> ");

        int i = 0, flag = 0;

        if (fgets(comando, sizeof(comando), stdin) != NULL)
        {

            comando[strcspn(comando, "\n")] = 0;

            tokens[i] = strtok(comando, " ");

            i++;

            while (tokens[i] = strtok(NULL, " "))
                i++;

            tokens[i] = NULL;
        }

        for (int j = 0; j < i; j++)
        {
            if (i > 0 && strcmp(tokens[j], "&") == 0)
            {
                flag = 1;
                tokens[i - 1] = NULL;
            }
            else if (strcmp(tokens[j], "<") == 0)
            {
                input = tokens[j + 1];
                tokens[j] = NULL;
            }
            else if (strcmp(tokens[j], ">") == 0)
            {
                output = tokens[j + 1];
                tokens[j] = NULL;
            }
        }

        pid = fork();

        if (pid)
        {
            if (!flag)
                waitpid(pid, NULL, 0);

            for (int i = 0; i < MAX; i++)
                comando[i] = 0;

            for (int k = 0; k < i; k++)
                tokens[k] = NULL;
            input = NULL;
            output = NULL;
        }
        else
        {
            if (input != NULL)
                freopen(input, "r", stdin) == NULL;

            if (output != NULL)
                freopen(output, "w", stdout) == NULL;

            execvp(tokens[0], tokens);
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
        }
    }
}

// if (!strcmp(comando, "exit"))
//         {
//             exit(EXIT_SUCCESS);
//         }

//         [ls -l Documentos]
//         token = [ls]

//         [0] "ls"
//         ["ls-lDocumentos"]