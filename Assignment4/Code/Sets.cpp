//Written by Quinn Roemer, based on code by Professor Ross.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#pragma warning( disable : 4996) 
#pragma warning( disable : 4244) 

#define CHAR_BIT 8

//Small Universe
char Universe[8][10] = { "Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle" };

//Large Universe
char BigUniverse[32][20] = {
	"Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle",
	"Bear", "Dragon", "Horse", "Wolf", "Rat", "Gerbil", "Rabbit", "Monkey",
	"Donkey", "Llama", "Zebra", "Hippopotamus", "Rhiceros", "Gecko", "Frog", "Sloth",
	"Deer", "Kangaroo", "Gorilla", "Alligator", "Panda", "Squirrel", "Duck", "Platypus" };

typedef unsigned char set;
typedef unsigned long int set32;

//Prints out a set in set-sequence notation									
void printSet(set A)
{
	printf("{ ");

	bool commaflag = false;
	int i = 0;
	unsigned char mask = 0x80;
	for (; mask; mask >>= 1, i++) {
		if (mask & A)
		{
			if (commaflag) printf(", ");
			printf(Universe[i]);
			commaflag = true;
		}
	}
	printf(" }");
}

//Prints each bit of a byte
void print8bits(unsigned char x)
{
	for (unsigned char mask = 0x80; mask; mask >>= 1) {
		if (mask & x)
			printf("1");
		else
			printf("0");
	}
}

//Inserts an element of the universe into a set
void insert(set & A, char str[])
{
	// get a unique hash for each string
	int hash = (str[0] + str[2]) % 20;

	int g[20] = { 6, -1, 0, 1, -1, 4, -1, -1, -1, -1, -1, 3, 2, -1, -1, -1, -1, -1, 7, 5 };

	int index = g[hash];

	// make a mask
	set mask = 0x80 >> index;

	// insert this element
	A = A | mask;
}

//Calculates base raised to the power exp
int my_pow(int base, int  exp)
{
	int x = 1;
	for (int i = 0; i < exp; i++)
		x *= base;

	return x;
}

//===========================
//=== My code starts here ===
//===========================

//This function computes the union of two passed sets.
set Union(set A, set B)
{	
	return A | B;
}

//This function computes the intersection of two passed sets.
set Intersection(set A, set B)
{
	return A & B;
}

//This function returns the complement of a passed set.
set Complement(set A)
{
	return ~A;
}

//This function returns the difference two sets.
set Difference(set A, set B)
{
	return Intersection(A, Complement(B));
}

//This function computes the cardinality of a set.
int Cardinality(set A)
{
	//Mask starts at 1000 0000.
	//Note, this will have to be changed for the bigUniverse.
	int mask = 0x80;
	int card = 0;

	//Iterating through set to find all 1's. Note, iterates to the bit size of char passed.
	for (int count = 0; count < sizeof(A) * CHAR_BIT; count++)
	{
		//If a 1 is found, card will be incremented.
		if (A & mask)
		{
			card++;
		}
		mask >>= 1;
	}
	return card;
}

//This function computes all possible power sets of a given set.
void printPowerSet(set A)
{
	int cardP = my_pow(2, Cardinality(A));
	int exponent = Cardinality(A) - 1;

	set temp;
	set temp2;
	set result = 0;

	int mask = 0x80;

	cout << "Powerset(A): " << endl;

	//This loop generates all possible powerSets.
	for (int count = 0; count < cardP; count++)
	{
		temp = count;

		//This loop iterates through the entire char placing the bits in the correct location.
		for (int index = 0; index < sizeof(A) * CHAR_BIT; index++)
		{
			//If the mask & A = 1 this will execute.
			if (mask & A)
			{
				//Setting char to correct bit power.
				temp2 = my_pow(2, exponent);

				//If the correct location in temp is 1 this will execute.
				if (temp & temp2)
				{
					//Set the result to the OR of mask.
					result = result | mask;
				}
				exponent--;
			}
			mask >>= 1;
		}
		//Printing the result.
		printSet(result);
		cout << endl;

		//Resetting the necessary variables for the next iteration.
		result = 0;
		mask = 0x80;
		exponent = Cardinality(A) - 1;
	}	
}

//This function returns true of a subset is passed. Else false.
bool IsSubset(set ASubset, set ASet)
{
	if ((ASet | ASubset) == ASet)
	{
		return true;
	}
	return false;
}

//This function returns true if a proper subset is passed. Else false.
bool IsProperSubset(set ASubset, set ASet)
{
	if (ASet == ASubset)
	{
		return false;
	}
	else if ((ASet | ASubset) == ASet)
	{
		return true;
	}
	return false;
}

//Main function to execute.
int main(void)
{
	set A = 0;

	insert(A, "Bat");
	insert(A, "Chimp");
	insert(A, "Liger");
	insert(A, "Snake");
	insert(A, "Turtle");
	printf("Set A: ");
	printSet(A);

	set B = 0;
	insert(B, "Bat");
	insert(B, "Cat");
	insert(B, "Chimp");
	insert(B, "Dog");
	insert(B, "Fish");
	printf("\nSet B: ");
	printSet(B);

	set C = 0;
	insert(C, "Dog");
	insert(C, "Fish");
	insert(C, "Liger");
	insert(C, "Snake");
	insert(C, "Turtle");
	printf("\nSet C: ");
	printSet(C);
	cout << endl;

	set D = 0;

	cout << "\n(A union B) Intersection C: ";
	D = Intersection(Union(A, B), C);
	printSet(D);
	cout << endl;

	cout << "\nA union (B intersection C): ";
	D = Union(A, Intersection(B, C));
	printSet(D);
	cout << endl;

	cout << "\nComplement (A intersection B): ";
	D = Complement(Intersection(A, B));
	printSet(D);
	cout << endl;

	cout << "\nComplement A union complement B: ";
	D = Union(Complement(A), Complement(B));
	printSet(D);
	cout << endl;

	cout << "\nA difference B: ";
	D = Difference(A, B);
	printSet(D);
	cout << endl << endl;

	printPowerSet(A);

	if (IsSubset(A, B))
		cout << "\nA is a subset of B" << endl;
	else
		cout << "\nA is not a subset of B" << endl;

	if (IsProperSubset(A, B))
		cout << "\nA is a proper subset of B" << endl;
	else
		cout << "\nA is not a proper subset of B" << endl;

	//Of my own design.

	cout << "\nCardinality (A union complement (B difference C)): ";
	D = Union(A, Complement(Difference(B, C)));
	cout << Cardinality(D);
	cout << endl << endl;

	if (IsSubset(Intersection(A, B), A))
		cout << "Intersection (A, B) is a subset of A" << endl;
	else
		cout << "Intersection (A, B) is not a subset of A" << endl;
}