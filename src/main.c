#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_loop(void){
    char *line = malloc(1024); //line from the user
    char **args; // arguments to the line
    int status; // Status of the loop(0 or 1)

    if (line == NULL){
        fprintf(stderr, "Memory allocation failed\n");
    }


    int i = 0;

    while (i < 5){
        printf("> ");
        
        if (scanf(" %1023[^\n]", line) == 1){
            printf("%s \n", line);
            args = strtok(line, " ");
            printf(" %s" args);
        }
        else {
            fprintf(stderr, "printing failed \n");
        }
        
        getchar();
        i++;
    }


    free(line);
}


int main(int argc, char **argv){
    shell_loop();


    return 0;
}