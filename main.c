////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        main.c
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h
//                   linkedlist.c linkedlist.h buildgraph.c buildgraph.h
//                   buildrepr.c buildrepr.h
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
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Textparsing.h"
#include "buildrepr.h"
#include "linkedlist.h"
#include "buildgraph.h"
#include "progexe.h"

#define buffersize 1024

int main(int argc, const char * argv[]) {
    
    
    // Situation when there's no argument for the program
    if(argc == 1 ){
        struct parseresult* makeinput;
        
        if((makeinput = Textparsing(NULL))== NULL) {
            return -1;
        }
        // Empty file
        if(makeinput->lines == 0){
            fprintf(stderr, "empty file detected\n");
            return -1;
        }
        struct LinklistNode* head  = buildrepr(makeinput);
        struct LinklistNode* graph = buildgraph(head, NULL);
        progexe(graph);
        for (int i = 0; i< (int)(makeinput->lines); i ++) {
            free(makeinput->result[i]);
        }
        free(makeinput->result);
        free(makeinput);
        
    }
    
    // Situation when there's 1 argument that user want to execute
    else if (argc == 2){
        if(strcmp(argv[1], "-f")==0){
            fprintf(stderr, "needs more argument for make\n");
            exit(-1);
        }
        struct parseresult* makeinput;
        
        if((makeinput = Textparsing(NULL))== NULL) {
            return -1;
        }
        // Empty file
        if(makeinput->lines == 0){
            fprintf(stderr, "empty file detected\n");
            return -1;
        }
        struct LinklistNode* head  = buildrepr(makeinput);
        struct LinklistNode* graph = buildgraph(head, (char *)argv[1]);
        progexe(graph);
        for (int i = 0; i< (int)(makeinput->lines); i ++) {
            free(makeinput->result[i]);
        }
        free(makeinput->result);
        free(makeinput);
    }
    
    // Situation when there's 2 argument that user want to execute
    else if (argc == 3){
        struct parseresult* makeinput;
        
        if((makeinput = Textparsing((char *)argv[2]))== NULL) {
            return -1;
        }
        // Empty file
        if(makeinput->lines == 0){
            fprintf(stderr, "empty file detected\n");
            return -1;
        }
        struct LinklistNode* head  = buildrepr(makeinput);
        struct LinklistNode* graph = buildgraph(head, NULL);
        progexe(graph);
        for (int i = 0; i< (int)(makeinput->lines); i ++) {
            free(makeinput->result[i]);
        }
        free(makeinput->result);
        free(makeinput);
    }
    
    // Situation when there's 4 arguments that user specifially want to execute
    else if (argc == 4){
        struct parseresult* makeinput;
        
        if((makeinput = Textparsing((char *)argv[2]))== NULL) {
            return -1;
        }
        // Empty file
        if(makeinput->lines == 0){
            fprintf(stderr, "empty file detected\n");
            return -1;
        }
        struct LinklistNode* head  = buildrepr(makeinput);
        struct LinklistNode* graph = buildgraph(head, (char *)argv[3]);
        progexe(graph);
        for (int i = 0; i< (int)(makeinput->lines); i ++) {
            free(makeinput->result[i]);
        }
        free(makeinput->result);
        free(makeinput);
    }
    
    
    exit(0);
}
