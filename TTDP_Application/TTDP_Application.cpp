#include "TTDP_Application.h"


TTDP_Application::TTDP_Application(QWidget *parent)
	: QMainWindow(parent)
{
	mainWidget = new QWidget(this);
	tabWidget = new QTabWidget(mainWidget);
	tabWidget->setFixedSize(795, 445);
	generatorWidget* generator = new generatorWidget();
	searchingWidget* searching = new searchingWidget();
	displayWidget* display = new displayWidget();
	tabWidget->addTab(generator, "Generation d'instance");
	tabWidget->addTab(searching, "Recherche de solution");
	tabWidget->addTab(display, "Affichage de solution");
	tabWidget->setCurrentIndex(0);
	setCentralWidget(mainWidget);
}
