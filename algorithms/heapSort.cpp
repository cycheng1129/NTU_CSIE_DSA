#include <bits/stdc++.h> 
using namespace std;

template<typename T>
vector<T> minHeapSort(vector<T> &vec);
template<typename T>
T minHeapExtract(vector<T> &vec);

int main(){
    vector<int> test(9);
    int min;
    test = {3, 5, 1, 8, 23, 6 ,34, 75, 25};
    test = minHeapSort(test);
    int length = test.size();
    for (int i = 0 ; i < length; i++){
        min = minHeapExtract(test);
    }
    return 0;
}

template<typename T>
vector<T> minHeapSort(vector<T> &vec){
    vector<T> minHeap;
    for (int i = 0; i < vec.size(); i++){
        minHeap.push_back(vec[i]);

        int j = minHeap.size() - 1, k;
        while (j != 0){
            k = (j - 1) / 2;
            if (minHeap[j] < minHeap[k]) swap(minHeap[j], minHeap[k]);
            j = k;
        }
    }

    return minHeap;
}

template<typename T>
T minHeapExtract(vector<T> &vec){
    T min = vec[0];
    vec[0] = vec[vec.size() - 1];
    vec.pop_back();
    
    int i = 0, j, k;
    while (2 * i + 1 < vec.size()){
        j = 2 * i + 1;
        k = 2 * i + 2;
        if (k < vec.size() && vec[k] < vec[i] && vec[k] < vec[j]){
            swap(vec[i], vec[k]);
            i = k;
        }
        else if (vec[j] < vec[i]){
            swap(vec[i], vec[j]);
            i = j;
        }
        else break;
    }
    cerr << "min: " << min << " vec: ";
    for (int i = 0 ; i < vec.size(); i++){
        cerr << vec[i] << " ";
    }
    cerr << '\n';
    return min;
}