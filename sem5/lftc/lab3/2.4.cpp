#include <iostream>

using namespace std;

int main() {
    int n;
    cin>>n;
    int i=0, sum = 0;
    cat timp (i < n) executa {
        int x;
        cin >> x;
        sum = sum + x;
        i = i+1;
    }
    cout << sum;
    return 0;
}