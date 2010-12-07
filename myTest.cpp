#include"airVector.h"

int main(void)
{
	airVector<int> * test = new airVector<int>;
	test->insert(0, 1);
	cout << test->at(0);
	cout << *(test);
	delete test;
	return 1;
}
