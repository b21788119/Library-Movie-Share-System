#include "Movie.h"
#include <string>

Movie::Movie()
{
    movieId = -1;
    title = "?";
    year = 0;
    status = false;
    activeUser = -1;
}
Movie::Movie(int Id,std::string movieTitle,int movieYear){
    movieId = Id;
    title = movieTitle;
    year = movieYear;
    status = false;        // Movies will be unchecked by  default.
    activeUser = -1;     // No active user at the beginning.
}
Movie::Movie(const Movie &source){
    movieId = source.movieId;
    title = source.title;
    year = source.year;
    status = source.status;
    activeUser = source.activeUser;
}
void Movie::changeStatus(){
    if(status){
        status = false;
    }
    else{
        status = true;
    }
}
std::string Movie::display(){
    std::string movieInfo = "";
    if(status){
        movieInfo = std::to_string(movieId) + " " + title + " " + std::to_string(year) +" "+"Checked out by User "+ std::to_string(activeUser)+".\n";
    }
    else {
        movieInfo = std::to_string(movieId) + " " + title + " " + std::to_string(year) +" "+"Not checked out.\n";
    }
    return movieInfo;
}
void Movie::setActiveUser(int userID){ // If movie will become checked,we will set userID according to the user that selects this movie.
    activeUser = userID;
}
Movie::~Movie()
{
    //Nothing
}

