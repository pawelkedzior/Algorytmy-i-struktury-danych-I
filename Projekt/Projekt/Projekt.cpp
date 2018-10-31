#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h> 
#include <memory>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

void CzyscEkr(){
  printf("\033[2J");
  printf("\033[0;0f");
}

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
 }

string Cyfry[10]={" 0",".,!?:\"()';/<>@#$%^&*+-=_~`[]{}|1\n","aąbcćAĄBCĆ","deęfDEĘF","ghiGHI","jklłJKLŁ","mnńoóMNŃOÓ","prsśPRSŚ","tuTU","wyzźżWYZŹŻ"};

int zakoduj(char odkod){
	int zakod;
	if(static_cast<int>(odkod)>57)
	{
	//cout<<"odkod:"<<odkod<<endl;
		for(int e=1;e<10;e++)
		{
			if(Cyfry[e].find(odkod)!=string::npos)
				{
					zakod=e;
					//cout<<endl<<"kod["<<e<<"]: "<<zakod<<endl<<endl;
					break;
				}
		}
	}
	CzyscEkr();
	return zakod;
}

char * charZPliku(const char * nazwa) {
    ifstream plik(nazwa);
    if(plik.bad()) {
        cout << "Plik nie istnieje lub nie masz do niego praw!" << endl;
        exit(-1);
    }    
    filebuf * buforPliku=plik.rdbuf();
    long jakDuzy=buforPliku->pubseekoff(0, ios::end, ios::in);
    plik.seekg(0);    
    char * zwrot=new char[jakDuzy+1];    
    plik.read(zwrot, jakDuzy);    
    return zwrot;
}

string przeszukajSlownik(int* zakodow, int ile, string ostatni)
{
	 const char * sciezka="Słownik.xml";
    auto_ptr <char> zawartosc_pliku(charZPliku(sciezka));
    xml_document <> dokument;
    try 
    {
        dokument.parse <0>(zawartosc_pliku.get());
    } 
    catch(parse_error p) 
    {
        p.what();
    }
    xml_node <> * slownik=dokument.first_node();
    string spr;
    for(int i=0;i<ile;i++)
	    spr[i]=static_cast<char>(zakodow[i]+48);
	 
	 xml_node <> * galaz=slownik->first_node();
	 int i=0;
	 bool znaleziono=false;
	 while(!znaleziono)
	 {
	 	char jaki[i+2];
	 	for (int j=0;j<i+1;j++)
	 	{
	 		jaki[j]=spr[j];
	 		jaki[j+1]='\0';
	 	}
	 	galaz=galaz->next_sibling();
	 	if(!galaz)
	 	{
	 		break;
	 	}
	 	if(strcmp(galaz->name(),jaki)==0)
	 	{
	 		i++;
	 		if(i==ile)
	 			znaleziono=true;
	 		else
	 		{
	 			galaz=galaz->first_node();
	 			if(!galaz)
	 			{
	 				break;
	 			}
	 		}
	 	}	 	
	 }
	 if(znaleziono)
	 {
	 	galaz=galaz->first_node();
	 	spr=galaz->value();
	 	spr=spr.substr(1,spr.length()-2);
	 	if(ostatni[0]==' ')
	 	{
	 		spr=spr.substr(0,ile);
	 	}
	 	else
	 	{
	 		size_t pozOstat=spr.find(ostatni);
	 		if((pozOstat!=string::npos)&&((pozOstat+ostatni.length()+1)<spr.length()))
	 			spr=spr.substr(pozOstat+ile+1,ile);
	 		else
	 			spr=spr.substr(0,ile);
	 	}	 	
	 }
    dokument.clear();
    return spr;
}

string odkoduj(int zakod[], int n)
{	
		string przekaz;
		if(n>1){
			char odkod[n];
			for (int i=0;i<n;i++)
				{
					odkod[i]=Cyfry[zakod[i]][0];
				}
			przekaz=odkod;
		}
		else
		{
			char odkod;
			odkod=Cyfry[zakod[0]][0];
			przekaz=odkod;
		}
		przekaz[n]='\0';
		przekaz=przeszukajSlownik(zakod, n, " ");
	return przekaz;
}

