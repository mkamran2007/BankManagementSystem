#ifndef ENGINE_H
#define ENGINE_H

#include<string>
#include<vector>
using namespace std;
// ====== Structure for Accounts ====== 
struct Account {
    int id;
    string name;
    float balance;
};
// Structure is being used in dealing with accounts in the file -> accounts.txt
struct engine {
    vector<Account> acc;
    bool found = false;
    int pos = 0;
};
// engine() function returns the above structure. 
// It tells whether the account exixts or not + position of account in the vector
engine search(engine &e, int userId) {

    ifstream file("accounts.txt");
    string line, id, name, balance;    
    int i = 0;

    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        Account tempAcc;
        tempAcc.id = stoi(id);
        tempAcc.name = name;
        tempAcc.balance = stof(balance);
        e.acc.push_back(tempAcc);

        if(userId == tempAcc.id) {
            e.found = true;
            e.pos = i;
        }
        i++;
    }
    file.close();
    return e;
}

#endif