// closh.c - COSC 315, Winter 2020

// Florencia Chomski
// Ahmad Raza Jamal
// Kshtij Suri

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

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

struct ThreadData { //
    char** cmdTokens; // array of strings
    char* cmd; // the cmd token
};

// A fn that takes the thread data (e.g. cmdTokens and cmd) and executes a process
void * parallelThreadsFn (struct ThreadData * thread_data) {	
    int cid;
    cid = fork();
    if(cid == 0){
        execvp(thread_data -> cmdTokens[0], thread_data -> cmdTokens); // loading the program
        printf("Didn't find program %s\n", thread_data -> cmd);// This line of code only runs when the command cannot be found
        exit(1);// Temination of code
    }
    else{
        waitpid(cid, 0, 0);
    }
	
	pthread_exit(NULL); // Once thread is done, exit
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
            pthread_t threads[count]; // Array of threads
            struct ThreadData thread_data; // A struct to store the data to be passed into the threadFn

            // Assigning data to the struct objects 
            thread_data.cmd = cmd;
            thread_data.cmdTokens = cmdTokens;

	        for(int i = 0; i < count; i++) {		
		        pthread_create(&threads[i], NULL, &parallelThreadsFn, &thread_data); //	Create a thread process 
		        pthread_join(threads[i], NULL);	// Make parent thread wait for children to finish first
	        }
        }

        else if(parallel == FALSE){
            int cid;
            for(int i=0; i<count; i++){
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
        exit(1);    
    }    
}

