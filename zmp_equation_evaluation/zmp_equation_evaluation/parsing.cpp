// parsing_training.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//This file defines the functions to parse the equations into a matrix

#include <iostream>
#include <string>
#include <sstream>
#include "parsing.h"

//In our exercice we suppose that we know the size of the equation : 3 
//We will parse the equation into a size 4 vector
#define N 3
using namespace std;

//The following functions will act on the stream to parse it into the information we need

//function to suppress the spaces
string erase_space(string sentence)
{
	if (sentence.find(' ') == string::npos)
	{
		return sentence;
	}
	else if (sentence.find(' ') != string::npos)
	{
		return(sentence.substr(0, sentence.find(' ')) + erase_space(sentence.substr(sentence.find(' ') + 1, sentence.length())));
	}

}
//function to return the left side of the equation
string left_side(string eq, char sign)
{
	return eq.substr(0, eq.find(sign));
}
//function to return the right side of the equation
string right_side(string eq, char sign)
{
	return eq.substr(eq.find(sign) + 1, eq.length());
}
//this function finds the factor before a given variable and returns it as a double
double factor_isolation(char x, string text)
{
	if (text.find(x) == string::npos)
	{
		return 0;
	}
	else
	{
		//if we find the character, we focus on the previous part
		string previous = left_side(text, x);
		//if the left part is empty, it means the variable is on the top of the ligne with no factor neither sign
		if (previous == "")
		{
			return 1;
		}
		else
		{
			int addpos, subpos;

			//necessarry to assert the colsest previsous sign position before because if none is associated npos which has a value of 577784784
			if (previous.rfind('+') == string::npos)
			{
				addpos = -1;
			}
			//if the + sign is just before : the coeff is 1
			else if (previous.rfind('+') == previous.length() - 1)
			{
				return 1;
			}
			else
			{
				addpos = previous.rfind('+');
			}
			if (previous.rfind('-') == string::npos)
			{
				subpos = -1;
			}
			//if the + sign is just before : the coeff is -1
			else if (previous.rfind('-') == previous.length() - 1)
			{
				return -1;
			}
			else
			{
				subpos = previous.rfind('-');
			}
			//if there is no sign before it means the factor is positive on top of the line
			if (addpos == subpos)
			{
				return stod(previous);
			}
			//if the closest sign is a + we add the factor
			else if (addpos > subpos)
			{
				string factor = previous.substr(addpos + 1, previous.length());
				return stod(factor);
			}
			//if the closest sign is a - we substract the factor
			else
			{
				string factor = previous.substr(subpos + 1, previous.length());
				return -stod(factor);
			}
		}
	}

}
//this function find the factor of all the repetition of the given variable
double global_factor_isolation(char x, string text)
{
	if (factor_isolation(x, text) == 0)
	{
		return 0;
	}
	else
	{
		return(factor_isolation(x, text) + global_factor_isolation(x, text.substr(text.find(x) + 1, text.length())));
	}

}
//this function find the factor of the first repetion of the given variable and erase the variable and factor
double factor_isolation_erasing(char x, string& text)
{
	if (text.find(x) == string::npos)
	{
		return 0;
	}
	else
	{
		//if we find the character, we focus on the previous part
		string previous = left_side(text, x);
		string next = right_side(text, x);
		//if the left part is empty, it means the variable is on the top of the ligne with no factor neither sign
		if (previous == "")
		{
			text = next;
			return 1;
		}
		else
		{
			int addpos, subpos;

			//necessarry to assert the colsest previsous sign position before because if none is associated npos which has a value of 577784784
			//if there is no + sign
			if (previous.rfind('+') == string::npos)
			{
				addpos = -1;
			}
			//if the + sign is just before : the coeff is 1
			else if (previous.rfind('+') == previous.length() - 1)
			{
				text = previous.erase(previous.length() - 1) + next;
				return 1;
			}
			else
			{
				addpos = previous.rfind('+');
			}
			//if there is no - sign
			if (previous.rfind('-') == string::npos)
			{
				subpos = -1;
			}
			//if the - sign is just before : the coeff is -1
			else if (previous.rfind('-') == previous.length() - 1)
			{
				text = previous.erase(previous.length() - 1) + next;
				return -1;
			}
			else
			{
				subpos = previous.rfind('-');
			}
			//if there is no sign before it means the factor is positive on top of the line
			if (addpos == subpos)
			{
				text = next;
				return stod(previous);
			}
			//if the closest sign is a + we add the factor
			else if (addpos > subpos)
			{
				string factor = previous.substr(addpos + 1, previous.length());
				text = previous.erase(addpos, previous.length()) + next;
				return stod(factor);
			}
			//if the closest sign is a - we substract the factor
			else
			{
				string factor = previous.substr(subpos + 1, previous.length());
				text = previous.erase(subpos, previous.length()) + next;
				return -stod(factor);
			}
		}
	}
}
// this function erase variable and factors while storing the global factor of the given variable
double global_factor_isolation_erasing(char x, string& text)
{
	if (factor_isolation(x, text) == 0)
	{
		return 0;
	}
	else
	{
		return(factor_isolation_erasing(x, text) + global_factor_isolation_erasing(x, text));
	}

}
//function to add up the constant remainind term
double constant_add(string& text)
{
	//if the text is empty , we finished
	if (text == "")
	{
		return 0;
	}
	//if the text doesn't contain any sign : we have a positive constant remaining
	else if ((text.find('+') == string::npos) && (text.find('-') == string::npos))
	{
		//we need to erase the last term but store value before. c is the name of the storing variabl standing for constant
		double c = stod(text);
		text = "";
		return c;
	}
	//if there is at least one + sign remaining (we arbitrary decide to treat positive constant first)
	else if (text.find('+') != string::npos)
	{
		int addpos = text.find('+');
		string right = right_side(text, '+');
		//we need to know more about the right side 
		//if there is no sign remaining we take the right side as the constant to add
		if ((right.find('+') == string::npos) && (right.find('-') == string::npos))
		{
			text = left_side(text, '+');
			return stod(right);
		}
		//if there are sign remaining in the right part, we have to understand if the next one is a - or a +, for this we find position of next + and -
		int nextaddpos;
		int nextsubpos;
		int nextpos;
		if (right.find('+') == string::npos)
		{
			nextaddpos = -1;
		}
		else
		{
			nextaddpos = right.find('+');
		}
		if (right.find('-') == string::npos)
		{
			nextsubpos = -1;
		}
		else
		{
			nextsubpos = right.find('-');
		}
		// then act differently depending on their position:
		if (nextaddpos > nextsubpos)
		{
			nextpos = nextaddpos;
		}
		else
		{
			nextpos = nextsubpos;
		}
		//we deternined the position of the next sign in the right part. we need to return the number between the two signs 
		string c = right.substr(0, nextpos - 1);
		text = text.substr(0, addpos - 1) + right.substr(nextpos - 1, right.length());
		return stod(c);
	}
	//if there is no + remaining but at least one - remaining
	else if (text.find('-') != string::npos)
	{
		int subpos = text.find('-');
		string right = right_side(text, '-');
		//we need to know more about the right side 
		//if there is no sign remaining we take the right side as the constant to add
		if ((right.find('+') == string::npos) && (right.find('-') == string::npos))
		{
			text = left_side(text, '-');
			return -stod(right);
		}
		//if there are sign remaining in the right part, it should be a - beacause we treated all the + in priority
		int nextpos = right.find('-');
		//we deternined the position of the next sign in the right part. we need to return the number between the two signs 
		string c = right.substr(0, nextpos - 1);
		text = text.substr(0, subpos - 1) + right.substr(nextpos - 1, right.length());
		return -stod(c);
	}
}
//this function erase the constant while storing their sum 
double global_constant_add(string& text)
{
	double sum = constant_add(text);//we have to store this value because calling the function several time would erase the text
	if (sum == 0)
	{
		return 0;
	}
	else
	{
		return(sum + global_constant_add(text));
	}

}

