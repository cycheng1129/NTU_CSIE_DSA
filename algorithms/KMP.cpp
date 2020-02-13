#include <bits/stdc++.h>
using namespace std;

void prefixTable(string pattern, int prefix[], int n);
int KMP(string text, string pattern);

int main(){
    string text = "BACABCAAABABCABAA";
    string pattern = "ABABCABAA";
    int index = KMP(text, pattern);
    cout << index << '\n';

    return 0;
}

void prefixTable(string pattern, int prefix[], int n){
    prefix[0] = 0;
    int len = 0, i = 1;
    while (i < n){
        if (pattern[i] == pattern[len]){
            len++;
            prefix[i] = len;
            i++;
        }
        else {
            if (len > 0) len = prefix[len - 1];
            else {
                prefix[i] = len;
                i++;
            }
        }
    }
    for (int i = n - 1; i > 0; i--)
        prefix[i] = prefix[i - 1];
    prefix[0] = -1;
}
    
int KMP(string text, string pattern){
    int m = text.length(), n = pattern.length();
    if (n == 0) return 0;
    int i = 0, j = 0, prefix[n];
    prefixTable(pattern, prefix, n);
        
        // text[i], len = m
        // pattern[j], len = n
    while (i < m){
        if (j == n - 1 && text[i] == pattern[j]){
            return i - j;
            // if continue search:
            j = prefix[j];
        }
        if (text[i] == pattern[j]){
            i++;
            j++;
        }
        else {
            j = prefix[j];
            if (j == -1){
                i++;
                j++;
            }
        }        
    }
    return -1;
}