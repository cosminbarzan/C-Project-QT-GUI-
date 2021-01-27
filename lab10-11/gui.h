#pragma once
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qspinbox.h>

class CosGui : public QWidget {
private:
	QListWidget* lst = new QListWidget;
public:
	CosGui() {
		QHBoxLayout* lyMain = new QHBoxLayout{};
		setLayout(lyMain);

		lyMain->addWidget(lst);

	}
	void load(vector<Oferta> oferte) {
		lst->clear();
		for (auto& o : oferte) {
			string afis;
			afis += o.getDenumire();
			afis += " ";
			afis += o.getDestinatie();
			afis += " ";
			afis += o.getTip();
			afis += " ";
			afis += ((char)o.getPret() + '0');
			lst->addItem(QString::fromStdString(afis));
		}
	}
};
class Gui: public QWidget {
public:
	Gui(ServiceOferta& srv) :srv{ srv } {
		initGui();
		loadData(srv.srv_get_all());
		initConnect();
		adaugaButoane(srv.srv_get_all());
	}
private:
	ServiceOferta& srv;
	QListWidget* lst = new QListWidget;
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdd = new QPushButton{ "&Adauga" };
	QPushButton* btnDel = new QPushButton{ "&Sterge" };
	QPushButton* btnC = new QPushButton{ "&Cauta" };
	QPushButton* btnMod = new QPushButton{ "&Modifica" };
	QPushButton* btnFD = new QPushButton{ "&Filtrare destinatie" };
	QPushButton* btnFP = new QPushButton{ "&Filtrare pret" };
	QPushButton* btnSDen = new QPushButton{ "&Sortare denumire" };
	QPushButton* btnSDes = new QPushButton{ "&Sortare destinatie" };
	QPushButton* btnSTP = new QPushButton{ "&Sortare tip+pret" };
	QPushButton* btnU = new QPushButton{ "&Undo" };
	QPushButton* btnR = new QPushButton{ "&Redo" };
	QPushButton* btnCos = new QPushButton{ "&Cos" };
	QPushButton* btnAddCos = new QPushButton{ "&Adauga Cos" };
	QPushButton* btnDelCos = new QPushButton{ "&Sterge Cos" };
	QPushButton* btnGenCos = new QPushButton{ "&Genereaza Cos" };
	QPushButton* btnExpCos = new QPushButton{ "&Export Cos" };
	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtDestinatie = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtFisier = new QLineEdit;
	QSpinBox* spAge = new QSpinBox();
	QSlider* slAge = new QSlider(Qt::Horizontal);
	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;
	vector<QPushButton*> btns;

