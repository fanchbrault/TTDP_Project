#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include "ui_generatorWidget.h"
#include "instance_reader.h"
#include "instance_generator.h"
#include "instance_writer.h"
#include "classic_instance.h"
#include "new_instance.h"

class generatorWidget : public QWidget
{
	Q_OBJECT

public:
	generatorWidget(QWidget *parent = Q_NULLPTR);
	~generatorWidget();

private slots:

	void OpenFileInDialog();
	void OpenFileOutDialog();
	void GenerateInstance();
private:
	Ui::generatorWidget ui;
	QLabel* labelFileIn;
	QLabel* labelFileOut;
	QLabel* labelFileName;
	QLineEdit* lineFileIn;
	QLineEdit* lineFileOut;
	QLineEdit* lineFileName;
	QPushButton* browseButtonIn;
	QPushButton* browseButtonOut;
	QPushButton* generateButton;
	QLabel* labelStatut;

};
