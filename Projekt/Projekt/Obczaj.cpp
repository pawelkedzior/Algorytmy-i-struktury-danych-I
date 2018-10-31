#include <iostream>
#include <fstream>
#include <string>
#include <memory> // (1)
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

inline char * stringToChar( string & s ) {
    long long N = s.length();
    char * out = new char[ N + 1 ];
    ::copy( s.c_str(),( s.c_str() + N - 1 ), out ); // (2)
    return out;
}

char * plikDoChar( const char * nazwa_pliku ) {
    ifstream plik( nazwa_pliku );
    if( plik.bad() ) { // (3)
        cout << "Plik nie istnieje lub nie masz do niego praw!" << endl;
        exit( - 1 );
    }
    
    filebuf * pbuf = plik.rdbuf(); // (4)
    long long wielkosc_pliku = pbuf->pubseekoff( 0, ios::end, ios::in );
    plik.seekg( 0 ); // (5)
    
    char * wyjscie = new char[ wielkosc_pliku + 1 ];
    
    plik.read( wyjscie, wielkosc_pliku ); // (6)
    
    return wyjscie;
}

void wyswietlAtrybuty( xml_node <> * wezel ) {
    for( xml_attribute <>* atrybut = wezel->first_attribute(); atrybut; atrybut = atrybut->next_attribute() ) // (7)
         cout << " atrybut '" << atrybut->name() << "' = '" << atrybut->value() << "'\t";
    
    cout << endl;
}

int main() {
    const char * nazwa_pliku = "./Słownik.xml";
    auto_ptr < char > zawartosc_pliku( plikDoChar( nazwa_pliku ) );
    xml_document <> dokument;
    try {
        dokument.parse < 0 >( zawartosc_pliku.get() ); // (8)
    } catch( parse_error p ) {
        p.what();
        cout<<p.what();
    }
    xml_node <> * korzen = dokument.first_node(); // (10)
    cout<<korzen->name()<<endl;
    if(dokument.first_node()!=0)
    	cout<<"tu też"<<endl;
    for( xml_node <> * galazka = korzen->first_node(); galazka; galazka = galazka->next_sibling() ) { // (11)
        {cout << "Mamy teraz wezel: '" << galazka->name() << "', ma atrybuty:\t";}
        
        /*for( xml_node <> * galazeczka = galazka->first_node(); galazeczka; galazeczka = galazeczka->next_sibling() )
             cout << "\tteraz '" << galazeczka->name() << "' co ma " << galazeczka->first_attribute()->value() << "lat\ti niesie przeslanie '" << galazeczka->value() << "'\n";*/
        
    }
    dokument.clear(); // (12)
    return 0;
}