	void adaugaButoane(const vector<Oferta>& oferte) {
		for (const auto& o : oferte) {
			auto btn = new QPushButton{QString::fromStdString(o.getDenumire())};
			lyBtnDy->addWidget(btn);
			btns.push_back(btn);
			QObject::connect(btn, &QPushButton::clicked, [this, btn, o]() {
				srv.srv_sterge(o.getDenumire());
				loadData(srv.srv_get_all());
				delete btn;
				});
		}
	}
	void deleteButoane() {
		for (auto btn : btns) {
			delete btn;
		}
		btns.clear();
	}
	void initConnect() {
		QObject::connect(btnExit, &QPushButton::clicked, [&]() {
			QMessageBox::information(nullptr, "Info", "Exit apasat!");
			close();
			});
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			auto denumire = txtDenumire->text().toStdString();
			auto destinatie = txtDestinatie->text().toStdString();
			auto tip = txtTip->text().toStdString();
			//auto pret = txtPret->text().toDouble();
			auto pret = spAge->value();
			try {
				srv.srv_adauga(denumire, destinatie, tip, pret);
				loadData(srv.srv_get_all());
				deleteButoane();
				adaugaButoane(srv.srv_get_all());
			}
			catch (ValidateException& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			});
		QObject::connect(btnDel, &QPushButton::clicked, [&]() {
			auto denumire = txtDenumire->text().toStdString();
			srv.srv_sterge(denumire);
			loadData(srv.srv_get_all());
			deleteButoane();
			adaugaButoane(srv.srv_get_all());
			});
		QObject::connect(btnC, &QPushButton::clicked, [&]() {
			auto denumire = txtDenumire->text().toStdString();
			const auto& o = srv.srv_cauta(denumire);
			string afis;
			afis += o.getDenumire();
			afis += " ";
			afis += o.getDestinatie();
			afis += " ";
			afis += o.getTip();
			afis += " ";
			afis += ((char)o.getPret() + '0');
			QString afis2 = QString::fromStdString(afis);
			QMessageBox::information(nullptr, "Cautare", afis2);
			});
		QObject::connect(btnMod, &QPushButton::clicked, [&]() {
			auto denumire = txtDenumire->text().toStdString();
			auto destinatie = txtDestinatie->text().toStdString();
			auto tip = txtTip->text().toStdString();
			auto pret = txtPret->text().toDouble();
			srv.srv_modifica(denumire, destinatie, tip, pret);
			loadData(srv.srv_get_all());
			QMessageBox::information(nullptr, "Modifica", "Oferta modificata!");
			});
		QObject::connect(btnFD, &QPushButton::clicked, [&]() {
			auto destinatie = txtDestinatie->text().toStdString();
			vector <Oferta> rez;
			const auto& oferte = srv.srv_filtrare_dest(destinatie, rez);
			loadData(oferte);
			deleteButoane();
			adaugaButoane(oferte);
			});
		QObject::connect(btnFP, &QPushButton::clicked, [&]() {
			
			});
		QObject::connect(btnSDen, &QPushButton::clicked, [&]() {
			loadData(srv.sort_denumire());
			deleteButoane();
			adaugaButoane(srv.sort_denumire());
			});
		QObject::connect(btnSDes, &QPushButton::clicked, [&]() {
			loadData(srv.sort_destinatie());
			deleteButoane();
			adaugaButoane(srv.sort_destinatie());
			});
		QObject::connect(btnSTP, &QPushButton::clicked, [&]() {
			loadData(srv.sort_tip_pret());
			deleteButoane();
			adaugaButoane(srv.sort_tip_pret());
			});
		QObject::connect(btnU, &QPushButton::clicked, [&]() {
			srv.undo();
			loadData(srv.srv_get_all());
			deleteButoane();
			adaugaButoane(srv.srv_get_all());
			});
		QObject::connect(btnR, &QPushButton::clicked, [&]() {
			srv.redo();
			loadData(srv.srv_get_all());
			deleteButoane();
			adaugaButoane(srv.srv_get_all());
			});
		QObject::connect(btnCos, &QPushButton::clicked, [&]() {
			auto gui = new CosGui{};
			gui->load(srv.srv_get_cos());
			gui->show();
			});
		QObject::connect(btnAddCos, &QPushButton::clicked, [&]() {
			auto denumire = txtDenumire->text().toStdString();
			try {
				srv.srv_adauga_cos(denumire);
			}
			catch (ValidateException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			});
		QObject::connect(btnDelCos, &QPushButton::clicked, [&]() {
			try {
				srv.srv_sterge_cos();
			}
			catch (ValidateException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			});
		QObject::connect(btnGenCos, &QPushButton::clicked, [&]() {
			try {
				srv.srv_sterge_cos();
				auto nr = spAge->value();
				srv.srv_genereaza_cos(nr);
			}
			catch (ValidateException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			});
		QObject::connect(btnExpCos, &QPushButton::clicked, [&]() {
			auto filename = txtFisier->text().toStdString();
			try {
				srv.srv_export_cos(filename);
			}
			catch (ValidateException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
			});

		QObject::connect(spAge,
			SIGNAL(valueChanged(int)), slAge, SLOT(setValue(int)));
		
		QObject::connect(slAge,
			SIGNAL(valueChanged(int)), spAge, SLOT(setValue(int)));
		
		QObject::connect(spAge, SIGNAL(valueChanged(int)), slAge,
			SLOT(setValue(int)));
		
		QObject::connect(slAge, &QSlider::valueChanged, [&](int val) {
			spAge->setValue(val); 
			}
		);

	}
	void loadData(vector<Oferta> oferte) {
		lst->clear();
		for (auto& o : oferte) {
			string afis;
			afis += o.getDenumire();
			afis += " ";
			afis += o.getDestinatie();
			afis += " ";
			afis += o.getTip();
			afis += " ";
			afis += ((char)o.getPret() + '0');
			lst->addItem(QString::fromStdString(afis));
		}
	}
	void initGui() {
		QHBoxLayout* lyMain = new QHBoxLayout{};
		QGridLayout* lyGrid = new QGridLayout{};
		setLayout(lyMain);
		
		lyMain->addWidget(lst);

		auto stgLy = new QVBoxLayout{};

		auto formLy = new QFormLayout;
		formLy->addRow("Denumire", txtDenumire);
		formLy->addRow("Destinatie", txtDestinatie);
		formLy->addRow("Tip", txtTip);
		formLy->addRow("Pret", txtPret);
		stgLy->addLayout(formLy);
		stgLy->addWidget(spAge);

		auto lyVBtn = new QVBoxLayout{};

		auto lyBtn1 = new QHBoxLayout{};
		lyBtn1->addWidget(btnAdd);
		lyBtn1->addWidget(btnDel);
		lyBtn1->addWidget(btnC);
		lyBtn1->addWidget(btnMod);
		lyBtn1->addWidget(btnFD);
		lyBtn1->addWidget(btnFP);
		lyVBtn->addLayout(lyBtn1);

		auto lyBtn2 = new QHBoxLayout{};
		lyBtn2->addWidget(btnSDen);
		lyBtn2->addWidget(btnSDes);
		lyBtn2->addWidget(btnSTP);
		lyBtn2->addWidget(btnU);
		lyBtn2->addWidget(btnR);
		lyBtn2->addWidget(btnExit);
		//lyGrid->addLayout(lyBtn,9,1);
		lyVBtn->addLayout(lyBtn2);

		auto lyBtn3 = new QHBoxLayout{};
		lyBtn3->addWidget(btnAddCos);
		lyBtn3->addWidget(btnDelCos);
		lyBtn3->addWidget(btnGenCos);
		lyBtn3->addWidget(btnExpCos);
		lyBtn3->addWidget(btnCos);
		lyVBtn->addLayout(lyBtn3);

		auto formFis = new QFormLayout;
		formFis->addRow("Fisier export", txtFisier);
		lyVBtn->addLayout(formFis);
		
		stgLy->addLayout(lyVBtn);

		lyMain->addLayout(stgLy);

		btnDyn->setLayout(lyBtnDy);
		lyMain->addWidget(btnDyn);
	}
};