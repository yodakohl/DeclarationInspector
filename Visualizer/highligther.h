#ifndef HIGHLIGTHER_H
#define HIGHLIGTHER_H

#include <QSyntaxHighlighter>

class highligther : public QSyntaxHighlighter
{
public:
	highligther(QTextDocument* document);
	void highlightBlock(const QString &text);
	void addCustom(QString custom);
	void addOperator(QString custom);
	void addType(QString custom);

	void clear();
	void reload();

protected:
	void setUpFormat();

private:

	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};

	QVector<HighlightingRule> highlightingRules;
	QVector<HighlightingRule> fixedRules;
	QTextCharFormat keywordFormat;
	QTextCharFormat commentFormat;
	QTextCharFormat typeFormat;
	QTextCharFormat numericFormat;
	QTextCharFormat preprocessorFormat;
	QTextCharFormat operatorFormat;
	QTextCharFormat fixedFormat;


};

#endif


