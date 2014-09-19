#include "memoryarea.h"



memoryArea::memoryArea(size_t BlockCount,QWidget *parent) :
	QDockWidget(parent)
{
	mBlockCount = BlockCount;
	mBlockCountExpanded = mBlockCount;
	mSideOffset = 0;
	mCaption = "unnamed";
	this->setMinimumWidth(300);
}


void memoryArea::resizeEvent ( QResizeEvent * event )
{
	recalcSizes();
}


void memoryArea::setBlockCountExpanded(size_t sizeRequirement)
{
	if(sizeRequirement > mBlockCount)
	{
		mBlockCountExpanded = sizeRequirement;
	} else {
		mBlockCountExpanded = mBlockCount;
	}
	recalcSizes();
}

void memoryArea::drawFrame(QPainter *painter)
{
	QFont font = painter->font() ;

	//Draw Caption
	font.setPointSize(font.pointSize() * 2);
	painter->setFont(font);
	painter->drawText(QRectF(mSideOffset,30,mWidth,30), Qt::AlignCenter, mCaption);
	font.setPointSize(font.pointSize() * 0.5);
	painter->setFont(font);

	//Draw Background
	QRectF rectangle(0,mTopOffset,this->width()-mRightMargin,mHeight);
	painter->setBrush(Qt::white);
	painter->drawRect(rectangle);


	bool byteZebra = false;

	//Draw Bytes
	for (int i = 0; i < mBlockCountExpanded; i++)
	{
		setZebra(painter,byteZebra);
		QRectF rectangle(mSideOffset,i*mBlockHeight+mTopOffset,mByteWidth,mBlockHeight);
		painter->drawRect(rectangle);
	}

}

void memoryArea::setZebra(QPainter *painter, bool &zebra)
{
	if(zebra){
		painter->setBrush(Qt::lightGray);
		painter->setPen(Qt::black);
		zebra = !zebra;
	} else {
		painter->setBrush(Qt::gray);
		painter->setPen(Qt::black);
		zebra = !zebra;
	}
}


void memoryArea::recalcSizes()
{
	mRightMargin = this->width()/20.0;
	mWidth = this->width() - mSideOffset;
	mByteWidth = mWidth * 0.05;
	mObjWidth = mWidth - mByteWidth -mRightMargin;
	mTopOffset =  this->height()/12.0;
	mHeight = this->height()- mTopOffset;
	if(mBlockCountExpanded !=0){
		mBlockHeight = mHeight/mBlockCountExpanded;
	} else {
		mBlockHeight = 1;
	}
}



void memoryArea::setCaption(QString caption)
{
	mCaption = caption;
}



