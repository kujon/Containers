/**
* \file airContainer.h
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 07.12.2010
* \version 1.0
* \brief Zawiera definicje klasy abstrakcyjnej airContainer, bedaca baza dla roznych typow klas pojemnikowych
*/

// -----------------------------------------------------------------

#ifndef AIRCONTAINERH
#define AIRCONTAINERH

// -----------------------------------------------------------------

#include<iostream>

using namespace std;

// -----------------------------------------------------------------

/**
* \class airContainer
* \author Jakub Korzeniowski, Łukasz Bobola
* \date 07.12.2010
* \brief klasa abstrakcyjna bedaca baza dla roznych typow klas pojemnikowych
*/
template <typename T>
class airContainer
{
	public:
	void append(T const & element);
	bool replace(int index, T const & element);
	void clear(void);
	bool isEmpty(void);
	int indexOf(T const & _value, int _from = 0) const;
	bool contains(T const & _value, int _from = 0) const;
	
	virtual bool insert(int index, T const & element) = 0;
	virtual T & at(int index) const = 0;
	virtual int size(void) const = 0;
	virtual bool remove(int index) = 0;

	airContainer<T> & operator=(airContainer<T> const & right);
	bool operator==(airContainer<T> const & right);
	bool operator!=(airContainer<T> const & right);
	T & operator[](int n) const;
	airContainer<T> & operator+=(airContainer<T> const & right);
	airContainer<T> & operator+=(T const & element);
	airContainer<T> & operator<<(airContainer<T> const & right);
	airContainer<T> & operator<<(T const & element);

	protected:
	int checkEach(T const & element, bool invert, int from = 0) const;
	bool compare(airContainer<T> const & right);
	airContainer<T> & appendContainer(airContainer<T> const & right);
};

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

/// \append - dodaje podany jako parametr obiekt typu T do pojemnika
///
/// \param element - element, ktory ma zostac dodany
template <typename T> void airContainer<T>::append(T const & element)
{
	int size = this->size();
	
	this->insert(size, element);
}

/// \remove - podmienia obiekt typu T z obiektem na wybranym miejscu. 
///
/// \param index - miejsce, w ktorym dokonujemy podmiany
/// \param element - element, na ktory podmieniamy
/// \return Zwraca true jezeli podane miejsce usuniecia jest prawidlowe, w przeciwnym wypdaku zwraca false.
template <typename T> bool airContainer<T>::replace(int index, T const & element)
{
	int size = this->size();

	if(index >= 0 && index < size)
	{
		this->at(index) = element;
		return true;
	}
	return false;
}

/// \clear - usuwa wszystkie elementy pojemnika
template <typename T> void airContainer<T>::clear(void)
{
	int size = this->size();

	for(int i = size - 1; i >= 0; i--)
		this->remove(i);
}

/// \isEmpty - sprawdza czy pojemnik jest pusty
///
/// \return zwraca true jezeli pojemnik jest pusty, inaczej false   
template <typename T> bool airContainer<T>::isEmpty(void)
{
	if(this->size() == 0) 
		return true;
	return false;
}

/// \indexOf - wyszukuje i zwraca indeks pierwszego elementu o wartosci _value zaczynajac od elementu _from
///
/// \param _value - wartosc, ktora ma zostac wyszukana
/// \param _from - index, od ktorego zaczynamy przeszukiwanie
/// \return index elementu, jezeli go nie ma, zwraca -1
template <typename T> int airContainer<T>::indexOf(T const & _value, int _from) const
{
	return this->checkEach(_value, false, _from);
}

/// \contains - sprawdza czy dany elelment jest juz w pojemniku
///
/// \param _value - wartosc, ktora sprawdzamy
/// \param _from - index, od ktorego zaczynamy przeszukiwanie
/// \return zwraca true jezeli element o wartosci _value znajduje sie w pojemniku inaczej zwraca false
template <typename T> bool airContainer<T>::contains(T const & _value, int _from) const
{
	if(this->checkEach(_value, false, _from) >= 0)
		return true;
	return false; 
}

// -----------------------------------------------------------------

/**
* \Definicje operatorow
*/

/// \ = operator przypisania
///
/// \param right - pojemnik, ktory ma zostac przypisany
/// \return referencja do pojemnika, do ktorego przypisalismy
template <typename T> airContainer<T> & airContainer<T>::operator=(airContainer<T> const & right)
{
	this->clear();
	
	int size = right.size();
	for(int i = 0; i < size; i++)
		this->insert(i, right.at(i));

	return *(this);				
}

