#ifndef MEMORYAREA_H
#define MEMORYAREA_H

#include <QDockWidget>
#include <QPainter>

#include <Analyser/SymbolTable.h>

class memoryArea : public QDockWidget
{
	Q_OBJECT
public:
	memoryArea( size_t BlockCount,QWidget *parent = 0 );
	void setCaption(QString caption);
	void setBlockCountExpanded(size_t sizeRequirement);
	void resizeEvent ( QResizeEvent * event );
	virtual void calculateSize() = 0;

protected:
	void drawFrame(QPainter *painter);
	void setZebra(QPainter *painter, bool &zebra);
	void recalcSizes();

	size_t mBlockCount;
	size_t mBlockCountExpanded;
	size_t mBlockHeight;
	size_t mWidth;
	size_t mHeight;
	size_t mSideOffset;
	size_t mRightMargin;
	size_t mByteWidth;
	size_t mObjWidth;
	size_t mTopOffset;

	QString mCaption;
};

#endif // MEMORYAREA_H
