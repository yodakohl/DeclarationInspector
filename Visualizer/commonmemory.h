#ifndef STACKMEMORY_H
#define STACKMEMORY_H


#include <QEvent>
#include <QMouseEvent>
#include <QPoint>

#include "memoryarea.h"
#include "editor.h"
#include "boundingbox.h"
#include <Analyser/Declaration.h>


class commonMemory : public memoryArea
{
public:
	commonMemory( size_t BlockCount,editor * edit,QWidget *parent =0);
	bool event(QEvent* event);
	Declaration *hitTest(int x, int y);
	void clearHitBoxes();
	void calculateSize();
	void leaveEvent(QEvent *);
	void setSelection(Declaration *selection);
	void setClassWindow(memoryArea *classWindow);
	void setList( std::list<Declaration*> *Objects);

protected:
	void paintEvent(QPaintEvent *evt);

private:
	editor *mEdit;
	Declaration *mCurSelection;
	memoryArea *mClassWindow;
	std::list<Declaration*> *mObjects;
	std::list<boundingBox*> mBoundingBoxes;

};

#endif // STACKMEMORY_H
