#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "io.h"

char DISPLAY_NODES_FLAG[] = "-v";
char ERROR_MESSAGE[] = "ERROR\n";

int main(int argc, char **argv) {
    bool display_nodes = false; // obsługa flagi -v

    for (int i = 1; i < argc; i++) {
        if (strEqual(argv[i], DISPLAY_NODES_FLAG)) {
            display_nodes = true;
        } else {
            printf("%s", ERROR_MESSAGE);
            exit(EXIT_FAILURE);
        }
    }

    runIO(display_nodes);
    return 0;
}