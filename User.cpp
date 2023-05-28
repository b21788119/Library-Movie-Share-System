#include "User.h"
#include "Movie.h"
#include "CM.h"
#include <string>

User::User()
{
    userID = -1;
    name = "";
    checkouts = nullptr;  
}
User::User(int ID,std::string userName){
    userID = ID;
    name = userName;
    checkouts = nullptr;      // By default,our head is nullptr.
}
void User::checkOutMovie(Movie newMovie){
    if(checkouts){
        CM *first = checkouts;
        CM *temp1 = first;
        CM *temp2;
        while(true){
            temp2 = temp1;
            temp1 = temp1->next;
            if(temp1 == first){
                CM *newNode = new CM();
                newNode->checkedMovie = newMovie;
                temp2->next = newNode;
                newNode->next = first;
                break;
            }
        }
    }
    else{
        CM *newNode = new CM();
        newNode->checkedMovie = newMovie;
        newNode->next = newNode;
        checkouts = newNode;
    }
    
}
Movie User::returnMovie(int movieID) 
{
    CM *first = checkouts;
    CM *temp1 = first;
    CM *temp2;
    CM *last;
    while(true){
        temp2 = temp1;
        temp1=temp1->next;
        if(temp1 == first){
            last = temp2;
            break;
        }
    }
    Movie returningMovie;
    if(first->checkedMovie.getID() == movieID && first->next==first){
        returningMovie = first->checkedMovie;
        checkouts = nullptr;
    }
    else if(first->checkedMovie.getID() == movieID){
        returningMovie = first->checkedMovie;
        first=first->next;
        checkouts = first;
        last->next = first;
    }
    else if(last != first && last->checkedMovie.getID() == movieID){
        CM *newLast;
        while(true){
            temp2 = temp1;
            temp1 = temp1->next;
            if(temp1 == last){
                newLast = temp2;
                break;
            }
        }
        returningMovie = last->checkedMovie;
        newLast->next = last->next;
    }
    else{
        while(true){
            temp2 = temp1;
            temp1 = temp1->next;
            if(temp1->checkedMovie.getID() == movieID){
                returningMovie = temp1->checkedMovie;
                temp2->next = temp1->next;
                break;
            }
        }
    }
    returningMovie.changeStatus();
    returningMovie.setActiveUser(-1);
    return returningMovie;
 
}
std::string User::display(){
    std::string userInfo =  "User id: "+std::to_string(userID)+" User name: " + name+"\nUser "+std::to_string(userID)+" checked out the following Movies:\n";
    
    if(checkouts){
        userInfo+= "Movie id - Movie name - Year\n";
        CM *first = checkouts;
        CM *temp = first;
        while(true){
            userInfo+= std::to_string(temp->checkedMovie.getID())+" "+temp->checkedMovie.getTitle()+" "+std::to_string(temp->checkedMovie.getYear()) + "\n";
            temp = temp->next;
            if(temp->next == first){
                userInfo+= std::to_string(temp->checkedMovie.getID())+" "+temp->checkedMovie.getTitle()+" "+std::to_string(temp->checkedMovie.getYear()) + "\n";
                break;
            }
        }
    }
    return userInfo;
}

Movie User::returnSpecificMovie(int movieId){
    CM *first = checkouts;
    CM *temp1 = first;
    CM *returningNode;
    while(true){
        if(temp1->checkedMovie.getID() == movieId){
            returningNode = temp1;
            break;
        }
        temp1 = temp1->next;
    }
    return returningNode->checkedMovie;
}

bool User::checkForMovie(int movieID){
    bool control;
    if(checkouts){
        CM * first = checkouts;
        CM *temp = first;
        while(true){
            if(temp->checkedMovie.getID() == movieID){
                control = true;
                break;
            }
            else{
                temp = temp->next;
                if(temp == first){
                    control = false;
                    break;
                }
            }
        }
    }
    else{
        control = false;
    }
    return control;
}

std::string User::displayAllMovies(){
    if(!checkouts){
        return "";
    }
    std::string allMovies = "";
    CM *first = checkouts;
    CM *temp = first;
    while(true){
        allMovies+= temp->checkedMovie.display();
        temp=temp->next;
        if(temp==first){
            break;
        }
    }
    return allMovies;
}

void User::deleteMovie(int movieID){
    CM *first = checkouts;
    CM *temp1 = first;
    CM *temp2 ;
    
    if(first->next == first && first->checkedMovie.getID() == movieID){
        checkouts = nullptr;
    }
    else{
        while(true){
            temp2 = temp1;
            temp1 = temp1->next;
            if(temp1->checkedMovie.getID() == movieID){
                temp2->next = temp1->next;
                break;
            }
            if(temp1 == first){
                break;
            }
        }
    }
}

User::~User()
{
    delete checkouts;
}