string T9(string wiadomosc, char znak){
		if(znak=='0')
		{
			znak=Cyfry[0][0];
			return wiadomosc+znak;
		}
		else 
		if(znak=='1')
		{
			znak=Cyfry[1][0];
			return wiadomosc+znak;
		}
		else 
		if(znak=='*') 
		{
			if(zakoduj(wiadomosc[wiadomosc.length()-1])==1)
			{
				char doZmiany=wiadomosc[wiadomosc.length()-1];
				int i=Cyfry[1].find_first_of(doZmiany)+1;
				if(doZmiany!='\n')
				doZmiany=Cyfry[1][i];
				else
				doZmiany=Cyfry[1][0];
				wiadomosc[wiadomosc.length()-1]=doZmiany;
				return wiadomosc;
			}
			else if(wiadomosc[wiadomosc.length()-1]==' ')
			{
				wiadomosc[wiadomosc.length()-1]='0';
				return wiadomosc;
			}
			else if(wiadomosc[wiadomosc.length()-1]=='0')
			{
				wiadomosc[wiadomosc.length()-1]=' ';
				return wiadomosc;
			}
			else
			{
				string slowo=wiadomosc.substr(wiadomosc.find_last_of(' ')+1);
				int jakDlugie=slowo.length();
				int kod[jakDlugie];
				int j=0;	
				for (int i=0;i<jakDlugie;i++)
				{
					kod[i]=zakoduj(slowo[i]);
					if(kod[i]==1)
						j=i+1;
				}					
				if(j>0)
				{
					int nowyKod[jakDlugie-j];
					for (int i=jakDlugie-j;i>0;i--)
					{
						nowyKod[jakDlugie-j-i]=kod[jakDlugie-i];
					}
					slowo=slowo.substr(j);
					slowo=przeszukajSlownik(nowyKod, jakDlugie-j, slowo);
					wiadomosc.replace(wiadomosc.find_last_of(' ')+1+j,slowo.length(),slowo);
				}
				else
				{							
					slowo=przeszukajSlownik(kod, jakDlugie, slowo);
					wiadomosc.replace(wiadomosc.find_last_of(' ')+1,slowo.length(),slowo);
				}				
				return wiadomosc;
			}
		}
		else
		{
			CzyscEkr();
			string slowo=wiadomosc.substr(wiadomosc.find_last_of(' ')+1)+znak;
			slowo[slowo.length()-1]=Cyfry[static_cast<int>(slowo[slowo.length()-1])-48][0];
			int dlug=slowo.length();
			int kod[dlug];	
			int j=0;	
			for (int i=0;i<dlug;i++)
				{
					kod[i]=zakoduj(slowo[i]);
					if(kod[i]==1)
						j=i+1;
				}
			if(j>0)
			{
				int nowyKod[dlug-j];
				for (int i=dlug-j;i>0;i--)
				{
					nowyKod[dlug-j-i]=kod[dlug-i];
				}
				slowo=odkoduj(nowyKod,dlug-j);
				wiadomosc.replace(wiadomosc.find_last_of(' ')+1+j,slowo.length(),slowo);
			}
			else
			{				
				slowo=odkoduj(kod,dlug);
				wiadomosc.replace(wiadomosc.find_last_of(' ')+1,slowo.length(),slowo);
			}
			return wiadomosc;
		}
	}

void piszWiad()
{
	int znak;
	string wiadomosc="";
	do
	{
		CzyscEkr();
		cout<<"Tu wpisz wiadomość. Możesz używać tylko cyfr."<<endl; //dopisz coś odnośnie znaków interpunkcyjnych
		cout<<"Aby zakończyć pisanie wiadomości wciśnij ENTER."<<endl;
		cout<<"Jeśli chcesz cofnąć wciśnij znak BACKSPACE."<<endl;
		cout<<endl<<"Wiadomość:"<<endl;
		
		cout<<wiadomosc;
		znak=getch();
		switch(znak)
		{
			case 127:		
				wiadomosc=wiadomosc.substr(0,wiadomosc.length()-1);
			break;
			case 42:
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
				wiadomosc=T9(wiadomosc,static_cast<char>(znak));			
			break;
			default:
			break;
		}			
	}
	while(znak!=10);
}

int main()
{
	int menu=0;
	do{
		CzyscEkr();
		cout<<"Co chcesz zrobić?"<<endl<<endl;
		cout<<"1. Napisać wiadomość"<<endl;
		cout<<"2. Wyjść"<<endl;
		menu=getch()-48;
		switch(menu)
		{
			case 1:
			{
				CzyscEkr();
				piszWiad();
			}
			break;
			case 2:
			{
			}
			break;
			default:
			{
				CzyscEkr();
				cout<<"Podałeś błędną liczbę."<<endl;
				getch();
			}
			break;
		}
	}
	while(menu!=2);
	CzyscEkr();
	return 0;
}