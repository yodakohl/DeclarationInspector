#include "tutorial.h"

tutorial::tutorial(Visualizer *visualizer, QWidget *parent) :
	QWidget(parent)
{
	step = 0;
	mProgressBar = new QProgressBar(this);
	loadIndex();

	QPushButton *nextButton = new QPushButton("&Next", this);
	QPushButton *prevButton = new QPushButton("&Previous", this);
	QPushButton *reloadButton = new QPushButton("&Reload", this);
	QPushButton *closeButton = new QPushButton("&Close", this);

	QVBoxLayout *mLayout = new QVBoxLayout(this);
	QHBoxLayout *mVerticalLayout = new QHBoxLayout(this);
	
	mVerticalLayout->addWidget(nextButton);
	mVerticalLayout->addWidget(prevButton);
	mVerticalLayout->addWidget(reloadButton);
	mVerticalLayout->addWidget(closeButton);

	mTutText = new QTextBrowser(this);
	mTutText->setOpenExternalLinks(true);
	mTutText->setReadOnly(true);
	mLayout->addWidget(mTutText);
	mLayout->addWidget(mProgressBar);
	mLayout->addLayout(mVerticalLayout);
	this->setLayout(mVerticalLayout);

	connect(nextButton, SIGNAL(released()), this, SLOT(next()));
	connect(prevButton, SIGNAL(released()), this, SLOT(prev()));
	connect(closeButton, SIGNAL(released()), this, SLOT(closeTut()));
	connect(reloadButton, SIGNAL(released()), this, SLOT(reload()));

	mVisualizer = visualizer;
	reload();
}

void tutorial::closeTut()
{
	mVisualizer->stopTutorial();
	//this->close();
}



bool tutorial::reload()
{
	bool resLoad = load(TUTFOLDER + "tut" + mTutFiles[step]);
	bool resCode = loadCode(TUTFOLDER + "code" + mTutFiles[step]);
	if(resLoad && resCode)
		return true;

	return false;
}


void tutorial::next()
{
	if(step < mTutFiles.size()-1){
		step ++;
		mProgressBar->setValue(step);
		reload();
	}
}

void tutorial::prev()
{
	if(step >0){
		step --;
		mProgressBar->setValue(step);
		reload();
	}
}



void tutorial::loadIndex()
{
	mTutFiles.clear();

	QFile file(TUTFOLDER + "index");
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		in.setCodec("UTF-8");
		while ( !in.atEnd() )
		{
			QString line = in.readLine();
			mTutFiles.push_back(line);
		}
		file.close();
	}

	mProgressBar->setRange(0,mTutFiles.size()-1);
}

bool tutorial::loadCode(QString name)
{
	QFile file(name);

	if(file.open(QFile::ReadOnly | QFile::Text)){
		QTextStream ReadFile(&file);
		ReadFile.setCodec("UTF-8");
		mVisualizer->setText(ReadFile.readAll());
		return true;
	} else {
		return false;
	}
}

bool tutorial::load(QString name)
{
	mTutText->clear();
	QFile file(name);

	if(file.open(QFile::ReadOnly | QFile::Text)){
		QTextStream ReadFile(&file);
		ReadFile.setCodec("UTF-8");
		mTutText->setHtml(ReadFile.readAll());
		return true;
	} else {
		return false;
	}
}







