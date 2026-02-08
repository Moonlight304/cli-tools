#include <iostream>
using namespace std;

int main() {
    #if DEBUG
        cout << "HELLO" << endl;
    #else
        cout << "BYE" << endl;
    
    #endif
}