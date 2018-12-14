////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        Textparsing.h
// Other Files:      progexe.c progexe.h Textparsing.c linkedlist.c
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
#ifndef Textparsing_h
#define Textparsing_h

#include <stdio.h>

struct parseresult{
    char** result;
    int lines;
};

struct parseresult* Textparsing(char* inputmakename);

#endif /* buildgraph_h */
