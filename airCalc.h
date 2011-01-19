/**
* \file airCalc.h
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 19.01.2011
* \version 1.0
* \brief Zawiera definicje klasy airCalc bedacej kalkulatorem postfiksowym
*/

// -----------------------------------------------------------------

#ifndef AIRCALCH
#define AIRCALCH

// -----------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <string>
#include "airVector.h"
#include "airStack.h"

// -----------------------------------------------------------------

/**
* \class airCalc
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 18.01.2011
* \brief klasa pojemnikowa airCalc - kalkulator postfixowy
*/
class airCalc : public airStack<int>
{
	struct command
	{
		bool isNumber;
		int code;
		command();
		command(bool _isNumber, int _code);
	};

	public:
	int doWizardry(istream & input, ostream & output);

	private:
	bool read(airVector<command> * array, istream & input);
	int doMath(airVector<command> * array);
};

// -----------------------------------------------------------------

int fact(int n);

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

/// \konstrukto
airCalc::command::command() :
code(0)
{}

/// \konstruktor
airCalc::command::command(bool _isNumber, int _code) : 
isNumber(_isNumber),
code(_code)
{}

/// \doWizardry pobiera dzialanie z wejscia i zwraca jego wynik
///
/// \param input - referencja do strumeinia wejscia
/// \return wynik dzialania
int airCalc::doWizardry(istream & input, ostream & output)
{
	airVector<command> * array = new airVector<command>();
	
	while(!read(array, input))
	{
		output << "Podales bledne dane ponow probe!";
	}

	return doMath(array);		
}

/// \read - czyta dzialanie ze strumienia wejsciowego
///
/// \param array - pointer do tablicy komend, ktora zostanie wygenerowana
/// \param input - referencja do strumienia wejscia
bool airCalc::read(airVector<command> * array, istream & input)
{
	string operation;
	
	input >> operation;
	if(input.fail())
	{
        	input.clear(); 
                input.get();
		return false;
	}
	
	int length = operation.length(), sign, j, code;
	char last;
	for(int i = 0; i < length; i++)
	{
		sign = 0;

		if(operation[i] == ' ' && last && last != ' ' && ((operation[i] < '0' || operation[i] > '9') && operation[i] != '-' && operation[i] != '+' && operation[i] != '*' && operation[i] != '/' && operation[i] != '!' && operation[i] != '^')) //pierwsze sprawdza czy dany znak jest spacja, drugei zabezpiecza przypadki, ze ktos zaczal dzialanie od spacji, trzecie wyklucza wielokrotne spacje, ostatnie combo skipuje niedozwolone znaki
			i++;
		else
		{
			if(i + 1 < length && operation[i] == '-' && operation[i + 1] >= '0' && operation[i + 1] <= '9')
			{
				sign = -1;
				i++;
			}
			else if(operation[i] >= '0' && operation[i] <= '9')
				sign = 1;

			j = 0;
			code = 0;
			while(i < length && operation[i] >= '0' && operation[i] <= '9')
			{
				code += (operation[i] - 48) * pow(10, j);
				i++; j++;		 
			}
	
			if(sign != 0)
			{
				code *= sign;
				command * cmd = new command(true, code);
				array->append(*cmd);
			}
			else
			{
				command * cmd = new command(false, operation[i]);
				array->append(*cmd);
			}

		}

		last = operation[i];
	}           

	return true;
}

/// \doMath - oblicza wynik dzialania
///
/// \param array - pointer do tablicy komend
/// \return wynik dzialania
int airCalc::doMath(airVector<command> * array)
{
	int length = array->size(), code, x, y;

	for(int i = 0; i < length; i++)
	{
		if(array->at(i).isNumber)
			this->push(array->at(i).code);
		else
		{
			code = array->at(i).code;
			x = this->pop();
			if(code != '!')
				y = this->pop();

			if(code == '+')
				this->push(x + y);
			else if(code == '-')
				this->push(y - x);
			else if(code == '*')
				this->push(x * y);
			else if(code == '/')
				this->push(y / x);
			else if(code == '^')
				this->push(pow(y, x));
			else if(code == '!')
				this->push(fact(x));
		}
	}

	return this->at(0);
}

/*
/// \Helper functions
*/

/// \fact - liczy silnie
///
/// \return - wynik dzialania
int fact(int n)
{
	if(n == 0 || n == 1)
		return 1;
	else
		return (n * fact(n - 1));
}

#endif
