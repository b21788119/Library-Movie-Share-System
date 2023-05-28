#ifndef MOVIE_H
#define MOVIE_H
#include <string>

class Movie
{
private:
    std::string title;
    int movieId;
    int year;
    bool status;       // Checked(true) or unchecked(false)
    int activeUser;   // If movie is checked,this variable takes the user Id that checks movie.
public:
    Movie(); // Our default constructor if necessary.
    Movie(int Id,std::string movieTitle,int movieYear);
    Movie(const Movie &source);   // Copy constructor for functions that will use Movie objects.
    void changeStatus(); 
    bool getStatus(){return status;}
    int getID(){return movieId;}
    int getYear(){return year;}
    void setActiveUser(int userID);
    std::string getTitle(){return title;}
    std::string display();  // To write movie information in our output file.
    ~Movie();

};

#endif // MOVIE_H
