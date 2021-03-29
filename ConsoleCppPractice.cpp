// Written in C++

/*
	Version 1.0

	Last Revised 2/8/2021
	Author VisualPower

	Contact: geckoplayz4@gmail.com
*/

#include <iostream>				// Using iostream because this header file has cout/cin.
#include <string>				// This is not only a calculator but a playground for code so using this header file to include sentence capability.

using namespace std;            // Tells computer the code for cout etc.

int main()						// Code goes in this container and can be ended by using return 0 only if int main() is used.
{
	// Sentence

	string MySring = "Made by VisualPower";     // Using the string header file as a variable.

	// Calculator made in one project

	double sum1, sum2, result;  // Using double because it can hold values upto 15 - 15.
	char op;					// Assigning operator to a "character" - type variable.
	
	cout << "\nCalculator - Enter a number: ";	  // Cout asking for a number to work with.
	cin >> sum1;                                  // Enter a number at will.
	cout << "Enter a operator: ";				  // Cout asking for a operator to apply on the numbers.	
	cin >> op;									  // Enter a operator at will.
	cout << "Enter another number: ";			  // Cout asking for another number to work with.
	cin >> sum2;								  // Enter another number at will.

	if (op == '+') result = sum1 + sum2;		  // If operator + is instered then perform the operation "+".
	if (op == '-') result = sum1 - sum2;		  // If operator - is instered then perform the operation "-".
	if (op == '*') result = sum1 * sum2;		  // If operator * is instered then perform the operation "*".
	if (op == '/') result = sum1 / sum2;		  // If operator / is instered then perform the operation "/".

	cout << result;                               // Cout will put out the result.

	// Formula Practice Conversion of Mins = Secs

		int mins, secs;							  // Defines and gives a life to mines/secs.

		cout << "Enter minutes: ";				  // Cout will ask for mins.	
		cin >> mins;							  // Enter minutes.

		secs = mins * 60;						  // Formula for seconds conversion.
		mins = secs % 60;						  // Formula for minutes conversion.

		cout << secs << " seconds ";			  // Cout will present the answer.	

		// Basic mathematic operations on variables using cout.

		double Value = 1000; double Value2 = 2000;    // Testing double values and storing 64Bit vals.
		double Value3 = 3000; double Value4 = 120541; // Testing double values and storing 64Bit vals.
			
		cout << Value + Value2 / 5;					  // Addition,Division	
		cout << Value + Value2 + 2 / Value3 + 500 / 2 + Value4 + 500 / 100; // Addition,Division
		cout << Value + Value2 * 5 / 5 + 2 / 1 + 1000 * 2 / 1000; // Addition,Division, Multiplication
		cout << Value + Value2; // Adding two values

		// Making Inputs and Outputs

		string Name = "Rayyan Raza";              // Making a string variable to assign a text value.
		int Age = 14;							  // Making a int variable to assign a number value.

		cout << "My Name is: " + Name << endl;    // Will give an Output of My name. 
		cout << "My Age is: " + Age << endl;      // Will give an Output of My age.

		cout << "GitHud gittgore" << endl;       // Will give an Output of the strings.


		cout << MySring;                          // Credit.

	return 0;                                     // Teminate the program and stop it.

}