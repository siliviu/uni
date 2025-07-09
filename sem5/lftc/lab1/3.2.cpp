#include <iostream>

using namespace std;

int main() {
    int a;
    int b;
    cin >> a;
    cin >> b;
    while (b) { // in MLP ne mai trebuie un comparator si o alta expresie; in C++ e ok
        int r = a % b;
        a = b;
        b = r;
    }
    cout << a;
    return 0;
}