#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
    Mass<string> mas(5);
    Stack<string> stak;
    Data<string>* stk = &stak;
    Mass<string> mass(7);
    Data<string>& ms = mass;
    testUkazatel<string>(stk);
    testSsilka<string>(ms);
    cout << "\n";
    mas.Push("Lexa");
    cout << mas.Peek() << "\n";
    mas.Pop();

    mas.Push("Lexa");
    mas.Push("root");
    mas.Push("ubuntu");
    mas.Push("char");
    mas.Push("mag");
    cout << mas.Peek() << "\n";
    cout << mas;
}