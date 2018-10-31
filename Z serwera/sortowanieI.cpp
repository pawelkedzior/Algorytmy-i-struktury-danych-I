#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

void wypisz(int a[],int l, int n)
{
  for(int i=l;i<n;i++)
    {
      if(i!=n-1)
	printf("%d, ",a[i]);
      else
	printf("%d\n",a[i]);
    }
}

void bitmerge (int l, int m, int r, int a[])
{
  int aux[r];
  for (int i=0;i<r;i++)
    {
      if(!(i>m))
	aux[i]=a[i];
      else
	aux[i]=a[r-(i-m-1)];
    }
  int i=0;
  int j=r;
  int g=0;
  do
    {
      if(aux[i]<aux[j])
	{
	  a[g]=aux[i];
	  i++;
	}
      else
	{
	  a[g]=aux[j];
	  j--;
	}
      g++;
    }
  while(g==r);
  //  wypisz(a,l,m);
}

void mergesort (int l, int r, int a[])
{
  int m;
  if (l<r)
    {
      m=(l+r)/2;
      mergesort(l,m,a);
      mergesort(m+1,r,a);
      bitmerge(l,m,r,a);
    }
}

int main ()
{ 
  cout<<"Ile elementów ma zawierać tablica?"<<endl;
  int n;
  cin>>n;
  int a[n];
  for (int i=0;i<n;i++)
    a[i]=rand()%1000+1;
  wypisz(a,0,n);
  mergesort(0,2,a);
  wypisz(a,0,n); 
  return 0;
}
