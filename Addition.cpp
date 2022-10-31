#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;

bool iszero(int* a, int n){
    for (int i = 0; i < n; i++) if (a[i] != 0) return true;
    return false;
}

void adddecimal(int* a, int* b, int n){
    int* temp = new int[n + 1];
    int* trans = new int[n + 1];
    trans[n] = 0;
    for (int i = 0; i < n; i++) {
        temp[i + 1] = (a[i] + b[i]) % 10;
        if (a[i] + b[i] >= 10) trans[i] = 1;
        else trans[i] = 0;
    }
    while (iszero(trans, n)){
        for (int i = 0; i < n; i++){
            temp[i] = (temp[i] + trans[i]) % 10;
            if (temp[i + 1] + trans[i + 1] >= 10) trans[i] = 1;
            else trans[i] = 0;
        }
    }
    for (int i = 0; i < n + 1; i++) cout << temp[i];
    cout << '\n';
}

void addbin(int* a, int* b, int n){
    int* temp = new int[n + 1];
    int* trans = new int[n + 1];
    trans[n] = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] + b[i] == 0 or a[i] + b[i] == 2) temp[i + 1] = 0;
        else temp[i + 1] = 1;
        if (a[i] + b[i] == 2) trans[i] = 1;
        else trans[i] = 0;
    }
    while (iszero(trans, n)){
        for (int i = 0; i < n; i++){
            if (temp[i] + trans[i] == 2 or temp[i] + trans[i] == 0) temp[i] = 0;
            else temp[i] = 1;
            if (temp[i + 1] + trans[i + 1] == 2) trans[i] = 1;
            else trans[i] = 0;
        }
    }
    for (int i = 0; i < n + 1; i++) cout << temp[i];
    cout << '\n';
}

int randint(int n){
    return rand() % n;
}

void bin(int n){
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++) a[i] = randint(2);
    for (int i = 0; i < n; i++) b[i] = randint(2);

    cout << "num1  ";
    for (int i = 0; i < n; i++) cout << a[i];
    cout << "\nnum2  ";
    for (int i = 0; i < n; i++) cout << b[i];
    cout << '\n';

    addbin(a, b, n);

    delete[] a;
    delete[] b;
}
void decimal(int n){
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++) a[i] = randint(10);
    for (int i = 0; i < n; i++) b[i] = randint(10);
    cout << "num1  ";
    for (int i = 0; i < n; i++) cout << a[i];
    cout << "\nnum2  ";
    for (int i = 0; i < n; i++) cout << b[i];
    cout << '\n';
    adddecimal(a, b, n);
    delete[] a;
    delete[] b;
}

int main() {
    srand(7);
    int n = 70;
    // decimal(n) / bin(n)
}


