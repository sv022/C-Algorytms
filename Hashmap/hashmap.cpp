#include <string>
#include "linkedlist.cpp"

using namespace std;

template<typename T1, typename T2>
class hashmap;
string tostr(char);
string tostr(int);
string tostr(string);

string tostr(char s){
    string res(1, s);
    return res;
}

string tostr(int s){
    return to_string(s);
}

string tostr(string s){
    return s;
}

template<typename T1, typename T2>
ostream& operator << (ostream& stream, hashmap<T1, T2>& h){
    stream << '{';
    int i = 0;
    string out;
    for (; i < h.HASH_SIZE; i++){
        Node<T1, T2>* p = h.hashlist[i];
        if (p == nullptr) continue;
        while (p){
            vector<T2> items = p->data;
            out += tostr(p->key);
            out += " : ";
            if (items.size() == 1) {out += (tostr(items[0]) + ", "); p = p->next; continue;}
            out += '(';
            for (int j = 0; j < items.size(); j++) out += (tostr(items[j]) + ", ");
            out = out.substr(0, out.length() - 2);
            out += "); ";
            p = p->next;
        }
    }
    out = out.substr(0, out.length() - 2);
    stream << out;
    stream << "}\n";
    return stream;
}

template<typename T1, typename T2>
class hashmap {
private:
    static const int HASH_MUL = 31;
    static const int HASH_SIZE = 128;

    Node <T1, T2> * hashlist[HASH_SIZE];
    
    unsigned int hash(string s){
        unsigned int h = 0;
        for (int i = 0; i < s.size(); i++)
            h = h * HASH_MUL + (unsigned int)s[i];
        return h % HASH_SIZE;
    }

    unsigned int hash(int s){
        unsigned int h = 0;
        while (s > 0){
            h = h * HASH_MUL + (s % 10);
            s = s / 10;
        }
        return h % HASH_SIZE;
    }
public:
    hashmap(){
        for (int i = 0; i < HASH_SIZE; i++) hashlist[i] = nullptr;
    }

    void add(const T1 key, const T2 value){
        unsigned int h = hash(key);
        if (hashlist[h] == nullptr){
            hashlist[h] = addnode(key, value);
            return;
        }
        if (hashlist[h]->key == key) {hashlist[h]->data.push_back(value); return;}
        hashlist[h]->next = addnode(key, value);
    }

    vector <T2> get(T1 key){
        unsigned int h = hash(key);
        if (hashlist[h] == nullptr) throw exception();
        Node<T1, T2>* p = hashlist[h];
        while (p){
            if (p->key == key) return p->data;
            p = p->next;
        }
        throw exception();
    }

    void remove(const T1 key){
        unsigned int h = hash(key);
        if (hashlist[h] == nullptr) throw exception();
        Node<T1, T2>* p = hashlist[h];
        if (p->next == nullptr){
            if (p->key == key){
                delete p;
                hashlist[h] = nullptr;
                return;
            } else {
                throw exception();
            }
        } 
        while (p->next){
            if (p->next->key == key){
                if (p->next->next == nullptr){
                    delete p->next;
                    p->next = nullptr;
                } else {
                    Node <T1, T2>* next = p->next->next;
                    delete p->next;
                    p->next = next;
                    delete next;
                }
            }
        }
        delete p;
    }

    vector <T2>& operator [](T1 key){
        unsigned int h = hash(key);
        if (hashlist[h] == nullptr) throw exception();
        Node<T1, T2>* p = hashlist[h];
        while (p){
            if (p->key == key) return p->data;
            p = p->next;
        }
        throw exception();
    }


    friend ostream& operator << <T1, T2>(ostream &stream, hashmap& object);

};



