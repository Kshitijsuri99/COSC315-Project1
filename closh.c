// closh.c - COSC 315, Winter 2020

// Florencia Chomski
// Ahmad Raza Jamal
// Kshtij Suri

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code

        if(parallel == TRUE){
            for( int i = 0; i < count; ++i ) {
                pid_t pid;
                pid = fork ();
                switch(pid) { 
                    case 0: /* child */
                        sleep(timeout); //process will end and exit in the given timeout seconds if it is taking too long
                        execvp(cmdTokens[0], cmdTokens); // loading the program
                        printf("Didn't find program %s\n", cmd);// This line of code only runs when the command cannot be found
                        exit(0);// Temination of code
                    case -1:
                        perror( "fork" );
                        exit( 1 );
                    default:  /* parent */
                        exit(1);
                        /* do stuff, but don't wait() or terminate */
                } 
            }
        }

        else if(parallel == FALSE){
            int cid;
            for(int i=1; i<count; i++){
                cid = fork();
                if(cid == 0){
                    sleep(timeout); //process will end and exit in the given timeout seconds if it is taking too long
                    execvp(cmdTokens[0], cmdTokens); // loading the program
                    printf("Didn't find program %s\n", cmd);// This line of code only runs when the command cannot be found
                    exit(1);// Temination of code
                }
                else{
                    waitpid(cid, 0, 0);
                }
            }
        }

        // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
        execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
        // doesn't return unless the calling failed
        printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);        
    }
}

