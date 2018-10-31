#include <iostream>

using namespace std;

typedef int typelementu;

struct typkomorki
{
	typelementu element;
	typkomorki* nast;
};

typedef typkomorki* pozycja;

class Lista
{
protected:
	pozycja l;
public:
	Lista()
	{
		pozycja glowa=new typkomorki;
		glowa->nast=NULL;
		l=glowa;
	}
	
	~Lista()
	{
	}
	
	void Wstaw(typelementu x, pozycja p)
	{
		pozycja nowy=new typkomorki;
		nowy->element=x;
		nowy->nast=p->nast;
		p->nast=nowy;
	}
	
	void Usun(pozycja p)
	{
		pozycja tymcz=p->nast;
		p->nast=tymcz->nast;
		tymcz->nast=NULL;
	}
	
	typelementu Odczytaj(pozycja p)
	{
		return p->nast->element;
	}
	
	pozycja Znajdz(typelementu x)
	{
		pozycja tymcz=l;
		while((tymcz->nast->element!=x)&&tymcz!=KONIEC())
		{
			tymcz=tymcz->nast;
		}
		if(tymcz!=KONIEC())
		{
			return tymcz;
		}
		else 
		{
			cout<<"Elementu nie ma w liście"<<endl;
			return NULL;
		}
	}
	
	pozycja Pierwszy()
	{
		return l;
	}
	
	pozycja Nastepny(pozycja p)
	{
		return p->nast;
	}
		
	pozycja Poprzedni(pozycja p)
	{
		if(p!=l&&p!=KONIEC())
		{
			pozycja tymcz=l;
			while(tymcz->nast!=p)
			{
				tymcz=tymcz->nast;
			}
			return tymcz;
		}
		else
		{
			cout<<"To jest pierwszy element."<<endl;
			return p;
		}	
	}
	
	pozycja KONIEC()
	{
		pozycja tymcz=l;
		while(tymcz->nast!=NULL)
		{
			tymcz=tymcz->nast;
		}
		return tymcz;
	}
};

void Wypisz_Liste(Lista lista)
{
	if(lista.Pierwszy()!=lista.KONIEC())
	{
		pozycja tymcz=lista.Pierwszy();
		while(lista.Nastepny(tymcz)!=lista.KONIEC())
		{
			cout<<lista.Odczytaj(tymcz)<<", ";
			tymcz=lista.Nastepny(tymcz);
		}
		cout<<lista.Odczytaj(tymcz)<<"."<<endl;
	}
	else
	{
		cout<<"Lista jest pusta."<<endl;
	}
}

int main ()
{
		Lista lista;
		Wypisz_Liste(lista);
		lista.Wstaw(1,lista.KONIEC());
		lista.Wstaw(2,lista.KONIEC());
		lista.Wstaw(3,lista.KONIEC());
		lista.Wstaw(4,lista.Pierwszy());
		Wypisz_Liste(lista);
		Wypisz_Liste(lista);
		lista.Usun(lista.Pierwszy());
		Wypisz_Liste(lista);
		lista.Wstaw(5,lista.Znajdz(2));
		Wypisz_Liste(lista);
		lista.Usun(lista.Znajdz(5));
		Wypisz_Liste(lista);
		cout<<""<<lista.Odczytaj(lista.Poprzedni(lista.Znajdz(1)))<<endl;
		return 0;	
}