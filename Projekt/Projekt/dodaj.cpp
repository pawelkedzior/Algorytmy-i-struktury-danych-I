#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
  fstream of,inf;
  inf.open("SłownikStary.txt",fstream::in);
  of.open("Słownik.txt",fstream::out);

while(!inf.eof())
{
	string lin;
	getline(inf,lin);
	of<<lin<<'\n';
}
  inf.close();
  of.close();
  return 0;
}