#include "service.h"
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>

vector<Oferta> ServiceOferta::generalSort(bool(*compara)(const Oferta&, const Oferta&))const
{
	vector<Oferta> v{ repo.get_all() };//fac o copie	

	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!compara(v[i], v[j])) {
				Oferta aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Oferta> ServiceOferta::filtreaza(function<bool(const Oferta&)> fct)const
{
	vector<Oferta> rez;
	for (const auto& oferta : repo.get_all()) {
		if (fct(oferta)) {
			cout << "Start push_back\n";
			rez.push_back(oferta);
			cout << "Stop push_back\n";
		}
	}
	return rez;
}

void ServiceOferta::srv_adauga(string denumire, string destinatie, string tip, double pret)
{
	Oferta oferta{ denumire, destinatie, tip, pret };
	val.valideaza(oferta);
	repo.store(oferta);
	undoActions.push_back(make_unique<UndoAdauga>(repo, oferta));
	redoActions.clear();
}

void ServiceOferta::srv_sterge(string denumire)
{
	Oferta oferta{ denumire, "", "", 0 };
	auto o = repo.cauta(oferta);
	repo.sterge(oferta);
	undoActions.push_back(make_unique<UndoSterge>(repo, o));
	redoActions.clear();
}

void ServiceOferta::srv_modifica(string denumire, string destinatie, string tip, double pret)
{
	Oferta ofertaNoua{ denumire, destinatie, tip, pret };
	val.valideaza(ofertaNoua);
	auto ofertaVeche = repo.cauta(ofertaNoua);
	repo.modifica(ofertaNoua);
	undoActions.push_back(make_unique<UndoModifica>(repo, ofertaVeche, ofertaNoua));
	redoActions.clear();
}

void ServiceOferta::undo()
{
	if (undoActions.empty()) {
		throw RepoException("Nu se mai poate face undo!");
	}
	undoActions.back()->doUndo();
	redoActions.push_back(std::move(undoActions.back()));
	undoActions.pop_back();
}

void ServiceOferta::redo()
{
	if (redoActions.empty()) {
		throw RepoException("Nu se mai poate face redo!");
	}
	redoActions.back()->doRedo();
	undoActions.push_back(std::move(redoActions.back()));
	redoActions.pop_back();
}

const Oferta& ServiceOferta::srv_cauta(string denumire) const
{
	Oferta oferta{ denumire,"","",0 };
	return repo.cauta(oferta);
}

const vector<Oferta>& ServiceOferta::srv_filtrare_dest(string destinatie, vector<Oferta>& rez) const
{
	const auto& oferte = repo.get_all();
	std::copy_if(oferte.begin(), oferte.end(), std::back_inserter(rez), [destinatie](const Oferta& o) {
		return o.getDestinatie() == destinatie;
		});
	return rez;
}

vector<Oferta> ServiceOferta::srv_filtrare_pret(double pretMin, double pretMax)const
{
	const auto& oferte = repo.get_all();
	vector<Oferta> rez;
	std::copy_if(oferte.begin(), oferte.end(), std::back_inserter(rez), [pretMin, pretMax](const Oferta& o) {
		return o.getPret() >= pretMin && o.getPret() <= pretMax;
		});
	return rez;
}


vector<Oferta> ServiceOferta::sort_denumire()const
{
	vector<Oferta> v{ repo.get_all() };
	std::sort(v.begin(), v.end(), cmpDenumire);
	return v;
	//return generalSort(cmpDenumire);
}

vector<Oferta> ServiceOferta::sort_destinatie()const
{
	vector<Oferta> v{ repo.get_all() };
	std::sort(v.begin(), v.end(), cmpDestinatie);
	return v;
	//return generalSort(cmpDestinatie);
}

vector<Oferta> ServiceOferta::sort_tip_pret()const {
	vector<Oferta> v{ repo.get_all() };
	std::sort(v.begin(), v.end(), [](const Oferta& o1, const Oferta& o2) {
		if (o1.getTip() == o2.getTip()) {
			return o1.getPret() < o2.getPret();
		}
		return o1.getTip() < o2.getTip();
		});
	return v;
}

const vector<DTO>& ServiceOferta::raport(vector<DTO>& rez) const
{
	map<string, DTO> m;
	map<string, DTO>::iterator itr;
	const auto& oferte = repo.get_all();
	for (const auto& o : oferte) {
		itr = m.find(o.getTip());
		if (itr != m.end()) {
			itr->second.set_count();
		}
		else {
			DTO p{ o.getTip(), 1 };
			m.insert(pair<string, DTO>(o.getTip(), p));
		}
	}

	for (itr = m.begin(); itr != m.end(); ++itr) {
		rez.push_back(itr->second);
	}
	sort(rez.begin(), rez.end());
	return rez;
}

const vector<Oferta>& ServiceOferta::srv_get_all()const
{
	return repo.get_all();
}

void ServiceOferta::srv_adauga_cos(string denumire)
{
	Oferta oferta{ denumire,"","",0 };
	const auto& o = repo.cauta(oferta);
	repo.adauga_cos(o);
}

void ServiceOferta::srv_sterge_cos()
{
	repo.sterge_cos();
}

const vector<Oferta>& ServiceOferta::srv_get_cos() const
{
	return repo.get_cos();
}

size_t ServiceOferta::size_cos()
{
	return repo.sizec();
}

void ServiceOferta::srv_genereaza_cos(const int& nr)
{
	repo.genereaza_cos(nr);
}

void ServiceOferta::srv_export_cos(string filename)
{
	ofstream out;
	out.open(filename);
	if (!out.is_open())
		throw RepoException("Unable to open: " + filename);
	const auto& cos = repo.get_cos();
	for (const auto& o : cos) {
		out << o.getDenumire() << "," << o.getDestinatie() << "," << o.getTip() << "," << o.getPret() << "\n";
	}
	out.close();
}
