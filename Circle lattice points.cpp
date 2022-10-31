#include <iostream>
#include <math.h>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

struct factor {
    int n;
    vector< pair<int, int> > m;
};

void sieve(int n, int* a){
    for (int i = 2; i <= n; i++){
        if (a[i] != 0){
            for (int j = i * i; j <= n; j += i){
                a[j] = 0;
            }
        }
    }
}

factor fact(int n){
    const int N = n;
    factor f;
    f.n = N;
    int *primes = new int[n + 1];
    for (int i = 0; i <= n; i++) primes[i] = i;
    sieve(n, primes);
    if (primes[N]) {
        pair <int, int> p;
        p.first = N;
        p.second = 1;
        f.m.push_back(p);
        return f;
    }
    for (int i = 2; i < N; i++){
        if (not(primes[i])) continue;
        int p = 0;
        while (n % i == 0) {
            n = n / i;
            p++;
        }
        pair <int, int> t;
        t.first = i;
        t.second = p;
        if (p != 0) f.m.push_back(t);
    }
    delete[] primes;
    return f;
}

void printfact(int n){
    factor f = fact(n);
    for (int i = 0; i < f.m.size(); i++){
        cout << f.m[i].first << '^' << f.m[i].second << ' ';
    }
}

int ki(int n){
    int c[4] = {0, 1, 0, -1};
    return c[n % 4];
}

int latticepoints(int r){
    if (r < 1) return 0;
    if (r == 1) return 4;
    factor f = fact(r);
    int res = 4;
    for (int i = 0; i < f.m.size(); i++){
        int p = 0;
        pair <int, int >num = f.m[i];
        for (int j = 0; j <= num.second; j++) p += ki(pow(num.first, j));
        res *= p;
    }
    return res;
}

int main() {
    int n = 25; // n = R^2
    cout << latticepoints(n);
}


