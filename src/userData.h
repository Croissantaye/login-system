#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

const int MIN_NAME_LEN = 8;
const int MIN_PASSWORD_LEN = 8;

struct userData
{
    std::string userName;
    std::string userPassword;
};

userData createUser(std::string, std::string);
void createUser();
void printUserData(userData&);
void writeUserToFile(userData&, std::string);
void writeUserToFile(userData&);
userData readUserFromFile(std::string);
void readAllUsersFromFile(std::string);
bool isValidUserName(std::string);
bool isValidPassword(std::string, std::string);
bool doesUserNameExist(std::string);

userData createUser(std::string name, std::string password){
    userData newUser;
    newUser.userName = name;
    newUser.userPassword = password;
    return newUser;
}

void createUser(){
    userData newUser;
    std::string name = "";
    std::string password = "";

    while(!isValidUserName(name)){
        std::cout << "enter new user name: " << std::endl;
        getline(std::cin, name);
    }
    while(!isValidPassword(password, name)){
        std::cout << "enter password for user " << name << ": " << std::endl;
        getline(std::cin, password);
    }

    newUser.userName = name;
    newUser.userPassword = password;

    writeUserToFile(newUser);
    std::cout << "new user written to file" << std::endl << std::endl;
}

void printUserData(userData &user){
    std::cout << std::endl << "user name: " << user.userName << std::endl;
    std::cout << "user password: " << user.userPassword << std::endl;
}

void writeUserToFile(userData &user, std::string fileName){
    const std::string userFilePath = "../user files/users.txt";
    const std::string delim = ",";
    std::ofstream myFile;
    myFile.open(userFilePath + fileName + ".txt");
    myFile << user.userName + delim + user.userPassword;
    myFile.close();
}

void writeUserToFile(userData &user){
    const std::string userFilePath = "../user files/users.txt";
    const std::string delim = ",";
    std::ofstream myFile;
    myFile.open(userFilePath, std::ios::out|std::ios::app);
    myFile << user.userName << delim << user.userPassword << std::endl;
    myFile.close();
}

userData readUserFromFile(std::string filePath){
    std::cout << std::endl << "read user from file" << std::endl;
    userData user;
    std::string userName;
    std::string userPassword;
    std::ifstream myFile;
    myFile.open(filePath);
    std::string fileContents;
    std::getline(myFile, fileContents);
    std::stringstream s_stream(fileContents);
    std::getline(s_stream, user.userName, ',');
    std::getline(s_stream, user.userPassword, ',');
    return user;
}

void readAllUsersFromFile(std::string filePath){
    std::cout << "reading all users from file" << std::endl;

    std::string name;
    std::string password;
    std::string line;
    int userNum = 0;

    std::ifstream usersFile;
    usersFile.open(filePath);
    std::cout << std::endl;
    std::getline(usersFile, line);
    while(line.compare("") != 0){
        std::stringstream ss(line);
        std::getline(ss, name, ',');
        std::getline(ss, password, ',');
        std::cout << "user number: " << userNum << 
            "\t" << name <<
            "\t" << password << std::endl;
        std::getline(usersFile, line);
        userNum++;
    }
    usersFile.close();
}

bool isValidUserName(std::string name){
    if(name.compare("") == 0){
        return false;
    }
    if(name.length() - 1 < MIN_NAME_LEN){
        std::cout << "user names must be " << MIN_NAME_LEN << " characters long" << std::endl;
        return false;
    }
    if(isdigit(name[0])){
        std::cout << "user names can't start with a digit" << std::endl;
        return false;
    }
    if(doesUserNameExist(name)){
        std::cout << "user name already exists" << std::endl;
        return false;
    }
    if(name.find(" ") != std::string::npos){
        std::cout << "no spaces in usernames" << std::endl;
        return false;
    }
    return true;
}

bool isValidPassword(std::string password, std::string name){
    if(password.compare("") == 0){
        return false;
    }
    if(password.length() - 1 < MIN_PASSWORD_LEN){
        std::cout << "passwords must be " << MIN_PASSWORD_LEN << " characters long" << std::endl;
        return false;
    }
    if(password.find(name) != std::string::npos){
        std::cout << "can't have your username in your password" << std::endl;
        return false;
    }
    if(name.find(" ") != std::string::npos){
        std::cout << "no spaces in passwords" << std::endl;
        return false;
    }
    return true;
}

bool doesUserNameExist(std::string newUserName){
    std::string line;
    std::string userName;
    std::ifstream usersFile;
    usersFile.open("../user files/users.txt");
    std::cout << std::endl;
    std::getline(usersFile, line);
    while(line.compare("") != 0){
        std::stringstream ss(line);
        std::getline(ss, userName, ',');
        if(userName.compare(newUserName) == 0){
            usersFile.close();
            return true;
        }
        std::getline(usersFile, line);
    }
    usersFile.close();
    return false;
}

bool doesUserNameMatchPassword(std::string password){
    std::string line, userName, userPassword;
    std::ifstream usersFile;
    usersFile.open("../user files/users.txt");
    std::cout << std::endl;
    std::getline(usersFile, line);
    while(line.compare("") != 0){
        std::stringstream ss(line);
        std::getline(ss, userName, ',');
        std::getline(ss, userPassword, ',');
        if(userPassword.compare(password) == 0){
            usersFile.close();
            return true;
        }
        std::getline(usersFile, line);
    }
    usersFile.close();
    return false;
}