#include <bits/stdc++.h>

using namespace std;

void* go(void* a) {
    int b=(int)a;
    printf("%lld",b);
    return NULL;
}

int main () {
    go((void*)2);
}
