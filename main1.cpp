/*
This program converts Roman Numerals into Modern (Arabic) Numbers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

static int modernM = 1000;
static int modernD = 500;
static int modernC = 100;
static int modernL = 50;
static int modernX = 10;
static int modernV = 5;
static int modernI = 1;

static char romanM = 'M';
static char romanD = 'D';
static char romanC = 'C';
static char romanL = 'L';
static char romanX = 'X';
static char romanV = 'V';
static char romanI = 'I';

static bool TRUE = 1;
static bool FALSE = 0;

/*
Checks to see that the input string is, in fact, a roman numeral.
Valid numerals are M D C L X V I.
*/
bool check_Roman(char* inputArray, int stringLength) {
	bool isRoman = FALSE;

	//Valid numerals are M D C L X V I.
	for (int i = 0; i < stringLength; i++) {
		if ((inputArray[i] == romanM) || (inputArray[i] == romanD) || (inputArray[i] == romanC) || (inputArray[i] == romanL) 
			|| (inputArray[i] == romanX) || (inputArray[i] == romanV) || (inputArray[i] == romanI)) {
			isRoman = TRUE;
		}
		else {
			isRoman = FALSE;
			return isRoman;
		}
	}

	return isRoman;
}

/*
Checks to see that the input string is a valid roman numeral.
M can only be preceeded by M/C
D						by M/C
C						by M/D/C/X
L						by M/D/C/X
X						by M/D/C/L/X/I
V						by M/D/C/L/X/I
I						by M/D/C/L/X/V/I
D, L, and V cannot repeat after themselves.
Numbers that can repeat cannot occur more than 3 times in a row.
Numbers that subtract can only occur once, even if they can otherwise repeat.
CMD, XCL, and IXV are not valid sequences.
Any sequence that subtracts a number and adds it immediately after is invalid.
*/
bool check_Valid_Placement(int* modernArray, int stringLength) {
	bool isValid = FALSE;
	int A = 0;
	int B = 0;
	int DEFAULTCOUNTER = 1;
	int counter = DEFAULTCOUNTER;
	int MAXCOUNT = 4;

	for (int i = 0; i < stringLength; i++) {
		A = modernArray[i];
		B = modernArray[i + 1];

		//D, L, and V cannot repeat after themselves.
		if ((A == B) && ((B == modernV) || (B == modernL) || (B == modernD))) {
			isValid = FALSE;
			return isValid;
		}
		//Numbers that can repeat cannot occur more than 3 times in a row.
		else if (A == B){
			counter += 1;
			if (counter >= MAXCOUNT) {
				isValid = FALSE;
				return isValid;
			}
		}
		//Numbers that subtract can only occur once, even if they can otherwise repeat.
		else if ((A < B) && (counter > DEFAULTCOUNTER)) {
			isValid = FALSE;
			return isValid;
		}
		//CMD is not a valid sequence.
		else if ((A == modernC) && (B == modernM)) {
			if (modernArray[i + 2] == modernD) {
				isValid = FALSE;
				return isValid;
			}
		}
		//XCL is not a valid sequence.
		else if ((A == modernX) && (B == modernC)) {
			if (modernArray[i + 2] == modernL) {
				isValid = FALSE;
				return isValid;
			}
		}
		//IXV is not a valid sequence.
		else if ((A == modernI) && (B == modernX)) {
			if (modernArray[i + 2] == modernV) {
				isValid = FALSE;
				return isValid;
			}
		}
		else {
			counter = DEFAULTCOUNTER;
		}
		
		/*
		M and D can only be preceeded by M / C 
		C and L can only be preceeded by M / D / C / X 
		X and V can only be preceeded by M / D / C / L / X / I 
		I can be preceeded by M / D / C / L / X / V / I
		*/
		if (A >= B) {
			if (A < modernArray[i + 2]) {
				isValid = FALSE;
				return isValid;
			}
			isValid = TRUE;
		}
		else if (A < B) {
			if ((A == modernC) && ((B == modernM) || (B == modernD))) {
				isValid = TRUE;
			}		
			else if ((A == modernX) && ((B == modernC) || (B == modernL))) {
				isValid = TRUE;
			}
			else if ((A == modernI) && ((B == modernX) || (B == modernV))) {
				isValid = TRUE;
			}
			//Anything else is invalid.
			else {
				isValid = FALSE;
				return isValid;
			}
		}

		//Any sequence that subtracts a number and adds it immediately after is invalid.
		if ((modernArray[i + 2] == A) && (B != A) && (A < B)) {
			isValid = FALSE;
			return isValid;
		}
	}
	return isValid;
}

