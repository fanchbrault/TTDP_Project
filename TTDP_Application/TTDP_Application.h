#pragma once

#include <QtWidgets/QMainWindow>
#include <QTabWidget>
#include "ui_TTDP_Application.h"
#include <string>
#include "generatorWidget.h"
#include "searchingWidget.h"
#include "displayWidget.h"

using namespace std;

class TTDP_Application : public QMainWindow
{
	Q_OBJECT

public:
	TTDP_Application(QWidget *parent = Q_NULLPTR);


private:
	Ui::TTDP_ApplicationClass ui;
	QWidget* mainWidget;
	QTabWidget* tabWidget;
};
