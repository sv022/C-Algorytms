#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void sieve(int n){
    vector <int> a;
    for (int i = 0; i < n; i++) a.push_back(i);
    for (int i = 2; i < n; i++){
        if (a[i] != 0){
            cout << a[i] << ' ';
            for (int j = i * i; j < n; j += i){
                a[j] = 0;
            }
        }
    }
}

int main() {
    int n = 1000;
    sieve(n);
}


