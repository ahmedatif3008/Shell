#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LSH_RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"


char *read_line(void) {
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer){
        printf("malloc failed");
        exit(EXIT_FAILURE);
    }

    while (1){
        c = getchar();

        if (c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;
    
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer){
                printf("malloc failed");
                exit(EXIT_FAILURE);
            }

        }
    
    }

}




char** parse_line(char *line){
    int buf_size = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(buf_size * sizeof(char*));
    char *token;

    if (!tokens){
        printf("malloc failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);

    while (token != NULL){

        tokens[position] = token;
        position++;

        if (position >= buf_size){
            buf_size += LSH_RL_BUFSIZE;
            tokens = realloc(tokens, buf_size * sizeof(char*));

            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM); // THIS? 

    }

    tokens[position] = NULL; // THIS?
    return tokens;

}


void test_memory(char *memory, int size) {
    printf("Memory content:\n");
    for (int i = 0; i < size; i++) {
        if (memory[i] == '\0') { // End of the string
            printf("\\0");
            break;
        }
        printf("%c", memory[i]);
    }
    printf("\n");
}


void shell_loop(void){
    char *line = malloc(1024); //line from the user
    char **args; // arguments to the line
    int status = 1; // Status of the loop(0 or 1)

    if (line == NULL){
        fprintf(stderr, "Memory allocation failed\n");
    }


    while (status) {
        printf("$ ");
        line = read_line();  // Read input
        // test_memory(line, strlen(line) + 1);

        args = parse_line(line);

        // If input is empty, clear buffer and continue
        if (strlen(line) == 0) {
            free(line);  // Free memory for the current line
            continue;
        }

        // Check for exit condition
        if (strcmp(line, "exit") == 0) {
            free(line);
            status = 0;  // Exit loop
        } else {
            printf("You entered: %s\n", line);
        }

        free(line);  // Free memory after processing input
    }
        


    free(line);
    free(args);
}


int main(int argc, char **argv){
    shell_loop();
    
    return 0;
}