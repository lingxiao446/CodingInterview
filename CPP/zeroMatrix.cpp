
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void zeroMatrix(vector<vector<int>>&);
void zeroMatrix_1(vector<vector<int>>&);
void printItem(const vector<vector<int>>&);

int main()
{
    vector<vector<int>> matrix{{1, 2, 3, 4}, {0, 1, 2, 3}, {4, 5, 0, 6}};

    cout<<"before:"<<endl;
    printItem(matrix);
    
    zeroMatrix(matrix);
    
    cout<<"after:"<<endl;
    printItem(matrix);


    vector<vector<int>> matrix_1{{1, 2, 3, 4, 5}, {0, 1, 2, 3, 9}, {4, 5, 0, 6, 8}};

    cout<<"before:"<<endl;
    printItem(matrix_1);
    
    zeroMatrix_1(matrix_1);
    
    cout<<"after:"<<endl;
    printItem(matrix_1);


    return 0;
}

/*
  Function: if the element value is 0, set the elements that the same row and same column to 0.
  For example:
  Originnal matrix:
  1 2 3 4 5
  0 1 2 3 6
  6 6 7 0 9
  After:
  0 2 3 0 5
  0 0 0 0 0
  0 0 0 0 0
*/
void zeroMatrix(vector<vector<int>>&matrix)
{
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    int row = matrix.size(), col = matrix[0].size();

    vector<pair<int, int>> zeroVec;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == 0) {
                zeroVec.push_back({i, j});
            }
        }
    }

    for (const auto &e: zeroVec) {
        for (int i = 0; i < row; i++) {
            matrix[i][e.second] = 0;
        }

        for (int j = 0; j < col; j++) {
            matrix[e.first][j] = 0;
        }
    }

}

/*
  Note: compare with zeroMatrix(), 
    using set<> to save the position that needs to be reset to zero, there are not duplicated reset action.
*/
void zeroMatrix_1(vector<vector<int>>&matrix)
{
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    int row = matrix.size(), col = matrix[0].size();

    set<int> zeroRow;
    set<int> zeroCol;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == 0) {
                zeroRow.insert(i);
                zeroCol.insert(j);
            }
        }
    }

    for (const auto &e: zeroRow) {
        for (int j = 0; j < col; j++) {
            matrix[e][j] = 0;
        }
    }

    for (const auto &e: zeroCol) {
        for (int i = 0; i < row; i++) {
            matrix[i][e] = 0;
        }
    }
    
}

void printItem(const vector<vector<int>>& vecs)
{
    if (vecs.empty() || vecs[0].empty()) {
        return;
    }

    int row = vecs.size(), col = vecs[0].size();
    for (int i = 0; i < row; i++){
        for ( int j = 0; j < col; j++) {
            cout<<vecs[i][j]<<" ";
        }
        cout<<endl;
    }

}