/*
Converts the roman numeral to arabic/modern numbers
M = 1000
D = 500
C = 100
L = 50
X = 10
V = 5
I = 1
*/
int* convert_to_Modern(char* inputArray, int stringLength) {
	int* modernArray = new int[stringLength + 1];

	for (int i = 0; i < stringLength; i++) {
		//M = 1000
		if (inputArray[i] == romanM) {
			modernArray[i] = modernM;
		}
		//D = 500
		else if (inputArray[i] == romanD) {
			modernArray[i] = modernD;
		}
		//C = 100
		else if (inputArray[i] == romanC) {
			modernArray[i] = modernC;
		}
		//L = 50
		else if (inputArray[i] == romanL) {
			modernArray[i] = modernL;
		}
		//X = 10
		else if (inputArray[i] == romanX) {
			modernArray[i] = modernX;
		}
		//V = 5
		else if (inputArray[i] == romanV) {
			modernArray[i] = modernV;
		}
		//I = 1
		else if (inputArray[i] == romanI) {
			modernArray[i] = modernI;
		}
	}

	return modernArray;
}

/*
Adds up all the numbers.
"normal" indicates addition.
If normal is false, it implies subtraction.
*/
int sum_Numbers(int* modernArray, int stringLength) {
	int total = 0;
	int A;
	int B;
	bool normal = TRUE;

	for (int i = 0; i < stringLength; i++) {
		int A = modernArray[i];
		int B = modernArray[i + 1];

		if (A >= B) {
			//The previous function was subtraction, so nothing new is added and normal is reset.
			if (normal == FALSE) {
				normal = TRUE;
			}
			//Addition, normal is true.
			else if (normal == TRUE) {
				total += A;
				normal = TRUE;
			}
		}
		//Subtraction, so normal is set to false.
		else if (A < B) {
			total += (B - A);
			normal = FALSE;
		}
	}
	return total;
}

/*
Interacts with the user, allowing for opportunities to complete further calculations.
*/
int main() {
	string inputString;
	int stringLength = 0;
	int totalSum = 0;
	bool replay = FALSE;
	string quit = "q";

	cout << "Hello, and welcome. I will convert your roman numerals to modern numbers. \n";
	cout << "Please enter a valid roman numeral: ";
	cin >> inputString;

	//Calculates at least one roman numeral, but at the end allows the user to choose whether to continue.
	do {
		stringLength = inputString.length();
		char* inputArray = new char[stringLength + 1];
		strcpy(inputArray, inputString.c_str());

		if (!check_Roman(inputArray, stringLength)) {
			cout << "That is not a roman numeral. Roman numerals contain the values M, D, C, L, X, V, or I.\n";
		}
		else {
			cout << "\nThank you.\n";
			int* modernArray = convert_to_Modern(inputArray, stringLength);

			if (check_Valid_Placement(modernArray, stringLength) == FALSE) {
				cout << "Unfortunately some of the numerals were not in a valid order, or a numeral was repeated too many times.\n";
				cout << "Try checking your entry for a typo.\n";
			}
			else {
				totalSum = sum_Numbers(modernArray, stringLength);
				cout << "The roman numeral \'" << inputString << "\' is equal to " << totalSum << ".\n";
			}
		}

		cout << "\nPlease enter a valid roman numeral (to quit, enter q): ";
		cin >> inputString;

		if (inputString == quit) {
			replay = FALSE;
		}
		else {
			replay = TRUE;
		}
	} while (replay);

	cout << "\nThank you for your participation.\n";

	return 0;
}