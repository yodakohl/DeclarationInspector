#include "editsidebar.h"



EditSideBar::EditSideBar(editor *pEditor) : QWidget(pEditor) {
	mEditor = pEditor;
}

QSize EditSideBar::sizeHint() const {
	return QSize(mEditor->lineNumberAreaWidth(), 0);
}

void EditSideBar::paintEvent(QPaintEvent *event) {
	mEditor->lineNumberAreaPaintEvent(event);
}

