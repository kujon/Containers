#include <iostream>
#include "airCalc.h"

using namespace std;

int main(void)
{
	airCalc * calc = new airCalc();
	cout << calc->doWizardry(cin, cout);

	return 1;
}
