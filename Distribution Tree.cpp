#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<fstream>

#define ld long double

using namespace std;

struct node{
    string value;
    ld abs;
    ld trans;

    node(string value, ld abs, ld trans){
        this->value = value;
        this->abs = abs;
        this->trans = trans;
    }
    node(string value){
        this->value = value;
        this->abs = 0;
        this->trans = 0;
    }
};

vector<vector<node>> p;

string bin(int n, int length){
    string r;
    while (n != 0){
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    while (r.size() < length) r = "0" + r;
    return r;
}

int randint(int a, int b){
    return a + (rand() % (b - a));
}

ld g(int i, int j){
    ld r = ((ld)randint(1, 9) / 10);
    return r;
}

void logfile(vector<vector<node>> p){
    ofstream f("log.txt");
    for (int i = 0; i < p.size(); i++){
        for (int j = 0; j < pow(2, i); j++)
            f << p[i][j].trans << ' ';
        f << '\n';
    }
    f.close();
}

void getdistribution(int n, ld a, ld b){
    p.push_back(vector<node>{node("", 1, 1)});
    p.push_back(vector<node>{node("0", a, a), node("1", b, b)});
    if (n == 1) return;
    for (int i = 2; i < n + 1; i++){
        vector<node> layer;
        for (int j = 0; j < pow(2, n); j++)
            layer.push_back(node(bin(j, i)));
        
        for (int k = 0; k < pow(2, i - 2); k++){
            long double maxp = min(p[i - 1][k].abs, p[i - 1][2 * k].abs);
            
            long double min_condition1 = p[i - 1][k].abs - p[i - 1][2 * k + 1].abs;
            long double min_condition2 = p[i - 1][2 * k].abs - p[i - 1][k + pow(2, (i - 2))].abs;
            long double minp;
            if (min_condition1 < 0 || min_condition2 < 0) minp = 0;
            else minp = max(min_condition1, min_condition2);

            layer[2 * k].abs = (maxp - minp) * g(i, k) + minp;

            layer[2 * k + 1].abs = p[i - 1][k].abs - layer[2 * k].abs;
            layer[2 * k + pow(2, i - 1)].abs = p[i - 1][2 * k].abs - layer[2 * k].abs;
            layer[2 * k + 1 + pow(2, i - 1)].abs = p[i - 1][2 * k + 1].abs - layer[2 * k + 1].abs;
        }
        for (int j = 0; j < pow(2, n); j++)
            layer[j].trans = layer[j].abs / p[i - 1][j / 2].abs;
        
        p.push_back(layer);
    }
}

int main(){
    getdistribution(6, 0.4, 0.6);
    logfile(p);
}