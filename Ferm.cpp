#include <iostream> 
#include <vector> 
#include <cmath> 
 
using namespace std; 

vector <int> primes;

bool issquare(double n) { 
    return trunc(sqrt(n)) == sqrt(n); 
}

void sieve(int n){
    for (int i = 0; i < n + 1; i++) primes.push_back(i);
    for (int i = 2; i < n + 1; i++){
        if (primes[i] != 0){
            // cout << primes[i] << ' ';
            for (int j = i * i; j < n + 1; j += i){
                primes[j] = 0;
            }
        }
    }
}
 
void ferm(int n) {
    //cout << 'n' << n << '\n';
    if (primes[n]){
        cout << n << ' ';
        return;
    }
    if (issquare(n)){
         ferm(sqrt(n));
         ferm(sqrt(n));
         return;
    }
    if (n % 2 == 0){
        cout << '2' << ' ';
        ferm(n / 2);
        return;
    }
    int m = trunc(sqrt(n));
    for (int i = 1; i < n; i++) { 
        int q = pow((m + i), 2) - n; 
        if (issquare(q)) { 
            int a = m + i; 
            int b = sqrt(q);
            int x = a + b;
            int y = a - b;
            ferm(x);
            ferm(y);
            return;
        } 
    } 
} 

int main() {
    int n = 19691;
    sieve(n);
    ferm(n); 
}
