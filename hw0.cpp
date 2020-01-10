#include <iostream>
#include<vector>
using namespace std;

void printMat1(vector<vector<double>> mat){
    int order = mat.size();
    for (int i = 0; i < order; i++){
        for (int j = 0; j < order; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void printMat2(vector<vector<double>> mat){
    int order = mat.size();
    for (int i = 0; i < order; i++){
        for (int j = order; j < 2 * order; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    double divide;
    vector<vector<double>> mat, matOrigin;
    cout << "What's the matrix (n*n) size? (n=?)" << endl;
    cin >> n;
    mat.resize(n);
    cout << "Enter the value of each element." << endl;
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
    matOrigin = mat;
    printMat1(matOrigin);
    cout << endl;

    /************** partial pivoting **************/
    for (int i = n-1; i > 0; i--){
        if (mat[i][0] > mat[i-1][0]){
            for (int j = 0; j < 2*n; j++){
                double temp = mat[i - 1][j];
                mat[i - 1][j] = mat[i][j];
                mat[i][j] = temp;
            }
        }
    }

    /********** reducing to diagonal  matrix ***********/
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j){
                divide = mat[j][i] / mat[i][i];
                for (int k = 0; k < 2 * n; k++){
                    mat[j][k] -= mat[i][k] * divide;
                }
            }
        }
    }

    /************** reducing to unit matrix *************/
    for (int i = 0; i < n; i++){
        for (int j = n; j < 2 * n; j++){
            mat[i][j] /= mat[i][i];
        }
    }

    printMat2(mat);
    cout << endl;

    /************** multiply ******************/
    double max = 0;
    double error;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            error = 0;
            if (i == j)
                error -= 1;
            for (int k = 0; k < n; k++){
                error += matOrigin[i][k] * mat[k][j + n];
            }
            cout << error << " ";
        }
        cout << endl;
        if (abs(error) > max)
            max = abs(error);
    }
    cout << max;

    system("pause");
    return 0;
}
