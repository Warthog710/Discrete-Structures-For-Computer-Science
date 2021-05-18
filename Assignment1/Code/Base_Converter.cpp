//Written by Quinn Roemer. Based on code by Professor Ross.
#include <iostream>
#include <string>
#include <math.h>
#include <stack>
#include <algorithm>

using namespace std;

//Converts an entered number into an internal representation.
long int atoi(string, int);
//Converts an internal rep number into any base from 2-36.
string itoa(long int, int);
//Perform addition in base.
string baseAddition(string, string, int);
//Convert from encoded to decoded DNA sequence.
string dnaCodonA(string);
//Convert from decoded to encoded DNA sequence.
string aDnaCodon(string);
//Global Ref Array for determining notation.

char refArray[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main()
{
    char answer;
    string base;
    string addNum1;
    string addNum2;
    string num;
    string original;
    bool enteredDNA = false;
    bool outputDNA = false;
    int enteredBase;
    int conversionBase;
    long int result;

    cout << "Menu" << endl;
    cout << "===========================" << endl;
    cout << "1. Perform Base Conversion" << endl;
    cout << "2. Perform Base Addition" << endl;
    cout << "3. Quit" << endl;
    cin >> answer;

    while (answer != '1' && answer != '2' && answer != '3')
    {
        cout << "\nInvalid input. Please try again." << endl;
        cin >> answer;
    }

    switch (answer)
    {
        case '1':
            cout << "\nPlease enter the base of the number: (Enter DNA for DNA conversion)" << endl;
            cin >> base;

            transform(base.begin(), base.end(), base.begin(), ::toupper);

            if (base == "DNA")
            {
                cout << "\nPlease enter the sequence:" << endl;
                cin >> base;
                transform(base.begin(), base.end(), base.begin(), ::toupper);
                original = base;
                num = dnaCodonA(base);
                enteredBase = 4;
                enteredDNA = true;
            }
            else
            {
                enteredBase = stoi(base);
                cout << "\nPlease enter the sequence:" << endl;
                cin >> num;
                original = num;
            }

            cout << "\nPlease enter the base for the conversion: (Enter DNA for DNA conversion)" << endl;
            cin >> base;

            transform(base.begin(), base.end(), base.begin(), ::toupper);

            if (base == "DNA")
            {
                result = atoi(num, enteredBase);
                num = itoa(result, 4);
                num = aDnaCodon(num);
                conversionBase = 4;
                outputDNA = true;
            }
            else
            {
                conversionBase = stoi(base);
                result = atoi(num, enteredBase);
                num = itoa(result, conversionBase);
            }
            if (enteredDNA == true && outputDNA == true)
            {
                cout << "\n" << original << " in base DNA" << " equals " << num << " in base DNA " << endl;
                enteredDNA = false;
                outputDNA = false;
            }
            else if (outputDNA == true)
            {
                cout << "\n" << original << " in base " << enteredBase << " equals " << num << " in base DNA" << endl;
                outputDNA = false;
            }
            else if (enteredDNA == true)
            {
                cout << "\n" << original << " in base DNA" << " equals " << num << " in base " << conversionBase << endl;
                enteredDNA = false;
            }
            else
            {
                cout << "\n" << original << " in base " << enteredBase << " equals " << num << " in base " << conversionBase << endl;
            }

            break;

        case '2':
            cout << "\nPlease enter the base for the addition:" << endl;
            cin >> enteredBase;

            cout << "\nPlease enter the first number:" << endl;
            cin >> addNum1;

            cout << "\nPlease enter the second number:" << endl;
            cin >> addNum2;

            num = baseAddition(addNum1, addNum2, enteredBase);

            cout << "\n" << addNum1 << " + " << addNum2 << " = " << num << " in base " << enteredBase << endl;
            break;

        case '3':
            break;
    }
}

long int atoi(string num, int enteredBase)
{
    long int total = 0;
    int length = num.length();
    int digit;
    int exponent = 0;
    char character;

    //Converting the entered number to its internal representation.
    for (int count = length - 1; count >= 0; count--)
    {
        character = num[count];

        //Finding number in ref array.
        for (int index = 0; index < 36; index++)
        {
            if (refArray[index] == character)
            {
                digit = index;
                break;
            }
        }

        //Adding totals for internal representation.
        total = total + (digit * (pow(enteredBase, exponent)));
        exponent++;
    }

    //Returning the result.
    return total;
}

string itoa(long int num, int conversionBase)
{
    string result;
    int remainder = 0;
    int rDivide;
    int size;
    char digit;

    //Stack for reversing result.
    stack<int> rStore;

    //Using MOD DIV to convert to any given base.
    while (num != 0)
    {
        rDivide = num / conversionBase;
        remainder = num % conversionBase;
        num = rDivide;
        rStore.push(remainder);
    }

    size = rStore.size();

    //Converting the stack to a string.
    for (int count = 0; count < size; count++)
    {
        remainder = rStore.top();
        digit = refArray[remainder];
        result += digit;
        rStore.pop();
    }

    //Returning the result.
    return result;
}

string baseAddition(string num1, string num2, int base)
{
    int carry = 0;
    int total, size;
    int place1, place2;
    int difference = 0;
    stack<int> answer;
    string result;
    char digit;

    //Equalizing number length.
    if (num1.size() != num2.size())
    {
        if (num1.size() > num2.size())
        {
            difference = num1.size() - num2.size();

            for (int count = 0; count < difference; count++)
            {
                num2.insert(0, "0");
            }
        }
        else
        {
            difference = num2.size() - num1.size();

            for (int count = 0; count < difference; count++)
            {
                num1.insert(0, "0");
            }
        }
    }

    //Performing the addition.
    for (int count = num1.size() - 1; count >= 0; count--)
    {
        for (int index = 0; index < 36; index++)
        {
            if (refArray[index] == num1[count])
            {
                place1 = index;
                break;
            }
        }

        for (int index = 0; index < 36; index++)
        {
            if (refArray[index] == num2[count])
            {
                place2 = index;
                break;
            }
        }

        total = place1 + place2 + carry;

        if (total - base >= 0)
        {
            total = total - base;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        answer.push(total);

        if (carry > 0 && count == 0)
        {
            answer.push(carry);
        }
    }

    size = answer.size();

    //Converting the stack into a string.
    for (int count = 0; count < size; count++)
    {
        carry = answer.top();
        digit = refArray[carry];
        result += digit;
        answer.pop();
    }

    return result;
}

string dnaCodonA(string codon)
{
    int size = codon.size();
    string result;
    char digit;
    int number;
    stack<int> answer;

    //Performing operation.
    for (int count = codon.size() - 1; count >= 0; count--)
    {
        switch (codon[count])
        {
            case 'C':
                answer.push(0);
                break;
            case 'T':
                answer.push(1);
                break;
            case 'A':
                answer.push(2);
                break;
            case 'G':
                answer.push(3);
                break;
        }
    }

    size = answer.size();

    //Converting the stack to a string.
    for (int count = 0; count < size; count++)
    {
        number = answer.top();
        digit = refArray[number];
        result += digit;
        answer.pop();
    }

    return result;
}

string aDnaCodon(string codon)
{
    int size = codon.size();
    string result;
    char digit;
    stack<char> answer;

    //Performing operation.
    for (int count = codon.size() - 1; count >= 0; count--)
    {
        switch (codon[count])
        {
            case '0':
                answer.push('C');
                break;
            case '1':
                answer.push('T');
                break;
            case '2':
                answer.push('A');
                break;
            case '3':
                answer.push('G');
                break;
        }
    }

    //Converting the stack to a string.
    for (int count = 0; count < size; count++)
    {
        digit = answer.top();
        result += digit;
        answer.pop();
    }
    
    return result;
}