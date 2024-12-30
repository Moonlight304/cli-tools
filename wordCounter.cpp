#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char * argv[]) {
    if (argc > 2) {
        cout << "Enter 1 file name only!" << endl;
        return 0;
    }

    string fileName = argv[1];

    ifstream file(fileName);
    if (!file) {
        cout << "File doesn't exist!" << endl;
        return 0;
    }
    
    int lineCount = 0, wordCount = 0, charCount = 0;

    string lineText;
    while (getline(file, lineText)) {
        lineCount++;

        bool inWord = false;
        for (char c : lineText) {
            charCount++;

            if (c == ' ' && inWord) {
                wordCount++;
                inWord = false;
            }
            else {
                inWord = true;
            }
        }

        if (inWord)
            wordCount++;

    }

    file.close();

    cout << "Line count : " << lineCount << endl;
    cout << "Word count : " << wordCount << endl;
    cout << "Character count : " << charCount << endl;

    return 0;
}