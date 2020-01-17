#include <iostream>
#include <deque>
using namespace std;

int binarySearch(deque<int> dq, int left, int right, int target);

int main(){
    // test code
    int target = 0;
    while (target != -1){
        cin >> target;
        deque<int> dq = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        cout << binarySearch(dq, 0, dq.size() - 1, target) << endl;
    }
    system("pause");
    return 0;
}

// Search target in dq, left & right are iterators
int binarySearch(deque<int> dq, int left, int right, int target){
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