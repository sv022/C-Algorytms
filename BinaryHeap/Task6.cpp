#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class ToDoList {
private:
    std::vector<int> A;
    std::vector<std::string> Tasks;

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
            std::swap(Tasks[n], Tasks[mx]);
            heapify_down(mx);
        }
    }
    // �������� �������� A[i] �������� �������� ����.
    void heapify_up(int i) {
        if (i && A[parent(i)] < A[i]) {
            std::swap(Tasks[i], Tasks[parent(i)]);
            std::swap(A[i], A[parent(i)]);
            heapify_up(parent(i));
        }
    }

public:

    int size() {
        return A.size();
    }

    void push(int key, std::string task) {
        A.push_back(key);
        Tasks.push_back(task);
        int index = size() - 1;
        heapify_up(index);
    }

    void pop() {
        if (size() == 0) return;
        A[0] = A.back();
        Tasks[0] = Tasks.back();
        A.pop_back();
        Tasks.pop_back();
        heapify_down(0);
    }

    std::string top() {
        if (A.size() == 0) throw(std::exception());
        return Tasks[0];
    }

    void edit(int k, std::string new_task){
        for (int i = 0; i < size(); i++){
            if (A[i] == k) {
            Tasks[i] = new_task;
            return;
            }
        }
    }
};

using namespace std;

int main(){
    ToDoList h;
    h.push(2, "eat");
    h.push(3, "eep");
    cout << h.top() << ' ' << h.size() << '\n';
    h.edit(2, "touch grass");
    h.pop();
    cout << h.top() << ' ' << h.size() << '\n';

}