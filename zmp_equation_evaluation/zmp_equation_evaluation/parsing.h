#pragma once
//This file defines the functions to parse the equations into a matrix

#include <iostream>
#include <string>
#include <sstream>

//In our exercice we suppose that we know the size of the equation : 3 
//We will parse the equation into a size 4 vector
#define N 3
using namespace std;

//The following functions will act on the stream to parse it into the information we need

//function to suppress the spaces
string erase_space(string sentence);
//function to suppress the * sign
string erase_mult(string sentence);
//function to return the left side of the equation
string left_side(string eq, char sign);
//function to return the right side of the equation
string right_side(string eq, char sign);
//this function finds the factor before a given variable and returns it as a double
double factor_isolation(char x, string text);
//this function find the factor of all the repetition of the given variable
double global_factor_isolation(char x, string text);
//this function find the factor of the first repetion of the given variable and erase the variable and factor
double factor_isolation_erasing(char x, string& text);
// this function erase variable and factors while storing the global factor of the given variable
double global_factor_isolation_erasing(char x, string& text);
//function to add up the constant remainind term
double constant_add(string& text);
//this function erase the constant while storing their sum 
double global_constant_add(string& text);

/*finally we need to write a function wich will fill a matrix using the previous function and the user input
We made several hypothesis :
The user is using the following variables : x, y and z.
The equation contains only + and - signs and can contain space
The equation must contain a = sign
The equation can contain repetitions of a variable or constant term
*/
void matrix_gen(double(&my_mat)[N][N + 1]);
//we add a function to print the matrix
void print_mat(double(&my_mat)[N][N + 1]);

