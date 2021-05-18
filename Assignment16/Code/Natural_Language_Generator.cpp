//Code written by Professor Ross, Modified by Quinn Roemer
#include <iostream>
#include <string.h>
#include <time.h>

#pragma warning( disable : 4996)

using namespace std;

// Strings
#define SIZE 10000
char w[SIZE] = "A";  //our initial string of N's and T's
char buf[SIZE] = ""; //a buffer for string processing

//Productions
char P[][5][20] = {
	"Bc", "", "", "", "",	// A -> Bc
	"Cb", "l", "", "", "",	// B -> Cb|l
	"Ba", "l", "",  "", "",		// C -> Ba
};

// Terminal Expansions
char tTable[][20] = {
	"he said ",			//a
	"she said ",		//b
	"you lie.",			//c
};

//Gets the cardinality for a row of the Productions table
int Cardinality(int row)
{
	int col = 0;

	// look for an empty string
	while (P[row][col][0])
		col++;

	return col;
}

//Returns true if there are Nonterminals in w
bool gotNs()
{
	for (int i = 0; w[i]; i++)
		if (w[i] >= 'A' && w[i] <= 'Z')
			return true;
	return false;
}

//Introduces verbosity
//Replaces terminals with big strings for humans to read and ponder
void expand()
{
	int i = 0;  buf[0] = 0;
	while (w[i])
	{
		int index = w[i] - 'a';
		strcat(buf, tTable[index]);
		i++;
	}

	// copy back to w
	strcpy(w, buf);
}

//Main function to execute.
int main(void)
{
	//Seed random number generator
	srand((unsigned)time(0));

	cout << "w = " << w << endl;  //Print status

	//Process all of w repeatedly until all nonterminals are gone
	while (gotNs())
	{
		//Scan w and replace nonterminals with random productions
		int i = 0; int j = 0; buf[0] = 0; int card = 0;

		//For each w[i] in w
		while (w[i])                              
		{
			//Nonterminals
			if (w[i] < 96)
			{
				//Finding row index.
				j = w[i] - 65;
				//cout << "J: " << j << endl;

				//Scanning the row in productions for characters.
				for (int count = 0; count < 5; count++)
				{
					if (strlen(P[j][count]) > 0)
					{
						card++;
					}
					//cout << "Card: " << card << endl;
				}

				card = rand() % card;

				strcat(buf, P[j][card]);        //Copy production to buf
			}
			// Terminals
			else                                //Else w[i] is a terminal
			{
				char lilbuf[10] = { w[i], 0 };  //Put this terminal into a lil buffer
				strcat(buf, lilbuf);            //Copy terminal to buf
			}

			i++;                                //Next char in w
		}

		//Copy back to w
		strcpy(w, buf);
		cout << endl << "w = " << w << endl;    //Print status
	}

	expand();
	cout << "w = " << w << endl;
}

