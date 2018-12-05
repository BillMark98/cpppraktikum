#include <iostream>
#include <fstream>
#include <cstdlib>  // support exit()
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ifstream;
using std::ostream;
using std::ofstream;
using std::string;
using std::vector;
using std::list;

typedef struct
{
    int Tag;
    int Monat;
    int Jahr;
    bool gueltig() const;
}Datum;
typedef struct
{
    string Nachname;
    string Vorname;
    string Email;
    int MatNr;
    Datum Geburtstag;
}Person;
typedef vector<Person> AdressbuchT;
typedef list<Datum> GebListeT;
typedef vector<Person>::const_iterator const_Piter;
typedef list<Datum>::const_iterator const_Diter;

void Datum_schreiben(ostream& out, const Datum& datum)
{
    out << datum.Tag << "." << datum.Monat << "."
        << datum.Jahr;
}

void Person_schreiben(ostream& out, const Person& person)
{
    out << person.Nachname << " " << person.Vorname << " "
        << person.Email << " " << person.MatNr << " ";
    Datum_schreiben( out, person.Geburtstag);
}

void AB_schreiben(ostream& out, const AdressbuchT& AB)
{
    for (int i= 0; i < AB.size(); i++) 
    {
        Person_schreiben( out, AB[i]);
        out << "\n";
    }
}

void Datum_lesen(istream& in, Datum& datum)
{
    in >> datum.Jahr >> datum.Monat >> datum.Tag;
}

void Person_lesen(istream& in, Person& person)
{
    in >> person.Nachname;
    in >> person.Vorname;
    in >> person.Email;
    in >> person.MatNr;
    Datum_lesen(in, person.Geburtstag);
}

void AB_lesen(istream& in, AdressbuchT& AB)
{
    do 
    {
        Person person;
        Person_lesen(in,person);
        AB.push_back(person);
    } while (!in.eof());
}
void AB_output(ostream & out, const AdressbuchT& AB)
{
    int n = (int) AB.size();
    for(int index = 0; index < n; index++)
    {
        Person_schreiben(out, AB[index]);
        out << endl;
    }
}

void Geb_output(ostream & out, const GebListeT& geb);

void geboren_in(int Monat, const AdressbuchT& AB, AdressbuchT& MonatAB)
{
    for(const_Piter iter = AB.begin(); iter != AB.end(); iter++)
    {
        if((*iter).Geburtstag.Monat == Monat)
        {
            MonatAB.push_back((*iter));
        }
    }
}
void listeGueltigeGeb( const AdressbuchT& AB, GebListeT& geb);
// operator overloading for datum
istream& operator>> (istream & in, Datum& dat);
ostream& operator<< ( ostream& out, const Datum& dat);

// operator overloading for person
istream& operator>> (istream & in, Person& pers);
ostream& operator<< ( ostream& out, const Person& pers);

//operator overloading for AdressbuchT
istream& operator>> (istream & in, AdressbuchT& AB);
ostream& operator<< ( ostream& out, const AdressbuchT& AB);

//operator overloading for GebListeT
ostream& operator<<( ostream& out, const GebListeT& geb);

