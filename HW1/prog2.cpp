#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int binarySearch(deque<int> &dq, int left, int right, int target);
void binaryInsert(deque<int> &dq, int left, int right, int insertion);

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int length, window, kth, k, prev;
    cin >> length >> window >> kth;
    deque<int> dq, remove;

    for(int i = 0; i < length; i++){
        cin >> k;
        binaryInsert(dq, 0, dq.size() - 1, k);
        remove.push_back(k);
        if (i >= window - 1){
            cout << dq[kth - 1] << '\n';
            prev = remove[0];
            remove.pop_front();
            dq.erase(dq.begin() + binarySearch(dq, 0, dq.size() - 1, prev));
        }
    }
}

int binarySearch(deque<int> &dq, int left, int right, int target){
    // Can't find the target
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2; // ensure not to overflow
    if (dq[mid] > target)
        return binarySearch(dq, left, mid - 1, target);
    else if (dq[mid] < target)
        return binarySearch(dq, mid + 1, right, target);
    else
        return mid;
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