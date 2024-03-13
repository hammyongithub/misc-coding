#include <iostream>
using namespace std;

void modifyViaPointer(int* ptr) {
    *ptr = 20; // Modifying the value via pointer
}

void modifyViaReference(int& ref) {
    ref = 30; // Modifying the value via reference
}

int main() {
    int x = 10;
    int* ptr = &x; // Pointer initialization
    int& ref = x;  // Reference initialization

    modifyViaPointer(ptr);
    cout << "Value after modification via pointer: " << x << endl; // Output: 20

    modifyViaReference(ref);
    cout << "Value after modification via reference: " << x << endl; // Output: 30

    return 0;
}
