#include <iostream>
#include<vector>
using namespace std;

void printMat(vector<vector<double>> mat){
    int order = mat.size();
    for (int i = 0; i < order; i++){
        for (int j = 0; j < 2 * order; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void becomeOne(vector<double> &row, int col){
    int divide = row[col];
    for (int i = 0; i < row.size(); i++){
        row[i] = row[i] / divide;
    }
}

void becomeZero(vector<vector<double>> &mat, int col){
    for (int i = 0; i < mat[0].size(); i++){
        int multiply;
    }
}

int main(){
    int n;
    vector<vector<double>> mat;
    cin >> n;
    mat.resize(n);
    for (int i = 0; i < n; i++){
        mat[i].resize(n*2);
        for (int j = 0; j < n; j++){
            cin >> mat[i][j];
            if (j==i)
                mat[i][j + n] = 1;
            else
                mat[i][j + n] = 0;
        }
    }
    printMat(mat);

    system("pause");
    return 0;
}
