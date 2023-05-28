#ifndef UM_H
#define UM_H
#include "Movie.h"
/* This structure is for our circular singly linked list that will store unchecked movies in Library System.*/
struct UM
{   // This struct only holds a movie object and a pointer that points to the next struct.The next struct will also hold a movie and a pointer.
    Movie uncheckedMovie;
    UM *next;
};

#endif // UM_H