#include<iostream>
#include"Person.h"
using namespace std;

Person::Person()
{
	m_strName = "Lorry";
}

void Person::play()
{
	cout << "Person--play()" << endl;
	cout << m_strName << endl;
}