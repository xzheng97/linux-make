////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        linkedlist.h
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h 
//                   linkedlist.c buildgraph.c buildgraph.h buildrepr.c
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

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>

struct LinklistNode {
    void* data;
    struct LinklistNode* next;
};

/*
 * Function that adds a new node at the end of a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * newdata: new data that will be saved into the linked list
 */
void append(struct LinklistNode** headref, void* newdata);
void removelastnode (struct LinklistNode** headref);
int getsize(struct LinklistNode** headref);

void* getnodedata(struct LinklistNode** headref,int index);

struct LinklistNode* getnode(struct LinklistNode** headref,int index);


#endif /* linkedlist_h */
