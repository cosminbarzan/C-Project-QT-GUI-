#include "repo.h"
#include <algorithm>
#include <fstream>

#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

void RepoOferta::store(const Oferta& oferta)
{
	auto exista = std::find_if(oferte.begin(), oferte.end(), [oferta](const Oferta& o) {
		return o == oferta;
		});
	if (exista != oferte.end()) {
		throw RepoException("Oferta exista deja!");
	}
	cout << "Start push_back\n";
	oferte.push_back(oferta);
	cout << "Stop push_back\n";
}

void RepoOferta::sterge(const Oferta& oferta)
{
	auto exista = std::find_if(oferte.begin(), oferte.end(), [oferta](const Oferta& o) {
		return o == oferta;
		});
	if (exista != oferte.end()) {
		oferte.erase(exista);
		return;
	}
	throw RepoException("Oferta inexistenta!");
}

void RepoOferta::modifica(const Oferta& oferta)
{
	auto exista = std::find_if(oferte.begin(), oferte.end(), [oferta](const Oferta& o) {
		return o == oferta;
		});
	if (exista != oferte.end()) {
		*exista = oferta;
		return;
	}
	throw RepoException("Oferta inexistenta!");
}

const Oferta& RepoOferta::cauta(const Oferta& oferta)const
{
	auto exista = std::find_if(oferte.begin(), oferte.end(), [oferta](const Oferta& o) {
		return o == oferta;
		});
	if (exista != oferte.end()) {
		return *exista;
	}
	throw RepoException("Oferta inexistenta!");
}

const vector<Oferta>& RepoOferta::get_all() const
{
	return oferte;
}

void RepoOferta::adauga_cos(const Oferta& oferta)
{
	auto exista = std::find_if(cos.begin(), cos.end(), [oferta](const Oferta& o) {
		return o == oferta;
		});
	if (exista != cos.end()) {
		throw RepoException("Oferta exista deja!");
	}
	cos.push_back(oferta);
}

void RepoOferta::sterge_cos()
{
	cos.clear();
}

size_t RepoOferta::sizec()
{
	return cos.size();
}

const vector<Oferta>& RepoOferta::get_cos() const
{
	return cos;
}

void RepoOferta::genereaza_cos(const int& nr)
{
	auto rez = oferte;

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(rez.begin(), rez.end(), std::default_random_engine(seed)); //amesteca vectorul v

	std::copy_if(rez.begin(), rez.begin() + nr, std::back_inserter(cos), [](const Oferta& o) {return true; });
}

string RepoException::getMessage() const
{
	return msg;
}

void RepoOfertaFile::loadFromFile()
{
	std::ifstream in(filename);
	if (!in.is_open()) {
		throw RepoException("Imposibil de deschis fisierul: " + filename);
	}
	while (!in.eof()) {
		string denumire;
		in >> denumire;
		string destinatie;
		in >> destinatie;
		string tip;
		in >> tip;
		if (in.eof())
			break;
		double pret;
		in >> pret;

		Oferta o{ denumire, destinatie, tip, pret };
		RepoOferta::store(o);
	}
	in.close();
}

void RepoOfertaFile::writeToFile()
{
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw RepoException("Imposibil de deschis fisierul: " + filename);
	}
	for (auto o : get_all()) {
		out << o.getDenumire() << "\n";
		out << o.getDestinatie() << "\n";
		out << o.getTip() << "\n";
		out << o.getPret() << "\n";
	}
	out.close();
}
