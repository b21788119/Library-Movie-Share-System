#ifndef CM_H
#define CM_H
#include "Movie.h"

/*This struct is for Checked Movies that will be stored by users in our Library System.*/
struct CM
{
    Movie checkedMovie;   // This struct holds a movie object and a pointer that points to the next struct of same type.
    CM *next;
};

#endif // CM_H