#include <iostream>
#include <cstring>
using namespace std;
const int MAX = 2e5;
const int ALPHABET = 26; // There are 26 alphabets

struct node{
    node* parent;
    node* child[ALPHABET];
    int depth;
    node(int x){
        parent = NULL;
        memset(child, 0, ALPHABET);
        depth = x;
    }
};

int main(int argc, const char * argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // build the tree nodes
    int n, l;
    char c;
    cin >> n;
    node *num[MAX];
    num[0] = new node(0);
    for (int i = 1; i <= n; i++){
        cin >> l >> c;
        c -= 'a';
        if (num[l] -> child[c])
            num[i] = num[l] -> child[c];
        else{
            num[i] = num[l] -> child[c] = new node(num[l] -> depth + 1);
            num[i] -> parent = num[l];
        }
    }

    // Answer the questions
    int m, a, b, diffDep;
    cin >> m;
    while(m--){
        cin >> a >> b;
        node *N1 = num[a];
        node *N2 = num[b];
        if (N1->depth < N2->depth)
            swap(N1,N2);
        diffDep = N1 -> depth - N2 -> depth;
        for (int i = diffDep; i > 0; i--){
            N1 = N1 -> parent;
        }
        while (N1 != NULL){
            if (N1 == N2){
                cout << N1 -> depth << endl;
                break;
            }
            N1 = N1 -> parent;
            N2 = N2 -> parent;
        }
        if (N1 == NULL)
            cout << 0 << endl;
    }

    return 0;
}