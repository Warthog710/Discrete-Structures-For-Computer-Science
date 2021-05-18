//Code written by Quinn Roemer 11/4/2018. Based on code by Professor Ross.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Global Data.
string outTable[100][100];

//Function prototypes.
void fillTable(string, string[100][100]);
void eraseTable(string[100][100]);
void printTable(string[100][100]);
void select(string[100][100], string, int);
void project(string[100][100], int[100]);
void join(string[100][100], string[100][100], string, string, int, int);
void cpyTable(string[100][100]);
void unionTable(string[100][100], string[100][100]);

//Main function to execute.
int main()
{
	string T1[100][100];
	string T2[100][100];
	int columns[100] = { 0 };	

	//This code executes 4 problems to demonstrate its function(s).
	//Problem 1.
	cout << "1: Find the names of all employees who work in departments that supply parts for JCN electronics." << endl << endl;
	fillTable("buyer.txt", T1);
	cout << "--Buyer Table--" << endl;
	printTable(T1);
	select(T1, "JCN Electronics", 0);
	cout << "\n--TEMP1 = Buyer[Buyer = JCN Electronics]--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("supplier.txt", T2);
	cout << "\n--Supplier Table--" << endl;
	printTable(T2);
	join(T1, T2, "2A", " ", 1, 0);
	cout << "\n--TEMP1 = TEMP1[2A = 2A]Supplier--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("department.txt", T2);
	cout << "\n--Department Table--" << endl;
	printTable(T2);
	join(T1, T2, "23", " ", 0, 0);
	cout << "\n--TEMP1 = TEMP1[23 = 23]Department--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("employee.txt", T2);
	cout << "\n--Employee Table--" << endl;
	printTable(T2);
	join(T1, T2, "Jones", " ", 2, 0);
	cout << "\n--TEMP1 = TEMP1[Jones = Jones]Employee--" << endl;
	printTable(outTable);
	cpyTable(T1);
	columns[1] = 1;
	project(T1, columns);
	cout << "\n--TEMP1[Name]--" << endl;
	printTable(outTable);

	//Problem 2.
	cout << "\n2: Find all buyers who buy parts in the department managed by Jones." << endl << endl;
	fillTable("department.txt", T1);
	cout << "--Department Table--" << endl;
	printTable(T1);
	select(T1, "Jones", 1);
	cout << "\n--TEMP1 = Department[Manager = Jones]--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("supplier.txt", T2);
	cout << "\n--Supplier Table--" << endl;
	printTable(T2);
	join(T1, T2, "23", " ", 0, 0);
	cout << "\n--TEMP1 = TEMP1[23 = 23]Supplier--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("buyer.txt", T2);
	cout << "\n--Buyer Table--" << endl;
	printTable(T2);
	join(T1, T2, "2A", "772", 1, 0);
	cout << "\n--TEMP1 = TEMP1[2A = 2A || 772 = 772]Buyer--" << endl;
	printTable(outTable);
	cpyTable(T1);
	columns[0] = 1; columns[1] = 0;
	project(T1, columns);
	cout << "\n--TEMP1[Buyer]--" << endl;
	printTable(outTable);

	//Problem 3.
	cout << "\n3: Find all buyers who buy parts that are produced by the department for which Suzuki works." << endl << endl;
	cout << "--Employee Table--" << endl;
	fillTable("employee.txt", T1);
	printTable(T1);
	select(T1, "Suzuki", 1);
	cout << "\n--TEMP1 = Employee[Employee = Suzuki]--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("department.txt", T2);
	cout << "\n--Department Table--" << endl;
	printTable(T2);
	join(T1, T2, "Zamora", " ", 1, 0);
	cout << "\n--TEMP1 = TEMP1[Zamora = Zamora]Department--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("supplier.txt", T2);
	cout << "\n--Supplier Table--" << endl;
	printTable(T2);
	join(T1, T2, "96", " ", 0, 0);
	cout << "\n--TEMP1 = TEMP1[96 = 96]Supplier--" << endl;
	printTable(outTable);
	cpyTable(T1);
	fillTable("buyer.txt", T2);
	cout << "\n--Buyer Table--" << endl;
	printTable(T2);
	join(T1, T2, "20A8", "1199C", 1, 0);
	cout << "\n--TEMP1 = TEMP1[20A8 = 20A8 || 1199C = 1199C]Buyer--" << endl;
	printTable(outTable);
	cpyTable(T1);
	columns[0] = 1; columns[1] = 0;
	project(T1, columns);
	cout << "\n--TEMP1[Buyer]--" << endl;
	printTable(outTable);

	//Problem 4.
	cout << "\n4. Union 2 tables." << endl << endl;
	fillTable("Students.txt", T1);
	fillTable("MoreStudents.txt", T2);
	cout << "--Students Table--" << endl;
	printTable(T1);
	cout << "\n--MoreStudents Table--" << endl;
	printTable(T2);
	cout << "\n--TEMP1 = Union[Students, MoreStudents]--" << endl;
	unionTable(T1, T2);
	printTable(outTable);
}

