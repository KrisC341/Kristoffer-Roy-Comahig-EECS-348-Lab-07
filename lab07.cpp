#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//COMMENT: Completed this lab before the updates were dropped. This program was made with the matrix class utilizing stl::vectors and the input file having the
//size of the matrix being the first line of text.

const int mSIZE = 4;
static streampos currentPosition;

class Matrix {
    public:
       
    void matrixLoad(string filePath) { 
        static int firstCheck = 0;
        ifstream inputFile(filePath);
    
        int N;
        inputFile >> N; // Read the size of the matrix
        
        
        // Create a 2D vector to store the matrix
        vector<vector<int>> tempMatrix(mSIZE, vector<int>(mSIZE)); // Initialize with size N x N

        if(firstCheck != 0){
            inputFile.seekg(currentPosition);
        }


        for(int i = 0; i < mSIZE; i++){
            for(int j = 0; j < mSIZE; j++){
                    inputFile >> tempMatrix[i][j]; // Read directly into the matrix

            }
            
        }

        if(firstCheck == 0){
            firstCheck = 1;
            currentPosition = inputFile.tellg();
        }

        size = N;
        matrix = tempMatrix;
    }

    Matrix operator+(Matrix const& obj){
        Matrix res;
        res.size = size; // Set size of the result matrix
        res.matrix.resize(size, vector<int>(size)); // Resize the result matrix

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                res.matrix[i][j] = matrix[i][j] + obj.matrix[i][j];
            };
        };

        return res;
    }

    Matrix operator*(Matrix const& obj){
        Matrix res;
        res.size = size; // Set size of the result matrix
        res.matrix.resize(size, vector<int>(size, 0)); // Resize the result matrix

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) { 
                for(int k = 0; k < size; k++){
                    res.matrix[i][j] += matrix[i][k] * obj.matrix[k][j];
                    //cout << "Multiplying: " << matrix[i][k] << " * " << obj.matrix[k][j] << " -> res[" << i << "][" << j << "]" << endl;
                }
            }
        }

        return res;
    }

    void printMatrix(){
        cout << "------------------------------" << endl;
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << "------------------------------" << endl;
    }

    int swapRows(int indice1, int indice2) {

        if((indice1 < mSIZE) && (indice2 < mSIZE) && (indice1 >= 0) && (indice2 >= 0)){
            matrix[indice1].swap(matrix[indice2]);
        }
        else {
            std::cout << "Invalid indices. Please try again" << std::endl;
            return 0;
        }

        return 1;
}


    vector<vector<int>> matrix;

    vector<vector<int>> retrieveMatrix(){
        return matrix;
    }

    int retrieveSize(){
        return size;
    }

    void diagonalSum() {
        int mainSum = 0;
        for(int i = 0; i < mSIZE; i++) {
            mainSum += matrix[i][i];
        }

        int secondarySum = 0;
        for(int i = 0; i < mSIZE; i++) {
            secondarySum += matrix[i][mSIZE - i - 1];
        }

        std::cout << "Main diagonal: " << mainSum << std::endl;
        std::cout << "Secondary diagonal: " << secondarySum << std::endl;
    }

    private:
    int size; 
};


int main(){

    Matrix test1;
    test1.matrixLoad("input.txt");
    test1.printMatrix();

    Matrix test2;
    test2.matrixLoad("input.txt");
    test2.printMatrix();

    Matrix test3 = test1 + test2;
    std::cout << "Matrix Sum: " << endl;
    test3.printMatrix();

    Matrix test4 = test1 * test2;
    std::cout << "Matrix Multiplication: " << endl;
    test4.printMatrix();

    test1.swapRows(1, 3);
    std::cout << "Matrix 1 after swapping rows: " << endl;
    test1.printMatrix();

    std::cout << "Diagonal Sums of Matrix 1: " << endl;
    test1.diagonalSum();

    return 0;
}




