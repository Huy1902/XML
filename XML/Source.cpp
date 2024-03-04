#include <iostream>
#include "XmlTree.h"
using namespace std;

int main()
{
	string s;
	cin >> s;
	XmlTree a;
	a.parseXmlFile(s);
}
