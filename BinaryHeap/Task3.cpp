#include <iostream>
#include <vector>
#include <algorithm>

class Heap {
private:
    std::vector<int> A;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return (2 * i + 1);
    }

    int right(int i) {
        return (2 * i + 2);
    }
    // ������� A[i] �������� �������� ���� � ��� ��������� ����������.
    void heapify_down(int n) {
        int l = left(n);
        int r = right(n);

        int mn = n;
        if (l < size() && A[l] < A[n]) {
            mn = l;
        }
        if (r < size() && A[r] < A[mn]) {
            mn = r;
        }
        if (mn != n) {
            std::swap(A[n], A[mn]);
            heapify_down(mn);
        }
    }
    // �������� �������� A[i] �������� �������� ����.
    void heapify_up(int i) {
        if (i && A[parent(i)] > A[i]) {
            std::swap(A[i], A[parent(i)]);
            heapify_up(parent(i));
        }
    }

public:

    Heap() {

    }

    Heap(std::vector<int> a) {
        for (int i = 0; i < a.size(); i++) push(a[i]);
    }

    friend Heap merge(Heap h1, Heap h2);

    int size() {
        return A.size();
    }

    void push(int key) {
        A.push_back(key);
        int index = size() - 1;
        heapify_up(index);
    }

    void pop() {
        if (size() == 0) return;
        A[0] = A.back();
        A.pop_back();
        heapify_down(0);
    }

    int top() {
        if (A.size() == 0) throw(std::exception());
        return A[0];
    }

};

using namespace std;

int main(){
    vector<int> a = {5, 4, 2, 8};
    Heap h(a);
    int s = 0;
    while (h.size() > 1) {
        int k1 = h.top();
        h.pop();
        int k2 = h.top();
        h.pop();
        s += k1 + k2;
        h.push(k1 + k2);
    }
    cout << s;
}