/*finally we need to write a function wich will fill a matrix using the previous function and the user input
We made several hypothesis :
The user is using the following variables : x, y and z.
The equation contains only + and - signs and can contain space
The equation must contain a = sign
The equation can contain repetitions of a variable or constant term
*/
void matrix_gen(double(&my_mat)[N][N + 1])
{
	string my_eq;
	for (int i = 0; i < N; i++)
	{
		cout << "Please write the "<<i+1<<"th equation :" << endl;
		getline(cin, my_eq);
		my_eq = erase_space(my_eq);
		string left = left_side(my_eq, '=');
		string right = right_side(my_eq, '=');
		//cout << "Without space the equation is:" << my_eq << endl;
		my_mat[i][0] = global_factor_isolation_erasing('x', left) - global_factor_isolation_erasing('x', right);
		//cout << "essai X The factor of x is:" << my_mat[i][0] << "\nThe equation without x is :" << left + '=' + right << endl;
		my_mat[i][1] = global_factor_isolation_erasing('y', left) - global_factor_isolation_erasing('y', right);
		//cout << "essai Y The factor of y is:" << my_mat[i][1] << "\nThe equation without x is :" << left + '=' + right << endl;
		my_mat[i][2] = global_factor_isolation_erasing('z', left) - global_factor_isolation_erasing('z', right);
		//cout << "essai Z The factor of z is:" << my_mat[i][2] << "\nThe equation without x is :" << left + '=' + right << endl;
		my_mat[i][3] = global_constant_add(right) - global_constant_add(left);
		//cout << "essai C The constant is:" << my_mat[i][3] << "\nThe equation without constant is :" << left + '=' + right << endl;
	}
}
//we add a function to print the matrix
void print_mat(double(&my_mat)[N][N + 1])
{
	for (int j = 0; j < N; j++)
	{
		cout << "[";
		for (int i = 0; i < N + 1; i++)
		{
			cout << my_mat[j][i] << " ";
		}
		cout << "]\n";
	}
}


