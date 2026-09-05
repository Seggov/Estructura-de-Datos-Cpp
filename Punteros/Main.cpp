#include <iostream>

using namespace std;

int main()
{

    int v[10];
    for (int i = 0; i < 10; i++)
    {

        v[i] = 10 * (i + 1);
    }

    int *p; // VARIABLE de tipo Puntero
    p = &v[7];
    *p = 4;
    int y = *p;

    cout << "*v = " << *v << endl;
    cout << " v = " << v << endl;
    cout << "&v = " << &v << endl;
    cout << "*p = " << *p << endl;
    cout << " p = " << p << endl;
    cout << "&p = " << &p << endl;
    cout << " y = " << y << endl;
    cout << "&y = " << &y << endl;
    return 0;
}