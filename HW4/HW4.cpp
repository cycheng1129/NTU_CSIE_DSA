#include <bits/stdc++.h>
using namespace std;

/********** Global Constants **********/
const int MAX = 1e9; // n <= 1e5, 26^6 = 308915776 < 1e9
const int MOD1 = 1e8 + 7;
const int MOD2 = 1e8 + 37;
const int K1 = 3;
const int K2 = 7;

/********** Global Variables **********/
int m; // the total num of a certain substring appears
string str; // input string
int n; // the length of string
// hash values substrings from the begin
vector<pair<uint64_t, uint64_t>> hashBase;
// hash values of substrings in between
vector<pair<uint64_t, uint64_t>> hashValue;
// index used to sort hashValues
vector<int> sorting;
vector<int> possibleLength;
int pos;

/********** Global Functions **********/
uint64_t power(uint64_t x, uint64_t a);
// hash values substrings from the begin
void init(string str);
// hash values of substrings in between
pair<uint64_t, uint64_t> hashBetween(int left, int right);
// 
bool MaxLengthMTimes(int length, int prob);
void samePreSuf();
bool sortCompare(int i, int j);

//========== Program Starts! ==========//
int main(int argc, const char * argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int left, right, mid;
    while(cin >> m){
        if (m == 0) break;
        cin >> str;
        n = str.length();
        init(str);

        // problem 1
        left = 1;
        right = n + 1;
        if(!MaxLengthMTimes(1, 1))
            cout  << "none\n";
        else{ // binary search
            while (right > left){
                mid = left + (right - left) / 2;
                if (MaxLengthMTimes(mid, 1))
                    left = mid + 1;
                else
                    right = mid;
            }
            MaxLengthMTimes(right - 1, 1);
            cout  << right - 1 << " " << pos << '\n';
        }

        // problem 2
        samePreSuf();
        // index in possibleLength
        left = 0;
        right = possibleLength.size();
        //cerr << right << '\n';

        if (right == 0)
            cout << "Just a legend\n";
        
        else {
            while (right > left){
                mid = left + (right - left) / 2;
                //cerr << "BEFORE: " << left << " " << mid << " " << right << '\n';
                //cerr << "Possible length: " << possibleLength[mid] << '\n';
                if (MaxLengthMTimes(possibleLength[mid], 2))
                    left = mid + 1;
                else 
                    right = mid;
                //cerr << "AFTER: " << left << " " << mid << " " << right << '\n';
            }
            if (right - 1 < 0)
                cout << "Just a legend\n";
            else {
                MaxLengthMTimes(possibleLength[right - 1], 2);
                //cerr << "Position: " << pos << '\n';
                for (int i = 0; i < possibleLength[right - 1]; i++){
                    cout << str[i];
                }
                cout << '\n';
            }
        }   
    }
    
    
    return 0;
}

/********** Global Function Definitions **********/
void init(string str){
    hashBase.resize(n);
    hashValue.resize(n);
    sorting.resize(n);
    hashBase[0].first = hashBase[0].second = str[0] - 'a';
    for (int i = 1; i < n; i++){
        hashBase[i].first = hashBase[i - 1].first * K1 + str[i] - 'a';
        hashBase[i].second = hashBase[i - 1].second * K2 + str[i] - 'a';
    }
}

pair<uint64_t, uint64_t> hashBetween(int left, int right){
    if (left == 0)
        return hashBase[right];

    uint64_t fir, sec;
    fir = hashBase[right].first 
        - hashBase[left - 1].first * power(K1, right- left + 1);
    sec = hashBase[right].second 
        - hashBase[left - 1].second * power(K2, right- left + 1);

    return make_pair(fir, sec);
}

bool MaxLengthMTimes(int length, int prob){
    // Problem 1:
    if (prob == 1){
        if (length == n){
            pos = 0;
            return true;
        }

        int count = 0;
        for (int i = 0; i < n - length + 1; i++){
            sorting[i] = i;
            hashValue[i] = hashBetween(i, i + length - 1);
        }

        sort(sorting.begin(), sorting.begin() + n - length + 1, sortCompare);

        pos = -1;
        for (int i = 1; i < n - length + 1; i++){
            if (hashValue[sorting[i]] != hashValue[sorting[i - 1]]) count = 0;
            else {
                count++;
                if (count >= m - 1) pos = max(pos, sorting[i]);
            }
        }

        return pos >= 0;
    }

    // Problem 2:
    else {
        pair<uint64_t, uint64_t> pre = hashBetween(0, length - 1);
        //cerr << "HashValue: " << pre.first << '\n';
        pos = -1;
        for (int i = 1; i < n - length; i++){
            if (hashBetween(i, i + length - 1) == pre)
                pos = max(pos, i);
        }

        return pos > 0;
    }
}

void samePreSuf(){
    possibleLength.clear();
    for (int i = 0; i < n - 2; i++){
        if (hashBetween(0, i) == hashBetween(n - i - 1, n - 1))
            possibleLength.push_back(i+1);
    }
}

bool sortCompare(int i, int j){
    return hashValue[i] < hashValue[j] || (hashValue[i] == hashValue[j] && i < j);
}

uint64_t power(uint64_t x, uint64_t a){
    if (a == 0) return 1;

    uint64_t y;
    if (a % 2) {
        y = power(x, (a - 1) / 2);
        return x*y*y;
    }
    else {
        y = power(x, a / 2);
        return y*y;
    }
}