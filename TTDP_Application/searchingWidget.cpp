#include "searchingWidget.h"

searchingWidget::searchingWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout* mainLayout = new QGridLayout(this);

	browseButtonIn = new QPushButton("Parcourir", this);
	lineFileIn = new QLineEdit(this);
	labelFileIn = new QLabel("Veuillez selectionner un fichier .txt valide :", this);
	browseButtonOut = new QPushButton("Parcourir", this);
	lineFileOut = new QLineEdit(this);
	labelFileOut = new QLabel("Veuillez selectionner un dossier de destination :", this);
	searchingButton = new QPushButton("Rechercher une solution", this);
	labelFileName = new QLabel("Veuillez renseigner un nom de fichier solution :", this);
	lineFileName = new QLineEdit(this);
	labelAlgo = new QLabel("Veuillez choisir un algorithme", this);
	comboAlgo = new QComboBox(this);
	comboAlgo->addItem("Glouton");
	comboAlgo->addItem("Genetique");

	mainLayout->addWidget(labelFileName, 0, 3, 1, 3);
	mainLayout->addWidget(lineFileName, 1, 3, 1, 3);
	mainLayout->addWidget(labelFileIn, 0, 0, 1, 3);
	mainLayout->addWidget(labelFileOut, 2, 3, 1, 3);
	mainLayout->addWidget(lineFileIn, 1, 0, 1, 2);
	mainLayout->addWidget(browseButtonIn, 1, 2, 1, 1);
	mainLayout->addWidget(lineFileOut, 3, 3, 1, 2);
	mainLayout->addWidget(labelAlgo, 2, 0, 1, 3);
	mainLayout->addWidget(comboAlgo, 3, 0, 1, 3);
	mainLayout->addWidget(browseButtonOut, 3, 5, 1, 1);
	mainLayout->addWidget(searchingButton, 4, 2, 1, 2);

	connect(browseButtonIn, SIGNAL(clicked()), this, SLOT(OpenFileInDialog()));
	connect(browseButtonOut, SIGNAL(clicked()), this, SLOT(OpenFileOutDialog()));
	connect(searchingButton, SIGNAL(clicked()), this, SLOT(SearchingSolution()));

	ui.setupUi(this);
}

searchingWidget::~searchingWidget()
{
}

void searchingWidget::OpenFileInDialog()
{
	QString filename = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Text files (*.txt)"));
	lineFileIn->setText(filename);
}
void searchingWidget::OpenFileOutDialog()
{
	QString filename = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
	lineFileOut->setText(filename);
}

void searchingWidget::SearchingSolution()
{
	instance_reader reader = instance_reader();
	new_instance newInstance = new_instance();
	solution s = solution();
	
	string fileIn = lineFileIn->text().toStdString();
	newInstance = reader.readNewFile(fileIn);
	Glouton	algoGlouton = Glouton();
	Genetique algoGenetique = Genetique();
	clock_t t1, t2;
	t1 = clock();
	switch (comboAlgo->currentIndex())
	{
	case 0 : s = algoGlouton.searchSolution(newInstance);
		break;
	case 1: s = algoGenetique.searchSolution(newInstance);
		break;
	default: s = algoGlouton.searchSolution(newInstance);
		break;
	}
	t2 = clock();
	double time = double(t2 - t1) / CLOCKS_PER_SEC;
	qDebug() << "temps d'execution : " << time;
	solution_writer writer = solution_writer();
	QString fileOut = lineFileOut->text();
	fileOut.append("/" + lineFileName->text());
	writer.writeSolution(s, fileOut.toStdString());
}
