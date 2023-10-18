#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>  // Include the necessary header
#include <sys/wait.h>

void display_prompt() {
    printf("simple_shell> ");
}

int execute_command(char *command_with_args) {
    char *command = strtok(command_with_args, " ");
    char *args[1024];  // Assuming a maximum of 1024 arguments

    int i = 0;
    while (command != NULL) {
        args[i] = command;
        i++;
        command = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (strcmp(args[0], "exit") == 0) {
        exit(0);  // Exit the shell
    }

    // Use the PATH environment variable to find the executable
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("Error getting PATH");
        return 1;
    }

    char path_copy[1024];  // Assuming a maximum PATH length of 1024
    strncpy(path_copy, path, sizeof(path_copy));

    char *path_token = strtok(path_copy, ":");
    while (path_token != NULL) {
        char command_path[1024];
        snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

        if (access(command_path, X_OK) == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                execv(command_path, args);
                perror("Error executing command");
                exit(1);
            } else if (pid < 0) {
                perror("Error forking process");
                return 1;
            } else {
                int status;
                waitpid(pid, &status, 0);
                return 0;
            }
        }

        path_token = strtok(NULL, ":");
    }

    printf("Command not found: %s\n", args[0]);
    return 1;
}
