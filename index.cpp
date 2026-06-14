#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

struct Account {
    int id;
    string name;
    float balance;
};

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

void createAccount() {
    ofstream file("accounts.txt", ios::app);
    int id;
    string name;
    cout << "Enter Account ID : ";
    cin >> id;
    cout << "Enter Your Name : ";
    cin >> name;
    file << id << "," << name << ",0" <<endl;
    cout << "Account Created Sucessfully!";
}
// Deposit Function
void deposit() {
    cout << "Enter Account ID : ";
    int userId;
    cin >> userId;

    ifstream file("accounts.txt");

    string line;
    vector<Account> acc;
    string id,name,balance;
    bool found = false;
    int i = 0;
    int pos = 0;

    while(getline(file, line)) {
        
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        Account tempAcc;

        tempAcc.id = stoi(id);
        tempAcc.name = name;
        tempAcc.balance = stof(balance);

        acc.push_back(tempAcc);

        if(userId == tempAcc.id) {
            found = true;
            pos = i;
        }
        i++;
    }

    file.close();
    
    if(found) {
        int amount;
        cout << "Enter amount to Deposit : ";
        cin >> amount;
        if(amount > 0) {
            acc[pos].balance += amount;
            ofstream f("accounts.txt");
            for(Account val: acc) {
                f << val.id << "," << val.name << "," << val.balance << endl;
            }
            f.close();
            cout << "Amount Deposited Successfully!";
        }
        else{
            cout << "Not a Valid Amount!";
        }
    }
    else{
        cout << "Account not Found!";
    }
}
// Withdraw Function
void withdraw() {
    cout << "Enter Account ID : ";
    int userId;
    cin >> userId;

    ifstream file("accounts.txt");

    string line;
    vector<Account> acc;
    string id,name,balance;
    bool found = false;
    int i = 0;
    int pos = 0;

    while(getline(file, line)) {
        
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        Account tempAcc;

        tempAcc.id = stoi(id);
        tempAcc.name = name;
        tempAcc.balance = stof(balance);

        acc.push_back(tempAcc);

        if(userId == tempAcc.id) {
            found = true;
            pos = i;
        }
        i++;
    }
    file.close();

    if(found) {
        int amount;
        cout << "Enter amount to Withdraw : ";
        cin >> amount;
        while(amount > acc[pos].balance || amount < 0) {
            cout << "Enter Valid Amount : ";
            cin >> amount;
        }
        acc[pos].balance -= amount;
        ofstream f("accounts.txt");
        for(Account val: acc) {
            f << val.id << "," << val.name << "," << val.balance << endl;
        }
        f.close();
        cout << amount << " Withdrawed from Your Account!";
    }
    else {
        cout << "Account not Found!";
    }
}

void choiceHandler(int ch) {
    if(ch == 1) {
        createAccount();
    }
    if(ch == 2) {
        deposit();
    }
    if(ch == 3) {
        withdraw();
    }
}
int main() {
    
    int choice;
    
    do{
        printMenu();
        cin >> choice;
        choiceHandler(choice);

    }while(choice != 10);
}