/**
* \file airStack.h
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 07.12.2010
* \version 1.0
* \brief Zawiera definicje klasy pojemnikowej airStack
*/

// -----------------------------------------------------------------

#ifndef AIRSTACKH
#define AIRSTACKH

// -----------------------------------------------------------------

#include "airVector.h"

// -----------------------------------------------------------------

/**
* \class airStack
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 18.01.2011
* \brief klasa pojemnikowa airStack, bedaca stosem
*/
template <typename T>
class airStack : public airVector<T>
{
	public:
	void push(const T & elem);
	T & top(void) const;
	T pop(void);
};

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

/// \push - dodaje element na szczyt stosu
///
/// \param elem - element do dodania
template <typename T> void airStack<T>::push(const T & elem)
{
	this->insert(this->size(), elem);
}

/// \top - zwraca element ze szczytu stosu bez usuwania go
///
/// \return element ze szczytu stosu
template <typename T> T & airStack<T>::top(void) const
{
	return this->at(this->size() - 1);
}

/// \pop - zwraca element ze szczytu stosu i od razu go usuwa
///
/// \return swiezo usuniety element
template <typename T> T airStack<T>::pop(void)
{
	int length = this->size();
	T temp = this->at(length - 1);
	this->remove(length - 1);
	return temp;	
}

#endif
