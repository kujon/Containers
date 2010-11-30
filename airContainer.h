#include<iostream>

using namespace std;

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
	int checkEach(T const & element, bool invert, int from = 0);
	bool compare(airContainer<T> const & right);
};

// -----------------------------------------------------------------

/**
* \Definicje metod
*/

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
	if(this->checkEach(NULL, true) >= 0)
		return true;
	return false;
}

template <typename T> int airContainer<T>::indexOf(T const & _value, int _from) const
{
	return this->checkEach(_value, false, _from);
}

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

template <typename T> airContainer<T> & airContainer<T>::operator=(airContainer<T> const & right)
{

}

template <typename T> bool airContainer<T>::operator==(airContainer<T> const & right)
{
	return this->compare(right);
}

template <typename T> bool airContainer<T>::operator!=(airContainer<T> const & right)
{
	return !(this->compare(right));
}

template <typename T> T & airContainer<T>::operator[](int n) const
{
	return this->at(n);
}

template <typename T> airContainer<T> & airContainer<T>::operator+=(airContainer<T> const & right)
{

}

template <typename T> airContainer<T> & airContainer<T>::operator+=(T const & element)
{

}

template <typename T> airContainer<T> & airContainer<T>::operator<<(airContainer<T> const & right)
{

}

template <typename T> airContainer<T> & airContainer<T>::operator<<(T const & element)
{

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
template <typename T> int airContainer<T>::checkEach(T const & element, bool invert, int from)
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
