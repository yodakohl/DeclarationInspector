#ifndef EDITSIDEBAR_H
#define EDITSIDEBAR_H

#include "editor.h"

class EditSideBar : public QWidget
{

public:
	EditSideBar(editor *pEditor);
	QSize sizeHint() const;

protected:
	void paintEvent(QPaintEvent *event);

private:

	editor *mEditor;
};

#endif // EDITSIDEBAR_H
