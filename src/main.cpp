#include<iostream>
#include<string>
#include<fstream>
#include"../src/userData.h"

using namespace std;

void userLogIn(bool*);

int main(){
    bool loggedIn = false;
    int input = 3;
    
    while(input != 0){
        cout << "1. log in" << endl;
        cout << "2. register new user" << endl;
        cout << "0. quit" << endl;
        cin >> input;
        cin.ignore();
        switch (input)
        {
        case 1: userLogIn(&loggedIn);
                if(loggedIn) cout << "user logged in" << endl;
            break;
        case 2: createUser();
            break;
        default:
            break;
        }
    }

    readAllUsersFromFile("../user files/users.txt");

    // cin.get();
}

void userLogIn(bool* loggedIn){
    string userName, password;
    userName = " ";
    while (!doesUserNameExist(userName)){
        cout << "user name: " << endl;
        getline(cin, userName);
        if(userName.compare("0") == 0) break;
        if(doesUserNameExist(userName)){
            cout << "password: " << endl;
            getline(cin, password);
            while(!doesUserNameMatchPassword(password)){
                cout << "password does not match username" << endl;
                cout << "Retype password or press 0 to exit" << endl;
                cout << "password: " << endl;
                getline(cin, password);
                if(password.compare("0") == 0) break;
            }
            password.compare("0") == 0 ? (*loggedIn) = false : (*loggedIn) = true;
        }
        else{
            cout << "user name does not exist" << endl;
            cout << "Retype username or press 0 to exit" << endl;
        }
        if (password.compare("0") == 0) break;        
    }
}