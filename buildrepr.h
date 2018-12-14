////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        buildrepr.h
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h
//                   linkedlist.c linkedlist.h buildgraph.c buildgraph.c
//                   buildrepr.c
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

#ifndef buildrepr_h
#define buildrepr_h

#include <stdio.h>
#include "linkedlist.h"
#include "Textparsing.h"

struct node{
    char *target;
    int visited;
    struct LinklistNode *parent;
    struct LinklistNode *children;
    struct LinklistNode *cmdlist;
    struct LinklistNode *dependlist;
};

struct LinklistNode* buildrepr(struct parseresult * result);
#endif /* buildrepr_h */
