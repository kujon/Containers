#include<iostream>

using namespace std;

template<typename T>
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

template<typename T>
ostream & operator<<(ostream & output, airContainer<T> const & right);
