#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include "ui_displayWidget.h"
#include "new_instance.h"
#include "solution.h"
#include "solution_reader.h"
#include <QPen>
#include <QBrush>
#include <stdlib.h>
#include <QGraphicsTextItem>

class displayWidget : public QWidget
{
	Q_OBJECT

public:
	displayWidget(QWidget *parent = Q_NULLPTR);
	~displayWidget();

private slots:
	void OpenFileInDialog();
	void DisplaySolution();

private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	QPushButton* browseButton;
	QPushButton* display;
	QLineEdit* lineFileIn;
	QLabel* labelFileIn;
	Ui::displayWidget ui;
};
