include "shell.h"
#include <stdio.h>

int main() {
    char input[1024];

    while (1) {
        display_prompt();

        if (fgets(input, sizeof(input), stdin) == NUL>
            printf("\n");
            break;
        }

        input[strlen(input) - 1] = '\0';

        if (strlen(input) == 0) {
            continue;
        }

        execute_command(input);
    }

    return 0;
}