//Joins two similiar tables together.
void unionTable(string T1[100][100], string T2[100][100])
{
	eraseTable(outTable);
	int place = 0;
	int innerCount = 0;

	for (int count = 0; count < 100; count++)
	{
		for (int index = 0; index < 100; index++)
		{
			outTable[count][index] = T1[count][index];
		}
		if (T1[count][0] == "NULL")
		{
			place = count;
			break;
		}
	}
	for (int count = place; count < 100; count++)
	{
		for (int index = 0; index < 100; index++)
		{
			outTable[count][index] = T2[innerCount][index];
		}
		innerCount++;
	}
}

//Copies outTable contents to the passed table.
void cpyTable(string table[100][100])
{
	for (int count = 0; count < 100; count++)
	{
		for (int index = 0; index < 100; index++)
		{
			table[count][index] = outTable[count][index];
		}
	}
}

//Sets outTable to hold the rows where data is found in the specified column.
void select(string inTable[100][100], string data, int column)
{
	eraseTable(outTable);

	int innerCount = 0;

	for (int count = 0; count < 100; count++)
	{
		if (inTable[count][column] == data)
		{
			//This row needs to go into new table.
			for (int index = 0; index < 100; index++)
			{
				//Location is NULL and can be ignored.
				if (inTable[count][index] == "NULL")
				{
					//Increment the innerCount for next iteration.
					innerCount++;
					break;
				}
				//Location needs to be entered in outTable.
				else
				{
					outTable[innerCount][index] = inTable[count][index];
				}
			}
		}
		if (inTable[count][0] == "NULL")
		{
			//cout << "\nCount: " << count << endl;
			break;
		}
	}
}

//Sets outTable to hold the selected column(s) of data.
void project(string inTable[100][100], int columns[100])
{
	eraseTable(outTable);

	int innerCount = 0;

	//Examining the entire table.
	for (int count = 0; count < 100; count++)
	{
		//If we have reached a specifed column.
		if (columns[count])
		{
			//This column needs to be included.
			for (int index = 0; index < 100; index++)
			{
				if (inTable[index][count] == "NULL")
				{
					innerCount++;
					break;
				}
				else
				{
					outTable[index][innerCount] = inTable[index][count];
				}
			}
		}	
	}
	return;
}

//Joins two tables on an indentical data point. Stores in outTable.
void join(string T1[100][100], string T2[100][100], string data1, string data2, int column, int line)
{
	eraseTable(outTable);

	int innerCount = 0;
	int place = 0;

	for (int count = 0; count < 100; count++)
	{
		//The row being looked at matches.
		if (T2[count][column] == data1 || T2[count][column] == data2)
		{
			for (int index = 0; index < 100; index++)
			{
				if (T2[count][index] != "NULL")
				{
					outTable[innerCount][index] = T2[count][index];
					place++;
				}
			}

			for (int index = 0; index < 100; index++)
			{
				if (T1[line][index] != "NULL")
				{
					outTable[innerCount][place] = T1[line][index];
					place++;
				}
			}
			innerCount++;
			place = 0;

		}
	}
}

//Fills a table from a .txt file.
void fillTable(string fileName, string table[100][100])
{
	string line, input;

	int length;
	int place = 0;
	int row = 0;

	eraseTable(table);

	//Open file.
	ifstream file(fileName);

	if (!file)
	{
		cerr << "No input file..." << endl;
		exit(1);
	}

	//Read file into array.
	getline(file, line);
	length = line.length();

	while (line.length() > 0)
	{
		for (int count = 0; count < length; count++)
		{
			//If there is no comma the line will continue to be processed.
			if (line[count] != ',')
			{
				input += line[count];
				//cout << input << endl;
			}
			//If there is a comma the line will be entered and the comma skipped over.
			if (line[count] == ',' || count == length - 1)
			{
				//cout << "In:" << input << endl;
				table[row][place] = input;
				input.erase();
				place++;
			}
		}

		//Reset necessary variables.
		getline(file, line);
		length = line.length();
		place = 0;
		row++;
	}

	file.close();
	return;
}

//Sets a table to "NULL".
void eraseTable(string table[100][100])
{
	for (int count = 0; count < 100; count++)
	{
		for (int index = 0; index < 100; index++)
		{
			table[count][index] = "NULL";
		}
	}
	return;
}

//Prints a table.
void printTable(string table[100][100])
{
	for (int count = 0; count < 100; count++)
	{
		for (int index = 0; index < 100; index++)
		{
			if (table[count][index] == "NULL")
			{			
				break;
			}
			else
			{
				cout << table[count][index] << ", ";
			}
		}
		if (table[count][0] == "NULL")
		{
			break;
		}
		else
		{
			cout << endl;
		}
	}
	return;
}
