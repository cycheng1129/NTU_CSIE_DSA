#include <iostream>
#include <deque>
using namespace std;

void binaryInsert(deque<int> &dq, int left, int right, int insertion);

int main(){
    int insertion = 0;
    deque<int> dq;
    while (insertion != -1){
        cin >> insertion;
        binaryInsert(dq, 0, dq.size() - 1, insertion);
        for (int i = 0; i < dq.size(); i++)
            cout << dq[i] << " ";
        cout << endl;
    }

    system("pause");
    return 0;
}

void binaryInsert(deque<int> &dq, int left, int right, int insertion){
    if (left > right){
        dq.push_back(insertion);
        return;
    }

    int mid = left + (right - left) / 2; // ensure not to overflow
    if (mid != 0 && insertion >= dq[mid - 1] && insertion <= dq[mid])
        dq.insert(dq.begin() + mid, insertion);
    else if (mid == 0 && insertion <= dq[mid])
        dq.push_front(insertion);
    else if (mid == dq.size() - 1) // && insertion >= dq[mid]
        dq.push_back(insertion);
    else if (insertion > dq[mid])
        return binaryInsert(dq, mid + 1, right, insertion);
    else if (insertion < dq[mid])
        return binaryInsert(dq, left, mid - 1, insertion);
}