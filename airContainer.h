#include<iostream>

using namespace std;

template <typename T>
class airContainer
{
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
};


template <typename T> void airContainer<T>::append(T const & element)
{

}

template <typename T> bool airContainer<T>::replace(int index, T const & element)
{

}

template <typename T> void airContainer<T>::clear(void)
{

}

template <typename T> bool airContainer<T>::isEmpty(void)
{
	if(checkEach(NULL, true, this) >= 0)
		return true;
	return false;
}

template <typename T> int airContainer<T>::indexOf(T const & _value, int _from) const
{
	return checkEach(_value, false, this, _from);
}

template <typename T> bool airContainer<T>::contains(T const & _value, int _from) const
{
	if(checkEach(_value, false, this, _from) >= 0)
		return true;
	return false; 
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
/// \param container - referencja do pojemnika
/// \param from - element, od ktorego zaczynamy iteracje 
/// \return index elementu, jezeli natrafi na element w pojemniku, -1, jezeli nie natrafi
template <typename T> int checkEach(T const & element, bool invert, airContainer<T> const & container, int from = 0)
{
	int size = container.size();

	from = from < 0 ? 0 : from;	

	for(int i = from; i < size; i++)
		if((container.at(i) == element) - invert)
			return i;
	return -1;		
} 
