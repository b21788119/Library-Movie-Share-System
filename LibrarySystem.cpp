#include "LibrarySystem.h"
#include "Movie.h"
#include "UM.h"
#include "CM.h"
#include "UserNode.h"
#include "User.h"
#include <sstream>
#include <vector>
#include <fstream>

LibrarySystem::LibrarySystem()
{
    head1 = nullptr;  // This is the head of our circular singly linked list which stores unchecked movies.
    interface = "";
    head2 = nullptr;  // This is the head of our circular doubly linked list which stores users.
    interfaceControl = 1;
}
void LibrarySystem::addMovie(const int movieId,const std::string movieTitle,const int year)
{
    if(head1)  // That means our list is not empty.
    { 
        bool control = checkMovieInLibrary(movieId) || checkMovieInUsers(movieId);
        if(!control){   //If movie does not exist both in Library and any user's list.
            UM *first = head1;
            UM *temp1 = first;
            UM *temp2;
            if(first->next == first){  // Not necessary but just to check if our system has 1 element or not.
                UM *newNode = new UM();
                Movie newMovie(movieId,movieTitle,year);
                newNode->uncheckedMovie = newMovie;
                first->next = newNode;  // I am combining my head node and new node.
                newNode->next = first;  // My newNode has to have a link to the first node because I am creating circular singly linked list.
            }
            else {   // That means our list has more than 1 items.
                while(true){
                    temp2 = temp1;
                    temp1 = temp1->next;
                    if(temp1== first){
                        UM *newNode = new UM();
                        Movie newMovie(movieId,movieTitle,year);
                        newNode->uncheckedMovie = newMovie;
                        temp2->next = newNode;
                        newNode->next = first;
                        break;
                    } 
                }
            }
            if(interfaceControl == 1){   //In some situations,I will use addMovie function again and no need to add this line again. 
                interface+= "Movie "+std::to_string(movieId)+" has been added.\n";
            }
        }
        else{
            if(interfaceControl==1){
                interface +=  "Movie "+std::to_string(movieId)+" already exists.\n";
            }
        }
    }
    else // Empty list
    {  
        if(checkMovieInUsers(movieId)){
            if(interfaceControl == 1){
                interface +=  "Movie "+std::to_string(movieId)+" already exists.\n";
            }
            return;
        }
        UM *newNode = new UM();
        Movie newMovie(movieId,movieTitle,year);
        newNode->uncheckedMovie = newMovie;
        newNode->next = newNode;   //Our new node becomes the first node and the last node.
        head1 = newNode;
        if(interfaceControl==1){
            interface+= "Movie "+std::to_string(movieId)+" has been added.\n";
        }
    }
}

