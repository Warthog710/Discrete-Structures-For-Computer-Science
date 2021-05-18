//Code written by Quinn Roemer, based on code by Professor Ross. 10/23/2018

#include <iostream>
#include <fstream>

using namespace std;

//Definitions
#define MAX 40

//Global data.
int squaredRelation[MAX][MAX];
int eClasses[MAX] = { 0 };
int relations[MAX][MAX];
int eCheck[3] = { 0 };
int mSize = 9;

//Function prototypes.
void printMatrix(bool);
void squareMatrix();
void equivClasses();
void printClasses();
void transitive();
void reflexive();
void readFile();
void symmetry();

//Main function to execute.
int main()
{
	readFile();

	cout << "Matrix:" << endl;
	printMatrix(true);
	squareMatrix();

	cout << "\nSquared Matrix:" << endl;
	printMatrix(false);
	cout << endl;

	reflexive();
	symmetry();
	transitive();

	//If the matrix represents an Equivalence Relation this code executes.
	if (eCheck[0] == 1 && eCheck[1] == 1 && eCheck[2] == 1)
	{
		cout << "\nEquiv Classes:" << endl;

		equivClasses();
		printClasses();
	}
}

//This function reads a matrix from a file.
void readFile()
{
	char value;

	//Opening file.
	ifstream file("R7.bin", ios_base::binary);

	//Checking to see if the file opened correctly.
	if (!file)
	{
		cerr << "Input file could not be opened." << endl;
		exit(1);
	}

	//Getting the matrix size.
	file.read(&value, 1);
	mSize = value;

	//Filling the matrix from the file.
	for (int count = 0; count < mSize; count++)
	{
		for (int index = 0; index < mSize; index++)
		{
			file.read(&value, 1);
			relations[count][index] = value;
		}
	}

	//Close the file.
	file.close();	
}

//This function prints the matrix.
void printMatrix(bool flag)
{
	//Note, the flag determines if the square or reg relation is to be printed.

	if (flag == true)
	{
		for (int count = 0; count < mSize; count++)
		{

			for (int index = 0; index < mSize; index++)
			{
				cout << relations[count][index] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		for (int count = 0; count < mSize; count++)
		{

			for (int index = 0; index < mSize; index++)
			{
				cout << squaredRelation[count][index] << " ";
			}
			cout << endl;
		}
	}
}

//This function checks a matrix for reflexivity.
void reflexive()
{
	for (int count = 0; count < mSize; count++)
	{
		if (relations[count][count] != 1)
		{
			cout << "This relation is NOT reflexive." << endl;
			return;
		}
	}

	cout << "This relation is reflexive." << endl;
	eCheck[0] = 1;
}

//This function checks a matrix for symmetry.
void symmetry()
{
	for (int count = 0; count < mSize; count++)
	{
		for (int index = 0; index < mSize; index++)
		{
			if (relations[count][index] == 1)
			{
				if (relations[index][count] != 1)
				{
					cout << "This relation is NOT symmetric." << endl;
					return;
				}
			}
		}
	}

	cout << "This relation is symmetric." << endl;
	eCheck[1] = 1;
}

//This function checks a matrix for transivity.
void transitive()
{
	//Comparing the relation against its square.
	for (int count = 0; count < mSize; count++)
	{
		for (int index = 0; index < mSize; index++)
		{
			if (squaredRelation[count][index] >= 1)
			{
				if (relations[count][index] == 0)
				{
					cout << "This relation is NOT transitive." << endl;
					return;
				}
			}
		}
	}

	cout << "This relation is transitive" << endl;
	eCheck[2] = 1;
}

//This function squares a matrix.
void squareMatrix()
{
	int sum = 0;

	//This loop keeps track of the row.
	for (int count = 0; count < mSize; count++)
	{
		//This loop keeps track of the column.
		for (int index = 0; index < mSize; index++)
		{
			//This loop iterates through all numbers on a row or column.
			for (int num = 0; num < mSize; num++)
			{
				sum = sum + (relations[count][num] * relations[num][index]);
			}

			//Saving and resetting the necessary values.
			squaredRelation[count][index] = sum;
			sum = 0;
		}
	}
}

//This function finds the equivalence classes of an ER relation.
void equivClasses()
{
	/*For debugging purposes.
	cout << "\nMatrix:" << endl;
	printMatrix(true);
	cout << endl;*/

	for (int count = 0; count < mSize; count++)
	{
		for (int index = count; index >= 0; index--)
		{
			//For debugging purposes.
			//cout << relations[count][index] << " ";

			//If the value currently being looked is 1 this code executes.
			if (relations[count][index] == 1)
			{
				//Setting the correct captain.
				eClasses[index] = 1;

				//This code look back to the beginning of the iteration and resets the captains in
				//front of the current captain.
				for (int number = count; number > index; number--)
				{
					if (relations[count][number] == 1)
					{
						eClasses[number] = 0;
					}
				}
			}
		}
	}
}

//This function prints the equivalence classes of a given ER relation.
void printClasses()
{
	for (int count = 0; count < mSize; count++)
	{
		if (eClasses[count] == 1)
		{
			cout << "[" << count << "] = { ";

			for (int index = 0; index < mSize; index++)
			{
				if (relations[count][index] == 1)
				{
					cout << index << ", ";
				}
			}
			cout << "}" << endl;
		}
	}
}