#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>  // Add this line to include necessary types

// Function declarations
void display_prompt();
int execute_command(char *command_with_args);  // Updated function signature

#endif  // SHELL_H
