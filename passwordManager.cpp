#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

string encrypt(const string& password, int key = 5) {
    string encrypted = password;
    for (char& c : encrypted) {
        c += key;
    }
    return encrypted;
}

string decrypt(const string& password, int key = 5) {
    string decrypted = password;
    for (char& c : decrypted) {
        c -= key;
    }
    return decrypted;
}

unordered_map <string, string> loadPasswords (string fileName) {
    ifstream file(fileName);
    unordered_map <string, string> passwordMapping;

    string lineText;
    while (getline(file, lineText)) {
        string account = "", password = "";

        bool isAccount = true;
        for (char c : lineText) {
            if (c == ':') {
                isAccount = false;
                continue;
            }
            
            if (isAccount)
                account += c;
            else
                password += c;
        }

        passwordMapping[account] = password;
    }
    file.close();

    return passwordMapping;
}

void savePasswords(const string &fileName, unordered_map <string, string> &passwordMapping) {
    ofstream file(fileName);

    for (const auto &passwordEntry : passwordMapping) {
        string account = passwordEntry.first;
        string password = passwordEntry.second;

        file << account << ":" << password << endl;
    }
    file.close();
}

int main (int argc, char * argv[]) {
    string fileName = "password.txt";

    if (argc < 2) {
        cout << "Usage : ./passwordManager <command> [arguments]" << endl;
        cout << "Commands: add <account> <password>, get <account>, list" << endl;

        return 0;
    }

    string command = argv[1];

    unordered_map <string, string> passwordMapping;
    passwordMapping = loadPasswords(fileName);

    if (command == "add") {
        if (argc != 4) {
            cout << "Usage : ./passwordManager add <account> <password>" << endl;
            return 0;
        }

        string account = argv[2];
        string password = argv[3];
        
        if (account == "" || password == "") {
            cout << "Incorrect arguments" << endl;
            return 0;
        }

        if (passwordMapping[account] == "") {
            cout << "Saved password for " << account << endl;
        }
        else {
            cout << "Updated password for " << account << endl;
        }
        passwordMapping[account] = encrypt(password);
        savePasswords(fileName, passwordMapping);
    }
    else if (command == "get") {
        if (argc < 3) {
            cout << "Usage : ./passwordManager get <account>" << endl;
            return 0;
        }

        string account = argv[2];

        if (account == "") {
            cout << "Account not found" << endl;
            return 0;
        }

        string password = decrypt(passwordMapping[account]);
        
        if (password == "")
            cout << "No entry found for " << account << endl;
        else
            cout << "Password for " << account << " is " << password << endl;
    }
    else if (command == "list") {
        if (passwordMapping.empty()) {
            cout << "No accounts listed" << endl;
            return 0;
        }
        else {
            cout << "Accounts are : " << endl;
            for (const auto &passwordEntry : passwordMapping) {
                string account = passwordEntry.first;

                cout << account << endl;
            }
        }
    }
    else {
        cout << "Usage : ./passwordManager <command> [arguments]" << endl;
        cout << "Commands: add <account> <password>, get <account>, list, help" << endl;

        return 0;
    }

    return 0;
}