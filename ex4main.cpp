#include <iostream>
using namespace std;
// ---------------------------------------------------------

#include "airVector.h"
// ---------------------------------------------------------

void showTestResult(int, bool);
// ---------------------------------------------------------

int main(void)
{
  cout << "main by kk. Last updated 29.11.2010\n";

  airVector<airVector<int> > a;
  airContainer<int>* c1 = new airVector<int>;
  airContainer<int>* c2;
  a << *((airVector<int>*)c1);

  // 1st test - dodawanie do pojemnika stalych, zmiennych, tymczasowych
  c1->append(3);
  c1->insert(0, 1+1);
  c1->insert(c1->size(), c1->size());
  
  bool t1 = c1->size() == 3;
  int ttab1[] = {2, 3, 2};
  for(int i=0;i<3;i++)
    t1 = t1 && (ttab1[i] == c1->at(i));
  showTestResult(1, t1);

  // 2nd test - konstruktor kopiujacy
  c2 = new airVector<int>(*c1);
  bool t2 = c2->size() == 3;
  int ttab2[] = {2, 3, 2};
  for(int i=0;i<3;i++)
    t2 = t2 && (ttab2[i] == c2->at(i));
    showTestResult(2, t2);

  // 3rd test - usuwanie z pojemnika
  c1->clear();
  for(int i=0;i<5;i++)
    *c1 += i;
  *c1 << 4 << 2+3;
  c1->remove(2);

  int ttab3[] = {0, 1, 3, 4, 4, 5};
  bool t3 = c1->size() == 6;
  for(int i=0;t3 && i<6;i++)
    t3 = t3 && (ttab3[i] == c1->at(i));
  showTestResult(3, t3);

  // 4th test - sprawdzenie dzialanie konstruktora kopiujacego
  bool t4 = c2->size() == 3;
  int ttab4[] = {2, 3, 2};
  for(int i=0;i<3;i++)
    t4 = t4 && (ttab4[i] == c2->at(i));
  showTestResult(4, t4);

  // 5th test - metoda indexOf
  showTestResult(5, c1->indexOf(3) == 2);

  // 6th test - metoda indexOf
  showTestResult(6, c1->indexOf(4, 4) == 4);

  // 7th test - metoda contains
  showTestResult(7, !c1->contains(-6));
  

  // 8th test - operacje na pojemniku w pojemniku
  for(int i=3;i>=0;i--)
    a.at(0) += i+1;

  bool t8 = a.at(0).size() == 4;
  int ttab8[] = {4, 3, 2, 1};
  for(int i=0;t8 && i<4;i++)
    t8 = t8 && (a.at(0).at(i) == ttab8[i]);
  showTestResult(8, t8);

  // 9th test - usuwanie z pojemnika
  a.at(0).remove(2);   // 4,3,1
  a.at(0).remove(1);   // 4,1
  a.at(0).remove(1);   // 4
  a.at(0).remove(0);   // empty
  showTestResult(9, a.at(0).isEmpty());

  // 10th test - dzialanie operatora przypisania
  *c2 = *c1 = a.at(0);
  showTestResult(10, *c1 == a.at(0));
  
  // 11th test - zwalnianie paieci
  try
    {
      delete c1;
      delete c2;
      showTestResult(11, true);
    }
  catch(...)
    {
      showTestResult(11, false);
    }

  cout << "Finally, this is the end...\n";

  return 0;
}
// ---------------------------------------------------------

void showTestResult(int _ti, bool _r)
{
  if(_r)
    cout << "Test" << _ti << " PASSED\n";
  else
    cout << "Test" << _ti << " FAILED\n";
}
// ---------------------------------------------------------
