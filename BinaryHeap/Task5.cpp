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

        int mx = n;
        if (l < size() && A[l] > A[n]) {
            mx = l;
        }
        if (r < size() && A[r] > A[mx]) {
            mx = r;
        }
        if (mx != n) {
            std::swap(A[n], A[mx]);
            heapify_down(mx);
        }
    }
    // �������� �������� A[i] �������� �������� ����.
    void heapify_up(int i) {
        if (i && A[parent(i)] < A[i]) {
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

Heap merge(Heap h1, Heap h2) {
    for (int i = 0; i < h2.A.size(); i++) {
        //cout << h2.A[i] << '\n';
        h1.push(h2.A[i]);
    }
    return h1;
}

void heapSort(std::vector<int> &a){
    Heap h(a);
    int n = a.size();
    for (int i = 1; i < n + 1; i++){
        a[n - i] = h.top();
        h.pop();
    }
}

using namespace std;

int main(){
    vector<int> a = {4, 1, 2, 6, 5};
    heapSort(a);
    for (int i = 0; i < a.size(); i++) cout << a[i] << ' ';
}