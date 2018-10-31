#include <cstdio>

typedef int elementtype, position ;
const int maxlength=10;
struct List
{
	elementtype elements[maxlength];
	int last;           //indeks ostatniego elementu listy
};

position END(List l)
{ 
  return l.last+1;
}

position First(List l) 
{
  return 0;
}

position Next(position p,List l)
{
  if (p<l.last+1)
    return p+1;
  else
    return -1;
}

position Previous(position p,List l) 
{
  if (!(p<0))
    return p-1;
  else
    return -1;	
}

position Locate(elementtype x, List l) 
{ //zwraca pozycje x w l, gdy nie ma x w l zwraca end(l)
  for (int i=0;i<l.last;i++)
    if (l.elements[i]==x)
      return i;
  return l.last+1;
}

elementtype Retrieve(position p, List l) 
{
  if (p>=0&&p<l.last+1)
    return l.elements[p];
  else
    return -10000000;
}

bool Insert(int x, position p, List &l)
{
  if(l.last<maxlength)
    if ((!(p<0))&&(!(p>(l.last+1))))
      {
	for (int i=l.last+1;i>p;i--)
	  {
	    l.elements[i]=l.elements[i-1];
	  }
	l.elements[p]=x;
	l.last++;
	return true;
      }
    else
      {
	printf(":D");
	return false;
      }
  else
    return false;
}

bool Delete(position p, List &l)
{
  if (p>=0&&p<l.last+1)
    {
      for (int i=p;i<l.last+1;i++)
	l.elements[p]=l.elements[p+1];
      l.last--;
    }
  else
  return false;
}

void print(List l)
{
	position i=First(l);
	while (i!=END(l))
	{
	  if(i!=END(l)-1)
		printf ("%d,  ", Retrieve(i,l));
	  else
	        printf ("%d", Retrieve(i,l));
		i=Next(i,l);
	}
	printf("\n");
}

int main()
{
  List l;
  l.last=-1;
  Insert(100,First(l),l);
  print (l);
  for (int i=0; i<3;i++)
    Insert(i,First(l),l);
  print (l);
  Insert (20,Previous(END(l),l) ,l);
  print(l);
  Delete(Locate(20,l),l);
  Insert (5,Locate(0,l),l);
  print(l);
}
