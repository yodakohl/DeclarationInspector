#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QPainter>
#include <QTextBlock>
#include <QToolTip>
#include <list>
#include <map>
#include <cwchar>
#include <QDebug>

/*
Tooltip darf bei nicht ausserhalb des textfeldes aufgerufen werden
*/



class editor: public QPlainTextEdit
{
	Q_OBJECT
public:

	editor(QWidget *parent = 0);

	int lineNumberAreaWidth();
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	void setSynErrorList(std::list<int> *SynErrors);
	void setSynErrorMessages(std::map<int ,wchar_t*> *SynMessages);
	bool event(QEvent* event);
	void repaintSidebar();
	void highlightLine(int lineBegin, int lineEnd);

protected:

	void resizeEvent(QResizeEvent *e);

private slots:
	void updateLineNumberArea(const QRect &, int);
	void updateLineNumberAreaWidth(int newBlockCount);

private:
	QWidget *lineNumberArea;
	std::list<int> *mSynErrors;
	std::map<int ,wchar_t*> *mSynMessages;

	size_t mHighlightLineBegin;
	size_t mHighlightLineEnd;
		

};

#endif // EDITOR_H



