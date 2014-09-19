#include "editor.h"
#include "editsidebar.h"
#include <QDebug>
#include <algorithm>
#include <iostream>


editor::editor(QWidget* parent) : QPlainTextEdit(parent)
{
	lineNumberArea = new EditSideBar(this);
	mSynErrors = 0;
	mHighlightLineBegin = -1;
	mHighlightLineEnd = -1;
	updateLineNumberAreaWidth(0);
	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
}

/*
 * Return the Width that is needed to draw the line numbers
*/
int editor::lineNumberAreaWidth()
{
	int digits = 2;
	int max = qMax(1, blockCount());
	while (max >= 100) {
		max /= 10;
		++digits;
	}

	int space = 12 + fontMetrics().width(QLatin1Char('9')) * digits;
	return space;
}

void editor::repaintSidebar()
{
	lineNumberArea->repaint();
}

void editor::updateLineNumberAreaWidth(int)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void editor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void editor::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}


void editor::highlightLine(int lineBegin, int lineEnd)
{

	mHighlightLineBegin = lineBegin;
	mHighlightLineEnd = lineEnd;

	QTextEdit::ExtraSelection highlight;

	// Highlight Line
	if(lineBegin != -1){
		int pos = this->document()->findBlockByLineNumber(mHighlightLineBegin-2).position();
		highlight.cursor = this->textCursor();
		highlight.cursor.setPosition(pos);
		highlight.cursor.movePosition( QTextCursor::StartOfLine );
		highlight.cursor.movePosition( QTextCursor::EndOfLine, QTextCursor::KeepAnchor );
		highlight.format.setBackground( Qt::green );
		highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
		QList<QTextEdit::ExtraSelection> extras;
		extras << highlight;
		this->setExtraSelections( extras );
	} else {
		highlight.cursor = this->textCursor();
		highlight.format.setBackground( Qt::white );
		QList<QTextEdit::ExtraSelection> extras;
		extras << highlight;
		this->setExtraSelections( extras );
	}
}


void editor::setSynErrorList(std::list<int> *SynErrors)
{
	mSynErrors = SynErrors;
}


void editor::setSynErrorMessages(std::map<int ,wchar_t*> *SynMessages)
{
	mSynMessages = SynMessages;
}

bool editor::event(QEvent* event) 
{
	if (event->type() == QEvent::ToolTip)
	{
		QPoint p = this->mapFromGlobal(QCursor::pos());
		QPoint off(60,20);
		QHelpEvent* helpEvent = static_cast <QHelpEvent*>(event);
		QTextCursor tc = cursorForPosition(helpEvent->pos());

		QRect cRect =  cursorRect(tc);
		QPoint p2 = cRect.bottomRight();
		int number = tc.blockNumber() +1;

		if(mSynMessages->count(number)!=0){
			wchar_t *wstr = (*mSynMessages)[number];
			QString str = QString::fromWCharArray(wstr);
			QToolTip::showText(p2+off,str,this);

		} else {
			QToolTip::hideText();
			event->ignore();
		}

		return true;
	}
	return QPlainTextEdit::event(event);
}


void editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(lineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {  
		if (block.isVisible() && bottom >= event->rect().top()) {
			int blockNumberOff = blockNumber + 1;
			QString number = QString::number(blockNumberOff);
			if(mSynErrors && (std::find(mSynErrors->begin(), mSynErrors->end(), blockNumberOff) != mSynErrors->end())){
				painter.fillRect(QRect(lineNumberArea->width()-3,top,3,fontMetrics().height()), Qt::red);
			} else {
				painter.fillRect(QRect(lineNumberArea->width()-3,top,3,fontMetrics().height()), Qt::green);
			}
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumberArea->width() -9, fontMetrics().height(), Qt::AlignRight, number);
		}
		
		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}








