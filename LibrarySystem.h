#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <string>
#include <vector>
#include "UM.h"
#include "CM.h"
#include "UserNode.h"

class LibrarySystem
{
private:
    UM *head1;  
    std::string interface;
    UserNode *head2;
    bool interfaceControl;
public:
    LibrarySystem();
    ~LibrarySystem();
    void addMovie(const int movieId,const std::string movieTitle,const int year);
    bool checkMovieInLibrary(int movieID);
    bool checkMovieInUsers(int movieID);
    void deleteMovie(const int movieId);
    
    void addUser(const int userId,const std::string userName);
    bool checkUser(int userID);
    void deleteUser(const int userId);
    
    void checkoutMovie(const int movieId,const int userId);
    void returnMovie(const int movieId);
    
    void showAllMovies();
    void showMovie(const int movieId);
    void showUser(const int userId);
    void activateSystem(std::vector<std::string> commands,std::string outputFile);
    
};

#endif // LIBRARYSYSTEM_H
