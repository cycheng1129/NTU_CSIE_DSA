#include <bits/stdc++.h>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> inorderTraversal(TreeNode* root);
void inorder(TreeNode *root, vector<int> &ans);


int main(){
    vector<int> inorderAns;
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    inorderAns = inorderTraversal(root);
    for (int i = 0;i < inorderAns.size(); i++){
        cout << inorderAns[i] << " ";
    }
    cout << '\n';
    
    return 0;
}

// recursive
vector<int> inorderTraversal(TreeNode* root){
        vector<int> ans;
        TreeNode *curr = root;
        if (!curr) return ans;
        inorder(root, ans);
        return ans;
    }
void inorder(TreeNode *root, vector<int> &ans){
    if (root){
        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
}

/*// iterative
vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> procedure;
    vector<int> res;
    while (root != NULL || !procedure.empty()){
        while (root != NULL){
            procedure.push(root);
            root = root -> left;
        }
        root = procedure.top();
        procedure.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}

// Morris Traversal
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;
    TreeNode *curr = root, *nextRoot, *temp;
    while(curr){
        if (!curr->left){
            ans.push_back(curr->val);
            curr = curr->right;
        }
        else{
            nextRoot = curr->left;
            while(nextRoot->right) nextRoot = nextRoot->right;
            nextRoot->right = curr;
            temp = curr;
            curr = curr->left;
            temp->left = NULL;
        }
    }
    return ans;
}*/