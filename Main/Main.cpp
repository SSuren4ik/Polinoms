#include <iostream>
#include <fstream>
#include <istream>
#include "Polinom.h"
#include "Monom.h"

using namespace std;


int main() 
{
    Polinom p1, p2, p3, p4;
    string str;
    ifstream in("put.txt");
    ofstream out("put.txt");
    Monom m1(1.0, 2, 4, 5);
    Monom m2(9.0, 1, 4, 2);
    Monom m4(-1.0, 0, 0, 2);
    Monom m5(-8.0, 5, 0, 5);
    p1.Add(m1);
    p1.Add(m2);
    p2.Add(m4);
    out << p1 << endl;
    out << p2 << endl;
    p3 = p1 - p2;
    out << p3 << endl;
    p4 = p1 * p3;
    out << p4 << endl;
    out.close();
    in >> p1;
    in >> p2;
    in >> p3;
    in >> p4;
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    return 0;
}