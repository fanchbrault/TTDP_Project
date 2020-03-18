#include "displayWidget.h"

displayWidget::displayWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout* mainLayout = new QGridLayout(this);

	labelFileIn = new QLabel("Veuillez selectionner un fichier de solution:", this);
	lineFileIn = new QLineEdit(this);
	browseButton = new QPushButton("Parcourir",this);
	display = new QPushButton("Afficher", this);
	view = new QGraphicsView(this);
	scene = new QGraphicsScene(this);
	view->setScene(scene);

	mainLayout->addWidget(labelFileIn, 0, 0, 1, 3);
	mainLayout->addWidget(lineFileIn, 1, 0, 1, 2);
	mainLayout->addWidget(browseButton, 1, 2, 1, 1);
	mainLayout->addWidget(display, 3, 0, 1, 3);
	mainLayout->addWidget(view, 0, 3, 4, 4);

	connect(browseButton, SIGNAL(clicked()), this, SLOT(OpenFileInDialog()));
	connect(display, SIGNAL(clicked()), this, SLOT(DisplaySolution()));
	ui.setupUi(this);
}

displayWidget::~displayWidget()
{
}

void displayWidget::OpenFileInDialog() 
{
	QString filename = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Text files (*.txt)"));
	lineFileIn->setText(filename);
}
void displayWidget::DisplaySolution()
{
	scene->clear();
	solution_reader reader = solution_reader();
	solution s = reader.readSolutionFile(lineFileIn->text().toStdString());
	new_instance instance = s.getInstance();
	double minX = 99999;
	double maxX = -99999;
	double minY = 99999;
	double maxY = -99999;
	for (int i = 0; i < instance.getNbPoi(); i++) {
		point_of_interest poi = instance.getPois()[i];
		if (poi.getX() < minX) 
		{
			minX = poi.getX();
		}
		if (poi.getX() > maxX) 
		{
			maxX = poi.getX();
		}
		if (poi.getY() < minY) 
		{
			minY = poi.getY();
		}
		if (poi.getY() > maxY) 
		{
			maxY = poi.getY();
		}
	}
	int sizeX = abs(maxX - minX);
	int sizeY = abs(maxY - minY);
	int maxSize = (sizeX < sizeY ? sizeY : sizeX);
	double factor = (view->size().width() - 15) / maxSize;
	QPen blackPen = QPen(Qt::black);
	QPen redPen = QPen(Qt::red);
	QBrush blackBrush = QBrush(Qt::black);
	QBrush redBrush = QBrush(Qt::red);
	for (int i = 0; i < instance.getNbPoi(); i++) {
		point_of_interest poi = instance.getPois()[i];
		scene->addRect(poi.getX()*factor, poi.getY()*factor, 1, 1, blackPen, blackBrush);
	}
	scene->addRect(instance.getStartingPoint().getX()*factor, instance.getStartingPoint().getY()*factor, 2, 2, redPen, redBrush);
	QGraphicsTextItem *number = scene->addText("S");
	number->setPos(instance.getStartingPoint().getX()*factor, instance.getStartingPoint().getY()*factor);
	int lastIndex = 0;
	for (int i = 1; i < s.getNbPoisSelected(); i++) {
		int idP1 = s.getPoisSelected()[0][i - 1];
		int idP2 = s.getPoisSelected()[0][i];
		point_of_interest p1 = instance.getPois()[idP1 - 2];
		point_of_interest p2 = instance.getPois()[idP2 - 2];
		scene->addLine(p1.getX()*factor, p1.getY()*factor, p2.getX()*factor, p2.getY()*factor, redPen);
		//QGraphicsTextItem *number = scene->addText("" + p1.getId());
		//number->setPos(p1.getX()*factor +10 , p1.getY()*factor +10);
		//number->setDefaultTextColor(Qt::black);
		lastIndex = i;
	}
	int idP1 = s.getPoisSelected()[0][0];
	point_of_interest p1 = instance.getPois()[idP1 - 2];
	int idPn = s.getPoisSelected()[0][lastIndex];
	point_of_interest pn = instance.getPois()[idPn - 2];
	//QGraphicsTextItem *lastNumber = scene->addText("" + pn.getId());
	//lastNumber->setDefaultTextColor(Qt::black);
	//lastNumber->setPos(pn.getX()*factor + 10, pn.getY()*factor + 10);
	scene->addLine(p1.getX()*factor, p1.getY()*factor, instance.getStartingPoint().getX()*factor, instance.getStartingPoint().getY()*factor, redPen);
	scene->addLine(pn.getX()*factor, pn.getY()*factor, instance.getStartingPoint().getX()*factor, instance.getStartingPoint().getY()*factor, redPen);
}
