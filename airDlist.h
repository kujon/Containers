/**
* \file airDlist.h
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 15.12.2010
* \version 1.0
* \brief Zawiera definicje klasy pojemnikowej airDlist
*/

// -----------------------------------------------------------------

#ifndef AIRDLISTH
#define AIRDLISTH

// -----------------------------------------------------------------

#include "airContainer.h"

// -----------------------------------------------------------------

/**
* \class airDlist
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 15.12.2010
* \brief klasa pojemnikowa airDlist, bedaca dwukierunkowa lista, z wieloma metodami ulatwiajacymi jej obsluge
*/
template <typename T>
class airDlist : public airContainer<T>
{
	struct item
	{
		T * contentPointer;
		item * nextItem;
		item * previousItem;
	};

	public:
	airDlist();
	airDlist(airContainer<T> const & list);
	~airDlist();
	bool insert(int index, T const & element);
	T & at(int index) const;
	int size(void) const;
	bool remove(int index);

	private:
	item * startPointer;
	int length;
	bool splice(int index, bool add);
	item * itemAt(int index) const;
};

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

/// \konstruktor - tylko inicjalizuje zmienne
template <typename T>
airDlist<T>::airDlist() :
startPointer(NULL),
length(0)
{}

/// \konstructor kopiujacy
///
/// \param list - referencja do kontenera, z ktorego kopiujemy obiekty
template <typename T>
airDlist<T>::airDlist(airContainer<T> const & list) :
length(list.size())
{
	int size = list.size();
	item * currentItem = startPointer;
	item * previousItem = startPointer;

	for(int i = 0; i < size; i++)
	{
		currentItem = new item();
		currentItem->contentPointer = new T();
		*(currentItem->contentPointer) = list.at(i);
		if(i > 0)
			(previousItem->nextItem = currentItem) && (currentItem->previousItem = previousItem) && (previousItem = currentItem);
		else
			startPointer = currentItem;
	}
}

/// \destruktor
template <typename T>
airDlist<T>::~airDlist()
{
	int size = this->size();
	item * cachedItem = startPointer;
	item * currentItem = startPointer;
	for(int i = 0; i < size; i++)
	{
		cachedItem = currentItem->nextItem;
		delete currentItem;
		currentItem = NULL;
		currentItem = cachedItem;
	}	
	length = 0;
}

/// \insert - wstawia element na miejsce index
///
/// \param index - index, na ktory ma byc wstawiony element
/// \param element - wstawiany element
/// \return true, jezeli wskazany index jest prawidlowy, w przeciwnym wypadku false
template <typename T>
bool airDlist<T>::insert(int index, T const & element)
{
	bool returnValue = this->splice(index, true);
	if(index >= 0 && index < length)
	{
		this->at(index) = element;
	}
	return returnValue;
}

/// \at - zwraca referencje do obiektu na danym miejscu
///
/// \param index - index elementy, do ktorego ma byc zwrocona referencja
/// \return referencja do tego elementu
template <typename T>
T & airDlist<T>::at(int index) const
{
	if(index < length && index >= 0)
	{
		item * currentItem = this->itemAt(index);
		return *(currentItem->contentPointer);		
	}
}

/// \size - zwraca dlugosc kontenera
///
/// \return j.w.
template <typename T>
int airDlist<T>::size(void) const
{
	return length;
}

/// \remove - usuwa wybrany element
/// 
/// \param index - index elementu do usuniecia
/// \return true, jezeli wskazany index jest prawidlowy, w przeciwnym wypadku false
template <typename T>
bool airDlist<T>::remove(int index)
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
bool airDlist<T>::splice(int index, bool add)
{
	if(index > length || index < 0)
		return false;

	int newElementsCount = add ? 1 : -1;
	
	if(!add && index == length)
		return false;

	int i;

	length += newElementsCount;

	/*item * previousItem = index > 0 ? this->itemAt(index - 1) : NULL;


	if(add)
	{
		item * addedItem = new item();
		addedItem->contentPointer = new T();
		if(index > 0)
			(addedItem->nextItem = previousItem->nextItem) && (previousItem->nextItem = addedItem) && (addedItem->nextItem->previousItem = addedItem) && (addedItem->previousItem = previousItem);
		else
			(addedItem->nextItem = startPointer) && (startPointer = addedItem) && (addedItem->nextItem->previousItem = addedItem);
	}
	else
	{
		item * deletedItem = this->itemAt(index);

		if(index > 0)
			(previousItem->nextItem = deletedItem->nextItem) && (previousItem->nextItem->previousItem = previousItem);
		else
			(startPointer = deletedItem->nextItem) && (startPointer->previousItem = NULL);
		delete deletedItem;
	}
	*/
	return true;
}

/// \itemAt - zwraca wskaznik do elementu item o danym indexie
/// \
/// \param index - index elementu
/// \return wskaznik do elementu o danym indexie
template <typename T>
typename airDlist<T>::item * airDlist<T>::itemAt(int index) const
{
	item * returnValue = startPointer;
	for(int i = 0; i < index; i++)
		returnValue = returnValue->nextItem;
	return returnValue;
}

#endif
