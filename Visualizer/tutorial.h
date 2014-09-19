#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>
#include <QPainter>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QPushButton>
#include <QProgressBar>
#include <vector>

#include "visualizer.h"

#define TUTFOLDER QString("./Tutorial/")

class Visualizer;

class tutorial : public QWidget
{
	Q_OBJECT
public:
	explicit tutorial(Visualizer *visualizer, QWidget *parent = 0);

	bool load(QString name);
	bool loadCode(QString code);

public slots:
	void next();
	void closeTut();
	void prev();
	bool reload();
	void loadIndex();

private:
	QTextBrowser *mTutText;
	QPushButton *nextButton;
	QPushButton *prevButton;
	QPushButton *closeButton;
	QPushButton *reloadButton;
	QProgressBar* mProgressBar;

	Visualizer *mVisualizer;
	std::vector<QString> mTutFiles;
	int step;
};


#endif // TUTORIAL_H
