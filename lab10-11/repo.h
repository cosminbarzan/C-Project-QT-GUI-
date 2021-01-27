#pragma once
#include "domeniu.h"
//#include "vector.h"
#include <vector>
#include <random>

using std::vector;

class RepoException {
private:
	string msg;
public:
	RepoException(string m) :msg{ m } {

	}

	string getMessage() const;
};


class RepoAbstract {
public:
	virtual void store(const Oferta& oferta) = 0;
	virtual void sterge(const Oferta& oferta) = 0;
	virtual void modifica(const Oferta& oferta) = 0;
	virtual const Oferta& cauta(const Oferta& oferta) const = 0;
	virtual const vector<Oferta>& get_all() const = 0;
	virtual void adauga_cos(const Oferta& oferta) = 0;
	virtual void sterge_cos() = 0;
	virtual size_t sizec() = 0;
	virtual const vector<Oferta>& get_cos() const = 0;
	virtual void genereaza_cos(const int& nr) = 0;
	virtual ~RepoAbstract() = default;
};

class RepoOferta :public RepoAbstract {
private:
	vector<Oferta> oferte;
	vector<Oferta> cos;
public:
	/*Constructorul de copiere - nu dorim sa se faca copii ale obiectelor*/
	RepoOferta(const RepoOferta& ot) = delete;

	/*Constructorul default*/
	RepoOferta() = default;

	virtual ~RepoOferta() = default;
	/*
		Functie care adauga o oferta in vectorul de oferte
		Arunca exceptie daca exista deja
	*/
	virtual void store(const Oferta& oferta) override;

	/*
		Functie care sterge o oferta din vectorul de oferte
		Arunca exceptie daca nu exista
	*/
	virtual void sterge(const Oferta& oferta) override;

	/*
		Functie care modifica o oferta din vectorul de oferte
		Arunca exceptie daca nu exista
	*/
	virtual void modifica(const Oferta& oferta) override;

	/*
		Functie care cauta o oferta in vectorul de oferte
		Returneaza oferta
		Arunca exceptie daca nu exista
	*/
	const Oferta& cauta(const Oferta& oferta) const override;

	/*
		Functie care returneaza toate ofertele in ordinea in care au fost introduse
	*/
	const vector<Oferta>& get_all() const override;

	/*
		Functie care adauga o oferta dupa denumire in cos
	*/
	void adauga_cos(const Oferta& oferta) override;

	/*
		Functie care sterge ofertele din cos
	*/
	void sterge_cos() override;

	size_t sizec() override;
	/*
		Functie care returneaza toate ofertele din cos in ordinea in care au fost introduse
	*/
	const vector<Oferta>& get_cos() const override;

	/*
		Functie care populeaza aleator cosul cu un numar dat de oferte
	*/
	void genereaza_cos(const int& nr) override;
};


class RepoOfertaFile :public RepoOferta {
private:
	string filename;
	void loadFromFile();
	void writeToFile();
public:
	RepoOfertaFile(string filename) : RepoOferta(), filename{ filename }{
		loadFromFile();
	}

	void store(const Oferta& oferta) override {
		RepoOferta::store(oferta);
		writeToFile();
	}

	void sterge(const Oferta& oferta) override {
		RepoOferta::sterge(oferta);
		writeToFile();
	}

	void modifica(const Oferta& oferta) override {
		RepoOferta::modifica(oferta);
		writeToFile();
	}
};

class RepoProb : public RepoOferta {
private:
	int p;
public:
	RepoProb(int p) : RepoOferta(), p{ p } {

	}
	void store(const Oferta& oferta) override {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, 9);
		int rndNr = dist(mt);
		if (rndNr < p) {
			string msg;
			msg += "Probabilitate ";
			msg += ((char)p + '0');
			throw RepoException(msg);
		}
		RepoOferta::store(oferta);
	}

	void sterge(const Oferta& oferta) override {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, 9);
		int rndNr = dist(mt);
		if (rndNr < p) {
			string msg;
			msg += "Probabilitate ";
			msg += ((char)p + '0');
			throw RepoException(msg);
		}
		RepoOferta::sterge(oferta);
	}

	void modifica(const Oferta& oferta) override {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, 9);
		int rndNr = dist(mt);
		if (rndNr < p) {
			string msg;
			msg += "Probabilitate ";
			msg += ((char)p + '0');
			throw RepoException(msg);
		}
		RepoOferta::modifica(oferta);
	}
};