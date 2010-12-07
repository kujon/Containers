/**
* \file airVector.h
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 07.12.2010
* \version 1.0
* \brief Zawiera definicje klasy pojemnikowej airVector
*/

// -----------------------------------------------------------------

#ifndef AIRVECTORH
#define AIRVECTORH

// -----------------------------------------------------------------

#include "airContainer.h"

// -----------------------------------------------------------------

/**
* \class airVector
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 07.12.2010
* \brief klasa pojemnikowa airVector, bedaca dynamicznie alokowana tablica, z wieloma metodami ulatwiajacymi jej obsluge
*/
template <typename T>
class airVector : public airContainer<T>
{
	public:
	airVector();
	airVector(airContainer<T> const & vector);
	~airVector();
	bool insert(int index, T const & element);
	T & at(int index) const;
	int size(void) const;
	bool remove(int index);

	private:
	T * startPointer;
	int length;
	bool splice(int index, bool add);
};

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

/// \konstruktor - tylko inicjalizuje zmienne
template <typename T>
airVector<T>::airVector() :
startPointer(NULL),
length(0)
{}

/// \konstructor kopiujacy
///
/// \param vector - referencja do kontenera, z ktorego kopiujemy obiekty
template <typename T>
airVector<T>::airVector(airContainer<T> const & vector) :
length(vector.size())
{
	startPointer = new T[length];
	for(int i = 0; i < length; i++)
		startPointer[i] = vector.at(i);
}

/// \destruktor
template <typename T>
airVector<T>::~airVector()
{
	delete [] startPointer;
	startPointer = NULL;
	length = 0;
}

/// \insert - wstawia element na miejsce index
///
/// \param index - index, na ktory ma byc wstawiony element
/// \param element - wstawiany element
/// \return true, jezeli wskazany index jest prawidlowy, w przeciwnym wypadku false
template <typename T>
bool airVector<T>::insert(int index, T const & element)
{
	bool returnValue = this->splice(index, true);
	if(index >= 0 && index < length)
		startPointer[index] = element;
}

/// \at - zwraca referencje do obiektu na danym miejscu
///
/// \param index - index elementy, do ktorego ma byc zwrocona referencja
/// \return referencja do tego elementu
template <typename T>
T & airVector<T>::at(int index) const
{
	if(index < length && index >= 0)
		return startPointer[index];
}

/// \size - zwraca dlugosc kontenera
///
/// \return j.w.
template <typename T>
int airVector<T>::size(void) const
{
	return length;
}

/// \remove - usuwa wybrany element
/// 
/// \param index - index elementu do usuniecia
/// \return true, jezeli wskazany index jest prawidlowy, w przeciwnym wypadku false
template <typename T>
bool airVector<T>::remove(int index)
{
	return this->splice(index, false);
}


// -----------------------------------------------------------------

/**
* \Helper functions
*/

/// \splice - dodaje pusty/usuwa jeden element z kontenera
///
/// \param index - ktory element dodac/usunac
/// \param add - true - dodawac, false - usuwac
/// \return true jezeli wskazany index jest prawidlowy, w przeciwnym wypadku false
template <typename T>
bool airVector<T>::splice(int index, bool add)
{
	if(index > length || index < 0)
		return false;

	int newElementsCount = add ? 1 : -1;
	
	if(!add && index == length)
		return false;

	int i;
	
	length += newElementsCount;
	T * temp = new T[length];

	for(i = 0; i < index; i++)
		temp[i] = startPointer[i];

	if(add)
		index++;

	for(i = index; i < length; i++)
		temp[i] = startPointer[i - newElementsCount];

	delete [] startPointer;
	startPointer = temp;
	return true;
}

#endif
