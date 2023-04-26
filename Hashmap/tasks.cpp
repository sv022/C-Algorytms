#include "hashmap.cpp"

using namespace std;

void test(){
    hashmap<int, int> h;
    h.add(1, 124);
    h.add(1, 125);
    h.add(2, 238);
    h.remove(2);
    h.add(3, 781);
    vector<int> item = h.get(1);
    for (int i = 0; i < item.size(); i++) cout << item[i] << ' ';
    //cout << h;
}

void test2(){
    hashmap<int, string> h;
    h.add(1, "apple");
    cout << h;
}

void phonebook(){
    hashmap<string, string> book;
    book.add("steve", "236789");
    book.add("Jeff", "202937");
    book.add("vlad", "901217");
    book.remove("vlad");
    cout << book;
}

void task3(){
    string s = "aaabbccccr";
    hashmap <char, int> d;
    for (int i = 0; i < s.length(); i++){
        try {
            d.get(s[i]);
            d[s[i]][0]++;
        } catch (exception){
            d.add(s[i], 1);
        }
    }
    cout << d;
}

void task4(){
    hashmap <int, int> d;
    int a[10] = {4, 1, 5, 9, 12, 3, 41, 9, 10, 6}; //2 6
    int n = 46;
    int index;
    int i = 0;
    for (; i < 10; i++){
        try {index = d[n - a[i]][0]; break;}
        catch (exception){ d.add(a[i], i);}
    }
    cout << index << ' ' << i << '\n';
}

int main(){


    task3();
    task4();
}
