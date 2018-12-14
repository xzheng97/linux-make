////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        progexe.h
// Other Files:      progexe.c Textparsing.c Textparsing.h linkedlist.c
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

#ifndef progexe_h
#define progexe_h

#include <stdio.h>
#include "buildrepr.h"
#include "linkedlist.h"

void progexe(struct LinklistNode* head);
void executehelper (struct node* head);
void execute(struct node* head);
#endif /* progexe_h */
