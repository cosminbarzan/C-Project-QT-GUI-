#pragma once
#include "repo.h"
#include <functional>
#include "validator.h"
#include "undo.h"

using std::function;

class DTO {
private:
	string tip;
	int count;

public:
	DTO(const string tip, const int count) : tip{ tip }, count{ count }{

	}

	void set_count() {
		this->count++;
	}

	string get_tip()const {
		return tip;
	}

	int get_count()const {
		return count;
	}

	bool operator<(const DTO& ot)const { return count < ot.count; }
};

class ServiceOferta {
private:
	RepoAbstract& repo;
	OfertaValidator& val;
	vector<unique_ptr<ActiuneUndo>> undoActions;
	vector<unique_ptr<ActiuneUndo>> redoActions;

	/*
		Functie de sortare generala
		compara - functie care compara 2 oferte, verifica daca are loc relatia mai mare

		returneaza o vector sortata dupa criteriu dat ca paramatru
	*/
	vector<Oferta> generalSort(bool(*compara)(const Oferta&, const Oferta&))const;

	/*
		Functie generala de filtrare
		fct - poate fi o functie
		returneaza doar ofertele care trec de filtru (fct(oferta) == true)
	*/
	vector<Oferta> filtreaza(function<bool(const Oferta&)> fct)const;
public:
	ServiceOferta(RepoAbstract& repo, OfertaValidator& val) :repo{ repo }, val{ val } {

	}

	ServiceOferta(const ServiceOferta& ot) = delete;

	/*
		Functie care adauga o oferta in vectorul de oferte
		Arunca exceptie daca exista deja
	*/
	void srv_adauga(string denumire, string destinatie, string tip, double pret);

	/*
		Functie care sterge o oferta din vectorul de oferte
		Arunca exceptie daca nu exista
	*/
	void srv_sterge(string denumire);

	/*
		Functie care modifica o oferta din vectorul de oferte
		Arunca exceptie daca nu exista
	*/
	void srv_modifica(string denumire, string destinatie, string tip, double pret);

	/*
		Functie care face undo
		Arunca exceptie daca nu mai exista actiuni pt undo
	*/
	void undo();

	/*
		Functie care face redo
		Arunca exceptie daca nu mai exista actiuni pt redo
	*/
	void redo();

	/*
		Functie care cauta o oferta in vectorul de oferte
		Returneaza oferta
		Arunca exceptie daca nu exista
	*/
	const Oferta& srv_cauta(string denumire) const;

	/*
		Functie care filtreaza ofertele dupa o destinatie specificata
	*/
	const vector<Oferta>& srv_filtrare_dest(string destinatie, vector<Oferta>& rez)const;

	/*
		Functie care filtreaza ofertele dupa un pret minim si un pret maxim specificate
	*/
	vector<Oferta> srv_filtrare_pret(double pretMin, double pretMax)const;

	/*
		Functie care sorteaza ofertele dupa denumire
	*/
	vector<Oferta> sort_denumire()const;

	/*
		Functie care sorteaza ofertele dupa destinatie
	*/
	vector<Oferta> sort_destinatie()const;

	/*
		Functie care sorteaza ofertele dupa tip+pret
	*/
	vector<Oferta> sort_tip_pret()const;

	const vector<DTO>& raport(vector<DTO>& rez)const;
	/*
		Functie care returneaza toate ofertele
	*/
	const vector<Oferta>& srv_get_all()const;

	/*
		Functie care adauga o oferta dupa denumire in cos
	*/
	void srv_adauga_cos(string denumire);

	/*
		Functie care sterge toate ofertele din cos
	*/
	void srv_sterge_cos();

	/*
		Functie care returneaza toate ofertele din cos
	*/
	const vector<Oferta>& srv_get_cos()const;

	/*
		Functie care returneaza numarul de oferte din cos
	*/
	size_t size_cos();

	/*
		Functie care populeaza aleator cosul cu un numar dat de oferte
	*/
	void srv_genereaza_cos(const int& nr);

	/*
		Functie care salveaza continutul cosului in fisier
	*/
	void srv_export_cos(string filename);
};