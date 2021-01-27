#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include "gui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RepoOfertaFile repo{"oferte1.txt"};
	OfertaValidator val;
	ServiceOferta srv{ repo, val };
	Gui gui{ srv };
	gui.show();

	return a.exec();
}