/// \ == sprawdza, czy dwa pojemniki sa sobie rowne
///
/// \param right - pojemnik, z ktorym porownujemy
/// \return true jezeli oba pojemniki sa sobie rowne, false w przeciwnym wypadku
template <typename T> bool airContainer<T>::operator==(airContainer<T> const & right)
{
	return this->compare(right);
}

/// \ != sprawdza, czy dwa pojemniki sa rozne
///
/// \param right - pojemnik, z ktorym porownujemy
/// \return true jezeli pojemniki sa rozne, false w przeciwnym wypadku
template <typename T> bool airContainer<T>::operator!=(airContainer<T> const & right)
{
	return !(this->compare(right));
}

/// \ [] zwraca referencje do n-tego elementu
///
/// \param n - index elementu, ktory zwracamy
/// \return referencja do n-tego elementu
template <typename T> T & airContainer<T>::operator[](int n) const
{
	return this->at(n);
}

/// \ += dodaje wszystkie elementy z pojemnika right 
///
/// \param right - pojemnik, ktorego elementy maja byc dodane do this
/// \return referencja do this
template <typename T> airContainer<T> & airContainer<T>::operator+=(airContainer<T> const & right)
{
	return appendContainer(right);
}

/// \ += dodaje element do pojemnika
///
/// \param element - element, ktory ma zostac dodany
/// \return referencja do this
template <typename T> airContainer<T> & airContainer<T>::operator+=(T const & element)
{
	this->append(element);
	return *(this);
}

/// \ += dodaje wszystkie elementy z pojemnika right 
///
/// \param right - pojemnik, ktorego elementy maja byc dodane do this
/// \return referencja do this
template <typename T> airContainer<T> & airContainer<T>::operator<<(airContainer<T> const & right)
{
	return appendContainer(right);
}

/// \ += dodaje element do pojemnika
///
/// \param element - element, ktory ma zostac dodany
/// \return referencja do this
template <typename T> airContainer<T> & airContainer<T>::operator<<(T const & element)
{	
	this->append(element);
	return *(this);
}


// -----------------------------------------------------------------

/// \operator << dla klasy airContainer
///
/// \param output - strumien wyjscia
/// \param right - referencja do obiektu klasy airContainer, ktorej elementy maja byc wyswietlone
/// \return strumien wyjscia
template <typename T>
ostream & operator<<(ostream & output, airContainer<T> const & right)
{
	int size = right.size();
	
	for(int i = 0; i < size; i++)
		output << "element " << i << ": " << right.at(i) << endl;
	return output << endl;
}


// -----------------------------------------------------------------

/**
* \Helper functions
* \martwia sie o powtarzajace sie kawalki kodu
*/

/// \checkEach - iteruje przez caly pojemnik i jezeli natrafi na element podany jako parametr "element" zwraca jego index
///
/// \param element - element, z ktorym porownywanie sa elementy pojemnika
/// \param invert - jezeli true, to odwraca warunek ("==" -> "!=")
/// \param from - element, od ktorego zaczynamy iteracje 
/// \return index elementu, jezeli natrafi na element w pojemniku, -1, jezeli nie natrafi
template <typename T> int airContainer<T>::checkEach(T const & element, bool invert, int from) const
{
	int size = this->size();

	from = from < 0 ? 0 : from;	

	for(int i = from; i < size; i++)
		if((this->at(i) == element) - invert)
			return i;
	return -1;		
} 

/// \compare - porownuje zawartosci dwoch pojemnikow
///
/// \param right - referencja do pojemnika, z ktorym ma byc porownany obiekt
/// \return true jezeli pojemniki sa rowne, false, jezeli sa rozne
template <typename T> bool airContainer<T>::compare(airContainer<T> const & right)
{
	int size = this->size(), rightSize = right.size();

	if(size == rightSize)
	{
		for(int i = 0; i < size; i++)
			if(this->at(i) != right.at(i))
				return false;
		return true;
	}
	return false;
}

/// \appendContainer - dodaje na koniec pojemnika wszystkie elementy z pojemnika right
///
/// \param right - referencja do pojemnika, ktorego elementy trzeba dodac
template <typename T> airContainer<T> & airContainer<T>::appendContainer(airContainer<T> const & right)
{
	int size = right.size();
	
	for(int i = 0; i < size; i++)
	{
		this->append(right.at(i));
	}
	
	return this;
}

#endif
