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
    cout << "user name: " << endl;
    // cin.ignore();
    getline(cin, userName);
    if(doesUserNameExist(userName)){
        cout << "password: " << endl;
        getline(cin, password);
        while(!doesUserNameMatchPassword(password)){
            cout << "password does not match username" << endl;
            cout << "password: " << endl;
            getline(cin, password);
        }
        (*loggedIn) = true;
    }
}