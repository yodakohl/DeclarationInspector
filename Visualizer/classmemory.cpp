#include "classmemory.h"

#include <iostream>

classMemory::classMemory( size_t BlockCount,QWidget *parent): memoryArea(BlockCount,parent)
{
	recalcSizes();
	mCurSelection = 0;
}



void classMemory::setSelection(std::list<Declaration*> *selection)
{
	mCurSelection = selection;
	this->repaint();
}

void classMemory::calculateSize()
{

	if( mCurSelection == 0 )
		return;

	size_t sizeRequirement = 0;

	for ( auto it = mCurSelection->begin() ; it != mCurSelection->end(); it++)
	{
		sizeRequirement += (*it)->mSize;
	}

	setBlockCountExpanded(sizeRequirement);

}


void classMemory::paintEvent(QPaintEvent *evt)
{
	QPainter painter( (QWidget*) this);
	
	QFont font = painter.font() ;
	drawFrame(&painter);
	
	int tmpCount = 0;
	bool byteZebra = false;

	if( mCurSelection == 0 )
		return;

	int objLeft =  mSideOffset+mByteWidth;

	int topOffset = 0;
	for ( auto it = mCurSelection->begin() ; it != mCurSelection->end(); it++)
	{
		setZebra(&painter,byteZebra);

		int elemHeight =  mBlockHeight*(*it)->mSize;
				
		std::cerr << " Drawing Member" << std::endl;
		//Draw member
		QRectF rectangle(objLeft,topOffset+mTopOffset,mObjWidth,elemHeight);
		painter.drawRect(rectangle);
		painter.drawText(rectangle, Qt::AlignCenter, QString::fromWCharArray((*it)->mName));
		painter.drawText(rectangle, Qt::AlignRight, QString::number((*it)->mSize));


		if( (*it)->mIsPointer)
			painter.drawText(rectangle, Qt::AlignLeft, "  (Zeiger)");
		
		topOffset+= (*it)->mSize*mBlockHeight;
	}
}

