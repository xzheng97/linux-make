////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        progexe.c
// Other Files:      progexe.h Textparsing.c Textparsing.h linkedlist.c
//                   linkedlist.h buildgraph.c buildgraph.h buildrepr.c
//                   buildrepr.h
// Semester:         CS 537 Fall 2018
//
// Author:           Youmin Han
// Email:            youmin.han@wisc.edu
// CS Login:         youmin
//
// Author:           Xianjie Zheng
// Email:            xzheng97@wisc.edu
// CS Login:         xianjie
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NULL
//
// Online sources:   NULL
//
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sysexits.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include "buildrepr.h"
#include "linkedlist.h"
#include "progexe.h"


/*
 * Function that execution the command followed by exectuion list
 *
 * @param
 * head: the order of the execution
 */
void progexe(struct LinklistNode* head){
    // Go through the order list and execute
    for(int i = 1; i < getsize(&head); i++) {
        if(((struct node*)getnodedata(&head, i))->cmdlist != NULL) {
            execute((struct node*)getnodedata(&head, i));
        }
    }
}




/*
 * Function that execution the command
 *
 * @param
 * head: target node we want to execute
 */
void executehelper (struct node* head){
    
    // Execution for command
    for(int i = 0; i < getsize(&(head->cmdlist)); i++) {
        struct LinklistNode* command =(struct LinklistNode*)getnodedata(&(head->cmdlist), i);
        char** argument = (char **)malloc(sizeof(char *)* (getsize(&command)+1));
        for(int j = 0; j < getsize(&command); j++) {
            argument[j] =(char*)getnodedata(&command, j);
        }
        argument[getsize(&command)] = NULL;
        pid_t rc = fork();
        pid_t w;
        int wstatus;
        if(rc < 0) { //fork failed; exit
            fprintf(stderr, "ERROR: fork failed\n");
            exit(1);
        }
        else if (rc == 0) { //child, new process
            for(int i = 0; i<getsize(&command);i++){
                printf("%s ", argument[i] );
            }
            printf("\n");
            // Execution with execvp
            if (execvp((char*)getnodedata(&command, 0), argument) == -1) {
                fprintf(stderr, "ERROR: exec failed %d\n", errno);
                exit(1);
            }
        }
        // Catch Error
        else{
            do {
                w = waitpid(rc, &wstatus, WUNTRACED | WCONTINUED);
                if (w == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                if (WIFEXITED(wstatus)) {
                    if(WEXITSTATUS(wstatus)){
                        for(int i = 0; i<getsize(&command);i++){
                            printf("%s ", argument[i] );
                        }
                        printf("  : this command execuution failed %d\n", WTERMSIG(wstatus));
                        exit(EXIT_FAILURE);
                    }
                }
            } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
        }
        free(argument);
    }
}




/*
 * Function that execution the command
 *
 * @param
 * head: target node we want to execute
 */
void execute(struct node* head) {
    struct stat fileStat;
    
    // when the file does not exist
    if(stat((char*)(head->target),&fileStat) != 0){
        executehelper(head);
    }
    // when the file is already exist
    else {
        time_t parentime = fileStat.st_mtime;
        //compare child's access time with parent's modified time
        for(int i = 0; i < getsize(&(head->children)); i++) {
            struct node* tempnode = (struct node*)getnodedata(&(head->children), i);
            if(stat((char*)tempnode->target,&fileStat) < 0){
                continue;
            }
            // Update file by execution
            if(difftime(fileStat.st_mtime, parentime) > 0){
                executehelper(head);
                printf("Now %s is updated.\n", (char*)(head->target));
            }
        }
        
    }
}
