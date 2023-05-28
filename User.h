#ifndef USER_H
#define USER_H
#include <string>
#include "CM.h"
#include "Movie.h"

class User
{
private:
    int userID;
    std::string name;
    CM *checkouts;     // This is the head of checked movies.
public:
    User();
    User(int ID,std::string userName);
    std::string display();
    int getUserID(){return userID;}
    void checkOutMovie(Movie newMovie); // This function will check out movie that comes as an argument.
    CM *getCheckouts(){return checkouts;} // To use our linked list in another file if necessary.
    bool checkForMovie(int movieID); // This function will check all movies checked by the user.If movie that has the same ID as our argument,it will return true.
    void deleteMovie(int movieID);  // This function will delete movie corresponding to the movie ID argument.
    Movie returnMovie(int movieID);  // This function is for returning a movie back to the library system.
    Movie returnSpecificMovie(int movieId);
    std::string displayAllMovies();
    ~User();

};

#endif // USER_H
