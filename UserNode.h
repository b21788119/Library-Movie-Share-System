#ifndef USERNODE_H
#define USERNODE_H
#include "User.h"
/*This struct is for our circular doubly linked list that will store users in our Library System.*/

struct UserNode{
    User user;     // In order to create a circular doubly linked list,we need two pointers.
    UserNode *previous;   // For the previous struct of same type.
    UserNode *next;   // For the next struct of same type.
};

#endif // USERNODE_H