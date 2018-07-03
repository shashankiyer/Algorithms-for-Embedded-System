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
 * @file: DFS.c 
 * @brief: Traverses a Binary tree and returns its Inorder traversal
 *
 * A stack data structure has been created to facilitate this traversal.
 * The algorithm returns an array that contains the inorder traversal data.
 *
 * @author Shashank Iyer
 * @date 06-20-2018
 *
 */


#include <stdio.h>

/** 
 *Definition for a binary tree node.
 *@param val: An integer value that the TreeNode can hold
 *@param left: A pointer to the left subtree
 *@param right: A pointer to the right subtree
 */
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

/**
 *A stacknode struct that stores a single variable of a stack
 *@param next: a pointer to the next variable in the stack
 *@param t: a pointer to the Treenode to store in the stacknode
 */
typedef struct stacknode{
    struct TreeNode* t;
    struct stacknode* next;
}stacknode;

/**
 *An implementation of the stack data structure
 *@param sp: points to the top of the stack
 */
typedef struct stack{
    struct stacknode* sp;
} stack;

/**
 *Initialises a stack data structure
 *@param s: A reference to a stack
 */
void init(stack* s)
{
    s->sp = NULL;
}
/**
 *Adds a node to the top of the stack and shifts the stack pointer up
 *@param s: A reference to a stack
 *@param tt: A pointer to the TreeNode to store
 */
void push(stack** s, struct TreeNode* tt)
{
    stacknode* ss = (stacknode*) malloc(sizeof(stacknode));
    ss->t = tt;
    ss->next = (*s)->sp;
    (*s)->sp = ss;
}
/**
 *Fetches the TreeNode stored at the top of the stack
 *@param s: A reference to a stack
 *@return : The TreeNode stored at the top of the stack
 */
struct TreeNode* top(stack* s)
{
    if(s == NULL)
        return NULL;
    return s->sp->t;
}

/**
 *Removes a stacknode at the top of the stack
 *@param s: A reference to a stack
 */
void pop(stack** s)
{
    if((*s)->sp == NULL)
        return;
    stacknode* ss = (*s)->sp;
    (*s)->sp = (*s)->sp->next;
    free(ss);
}

/**
 *Checks if the stack is empty
 *@param s: A reference to a stack
 *@return : True if the stack is empty
 */
bool empty(stack* s)
{
    if(s->sp == NULL)
        return true;
    return false;
}

/**
 *An algorithm that traverses a binary tree Inorder
 *@param root: A pointer to the root of a binary tree.
 *@param size: The number of nodes in the tree.
 *@return : A pointer to an array that contains all the nodes Inorder.
 */
int* inorderTraversal(struct TreeNode* root, int size) {
    stack* s = (stack*)malloc(sizeof(stack));
    int* arr = (int*)malloc(size*(sizeof(int)));
    int index = 0;
    
    init(s);
    
    if(root == NULL)
        return arr;
    while(!empty(s) || root!=NULL)
    {
        while(root!=NULL)
        {
            push(&s,root);
            root=root->left;
        }
        root = top(s);
        pop(&s);
        arr[index++] = root->val;
        root=root->right;
    }
    return arr;
}