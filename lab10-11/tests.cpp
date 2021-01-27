#include "tests.h"
#include <assert.h>
#include "repo.h"
#include "service.h"

void test_oferta()
{
	Oferta o{ "aaa","bbb","ccc",4 };
	Oferta o2{ "aaa","ddd","ddd",5 };
	assert(o == o2);

	assert(strcmp(o.getDenumire().c_str(), "aaa") == 0);
	assert(strcmp(o.getDestinatie().c_str(), "bbb") == 0);
	assert(strcmp(o.getTip().c_str(), "ccc") == 0);
	assert(o.getPret() == 4);
}

void test_repo_store()
{
	RepoOferta repo;
	Oferta o{ "aaa","bbb","ccc",6 };
	repo.store(o);
	const auto& oferte = repo.get_all();
	assert(oferte.size() == 1);

	Oferta o2{ "ccc","bbb","ddd",5 };
	repo.store(o2);
	const auto& oferte2 = repo.get_all();
	assert(oferte2.size() == 2);

	try {
		repo.store(o);
		//assert(false)
	}
	catch (RepoException & ex) {
		//assert(true)
		assert(ex.getMessage() == "Oferta exista deja!");
	}

}

void test_srv_adauga()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	srv.srv_adauga("aa", "bb", "cc", 5);
	const auto& oferte = srv.srv_get_all();
	assert(oferte.size() == 1);
}

void test_repo_sterge()
{
	RepoOferta repo;
	Oferta o{ "aaa","bbb","ccc",1 };
	repo.store(o);

	Oferta o2{ "ccc","bbb","ccc",1 };
	repo.store(o2);

	Oferta o3{ "ddd","bbb","ccc",1 };
	repo.store(o3);

	assert(repo.get_all().size() == 3);

	repo.sterge(o2);
	auto oferte = repo.get_all();
	assert(oferte.size() == 2);
	assert(oferte[1].getDenumire() == "ddd");

	try {
		repo.sterge(o2);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta inexistenta!");
	}
}

void test_srv_sterge()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	srv.srv_sterge("aaa");
	const auto& oferte = srv.srv_get_all();
	assert(oferte.size() == 0);
}

void test_repo_modifica()
{
	RepoOferta repo;
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	o = { "sss","bbb","ccc",3 };
	repo.store(o);

	o = { "aaa","xxx","www",8 };
	repo.modifica(o);
	auto oferte = repo.get_all();
	assert(oferte[0].getDenumire() == "aaa");
	assert(oferte[0].getDestinatie() == "xxx");
	assert(oferte[0].getTip() == "www");
	assert(oferte[0].getPret() == 8);

	o = { "qqq","xxx","www",8 };

	try {
		repo.modifica(o);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta inexistenta!");
	}
}

void test_srv_modifica()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	srv.srv_modifica("aaa", "ddd", "ddd", 1);
	auto oferte = srv.srv_get_all();
	assert(oferte[0].getDestinatie() == "ddd");
	assert(oferte[0].getPret() == 1);
}

void test_srv_cauta()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	const auto& oferta = srv.srv_cauta("aaa");
	assert(oferta.getDestinatie() == "bbb");
	assert(oferta.getPret() == 3);

	try {
		srv.srv_cauta("bbb");
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta inexistenta!");
	}
}

void test_filtrare_dest()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","aaa","lll",9.4 };
	repo.store(o);

	o = { "vvv","bbb","lll",9.4 };
	repo.store(o);

	vector<Oferta> rez;
	auto oferte = srv.srv_filtrare_dest("bbb", rez);
	assert(oferte.size() == 2);
	assert(oferte[0].getDenumire() == "aaa");
	assert(oferte[1].getDenumire() == "vvv");
}

