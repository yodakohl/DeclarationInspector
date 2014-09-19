#include "commonmemory.h"
#include "classmemory.h"
#include <iostream>


commonMemory::commonMemory( size_t BlockCount,editor *edit,QWidget *parent): memoryArea(BlockCount,parent)
{
	recalcSizes();
	mCurSelection = 0;
	mObjects = 0;
	mEdit = edit;
}



void commonMemory::setSelection(Declaration *selection)
{
	mCurSelection = selection;
	if(mEdit && selection)
	{
		mEdit->highlightLine(selection->mLine,0);
	} else if (mEdit) {
		mEdit->highlightLine(-1,0);
	}
}


void commonMemory::setList(  std::list<Declaration*> *Objects)
{
	mObjects = Objects;
}


void commonMemory::calculateSize()
{
	
	if(mObjects == 0){return;}

	size_t sizeRequirement = 0;
	for (auto it = mObjects->begin(); it != mObjects->end(); it++)
	{
		sizeRequirement += (*it)->mSize;
	}
	setBlockCountExpanded(sizeRequirement);
}


bool commonMemory::event(QEvent* event) {
	if (event->type() == QEvent::MouseMove)
	{
		const QMouseEvent* const me = static_cast<const QMouseEvent*>( event );
		QPoint pos = me->pos();
		Declaration * selection = hitTest(pos.x(),pos.y());
		if(mCurSelection != selection){ 
			mCurSelection = selection;
			repaint(); 
			if(mEdit && selection)
			{
				mEdit->highlightLine(selection->mLine,0);
			} else if (mEdit) {
				mEdit->highlightLine(-1,0);
			}

			//Has Detail View and is not an Array
			if(selection && selection->mDataType && (selection->mDataType->mMembers.size() != 0) && selection->mIsArray == false)
			{
				((classMemory*)mClassWindow)->setSelection(&selection->mDataType->mMembers);
			}
			else if(selection && (selection->mDetail.size() != 0))
			{
				((classMemory*)mClassWindow)->setSelection(&selection->mDetail);
			} 
			else 
			{
				((classMemory*)mClassWindow)->setSelection(0);
			}
		}
	}
	return QDockWidget::event(event);
}



Declaration *commonMemory::hitTest(int x, int y)
{
	for (auto it = mBoundingBoxes.begin(); it!= mBoundingBoxes.end(); it++)
	{
		if((*it) && (*it)->hitsPosition(x,y))
			return (Declaration*) ((*it)->mObj);
	}
	return 0;
}


void commonMemory::clearHitBoxes()
{
	for (auto it = mBoundingBoxes.begin(); it!= mBoundingBoxes.end(); it++)
	{
		if( (*it)!= 0){delete *it; *it = 0;}
	}

	mBoundingBoxes.clear();
}




void commonMemory::leaveEvent(QEvent *)
{
	mCurSelection = 0;
	repaint();
	mEdit->highlightLine(-1,0);
	((classMemory*)mClassWindow)->setSelection(0);
}

void commonMemory::setClassWindow(memoryArea *classWindow)
{
	mClassWindow = classWindow;
}


void commonMemory::paintEvent(QPaintEvent *evt)
{
	clearHitBoxes();

	QPainter painter( (QWidget*) this);

	QFont font = painter.font() ;
	drawFrame(&painter);

	int tmpCount = 0;
	bool dataZebra = true;

	if(mObjects == 0){return;}

	int topAddOffset = 0;

	for (auto it = mObjects->begin(); it != mObjects->end(); it++)
	{
		int objTop     =  topAddOffset+mTopOffset;
		int objLeft    =  mSideOffset+mByteWidth;
		int objWidth   =  mObjWidth-mSideOffset*4;
		int objHeight  =  mBlockHeight*(*it)->mSize;
		int objBottom  =  objTop + objHeight;
		int objRight   =  objLeft + objWidth;
		
		setZebra(&painter,dataZebra);
			
		//Highlight Selection
		if( (*it) == mCurSelection)
			painter.setBrush(Qt::green);
		
		//Create BoundingBox
		boundingBox *bBox = new boundingBox(objTop, objBottom, objLeft, objRight, (*it));
		mBoundingBoxes.push_back(bBox);	

		//Draw Element
		QRectF rectangle(mSideOffset+mByteWidth,objTop,objWidth-mSideOffset,mBlockHeight*(*it)->mSize);
		painter.drawRect(rectangle);
		painter.drawText(rectangle, Qt::AlignCenter, QString::fromWCharArray((*it)->mName));
		painter.drawText(rectangle, Qt::AlignRight, QString::number((*it)->mSize));
		//If Pointer
		if( (*it)->mIsPointer)
			painter.drawText(rectangle, Qt::AlignLeft, "  (pointer)");

		topAddOffset += (*it)->mSize*mBlockHeight;
	}
}

