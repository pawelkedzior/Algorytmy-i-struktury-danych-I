#include <iostream>
#include <cstdio>

using namespace std;

const int B=65;

typedef char* elementtype;

struct celltype
{
  elementtype element;
  celltype * next;
};

typedef celltype * position;

class dictionary
{
protected:
  position d[B];
public:
  dictionary(){
    for (int i=0;i<B;i++){
      d[i]=NULL;
    }
  }
  ~dictionary()
  {
    Makenull();
    for (int i=0;i<B;i++)
      {
	delete d[i];      
      }
  };
  void Makenull()
  {
    for(int i=0;i<B;i++){
      while(d[i]!=NULL){
	position usun=d[i];
	d[i]=d[i]->next;
	delete usun;
      }
    }
  }
  bool Member (elementtype x){
    int gdzie=H(x);
	cout<<"Tu jest OK."<<endl;
    if(d[gdzie]!=NULL)
      {
	position nast=d[gdzie];
	while(nast!=NULL)
	  {
	    if(nast->element==x)
	      {
		return true;
	      }
	    else
	      {
		nast=nast->next;
	      }
	  }
	return false;
      }
    else
      {
	return false;
      }
  }
  void Insert (elementtype x){
    if (!Member(x))
      {
	celltype dodaj;
	dodaj.element=x;
	int gdzie=H(x);
	dodaj.next=d[gdzie];
	d[gdzie]=&dodaj;
      }
    else
      {
	cout<<"Element już jest w słowniku"<<endl;
      }
  }
  void Delete (elementtype x){
    int gdzie=H(x);
    if ((d[gdzie]!=NULL)&&Member(x))
      {
	if(d[gdzie]->element==x)
	  {
	    position tymcz=d[gdzie]->next;
	    delete d[gdzie];
	    d[gdzie]=tymcz;
	  }
	else
	  {
	    position zachowaj=d[gdzie];
	    while(zachowaj->next->element!=x)
	      {
		zachowaj=zachowaj->next;
	      }	      
	    position usun=zachowaj->next;
	    zachowaj->next=usun->next;
	    delete usun;
	  }
      }
    else
      {
	cout<<"Element nie istnieje."<<endl;
      }
  }
  int H (elementtype x){
	char* znaki=x;
	cout<<znaki<<endl;
	cout<<"Tu jest OK w H."<<endl;
	char znak=znaki[0];
	cout<<"Tu jest OK w H."<<endl;
	  
    int zwrot=static_cast<int>(znak)%B;
    cout<<"Tu jest OK w H."<<endl;
    return zwrot;
  }
};

int main()
{
  cout<<"Podaj słowa jakie chcesz umieścić w tablicy."<<endl;
  dictionary Slownik;
  char* slowo;
  char znak;
  do
    {
      znak=getchar();
    }
  while (znak!='\n');
  for (int i=0;i<4;i++)
    {
      Slownik.Insert(slowo);
    }
  cout<<"Podaj słowo, które chcesz usunąć."<<endl;
      scanf("%s",slowo);
  Slownik.Delete(slowo);
  if (Slownik.Member(slowo))
    {
      cout<<"Słowo należy do słownika."<<endl;
    }
  else
    {
      cout<<"Słowo nie należy do słownika."<<endl;
    }
  cout<<"Podaj słowo, aby sprawdzić, czy należy do słownika."<<endl;
      scanf("%s",slowo);
  if (Slownik.Member(slowo))
    {
      cout<<"Słowo należy do słownika."<<endl;
    }
  else
    {
      cout<<"Słowo nie należy do słownika."<<endl;
    }
  cout<<"Opróżniam tablicę"<<endl;
  Slownik.Makenull();
  if (Slownik.Member(slowo))
    {
      cout<<"Teraz to słowo nadal należy do słownika."<<endl;
    }
  else
    {
      cout<<"Teraz to słowo nie należy do słownika."<<endl;
    }  
  return 0;
}
