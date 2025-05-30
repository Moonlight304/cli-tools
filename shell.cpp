#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
using namespace std;

int main () {
    cout << "Welcome to my shell!" << endl;

    while (true) {
        cout << "nitin> ";
        char cwd[1024];
        char* currPath = getcwd(cwd, sizeof(cwd));
        cout << cwd << "$ "; 

        string input;
        getline(cin, input);

        if (input == "exit") return 0;

        stringstream ss(input);
        string token;
        vector <char*> args;

        while (ss >> token) {
            if (!token.empty() && token[0] == '$') {
                char* envVariable = getenv(token.substr(1).c_str());
                token = envVariable || "";
            }

            char* arg = new char[token.size() + 1];
            strcpy(arg, token.c_str());
            args.push_back(arg);
        }
        args.push_back(nullptr);

        if (args[0] && strcmp(args[0], "cd") == 0) {
            if (args[1])
                chdir(args[1]);
            else
                chdir(getenv("HOME"));
            
                continue;
        }


        pid_t pid = fork();

        if (pid == 0) {
            if (execvp(args[0], args.data()) == -1)
                perror("Error");

            exit(1);
        }
        else if (pid > 0) {
            wait(nullptr);
        }
        else {
            cout << "Fork failed." << endl;
        }
    }
}