void LibrarySystem::deleteMovie(const int movieId){
    if(head1 && checkMovieInLibrary(movieId)){  // If movie is in System and unchecked,this block will be executed.
        UM *first = head1;
        UM *last;
        UM *temp1 = first;
        UM *temp2;
        while(true){    // This loop will find the last node of our unchecked movies.
            temp2=temp1;
            temp1 = temp1->next;
            if(temp1 == first){   // That means we traversed all elements and come back to the head node.
                last = temp2;
                break;
            }
        }
        if(first->uncheckedMovie.getID() == movieId && first->next != first){   //If we have more than one elements in our list and try to delete our first element.
            first = first->next;   // First element is gone.
            head1 = first;         // Our head points to the new first.
            last->next = first;
        }
        else if(first->uncheckedMovie.getID() == movieId && first->next == first){   // If we have just one element and try to delete it.
            head1 = nullptr;   // From now on,no more element.
        }
        else if(last->uncheckedMovie.getID() == movieId){          // If we try to delete the last element.
            UM *newLast;   // We will decide what is going to be our last element.
            while(true)
            {
                temp2=temp1;
                temp1 = temp1->next;
                if(temp1 == last){
                    newLast = temp2;
                    temp1 = first;
                    break;
                }
            }
            last = newLast;
            newLast->next = first;   
        }
        else
        {  // If we try to delete element from different position 
            while(true){
                temp2=temp1;
                temp1 = temp1->next;
                if(temp1->uncheckedMovie.getID() == movieId){
                    temp2->next = temp1->next;
                    break;
                }
            }
        }
        if(interfaceControl == 1){
            interface+= "Movie "+std::to_string(movieId)+" has not been checked out.\nMovie "+std::to_string(movieId)+" has  been deleted.\n";
        }
    }
    else if(head2 && checkMovieInUsers(movieId)){ // If our movie is checked and not in library.
        UserNode *first = head2;
        UserNode *temp = first;
        while(true){
            if(temp->user.checkForMovie(movieId)){
                temp->user.deleteMovie(movieId);
                break;
            }
            else{
                temp = temp->next;
            }
        }
       if(interfaceControl==1){ 
            interface+= "Movie "+std::to_string(movieId)+" has been checked out.\nMovie "+std::to_string(movieId)+" has  been deleted.\n";  
        }
    }
    else{
        // If our movie does not exist both in library and any user list.
        if(interfaceControl==1){
            interface+= "Movie "+ std::to_string(movieId)+" does not exist.\n";
        }
    }
}
void LibrarySystem::showAllMovies(){
    /*This method shows all movies in the Library System.It control both Library System and active users in it. */
    interface += "Movie id - Movie name - Year - Status\n";
    if(head1){
        // For unchecked movies.
        UM *first = head1;
        UM *temp1 = first;
        while(true){
            interface+= temp1->uncheckedMovie.display();
            temp1 = temp1->next;
            if(temp1 == first){
                break;
            }
        }
    }
    if(head2){
        // For checked movies.
        UserNode *first = head2;
        UserNode *temp = first;
        while(true){
            interface+=temp->user.displayAllMovies();
            temp = temp->next;
            if(temp == first){
                    break;
            }
        }
    }
}
void LibrarySystem::showMovie(const int movieId){
    bool control = checkMovieInLibrary(movieId) || checkMovieInUsers(movieId);
   // First we have to check if our movie exist in system or not.
   if(!control){
        interface+="Movie with the id  "+ std::to_string(movieId)  + " does not exist.\n";
    }
    else{
        if(checkMovieInLibrary(movieId)){
            UM *first = head1;
            UM *temp = first;
            while(true){
                // I am traversing all movies in Library System and find approppriat movie.
                if(temp->uncheckedMovie.getID() == movieId){
                    interface+=temp->uncheckedMovie.display();
                    break;
                }
                temp = temp->next;
            }
        }
        else if(checkMovieInUsers(movieId)){
            UserNode *first = head2;
            UserNode *temp = first;
            Movie movie;
            while(true){
                // I am traversing all users in system and find approppriate user and movie.
                if(temp->user.checkForMovie(movieId)){
                    movie = temp->user.returnSpecificMovie(movieId);
                    interface+= movie.display();
                    break;
                }
                temp = temp->next;
            }
        }
    }
    
}
void LibrarySystem::showUser(const int userId){
    if(checkUser(userId)){
        // If user exists in the system,this method will send its infos to the interfacce.
        UserNode *first = head2;
        UserNode *temp = first;
        while(true){
            if(temp->user.getUserID() == userId){
                interface+= temp->user.display();
                break;
            }
            temp = temp->next;
        }
    }
}
void LibrarySystem::addUser(const int userId,const std::string userName){
    if(head2)  // If there are users in the system.We will insert new users int the beginning.
    {
        bool existance = checkUser(userId); // I am controlling if a user with the same Id exists in Library.
        if(!existance){
            UserNode *first = head2;
            UserNode *last = head2->previous;
            UserNode *newNode = new UserNode();
            User newUser(userId,userName);
            newNode->user = newUser;
            newNode->next = first;
            first->previous = newNode;
            last->next = newNode;
            newNode->previous = last;
            head2 = newNode;
            interface += "User " +std::to_string(userId)+" has been added.\n";
        }
        else{
            interface+= "User " + std::to_string(userId) + " is already exist.\n";
        }
    }
    else  // That means there is no user in the system.
    {
        UserNode *newNode = new UserNode();
        User newUser(userId,userName);
        newNode->user = newUser;
        head2 = newNode;
        newNode->next = newNode;
        newNode->previous = newNode;
        interface += "User " +std::to_string(userId)+" has been added.\n";
    }
}
void LibrarySystem::returnMovie(const int movieId){
    bool control = checkMovieInLibrary(movieId) || checkMovieInUsers(movieId);
    if(!control){
        interface+= "Movie "+std::to_string(movieId)+" does not exist in Library.\n";
        return;
    }
    else{
        if(checkMovieInLibrary(movieId)){
            interface+= "Movie "+std::to_string(movieId)+" has not been checked out.\n";
            return;
        }
        else if(checkMovieInUsers(movieId)){
            UserNode *first = head2;
            UserNode *temp = first;
            Movie returningMovie;
            while(true){
                if(temp->user.checkForMovie(movieId)){
                    returningMovie = temp->user.returnMovie(movieId);
                    interfaceControl = 0;
                    addMovie(returningMovie.getID(),returningMovie.getTitle(),returningMovie.getYear()); 
                    interfaceControl = 1;
                    interface+="Movie "+std::to_string(movieId)+" has been returned.\n";
                    break;
                }
                temp=temp->next;
            }
        }
    }
}
void LibrarySystem::checkoutMovie(const int movieId,const int userId)
{
    if(!checkMovieInLibrary(movieId) || checkMovieInUsers(movieId))
    {
        interface+= "Movie "+std::to_string(movieId)+" does not exist for checkout.\n";
        return;
    }
    
    if(!checkUser(userId)){
        interface+= "User "+std::to_string(userId)+" does not exist for checkout.\n";
        return;
    }
    if(checkMovieInLibrary(movieId))
    {   Movie checkedMovie;
        UM *first = head1;
        UM *temp1 = first;
        UserNode *temp2 = head2;
        while(true)
        {
            if(temp1->uncheckedMovie.getID() == movieId){
                checkedMovie = temp1->uncheckedMovie;
                break;
            }
            else{
                temp1 = temp1->next;
            }
        }
        interfaceControl = 0;
        while(true)
        {
            if(temp2->user.getUserID() == userId){
                deleteMovie(movieId);
                checkedMovie.setActiveUser(userId);
                checkedMovie.changeStatus();
                temp2->user.checkOutMovie(checkedMovie);
                interface+="Movie "+std::to_string(movieId)+" has been checked out by User "+std::to_string(userId)+"\n";
                break;
            }
            else{
                temp2 = temp2->next;
            }
        
        }
        interfaceControl = 1;
    }
    else{
        interface+=  "Movie "+std::to_string(movieId)+" does not exist for checkout.\n";
    }
}
bool LibrarySystem::checkMovieInLibrary(int movieID){ 
    // This method checks all unchecked nodes in Library System and if approppriate movie exists,it returns true.
    if(!head1){
        return false;
    }
    bool control ;
    UM *temp1 = head1;
    while(true){
        if(temp1->uncheckedMovie.getID() == movieID){
            control = true;
            break;
        }
        else{
            temp1 = temp1->next;
            if(temp1 == head1){
                control = false;
                break;
            }
        }
    }
    return control;
}
bool LibrarySystem::checkMovieInUsers(int movieID){
    // This method checks all user nodes in Library System and if approppriate movie exists,it returns true.
    if(!head2){         // If there is no user in our library system,no need to check for movie;
        return false;
    }
    UserNode *first = head2;
    UserNode *temp1 = first;
    bool control;
    while(true){
        if(temp1->user.checkForMovie(movieID)){
            control = true;
            break;
        }
        else{
            temp1 = temp1->next;
            if(temp1 == first){
                control = false;
                break;
            }
        }
    }
    return control;
}
void LibrarySystem::deleteUser(const int userId){
    if(checkUser(userId)){
        UserNode *first = head2;
        UserNode *temp1 = first->next;
        if(first->next == first && first->user.getUserID() == userId){
            head2 = nullptr;
        }
        else{
            while(true){
                if(temp1->user.getUserID() == userId){
                    temp1->previous->next = temp1->next;
                    temp1->next->previous = temp1->previous;   // temp1 is gone 
                    break;
                }
                else{
                    temp1 = temp1->next;
                    if(temp1 == first){
                        break;
                    }
                }
            }
            interface+= "User "+std::to_string(userId)+" has been deleted.\n";
        }
    }
    else{
        interface+= "User "+std::to_string(userId)+" does not exist.\n";
    }
}
bool LibrarySystem::checkUser(int userID){
    // This method checks if user that has the same ID as userID that comes as an argument or not.
    if(!head2){
        return false;
    }
    UserNode *temp = head2;
    bool control ;
    while(true)
    {
        int ID = temp->user.getUserID();
        if(ID == userID)
        {
            control = true;
            break;
        }
        else
        {
            temp = temp->next;
            if(temp == head2){
                control = false;
                break;
            }
        }
    }
    return control;
}
void LibrarySystem::activateSystem(std::vector<std::string> commands,std::string outputFile){
    // This method evaluates all commands that comes from our commands file and updates interface according to them.Finally,it creates an output file.
    interface+="====Movie Library System===\n";
    // From line 438 to 446,the integer variables are created to control the visibility of method headers.
    int addMovieControl = 0;
    int addUserControl = 0;
    int showAllMovieControl = 0;
    int checkOutMovieControl = 0;
    int showMovieControl = 0;
    int showUserControl = 0;
    int deleteMovieControl = 0;
    int deleteUserControl = 0;
    int returnMovieControl = 0;
    for(size_t i =0; i< commands.size();i++){
        std::string command = commands.at(i);
        if(command.substr(0,8) == "addMovie"){
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            size_t tab1 = command.find("\t",9);
            std::string ID = command.substr(9,tab1-9);
            int movieID;
            std::istringstream(ID) >> movieID;
            size_t tabPosition = command.find("\t",tab1+1);
            std::string movieTitle = command.substr(tab1+1, tabPosition-tab1-1);
            std::string year = command.substr(tabPosition+1,4);
            int movieYear;
            std::istringstream(year) >> movieYear;
            if(addMovieControl == 0){
                interface += "\n===addMovie() method test===\n"; // Example method header.
                addMovieControl++;
            }
            addMovie(movieID,movieTitle,movieYear);
        }
        else if(command.substr(0,7) == "addUser"){
            addMovieControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            size_t tabPosition = command.find("\t",8);
            std::string ID = command.substr(8,tabPosition-8);
            int userID ;
            std::istringstream(ID) >> userID;
            int lastIndex = command.length()-1;
            std::string userName = command.substr(tabPosition+1,lastIndex-tabPosition);
            if(addUserControl == 0){
                interface+="\n===addUser() method test===\n";
                addUserControl++;
            }
            addUser(userID,userName);
        }
        else if(command.substr(0,12) =="showAllMovie"){
            addMovieControl = 0;
            addUserControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            if(showAllMovieControl == 0){
                interface+="\n===showAllMovie() method test===\n";
                showAllMovieControl++;
            }
            showAllMovies();
        }
        else if(command.substr(0,13) == "checkoutMovie"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            int movID;
            int usID;
            size_t tabPosition = command.find("\t",14);
            std::string mID = command.substr(14,tabPosition-14);
            std::string uID = command.substr(16,command.length()-16);
            std::istringstream(mID) >> movID;
            std::istringstream(uID) >> usID;
            if(checkOutMovieControl == 0){
                interface+="\n===checkoutMovie() method test===\n";
                checkOutMovieControl++;
            }
            checkoutMovie(movID,usID);
        }
        else if(command.substr(0,9) == "showMovie"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            std::string ID = command.substr(10,command.length()-10);
            int movID ;
            std::istringstream(ID) >> movID;
            if(showMovieControl == 0){
                interface += "\n===showMovie() method test===\n";
                showMovieControl++;
            }
            showMovie(movID);
        }
        else if(command.substr(0,8) == "showUser"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            std::string ID = command.substr(9,command.length()-9);
            int usID ;
            std::istringstream(ID) >> usID;
            if(showUserControl == 0){
                interface+= "\n===showUser() method test===\n";
                showUserControl++;
            }
            showUser(usID);
        }
        else if(command.substr(0,11) == "deleteMovie"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteUserControl = 0;
            returnMovieControl = 0;
            std::string ID = command.substr(12,command.length()-12);
            int movID ;
            std::istringstream(ID)>>movID;
            if(deleteMovieControl == 0){
                interface+= "\n===deleteMovie() method test===\n";
                deleteMovieControl++;
            }
            deleteMovie(movID);
        }
        else if(command.substr(0,10) == "deleteUser"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            returnMovieControl = 0;
            std::string ID =  command.substr(11,command.length()-11);
            int usID ;
            std::istringstream(ID)>>usID;
            if(deleteUserControl == 0){
                interface+="\n===deleteUser() method test===\n";
                deleteUserControl++;
            }
            deleteUser(usID);
        }
        else if(command.substr(0,11) == "returnMovie"){
            addMovieControl = 0;
            addUserControl = 0;
            showAllMovieControl = 0;
            checkOutMovieControl = 0;
            showMovieControl = 0;
            showUserControl = 0;
            deleteMovieControl = 0;
            deleteUserControl = 0;
            std::string ID = command.substr(12,command.length()-12);
            int movID;
            std::istringstream(ID) >> movID;
            if(returnMovieControl == 0){
                interface+= "\n===returnMovie() method test===\n";
                returnMovieControl++;
            }
            returnMovie(movID);
        }
    }
    std::ofstream output(outputFile);
    output << interface << std::endl;
    output.close();
}
LibrarySystem::~LibrarySystem()
{
    delete head1;
    delete head2;
}

