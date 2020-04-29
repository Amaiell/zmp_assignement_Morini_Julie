// zmp_equation_evaluation.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <sstream>
//The parsing file contains all the function we created to realize parsing
#include "parsing.h"
using namespace std;

//We are making the hypothesis that the size of the system of equations is predefined and fixed. Here we chose N=3
#define N 3

//Moreover we chose to treat the problem using gaussian elimination. Hence the function needed to perform gaussian elimination are written as follow

//functions declarations :

//function to make matrix into row echelon form
//1 checking singularity
int singular_ref(double matrix[N][N + 1]);

//2 function to calculate the values of each variable when matrix is in row echelon form
void back_substitution(double matrix[N][N + 1]);

//3 function to test the matrix solavability/state
void gaussian_elimination(double matrix[N][N + 1])
{
    //transformation into row echelon form
    int singular_flag = singular_ref(matrix);

    //if singular:
    if (singular_flag != -1)
    {
        printf("Error :.\n");
        //matrice may have 0 on the diagonal, system may have infinite solutions or be inconsistant
        if (matrix[singular_flag][N])
        {
            printf("Inconsistent system.");
        }
        else
        {
            printf("May have inite number of solutions.");
        }
        return;
    }
    //In other cases the system is solvable and we can perform backward substitution
    back_substitution(matrix);
}

//function to swap two rows
void swap_row(double matrix[N][N+1], int i, int j)
{
    for (int n = 0; n <= N; n++)
    {
        double inter = matrix[i][n]; //temporarly storing the swapping line (ith line) value
        matrix[i][n] = matrix[j][n]; //puting the jth line value into ithline
        matrix[j][n] = inter;//putting the stored ith line value into jth line

    }
}


//function to make matrix into row echelon form
int singular_ref(double matrix[N][N + 1])
{
    for (int k = 0; k < N; k++) //we will perform pivot around all the diagonal element, hence N operations
    {
        //index for pivot
        int i_max = k;
        double value_max = matrix[i_max][k];

        //looking for greater values : before performaing pivot we ensure that the pivot vaue we have is the greatest 
       for (int i = k + 1; i < N; i++)
        {
            if (abs(matrix[i][k]) > value_max)
            {
                value_max = matrix[i][k];
                i_max = i;
            }
        }
        //testing i a diagonal element is 0 to indicate singularity
        if (!matrix[k][i_max])
            return k; //singular
        //swap the greatest value row with current row
        if (i_max != k)
        {
            swap_row(matrix, k, i_max);
        }
        for (int i = k + 1; i < N; i++)//as we proceed the column under the [k][k]elements are setted to 0 so we can examinate only element of column indices greater than k
        {
            //calculate the factor to make make current row kth element to 0
            double f = matrix[i][k] / matrix[k][k];
            //substract the the multiplied kth row element to all the ith row elements
            for (int n = k + 1; n <= N; n++)
            {
                matrix[i][n] -= matrix[k][n] * f;
            }
            //setting to 0 the kth element we targeted
            matrix[i][k] = 0;
        }
    }
    return -1;
}

//function to perform the back substitution en hence calculate the variable values
void back_substitution(double matrix[N][N + 1])
{
    double solution[N]; //array storing solution
    //starting from the bottom
    for (int i = N - 1; i >= 0; i--)
     {
        solution[i] = matrix[i][N];
        //going only  through the upper triangular part of the matrix
        for (int j = i + 1; j < N; j++)
        {
            solution[i] -= matrix[i][j] * solution[j]; //subtracting the left values
        }
        solution[i] = solution[i] / matrix[i][i];
     }
    printf("solution :\n");
   // for (int j = 0; j < N; j++)
   // {
        printf("x = %lf\n", solution[0]);
        printf("y = %lf\n", solution[1]);
        printf("z = %lf\n", solution[2]);
   // }
}

int main()
{
    /*
    We made several hypothesis concerning the user input :
    The user is using the following variables : x, y and z.
    The equation contains only + and - signs and can contain space
    The equation must contain a = sign
    The equation can contain repetitions of a variable or constant term
    */
    cout << "Let' solve systems of 3 equations !\nPlease enter the equations using the variable names : 'x', 'y' and 'z'\nPlease, use only '-', '+' and '=' signs\n";
   //Initilazing a matrix to store the equations factors values
    double my_mat[N][N+1];
    char user;
    //storing the factors of each variable for each equations into the matrix
    matrix_gen(my_mat);
    //Just in case if user wants to check what the matrix looks like
    cout << "Do you want to vizualize the matrix corresponding to your equation system?  ('Y' or 'N')\n";
    cin >> user;
    if (user == 'Y')
    {
        print_mat(my_mat);
        cout << "\n";
    }
    //solving the system and printing the solutions
    gaussian_elimination(my_mat);
}



// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー


