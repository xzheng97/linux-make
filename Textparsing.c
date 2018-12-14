////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        Textparsing.c
// Other Files:      progexe.c progexe.h Textparsing.h linkedlist.c
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
#include <stdlib.h>
#include <ctype.h>
#include "Textparsing.h"

#define buffersize 1024
/*
 * Function that detect any error for the inputfile and parse into the array of char
 *
 * @param
 * inputmakename: the filename defined by user
 */
struct parseresult* Textparsing(char * inputmakename) {
    struct parseresult* retresult = (struct parseresult*)calloc(1, sizeof(struct parseresult));
    FILE *makefile;
    int c;
    int modeflag = 0;
    int tgtflag = 0;
    int index = 0;
    int makeindex = 0;
    int numline= 1;
    int numcolon = 0;
    int nullflag = 0;
    int linecount = 0;
    
    // Open the inputfile
    if(inputmakename == NULL){
        if(!(makefile = fopen("./makefile","r"))) {
            makefile = fopen("./Makefile","r");
            if (makefile == NULL) {
                fprintf(stderr, "Error opening file: No Makefile or makefile found\n");
                free(retresult->result);
                free(retresult);
                fclose(makefile);
                return NULL;
            }
        }
    }
    // Open the inputfile  defined by user
    else{
        if(!(makefile = fopen(inputmakename,"r"))) {
            makefile = fopen(inputmakename,"r");
            if (makefile == NULL) {
                fprintf(stderr, "Error opening file: No Makefile or makefile found\n");
                free(retresult->result);
                free(retresult);
                fclose(makefile);
                return NULL;
            }
        }
    }
    
    char *str = (char *)calloc(buffersize+1, sizeof(char));
    
    while((c = fgetc(makefile)) != EOF){
        if (c == '\n') {
            linecount ++;
        }
    }
    rewind(makefile);
    
    char **makelines = (char **) calloc(buffersize, sizeof(char*));
    // Go through each character to parse into an array
    while((c = fgetc(makefile)) != EOF){
        // When the size is larger than buffersize
        if(index >= buffersize) {
            if(c != '\n') {
                continue;
            }
            str[index] = '\0';
            fprintf(stderr, "%d: Command line is too long: %s\n", numline, str);
            numline++;
            for (int z = 0 ; z < makeindex; z++){
                free(makelines[z]);
            }
            free(makelines);
            free(str);
            free(retresult->result);
            free(retresult);
            fclose(makefile);
            return NULL;
        }
        else {
            if (c == '\0') {
                nullflag = 1;
            }
            if(c == '\n') {
                if(index == 0){  // Emity line with \n
                    numline++;
                    continue;
                }
                str[index] = '\n';
                if ( modeflag == 0 || (modeflag == 1 && tgtflag != 2) || (modeflag == 1 && numcolon != 1) || nullflag == 1){  //Detect invalid lines
                    fprintf(stderr, "%d: Invalid line: %s", numline, str);
                    for (int z = 0 ; z < makeindex; z++){
                        free(makelines[z]);
                    }
                    free(makelines);
                    free(str);
                    free(retresult->result);
                    free(retresult);
                    fclose(makefile);
                    return NULL;
                }
                makelines[makeindex] = str;
                modeflag = 0;
                tgtflag = 0;
                nullflag = 0;
                makeindex++;
                numline++;
                index = 0;
                numcolon = 0;
                str = (char *)calloc(buffersize, sizeof(char));
            }
            else{
                if (index == 0) {
                    if ( isalpha(c) != 0) { //target
                        modeflag = 1; //target mode
                    }
                    else if ( c == '\t') { //cmd
                        modeflag = 2; //cmd mode
                    }
                    else if (c == '#') {
                        modeflag = 3;
                    }
                }
                
                else if (index != 0) {
                    if( modeflag == 1){ //target
                        if(tgtflag == 0) {
                            if (c == ' '){
                                tgtflag = 1;
                            }
                            if (c == ':') {
                                tgtflag = 2;
                            }
                        }
                        else if(tgtflag == 1) {
                            if (c == ':') {
                                tgtflag = 2;
                            }
                            else if (c != ' ') {
                                tgtflag = -1;
                            }
                        }
                    }
                }
                
                if(c == ':') {
                    numcolon++;
                }
                if(index != 0 && c == '\t'){
                    str[index] = ' ';
                }
                else{
                    str[index] = c;
                }
                index++;
            }
        }
    }
    if(index < buffersize && index > 0) {  // Add the last line into the makelines
        str[index] = '\n';
        if ( modeflag == 0 || (modeflag == 1 && tgtflag != 2) || (modeflag == 1 && numcolon != 1) || nullflag == 1){
            fprintf(stderr, "%d: Invalid line: %s", numline, str);
            for (int z = 0 ; z < makeindex; z++){
                free(makelines[z]);
            }
            free(makelines);
            free(str);
            free(retresult->result);
            free(retresult);
            fclose(makefile);
            return NULL;
        }
        makelines[makeindex] = str;
        makeindex++;
    }
    fclose(makefile);
    if(index == 0) {
        free(str);
    }
    retresult->result = makelines;
    retresult->lines = makeindex;
    return retresult;
}
