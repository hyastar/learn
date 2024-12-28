#include <iostream>
#include <string>
using namespace std;
 
int main(){
    string line;
    cout << "Enter a line of text: ";
    getline(cin, line);
    cout << "You entered: " << line << endl;
    return 0;
}
