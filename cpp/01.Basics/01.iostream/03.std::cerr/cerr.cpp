#include <iostream>
using namespace std;

int main(){
    int x;
    float y;

    cout << "Enter an integet: ";
    cin >> x;
    cout << "Enter a float: ";
    cin >> y;

    if(x < y){
        cerr << "Error: x is negative!" << endl;
    }
    return 0;
}
