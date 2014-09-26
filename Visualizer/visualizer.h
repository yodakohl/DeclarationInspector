#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <Analyser/Analyser.h>
#include <Analyser/SymbolTable.h>
#include <QTimer>
#include <QMenuBar>
#include <QByteArray>
#include <iostream>
#include <fstream>
#include <QMenu>

#include "tutorial.h"
#include "highligther.h"
#include "memoryarea.h"
#include "classmemory.h"
#include "commonmemory.h"
#include "editor.h"

class tutorial;

class Visualizer : public QMainWindow
{
	Q_OBJECT

public:
	explicit Visualizer(QWidget *parent = 0);
	~Visualizer();
	void createMenu();
	void setText(QString text);
	void repaintWidgets();
	void stopTutorial();


private slots:

	void compileNow();
	void on_text_changed();
	void quit();
	void startTutorial();
	
	void showStack();
	void showHeap();
	void showClass();


private:

	QMenuBar *menu;
	QMenu *fileMenu;
	QMenu *viewMenu;

	QAction *exitAction;
	QAction *tutorialAction;

	QAction *stackAction;
	QAction *heapAction;
	QAction *classAction;

	QGridLayout *mLayout;
	editor *mEditor;
	QWidget *mEditWidget;
	highligther *mHighlighter;
	memoryArea *mStack;
	memoryArea *mHeap;
	memoryArea *mClass;

	tutorial *mTut;
	Analyser *mAnalyser;
	SymbolTable *mSymbols;



};

#endif // VISUALIZER_H
