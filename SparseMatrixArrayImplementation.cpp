#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> convertToSparseMatrix(int rows, int cols, vector<vector<int>>& matrix) {
    vector<vector<int>> sparseMatrix;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != 0) {
                vector<int> entry = { i, j, matrix[i][j] };
                sparseMatrix.push_back(entry);
            }
        }
    }

    return sparseMatrix;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows in the matrix: ";
    cin >> rows;
    cout << "Enter the number of columns in the matrix: ";
    cin >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    cout << "Enter the elements of the matrix row by row:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<int>> sparseMatrix = convertToSparseMatrix(rows, cols, matrix);

    cout << "Sparse Matrix representation:" << endl;
    cout << "Row Column Value" << endl;
    for (const auto& entry : sparseMatrix) {
        cout << entry[0] << " " << entry[1] << " " << entry[2] << endl;
    }

    return 0;
}
