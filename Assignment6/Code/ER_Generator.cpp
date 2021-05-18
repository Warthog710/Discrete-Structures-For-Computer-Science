//Code written by Quinn Roemer 10/23/2018

#include <iostream>
#include <time.h>

using namespace std;

//Definitions.
#define MAX 40

//Global Data.
int eClasses[MAX][MAX] = { 0 };
int relation[MAX][MAX] = { 0 };
int equivSize[MAX] = { 0 };
int mSize;
int ecNum;

//Function prototypes.
void fillRelation();
void printClasses();
void printMatrix();
void erGen();

//Main function to execute.
int main()
{
	//Intilize a random seed.
	srand(time(NULL));

	//Generate equivalence classes and relation.
	erGen();
	fillRelation();

	//Print the matrix.
	cout << "Matrix:" << endl;
	printMatrix();

	//Print the size.
	cout << "\nSize: " << mSize << endl;

	//Print the classes.
	cout << "\nEquiv Classes:" << endl;
	printClasses();
}

//This function generates equivalence classes.
void erGen()
{
	int sum;
	int ecSize;
	int random;

	//Generate the size of the relation. No smaller than 2 and no bigger than 40.
	mSize = rand() % MAX;

	while (mSize < 2)
	{
		mSize = rand() % MAX;
	}

	//For debugging purposes.
	//cout << "Size: " << mSize << endl;

	//Generate number of equivalence relations no bigger than 8 but smaller than size and not 0;
	ecNum = rand() % mSize;

	while (ecNum == 0 || ecNum > 8)
	{
		ecNum = rand() % mSize;
	}

	//For debugging purposes.
	//cout << "ECNUM: " << ecNum << endl;

	//Generate the size of all ec classes. Must equal the orignal size.
	if (ecNum == 1)
	{
		equivSize[0] = mSize;
	}
	else
	{
		do
		{
			sum = 0;

			for (int count = 0; count < ecNum; count++)
			{
				ecSize = rand() % mSize;

				while (ecSize == 0)
				{
					ecSize = rand() % mSize;
				}

				sum = sum + ecSize;
				equivSize[count] = ecSize;
			}

		} while (sum != mSize);
	}

	//For debugging purposes.
	//for (int count = 0; count < ecNum; count++)
	//{
	//	cout << "EC: " << equivSize[count] << endl;
	//}

	//Make a new array to hold used values and intilize.
	int* usedNum = new int[mSize];

	for (int count = 0; count < mSize; count++)
	{
		usedNum[count] = 0;		
	}

	//Fill the equivalence classes.
	for (int count = 0; count < ecNum; count++)
	{
		for (int index = 0; index < equivSize[count]; index++)
		{
			random = rand() % mSize;			

			while (usedNum[random] == 1)
			{
				random = rand() % mSize;
			}

			eClasses[count][index] = random;
			usedNum[random] = 1;
		}
	}

	delete(usedNum);	
}

//This function fills a relation give equivalence classes.
void fillRelation()
{
	for (int number = 0; number < ecNum; number++)
	{
		for (int count = 0; count < equivSize[number]; count++)
		{
			for (int index = 0; index < equivSize[number]; index++)
			{
				relation[eClasses[number][count]][eClasses[number][index]] = 1;
			}
		}
	}
}

//This function sorts and prints equivalence classes.
void printClasses()
{
	int temp;

	//Sort the generated classes (using bubble sort #lazy).
	for (int row = 0; row < ecNum; row++)
	{
		for (int count = 0; count < equivSize[row] - 1; count++)
		{
			for (int index = 0; index < equivSize[row] - 1; index++)
			{
				if (eClasses[row][index] > eClasses[row][index + 1])
				{
					temp = eClasses[row][index];
					eClasses[row][index] = eClasses[row][index + 1];
					eClasses[row][index + 1] = temp;
				}
			}
		}
	}

	//Print eClasses.
	for (int count = 0; count < ecNum; count++)
	{
	
		cout << "EC " << eClasses[count][0] << ": { ";

		for (int index = 0; index < equivSize[count]; index++)
		{
			cout << eClasses[count][index] << ", ";
		}
		cout << "}" << endl;
	}
}

//This function prints the matrix.
void printMatrix()
{
	for (int count = 0; count < mSize; count++)
	{

		for (int index = 0; index < mSize; index++)
		{
			cout << relation[count][index] << " ";
		}
		cout << endl;
	}
}