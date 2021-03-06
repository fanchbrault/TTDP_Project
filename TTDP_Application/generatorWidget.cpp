#include "generatorWidget.h"


generatorWidget::generatorWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout* mainLayout = new QGridLayout(this);
	
	QVBoxLayout* fileInLayout = new QVBoxLayout(this);
	QVBoxLayout* fileOutLayout = new QVBoxLayout(this);
	QVBoxLayout* fileNameLayout = new QVBoxLayout(this);
	QSpacerItem* spacerFileIn = new QSpacerItem(0,400);
	QSpacerItem* spacerFileOut = new QSpacerItem(0,400);
	QSpacerItem* spacerFileName = new QSpacerItem(0,400);
	QSpacerItem* bottomSpacer = new QSpacerItem(0, 300);

	browseButtonIn = new QPushButton("Parcourir", this);
	lineFileIn = new QLineEdit(this);
	labelFileIn = new QLabel("Veuillez selectionner un fichier .txt valide :", this);
	browseButtonOut = new QPushButton("Parcourir", this);
	lineFileOut = new QLineEdit(this);
	labelFileOut = new QLabel("Veuillez selectionner un dossier de destination :", this);
	generateButton = new QPushButton("Generer", this);
	labelFileName = new QLabel("Veuillez renseigner un nom de fichier :", this);
	lineFileName = new QLineEdit(this);
	labelStatut = new QLabel("", this);

	fileInLayout->addItem(spacerFileIn);
	fileInLayout->addWidget(labelFileIn);
	fileOutLayout->addItem(spacerFileOut);
	fileOutLayout->addWidget(labelFileOut);
	fileNameLayout->addItem(spacerFileName);
	fileNameLayout->addWidget(labelFileName);

	mainLayout->addLayout(fileNameLayout, 0, 3, 1, 3);
	mainLayout->addWidget(lineFileName, 1, 3, 1, 3);
	mainLayout->addLayout(fileInLayout, 0, 0, 3, 3);
	mainLayout->addLayout(fileOutLayout, 2, 3, 1, 3);
	mainLayout->addWidget(lineFileIn, 3, 0, 1, 2);
	mainLayout->addWidget(browseButtonIn, 3, 2, 1, 1);
	mainLayout->addWidget(lineFileOut, 3, 3, 1, 2);
	mainLayout->addWidget(browseButtonOut, 3, 5, 1, 1);
	mainLayout->addItem(bottomSpacer, 4, 0, 1, 5);
	mainLayout->addWidget(generateButton, 5, 2, 1, 2);
	mainLayout->addWidget(labelStatut, 6, 0, 1, 3);
	
	connect(browseButtonIn, SIGNAL(clicked()), this, SLOT(OpenFileInDialog()));
	connect(browseButtonOut, SIGNAL(clicked()), this, SLOT(OpenFileOutDialog()));
	connect(generateButton, SIGNAL(clicked()), this, SLOT(GenerateInstance()));
	ui.setupUi(this);
}

generatorWidget::~generatorWidget()
{
}


void generatorWidget::OpenFileInDialog() {
	QString filename = QFileDialog::getOpenFileName(this, ("Open File"),"/home",("Text files (*.txt)"));
	lineFileIn->setText(filename);
}

void generatorWidget::OpenFileOutDialog()
{
	QString filename = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
	lineFileOut->setText(filename);
}

void generatorWidget::GenerateInstance()
{
	instance_reader reader = instance_reader();
	instance_generator generator = instance_generator();
	instance_writer writer = instance_writer();

	classic_instance instance = classic_instance();
	new_instance newInstance = new_instance();
	string fileIn = lineFileIn->text().toStdString();
	QString fileOut = lineFileOut->text();
	fileOut.append("/" + lineFileName->text());
	labelStatut->setText("Generation d'instance en cours");
	try{
		instance = reader.readClassicFile(fileIn);
		newInstance = generator.generateNewInstance(instance);
		writer.writeNewInstance(fileOut.toStdString(), newInstance);
		labelStatut->setText("Instance generee");
	}
	catch (exception& e) {
		labelStatut->setText(e.what());
	}
	
}

