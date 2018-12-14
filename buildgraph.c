////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        buildgraph.c
// Other Files:      progexe.c progexe.h Textparsing.c Textparsing.h
//                   linkedlist.c linkedlist.h buildgraph.h buildrepr.c
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
#include "buildgraph.h"
#include "buildrepr.h"
#include "Textparsing.h"
#include "linkedlist.h"

/*
 * Function that connect node to a graph
 *
 * @param
 * head: the nodelist for the program
 * inputarray: the argument that user want to run
 */
struct LinklistNode* buildgraph(struct LinklistNode* head, char * inputarray){
    struct node* newnode = NULL;
    int findflag = 0;
    struct node* targetnode = NULL;
    for (int i = 0; i < getsize(&head); i++){
        targetnode = (struct node*)getnodedata(&head, i);
        for (int j = 0; j < getsize(&targetnode->dependlist); j++){
            for (int k = 0 ; k < getsize(&head); k++){
                // When the children find in targetnode
                if(strcmp((char *)getnodedata(&targetnode->dependlist, j), (char *)(((struct node*)getnodedata(&head, k))->target)) == 0){
                    findflag = 1;
                    append(&(((struct node*)getnodedata(&head,k))->parent), getnodedata(&head, i));
                    append(&targetnode->children, getnodedata(&head, k));
                }
            }
            // When the children does not list in targetnode
            if(findflag == 0){
                newnode = (struct node*) calloc(1, sizeof(struct node));
                newnode->target = (char *)getnodedata(&targetnode->dependlist, j);
                //append this newnode's parent
                append(&newnode->parent, (void*)getnodedata(&head, i));
                append(&targetnode->children,(void*)newnode);
                append(&head, newnode);
            }
            findflag = 0;
        }
    }
    
    struct LinklistNode* exeorder = (struct LinklistNode*)calloc(1, sizeof(struct LinklistNode ));
    // Check if there's any cycle in the graph
    if(inputarray == NULL){
        if(detectcycle((struct node*)(getnodedata(&head,0)), exeorder, NULL)) {
            fprintf(stderr,"ERROR: cycle detected!\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        for (int i = 0; i < getsize(&head); i++){
            if(strcmp((char*)(((struct node*)getnodedata(&head,i))->target) , inputarray)==0){
                if(detectcycle((struct node*)(getnodedata(&head,i)), exeorder, NULL)) {
                    fprintf(stderr,"ERROR: cycle detected!\n");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
        
    }
    // return the exectuion oreder of the node
    return exeorder;
}


/*
 * Function that check if there's any cycle in the program
 *
 * @param
 * head: the nodelist for the program
 * order: the order of execution
 * path: temparary path of execution
 */
int detectcycle(struct node* head, struct LinklistNode* order, struct LinklistNode* path) {
    // Check if children exist
    if(head->children == NULL) {
        append(&order, (void*)head);
        return 0;
    }
    // Check if the path contains the node
    if(contains(&path, head)){
        for(int d = getsize(&path)-1; d >=0; d--){
            free(getnode(&path, d));
        }
        return 1;
    }
    // Add to the path
    append(&path,(void*)head);
    // Recutsion to check cycle
    for (int i = 0; i < getsize(&(head->children)); i++) {
        if(((struct node*)getnodedata(&head->children,i))->visited == 1) {
            continue;
        }
        
        else {
            if(!detectcycle((struct node*)getnodedata(&head->children,i), order, path)) {
                ((struct node*)getnodedata(&head->children,i))->visited = 1;
            }
            else {
                return 1;
            }
        }
    }
    append(&order, (void*)head);
    
    removelastnode(&path);
    return 0;
}

/*
 * Function that check if the node is reappear in the path
 *
 * @param
 * headref: the node linkedlist
 * linkednode: the node we want to check
 */
int contains(struct LinklistNode** headref, struct node* linkednode)
{
    for(int i = 0; i < getsize(headref); i++){
        if(strcmp((char*)((struct node*)getnodedata(headref, i))->target,(char*)(linkednode->target)) == 0 ) {
            return 1;
        }
    }
    return 0;
}


/*
 * Function that set revisted into 0
 *
 * @param
 * head: the nodelist for the program
 */
void resetvisited(struct LinklistNode* head) {
    struct node* root;
    for (int i = 0; i < getsize(&head); i++){
        root = (struct node*)getnodedata(&head, i);
        root->visited = 0;
    }
}
