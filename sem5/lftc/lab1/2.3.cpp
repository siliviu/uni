# include <iostream>

using namespace std ;

int main ( ) {
    int n ;
    cin >> n ;
    int i = 0 , sum = 0 ;
    while ( i < n ) {
        int x ;
        cin >> x ;
        sum = sum + x ;
        i = i + 1 ;
    }
    cout << sum ;
    return 0 ;
}