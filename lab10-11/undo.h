#pragma once
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	RepoAbstract& repo;
	Oferta oferta;
public:
	UndoAdauga(RepoAbstract& repo, const Oferta& oferta) :repo{ repo }, oferta{ oferta }{

	}
	void doUndo() override {
		repo.sterge(oferta);
	}
	void doRedo() override {
		repo.store(oferta);
	}
};

class UndoSterge :public ActiuneUndo {
	RepoAbstract& repo;
	Oferta oferta;
public:
	UndoSterge(RepoAbstract& repo, const Oferta& oferta) :repo{ repo }, oferta{ oferta }{

	}
	void doUndo() override {
		repo.store(oferta);
	}
	void doRedo() override {
		repo.sterge(oferta);
	}
};

class UndoModifica :public ActiuneUndo {
	RepoAbstract& repo;
	Oferta ofertaVeche;
	Oferta ofertaNoua;
public:
	UndoModifica(RepoAbstract& repo, const Oferta& ofertaV, const Oferta& ofertaN) :repo{ repo }, ofertaVeche{ ofertaV }, ofertaNoua{ ofertaN }{

	}
	void doUndo() override {
		repo.modifica(ofertaVeche);
	}
	void doRedo() override {
		repo.modifica(ofertaNoua);
	}
};