void test_filtrare_pret()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","aaa","lll",9.4 };
	repo.store(o);

	o = { "vvv","bbb","lll",11 };
	repo.store(o);

	vector<Oferta> rez;
	rez = srv.srv_filtrare_pret(1, 2);
	assert(rez.size() == 0);

	rez = srv.srv_filtrare_pret(9.2, 11);
	assert(rez.size() == 2);
	assert(rez[0].getDenumire() == "ccc");
	assert(rez[1].getDenumire() == "vvv");
}

void test_srv_sort_denumire()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	vector<Oferta> rez;

	rez = srv.sort_denumire();
	assert(rez.size() == 0);

	Oferta o{ "vvv","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","aaa","lll",9.4 };
	repo.store(o);

	o = { "vzz","bbb","lll",11 };
	repo.store(o);

	rez = srv.sort_denumire();
	assert(rez.size() == 3);
	assert(rez[0].getDenumire() == "ccc");
	assert(rez[1].getDenumire() == "vvv");
	assert(rez[2].getDenumire() == "vzz");
}

void test_srv_sort_destinatie()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	vector<Oferta> rez;

	rez = srv.sort_destinatie();
	assert(rez.size() == 0);

	Oferta o{ "vvv","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","abc","aaa",9.4 };
	repo.store(o);

	o = { "vzz","aaa","lll",11 };
	repo.store(o);

	rez = srv.sort_destinatie();
	assert(rez.size() == 3);
	assert(rez[0].getDestinatie() == "aaa");
	assert(rez[1].getDestinatie() == "abc");
	assert(rez[2].getDestinatie() == "bbb");
}

void test_srv_sort_tip_pret()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	vector<Oferta> rez;

	rez = srv.sort_tip_pret();
	assert(rez.size() == 0);

	Oferta o{ "vvv","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","abc","aaa",9.4 };
	repo.store(o);

	o = { "vzz","aaa","ccc",11 };
	repo.store(o);

	rez = srv.sort_tip_pret();
	assert(rez.size() == 3);
	assert(rez[0].getTip() == "aaa");
	assert(rez[1].getTip() == "ccc");
	assert(rez[1].getPret() == 3);
	assert(rez[2].getTip() == "ccc");
	assert(rez[2].getPret() == 11);
}

void test_validator()
{
	Oferta o{ "","","",-1 };
	OfertaValidator val;

	try {
		val.valideaza(o);
		assert(false);
	}
	catch (ValidateException & ex) {
		assert(ex.getMessage() == "Denumire vida!Destinatie vida!Tip vid!Pret negativ!");
	}
}

void test_srv_raport()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Oferta o{ "aaa","bbb","ccc",3 };
	repo.store(o);

	o = { "ccc","aaa","lll",9.4 };
	repo.store(o);

	o = { "vvv","bbb","lll",9.4 };
	repo.store(o);

	vector<DTO> rez;
	const auto& rap = srv.raport(rez);
	assert(rap[0].get_tip() == "ccc");
	assert(rap[0].get_count() == 1);

	assert(rap[1].get_tip() == "lll");
	assert(rap[1].get_count() == 2);
}

void test_adauga_cos()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	try {
		srv.srv_adauga_cos("aa");
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta inexistenta!");
	}

	srv.srv_adauga("aa", "bb", "cc", 5);

	try {
		srv.srv_adauga_cos("bb");
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta inexistenta!");
	}

	srv.srv_adauga_cos("aa");
	const auto& cos = repo.get_cos();
	assert(cos.size() == 1);
	assert(cos[0].getDenumire() == "aa");
	assert(cos[0].getTip() == "cc");

	try {
		srv.srv_adauga_cos("aa");
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Oferta exista deja!");
	}
}

void test_sterge_cos()
{
	RepoOferta repo;
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	srv.srv_adauga("aaa", "bbb", "ccc", 1);
	srv.srv_adauga("ddd", "eee", "fff", 2);
	srv.srv_adauga_cos("aaa");
	srv.srv_adauga_cos("ddd");

	const auto& cos = repo.get_cos();
	assert(cos.size() == 2);

	srv.srv_sterge_cos();
	assert(cos.size() == 0);
}
