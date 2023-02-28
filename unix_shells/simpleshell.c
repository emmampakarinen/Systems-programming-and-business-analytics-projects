/* Emma Pakarinen, 4.2.2023
This program is an outline for a larger shell project on the "Käyttöjärjestelmät ja systeemiohjelmointi" -course. */

/* Object: Write a simple shell that can be used to execute commands with parameters, in the foreground and background. 
Add an auto-logout feature, that is, if there is no input received during a specified period of time (e.g. 15 secs), the shell will exit. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

void sig_handler(int sig) {
    printf("\n");
    exit(0);
}

void run_command(int my_argc, char *my_argv[], bool bg) { 
    int status; 
    pid_t pid = fork();

    if (pid == -1) {
        printf("Fork fail.\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // child
        if (bg) { // writing bg process output to file
            int fd = open("background.txt", O_WRONLY | O_CREAT); // writing the background process to a file
            dup2(fd, 1); // duplicating the file descriptor to standard output, https://www.geeksforgeeks.org/dup-dup2-linux-system-call/ 
            close(fd);
        }
        if (execvp(my_argv[0], &my_argv[0]) == -1) {
            printf("Exec fail.\n");
            exit(EXIT_FAILURE);
        }
    } else { // parent
        if (!bg) { // run foreground
            waitpid(pid, &status, 0); // waiting for child to finish
        } else { // run background
            printf("Running command %s (pid: %d) in the background.\n", my_argv[0], pid);
            return; // not waiting for the child to finish
        }
    } 

    return;
}


int main(int argc, char *argv[]) {
    char command[128];
    char command_copy[128];
    bool bg;

    if (argc > 1) {
        printf("usage: ./omash\n");
        exit(1);
    }

    while (1) {
        int i = 0;
        char *tokens[128];
        char *word;
        signal(SIGALRM, sig_handler); // https://www.geeksforgeeks.org/signals-c-language/ 
        alarm(15);  

        printf("omash> ");
        fgets(command, 128, stdin);
        command[strcspn(command, "\n")] = 0; // removing newline
        if (strcmp(command, "exit") == 0) {
            exit(0);
        }

        strcpy(command_copy, command); // copy so that strtok will work
        word = strtok(command_copy, " ");
        
        while (word != NULL) { // parsing the input
            if (strchr(word, '&') != NULL) {
                bg = true;
                word = strtok(NULL, " ");
                continue; // not adding "&"" to the tokens list
            }
            tokens[i] = word;
            i++;
            word = strtok(NULL, " ");
        }

        tokens[i+1] = word; // adding NULL to the end
        run_command(i,tokens,bg);

        bg = false;
    }

    return 0;
}
