/******************************************************************************
 * Copyright (C) 2018 by Shashank Iyer
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Shashank Iyer is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file: LL_with_random_pointer.h 
 * @brief: Contains a function that creates a copy of a LL.
 *
 * Creates a copy of every list node and correctly maps the random pointer too.
 *
 * @author Shashank Iyer
 * @date 07-10-2018
 *
 */


#include <stdlib.h>

/*  
 * Definition for singly-linked list with a random pointer.
 */
typedef struct RandomListNode{
  int label;
  struct RandomListNode *next;
  struct RandomListNode *random;
}srn;
 

typedef struct RandomListNode* prn;

/*
 * Function that creates a list node
 * @param val: integer value to store in the newly created node
 * @return : A pointer to the newly created node
 */
prn insert_RandomListNode(int val)
{
    prn curr = (prn)malloc(sizeof(srn));
    curr->label = val;
    curr->next=NULL;
    curr->random=NULL;
    
    return curr;
}

/*
 * This function creates a copy of the linked list in O(N) time and O(1) space
 * In the first interation it creates a copy of the current node and places it adjacent to it. Eg. 1->1->9->9..
 * It correctly assigns a value to the random pointer of the newly created node.
 * Finally, it separates the original list from the newly created list
 *
 * @param head : A pointer to the head of the linkedlist to copy
 * @return : A pointer to the head of the newly created linkedlist
 */
prn copyRandomList(prn head) {
    
    for(prn iter = head, next = NULL; iter!=NULL; iter = next)
    {
        next = iter->next;
        prn copy = insert_RandomListNode(iter->label);
        iter->next = copy;
        copy->next = next;
    }
    
    for(prn iter = head; iter!=NULL; iter = iter->next->next)
        if(iter->random!=NULL)
            iter->next->random = iter->random->next;
    
    srn dummy;
    for(prn iter = &dummy, next = NULL, h = head; iter!=NULL && h!=NULL; iter = iter->next, h = next)
    {
        next = h->next->next;
        iter->next = h->next;
        
        h->next = next;
    }
    
    return dummy.next;
    
}