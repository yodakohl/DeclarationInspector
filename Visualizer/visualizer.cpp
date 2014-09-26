#include "visualizer.h"
#include <QDebug>
#include <sys/time.h>

static struct timeval tm1;
//std::ofstream timeDebugFile;

static inline void timestart()
{
	gettimeofday(&tm1, NULL);
}

static inline void timestop()
{
	struct timeval tm2;
	gettimeofday(&tm2, NULL);

	unsigned long long t = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;
	qDebug() << "Time: " << t;
//	timeDebugFile << t << std::endl;
}


Visualizer::Visualizer(QWidget *parent) :QMainWindow(parent)
{
	mTut = 0;
	mLayout = new QGridLayout(this);
	mEditWidget = new QWidget(this);
	mEditor = new editor(this);

	QFont font;
	font.setFamily("Courier");
	font.setStyleHint(QFont::Monospace);
	font.setFixedPitch(true);
	font.setPointSize(12);
	mEditor->setFont(font);
	QFontMetrics metrics(font);
	mEditor->setTabStopWidth(4 * metrics.width(' '));

	mLayout->addWidget(mEditor);
	mEditWidget->setLayout(mLayout);
	mStack = new commonMemory(60,mEditor,this);
	mHeap = new commonMemory(60,mEditor,this);
	mClass = new classMemory(60,this);

	mStack->setCaption("Stack");
	mHeap->setCaption("Heap");
	mClass->setCaption("Detail");

	((commonMemory*)mHeap)->setClassWindow(mClass);
	((commonMemory*)mStack)->setClassWindow(mClass);

	mHighlighter = new highligther(mEditor->document());
	mAnalyser = new Analyser();
	mSymbols = mAnalyser->getTable();
	this->setCentralWidget(mEditWidget);

	this->addDockWidget(Qt::RightDockWidgetArea, mClass);
	this->addDockWidget(Qt::RightDockWidgetArea, mStack);
	this->addDockWidget(Qt::RightDockWidgetArea, mHeap);

	tabifyDockWidget(mClass, mStack);
	tabifyDockWidget(mStack, mHeap);
	splitDockWidget(mClass, mStack, Qt::Horizontal);
	splitDockWidget(mStack, mHeap, Qt::Horizontal);

	this->show();
	this->showMaximized();
	connect(mEditor, SIGNAL(textChanged()), this, SLOT(on_text_changed()));

	createMenu();
	this->setMenuBar(menu);
	startTutorial();

	setWindowTitle("Declaration Inspector");


	
	//timeDebugFile.open ("data.txt");
	
	

}

void Visualizer::on_text_changed()
{
	compileNow();
}

void Visualizer::compileNow()
{
	timestart();

	QString content = mEditor->toPlainText();

	QByteArray ba = content.toLatin1();
	const char *data = ba.data(); 

	((commonMemory*)mStack)->setList(0);
	((commonMemory*)mHeap)->setList(0);
	((classMemory*)mClass)->setSelection(0);
	mSymbols->Clear();
	int errCount = mAnalyser->compile( (unsigned char*)data,strlen(data)   );


	mEditor->setSynErrorList(&mSymbols->mErrorLines);
	mEditor->setSynErrorMessages(&mSymbols->mErrorMessages);
	
	if (errCount != 0){
		qDebug() << "Compile Error";
		repaintWidgets();
		return;
	}

	auto objList = mSymbols->getStack();
	auto heapList = mSymbols->getHeap();
	auto definitionList = mSymbols->getDefinitions();

	((commonMemory*)mStack)->setList(objList);
	((commonMemory*)mHeap)->setList(heapList);
	
	mHeap->calculateSize();
	mStack->calculateSize();
	mClass->calculateSize();

	mHighlighter->clear();
	
	for (auto it = objList->begin(); it != objList->end(); it++)
	{
		QString n = QString::fromWCharArray((*it)->mName);
		mHighlighter->addCustom(n);
	}

	for (auto it = heapList->begin(); it != heapList->end(); it++)
	{
		QString n = QString::fromWCharArray((*it)->mName);
		mHighlighter->addCustom(n);
	}

	
	for (auto it = definitionList->begin(); it != definitionList->end(); it++)
	{
		QString n = QString::fromWCharArray((*it)->mName);
		mHighlighter->addType(n);
	}

	
	mEditor->blockSignals(true);
	mHighlighter->reload();
	mEditor->blockSignals(false);
	repaintWidgets();

	timestop();
}



Visualizer::~Visualizer()
{
	//timeDebugFile.close();
}

void Visualizer::repaintWidgets()
{
	mStack->repaint();
	mHeap->repaint();
	mClass->repaint();
	mEditor->repaintSidebar();
	mEditor->repaint();
}



void Visualizer::setText(QString text)
{
	mEditor->clear();
	mEditor->insertPlainText(text);
}

void Visualizer::startTutorial()
{
	if(mTut == 0){
		mTut = new tutorial(this,this);
		mLayout->addWidget(mTut,1,0);
	}
}


void Visualizer::stopTutorial()
{
	if(mTut){
		mTut->close();
	}
	mTut = 0;
}


void Visualizer::quit()
{
	this->close();
}



void Visualizer::showStack()
{
	mStack->setVisible(true);
}	

void Visualizer::showHeap()
{
	mHeap->setVisible(true);
}


void Visualizer::showClass()
{
	mClass->setVisible(true);
}


void Visualizer::createMenu()
{
	menu = new QMenuBar;
	fileMenu = new QMenu(tr("File"), this);
	viewMenu = new QMenu(tr("View"), this);

	stackAction = new QAction(tr("&Stack"), this);
	heapAction = new QAction(tr("&Heap"), this);
	classAction = new QAction(tr("&Class"), this);

	exitAction = new QAction(tr("&Quit"), this);
	tutorialAction = new QAction(tr("&Start Tutorial"), this);

	fileMenu->addAction(exitAction);
	fileMenu->addAction(tutorialAction);

	viewMenu->addAction(stackAction);
	viewMenu->addAction(heapAction);
	viewMenu->addAction(classAction);

	menu->addMenu(fileMenu);
	menu->addMenu(viewMenu);

	connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
	connect(tutorialAction, SIGNAL(triggered()), this, SLOT(startTutorial()));

	connect(stackAction, SIGNAL(triggered()), this, SLOT(showStack()));
	connect(heapAction, SIGNAL(triggered()), this, SLOT(showHeap()));
	connect(classAction, SIGNAL(triggered()), this, SLOT(showClass()));
}



