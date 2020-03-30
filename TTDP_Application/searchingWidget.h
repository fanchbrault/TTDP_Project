#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHboxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include "new_instance.h"
#include "Glouton.h"
#include "Genetique.h"
#include "solution_writer.h"
#include "instance_reader.h"
#include "ui_searchingWidget.h"
#include <time.h>
#include <QDebug>

class searchingWidget : public QWidget
{
	Q_OBJECT

public:
	searchingWidget(QWidget *parent = Q_NULLPTR);
	~searchingWidget();

private slots:

	void OpenFileInDialog();
	void OpenFileOutDialog();
	void SearchingSolution();

private:
	Ui::searchingWidget ui;
	QLabel* labelFileIn;
	QLabel* labelFileOut;
	QLabel* labelFileName;
	QLabel* labelAlgo;
	QLineEdit* lineFileIn;
	QLineEdit* lineFileOut;
	QLineEdit* lineFileName;
	QPushButton* browseButtonIn;
	QPushButton* browseButtonOut;
	QComboBox* comboAlgo;
	QPushButton* searchingButton;
	QLabel* labelStatus;
};
