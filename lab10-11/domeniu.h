#pragma once
#include <string>
#include <iostream>

using std::cout;

using std::string;

class Oferta {
private:
	string denumire;
	string destinatie;
	string tip;
	double pret;

public:
	Oferta(string den, string dest, string tip, double pret) : denumire{ den }, destinatie{ dest }, tip{ tip }, pret{ pret } {

	}

	/*Functie care furnizeaza denumirea pt obiectul curent*/
	string getDenumire() const {
		return denumire;
	}

	/*Functie care furnizeaza destinatia pt obiect curent*/
	string getDestinatie() const {
		return destinatie;
	}

	/*Functie care furnizeaza tipul pt obiectul curent*/
	string getTip() const {
		return tip;
	}

	/*Functie care furnizeaza pretul pt obiectul curent*/
	double getPret() const {
		return pret;
	}

	/*Functie de suprascriere a operatorului == intre doua oferte*/
	bool operator==(const Oferta& ot) const;

	/*Constructor de copiere*/
	Oferta(const Oferta& ot) :denumire{ ot.denumire }, destinatie{ ot.destinatie }, tip{ ot.tip }, pret{ ot.pret }{
		cout << "!!!!!!!!!!!!!!!!!!\n";
	}

	const Oferta& operator=(const Oferta& ot);
};

bool cmpDenumire(const Oferta& o1, const Oferta& o2);

bool cmpDestinatie(const Oferta& o1, const Oferta& o2);