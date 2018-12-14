////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        buildgraph.h
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h
//                   linkedlist.c linkedlist.h buildgraph.c buildrepr.c
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

#ifndef buildgraph_h
#define buildgraph_h

#include <stdio.h>
#include "buildrepr.h"
#include "linkedlist.h"

struct LinklistNode* buildgraph(struct LinklistNode* head, char * inputarray);

int detectcycle(struct node* head, struct LinklistNode* order, struct LinklistNode* path);

void resetvisited(struct LinklistNode* head);

int contains(struct LinklistNode** headref, struct node* linkednode);
#endif /* buildgraph_h */
