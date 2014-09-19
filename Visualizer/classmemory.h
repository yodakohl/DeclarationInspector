#ifndef CLASSMEMORY_H
#define CLASSMEMORY_H


#include <QEvent>
#include <QMouseEvent>
#include <QPoint>

#include "memoryarea.h"
#include <Analyser/DataType.h>


class classMemory : public memoryArea
{
public:
	classMemory( size_t BlockCount,QWidget *parent =0);
	void setSelection(std::list<Declaration*> *selection);
	void calculateSize();

protected:
	void paintEvent(QPaintEvent *evt);
	
private:
	std::list<Declaration*> *mCurSelection;
};

#endif
