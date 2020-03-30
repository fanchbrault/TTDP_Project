#include "TTDP_Application.h"
#include <QtWidgets/QApplication>

///
///\file main.cpp
///\brief Conception d'itineraires touristiques
///\author Fanch Brault
///
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TTDP_Application w;
	w.setFixedSize(800, 450);
	w.show();
	return a.exec();
}