// operator relation for datum
bool operator< (const Datum & dat1, const Datum & dat2);
bool compare_datum(const Datum & dat1, const Datum & dat2);
int main()
{
    Person Ich;
    Ich.Nachname = "Hu";
    Ich.Vorname = "Panwei";
    Ich.Email = "panwei.hu@rwth-aachen.de";
    Ich.MatNr = 374218;
    Ich.Geburtstag.Tag = 9;
    Ich.Geburtstag.Monat = 7;
    Ich.Geburtstag.Jahr = 1998;

    ifstream datei;
    datei.open("Datum.txt");
    if (!datei.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    Datum testdatum;
    Datum_lesen(datei, testdatum);
    Datum_schreiben(cout,testdatum);
    cout << endl;
    cout << "Test reading person data.\n";
    datei.close();

    Person newone;
    datei.open("AB.txt");
    if (!datei.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    Person_lesen(datei,newone);
    Person_schreiben(cout,newone);
    cout << endl;
    datei.close();

    datei.open("AB.txt");
    if (!datei.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    AdressbuchT AB;
    AB_lesen(datei,AB);
    ofstream myout;
    myout.open("myoutput.txt");
    if (!myout.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    AB_output(myout,AB);
    AB.push_back(Ich);
    AdressbuchT MonatAB;
    geboren_in(Ich.Geburtstag.Monat,AB,MonatAB);
    myout.close();
    myout.open("monat.txt");
    if (!myout.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    AB_output(myout,MonatAB);

    // Gebliste test
    // filter allowed datum
    GebListeT geblist;
    listeGueltigeGeb(AB,geblist);
    myout.close();
    myout.open("allowed_datum.txt");
    if (!myout.is_open())
    {
        cout << "cannot open file.\n";
        exit(EXIT_FAILURE);
    }
    myout << geblist;
    myout << "\n\n\n************  Now sorting *********** \n\n\n";
    geblist.sort();
    myout << geblist;

    datei.close();
    myout.close();
    return 0;
}

istream& operator>> (istream & in, Datum& dat)
{
    Datum_lesen(in,dat);
    return in;
}
ostream& operator<< ( ostream& out, const Datum& dat)
{
    Datum_schreiben(out, dat);
    return out;
}
// operator overloading for person
istream& operator>> (istream & in, Person& pers)
{
    Person_lesen(in,pers);
    return in;
}
ostream& operator<< ( ostream& out, const Person& pers)
{
    Person_schreiben(out,pers);
    return out;
}

//operator overloading for AdressbuchT
istream& operator>> (istream & in, AdressbuchT& AB)
{
    AB_lesen(in,AB);
    return in;
}
ostream& operator<< ( ostream& out, const AdressbuchT& AB)
{
    AB_output(out,AB);
    return out;
}
bool Datum::gueltig() const
{
    if(Monat < 1 || Monat > 12)
    {
        return false;
    }
    if(Tag < 1 || Tag > 31)
    {
        return false;
    }
    return true;
}
void listeGueltigeGeb( const AdressbuchT& AB, GebListeT& geb)
{
    for(const_Piter iter = AB.begin(); iter != AB.end(); iter++)
    {
        if((*iter).Geburtstag.gueltig())
        {
            geb.push_back((*iter).Geburtstag);
        }
    }
}

//operator overloading for GebListeT
ostream& operator<<( ostream& out, const GebListeT& geb)
{
    Geb_output(out,geb);
    return out;
}

// operator relation for datum
bool operator< (const Datum & dat1, const Datum & dat2)
{
    if(dat1.Jahr < dat2.Jahr)
    {
        return true;
    }
    // incase dat1.Jahr < dat2.Jahr we shouldn't test next the month
    // but still the year. 
    // for example 1995/11/2  1922/12/1 so at first 1995 > 1922 so
    // we test the month and 11 < 12 so we give back true
    // but actually we should get > since 1995 > 1922
    else if(dat1.Jahr > dat2.Jahr)
    {
        return false;
    }
    else if(dat1.Monat < dat2.Monat)
    {
        return true;
    }
    else if(dat1.Monat > dat2.Monat)
    {
        return false;
    }
    else if(dat1.Tag < dat2.Tag)
    {
        return true;
    }
    else if(dat1.Tag > dat2.Tag)
    {
        return false;
    }
    return true;
}
void Geb_output(ostream & out, const GebListeT& geb)
{
    for(const_Diter iter = geb.begin(); iter != geb.end(); iter++)
    {
        out << (*iter) << endl;
    }
}

bool compare_datum(const Datum & dat1, const Datum & dat2)
{
    if(dat1.Jahr < dat2.Jahr)
    {
        return true;
    }
    else if(dat1.Jahr > dat2.Jahr)
    {
        return false;
    }
    else if(dat1.Monat < dat2.Monat)
    {
        return true;
    }
    else if(dat1.Monat > dat2.Monat)
    {
        return false;
    }
    else if(dat1.Tag < dat2.Tag)
    {
        return true;
    }
    else if(dat1.Tag > dat2.Tag)
    {
        return false;
    }
    return true;
}