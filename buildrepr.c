////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        buildrepr.c
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h
//                   linkedlist.c linkedlist.h buildgraph.c buildgraph.h
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
#include "buildrepr.h"
#include "Textparsing.h"
#include "linkedlist.h"
#define size 200

/*
 * Function that build the linkelistnode for the graph
 *
 * @param
 * result: struct build from the Textparsing
 */
struct LinklistNode* buildrepr(struct parseresult *result){
    int numdepend = 0;
    int numchartarget = 0;
    int numlongchardeptemp = 0;
    int numlongchardep = 0;
    int charflag = 0;
    char *tempdep;
    char *temptar;
    int addcounter = 0;
    int endnum = 0;
    int tarreadcount = 0;
    char *temparg;
    
    char **inputmake = (char**)(result->result);
    int numrows = (int)(result->lines);
    
    struct LinklistNode* head = NULL;
    struct LinklistNode* headcmd = NULL;
    struct node* newnode = NULL;
    
    
    
    // read line by line
    for(int i = 0; i < numrows; i++){
        // case if the file is starts with a commandline
        if(inputmake[0][0] == '\t') {
            fprintf(stderr, "ERROR: Makefile starts with a commandline.\n");
            exit(EXIT_FAILURE);
        }
        // if this line starts with a target
        if(isalpha(inputmake[i][0]) != 0) {
            if(tarreadcount > 0) {
                append(&head, (void *)newnode);
                tarreadcount = 0;
            }
            newnode = (struct node*) calloc(1, sizeof(struct node));
            
            int j = 0;
            charflag = 0;
            numlongchardeptemp = 0;
            numlongchardep = 0;
            // read each line, char by char
            while(inputmake[i][j]!='\n'){
                if(inputmake[i][j]==' '){
                    // count the number of dependencies
                    if (numlongchardeptemp > 0){
                        numdepend++;
                    }
                    // get the longest string length
                    if(numlongchardeptemp > numlongchardep){
                        numlongchardep = numlongchardeptemp;
                    }
                    numlongchardeptemp = 0;
                }
                //count the string length of each dependency
                if(charflag == 1 && inputmake[i][j] != ' '){
                    numlongchardeptemp++;
                }
                // when meet a colon, determine the target string length
                if((charflag == 0 && inputmake[i][j]==':') || (charflag == 0 && inputmake[i][j]==' ')){
                    numchartarget = j;  //Get the number of char for target
                    charflag = 1;
                }
                j++;
            }
            // clear the flag and index after reading each line
            charflag = 0;
            j = 0;
            // case when there is no space after the last dependency
            // update the longest string length
            if(numlongchardeptemp > numlongchardep){
                numlongchardep = numlongchardeptemp;
            }
            if(numlongchardeptemp){
                numdepend++;
            }
            
            addcounter = 0;
            tempdep = (char*)calloc(numlongchardep+1,  sizeof(char));
            temptar = (char*)calloc(numchartarget+1, sizeof(char));
            
            newnode->dependlist = NULL;
            newnode->cmdlist = NULL;
            // traverse again to store the any information needed
            while(inputmake[i][j]!='\n'){
                //when a dependency has been read
                if(inputmake[i][j]==' ' && charflag == 1){
                    if (addcounter > 0){
                        tempdep[addcounter] = '\0';
                        // append the dependency to the list
                        append(&(newnode->dependlist), tempdep);
                        // clear the counter and the temp variable which used to store each dependency
                        addcounter = 0;
                        
                        tempdep = (char*)calloc(numlongchardep+1, sizeof(char));
                    }
                }
                //grab and store each dependency
                if(charflag == 1 && inputmake[i][j] != ' '){
                    tempdep[addcounter] = inputmake[i][j];
                    addcounter++;
                }
                
                // grab and store the target name
                if(charflag == 0){
                    if(inputmake[i][j] != ':' && inputmake[i][j] != ' ') {
                        temptar[j] = inputmake[i][j];
                        endnum++;
                    }
                    else {
                        if(inputmake[i][j] == ' ') {
                            charflag = 2;
                            temptar[endnum] = '\0';
                        }
                        else if(inputmake[i][j] == ':') {
                            charflag = 1;
                            temptar[endnum] = '\0';
                        }
                    }
                }
                else if(charflag ==2) {
                    if(inputmake[i][j] == ':'){
                        charflag =1;
                    }
                }
                j++;
            }
            
            // case when there is no space after the last dependency
            if (addcounter > 0){
                tempdep[addcounter] = '\0';
                append(&newnode->dependlist, (void *)tempdep);
            }
            if(tempdep[0] == 0) {
                free(tempdep);
            }
            endnum = 0;
            newnode->target = temptar;
            tarreadcount++;
        }
        // if this line is starts with a tab
        else if (inputmake[i][0] == '\t'){
            headcmd = NULL;
            int j= 0;
            charflag = 0;
            numlongchardeptemp = 0;
            numlongchardep = 0;
            // read each line, char by char
            while(inputmake[i][j]!='\n'){
                // count number of cmdline
                if(inputmake[i][j]==' '){
                    if (numlongchardeptemp > 0){
                        numdepend++;
                    }
                    // Get longest char number of dependence
                    if(numlongchardeptemp > numlongchardep){
                        numlongchardep = numlongchardeptemp;
                    }
                    numlongchardeptemp = 0;
                }
                //count the string length of each commandline
                if(charflag == 1 && inputmake[i][j] != ' '){
                    numlongchardeptemp++;
                }
                if(charflag == 0 && inputmake[i][0]=='\t'){
                    charflag = 1;
                }
                j++;
            }
            // case if there is no space at the end
            if(numlongchardeptemp > numlongchardep){
                numlongchardep = numlongchardeptemp;
            }
            if(numlongchardeptemp){
                numdepend++;
            }
            // clear variables after reading each line
            j = 0;
            charflag = 0;
            addcounter = 0;
            temparg = (char *)calloc(numlongchardep+1, sizeof(char));
            
            // traverse again to grab any information needed
            while(inputmake[i][j]!='\n'){
                // when a cmdline has been read
                if(inputmake[i][j]==' '){
                    if (addcounter > 0){
                        temparg[addcounter] = '\0';
                        // add read cmdline to list
                        append(&headcmd, (void *)temparg);
                        addcounter = 0;
                        temparg = (char*)calloc(numlongchardep+1, sizeof(char));
                    }
                }
                // grab and store each cmdline
                if(charflag == 1 && inputmake[i][j] != ' '){
                    temparg[addcounter] = inputmake[i][j];
                    addcounter++;
                }
                if(charflag == 0 && inputmake[i][0]=='\t'){
                    charflag = 1;
                }
                j++;
            }
            // case when there is no space at the end
            if (addcounter > 0){
                temparg[addcounter] = '\0';
                append(&headcmd, (void *)temparg);
            }
            if(temparg[0] == 0) {
                free(temparg);
            }
            // append the cmdlist to each target node
            append(&newnode->cmdlist, (void *)headcmd);
            
        }
    }
    
    if(tarreadcount > 0) {
        append(&head, (void *)newnode);
    }
    // check multiple rules for the same target
    for(int j = 0; j <getsize(&head); j++) {
        for(int k = j + 1; k < getsize(&head); k++) {
            if(strcmp((char*)(((struct node*)getnodedata(&head, j))->target),(char*)(((struct node*)getnodedata(&head, k))->target)) == 0) {
                fprintf(stderr, "ERROR: Multiple rules for the same target: %s.\n", (char*)(((struct node*)getnodedata(&head, j))->target));
                exit(EXIT_FAILURE);
            }
        }
    }
    return head;
}
