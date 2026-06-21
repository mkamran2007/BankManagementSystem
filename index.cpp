// ====== HEADER FILES ====== 
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include "engine.h"
using namespace std;
// ====== FUNCTION PROTOTYPES ====== 
void createAccount();
void withdraw();
void deposit();
void transfer();
void viewAccDetail();
void viewAll();
void searchByName();
void searchByBalance();
void deleteAccount();
int choiceHandler(int ch);
void printMenu();
// ====== MAIN FUNCTION ====== 
int main() {
    int choice;
    do{
        printMenu();
        cin >> choice;
        choiceHandler(choice);
    }while(choice != 10);
    
}
// ====== THE MENU ====== 
void printMenu() {
    cout << "\n--------------------------------------------------\n";
    cout << "|            BANK MANAGEMENT SYSTEM              |\n";
    cout << "--------------------------------------------------\n";
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. View Account Details"<< endl;
    cout << "6. View  All Accounts"<< endl;
    cout << "7. Search Account by Name" << endl;
    cout << "8. Search Accounts by Balance" << endl;
    cout << "9. Delete Account" << endl;
    cout << "10. Exit" << endl;
    
    cout << "\nENTER YOUR CHOICE : ";
}

// ====== HANDLING the USER CHOICE ====== 
int choiceHandler(int ch) {
    if(ch == 1) createAccount();
    else if(ch == 3) withdraw();
    else if(ch == 2) deposit();
    else if(ch == 4) transfer();
    else if(ch == 5) viewAccDetail();
    else if(ch == 6) viewAll();
    else if(ch == 7) searchByName();
    else if(ch == 8) searchByBalance();
    else if(ch == 9) deleteAccount();
    else if(ch == 10) return 10;
    else cout << "Invalid Choice.";
    
}
// ====== CREATE ACCOUNT FUNCTION ====== 
void createAccount() {
    int userId;
    cout << "\nEnter Unique Account ID : ";
    cin >> userId;
    
    engine e;
    search(e, userId);
    if(userId <= 0 ) {
        cout << "Invalid Account ID : " << endl;
        createAccount();
    }
    else if(!e.found) {
        ofstream file("accounts.txt", ios::app);
        string name;
        cout << "Enter Your Name : ";
        cin.ignore();
        getline(cin,name);
        file << userId << "," << name << ",0" <<endl;
        file.close();
        cout << "Account Created Sucessfully!";
    }
    else {
        cout << "Account already Exists!" << endl;
        createAccount();
    }
}
// ====== DEPOSIT FUNCTION ====== 
void deposit() {
    cout << "Enter Account ID : ";
    int userId;
    cin >> userId;

    engine e;
    search(e, userId);
    if(e.found) {
        int amount;
        cout << "Enter amount to Deposit : ";
        cin >> amount;
        while(amount <= 0) { // >>> validating the amount to deposit
            cout << "Enter Valid Amount : ";
            cin >> amount;
        }
        if(amount > 0) {
            e.acc[e.pos].balance += amount;
            ofstream f("accounts.txt");
            for(Account val: e.acc) {
                f << val.id << "," << val.name << "," << val.balance << endl;
            }
            f.close();
            cout << "Amount Deposited Successfully!";
        }
    }
    else{
        cout << "Account not Found!";
    }
}
// ====== WITHDRAW MONEY FUNCTION ====== 
void withdraw() {
    cout << "\nEnter Account ID : ";
    int userId;
    cin >> userId;

    engine e;
    search(e, userId);
    if(e.found) {
        int amount;
        cout << "Enter amount to Withdraw : ";
        cin >> amount;
        while(amount > e.acc[e.pos].balance || amount <= 0) {
            cout << "Error : Invalid Amount or Insufficient Balance." << endl;
            cout << ">>> Enter Valid Amount : ";
            cin >> amount;
        }
        e.acc[e.pos].balance -= amount;
        ofstream file("accounts.txt");
        for(Account val: e.acc) {
            file << val.id << "," << val.name << "," << val.balance << endl;
        }
        file.close();
        cout << amount << " Withdrawn from Your Account!";
    }
    else {
        cout << "Account not Found!";
    }
}
// ====== TRANSFER MONERY FUNCTION ====== 
void transfer() {
    int userId, transId;
    cout << "\nEnter your Account ID : ";
    cin >> userId;

    engine e;
    search(e, userId);    
    if(e.found) {
        cout << "Enter Account ID you want to Transfer : ";
        cin >> transId;

        e.acc.clear();
        e.found = false;
        int userPos = e.pos;
        e.pos = 0;
        search(e, transId);

        if(e.found) {
            int amount;
            cout << "Enter Amount to Transfer : ";
            cin >> amount;
            
            while(amount > e.acc[userPos].balance || amount <= 0) {
                cout << "Error : Invalid Amount or Insufficient Balance." << endl;
                cout << ">>> Enter Valid Amount : ";
                cin >> amount;
            }
            e.acc[userPos].balance -= amount;
            e.acc[e.pos].balance += amount;

            ofstream file("accounts.txt");
            for(Account val: e.acc) {
                file << val.id << "," << val.name << "," << val.balance << endl;
            }
            file.close();
            cout << "Amount Transferred Successfully!";
        }
        else {
            cout << "Transfer Account not Found!";
        }
    }
    else{
        cout << "User Account not Found!";
    }
    
}
// ====== VIEW ACCOUNT DETAILS ====== 
void viewAccDetail() {
    cout << "\nEnter Account ID : ";
    int userId;
    cin >> userId;

    engine e;
    search(e, userId);
    if(e.found) {
        cout << "Account Id : " << e.acc[e.pos].id << "   Name : " << e.acc[e.pos].name << "   Balance : " << e.acc[e.pos].balance << endl;
    }
    else {
        cout << "Account not Found!";
    }
}
// ====== VIEW ALL ACCOUNTS ====== 
void viewAll() {
    string line, id, name, balance;
    ifstream file("accounts.txt");

    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');
        cout << "Account ID : " << stoi(id) << "   " << " Name : " << name << "   " << "Balance : " << balance << endl;
    }
    file.close();
}
// ====== SEARCH ACCOUNT BY NAME ====== 
void searchByName() {
    string line, id, name, userName;
    cout << "\nEnter your Name : ";
    cin.ignore();
    getline(cin,userName);
    cout << "Showing Search Results for : '" << userName << "'" << endl << endl;

    bool found = false;
    ifstream file("accounts.txt");
    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');

        if(line.find(userName) != string::npos) {
            found = true;
            cout << "Account ID : " << stoi(id) << "   " << " Name : " << name << endl;
        }
    }
    file.close();
    if(!found) {
        cout << "No Account Found!";
    }
}
// ====== SEARCH ACCOUNT BY BALANCE ====== 
void searchByBalance() {
    cout << "\nEnter Balance : ";
    float searchBalance;
    cin >> searchBalance;
    cout << "Showing Search Results for : '" << searchBalance << "'" << endl << endl;

    string line, id, name, balance;
    bool found = false;

    ifstream file("accounts.txt");
    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        if(stof(balance) >= searchBalance) {
            found = true;
            cout << "Account ID : " << stoi(id) << "   " << " Name : " << name << "   " << "Balance : " << stof(balance) << endl;
        }
    }
    file.close();
    if(!found) {
        cout << "No Account Found!";
    }
}
// ====== DELETE ACCOUNT ======  
void deleteAccount() {
    cout << "\nEnter Account ID : ";
    int userId;
    cin >> userId;

    engine e;
    search(e, userId);
    if(e.found) {
        e.acc.erase(e.acc.begin() + e.pos);
        ofstream f("accounts.txt");
        for(Account val: e.acc) {
            f << val.id << "," << val.name << "," << val.balance << endl;
        }
        f.close();
        cout << "Account Deleted Successfully!";
    }
    else {
        cout << "Account not Found!";
    }
}