#include "highligther.h"
#include <QDebug>

highligther::highligther(QTextDocument* document):QSyntaxHighlighter(document)
{

	setUpFormat();

	HighlightingRule rule;

	QStringList keywordPatterns;
	keywordPatterns << "\\bclass\\b" 
			<< "\\benum\\b"
			<< "\\bstd::\\b" 
			<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b" 
			<< "\\bstruct\\b" 
			<< "\\bunion\\b" 
			<< "\\bnew\\b" 
			<< "\\bvoid\\b" << "\\bsigned" << "\\bunsigned";




	foreach (const QString &pattern, keywordPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = fixedFormat;
		fixedRules.append(rule);
	}


}

void highligther::addType(QString custom)
{
	HighlightingRule rule;
	rule.pattern = QRegExp("\\b" + custom + "\\b");
	rule.format = fixedFormat;
	highlightingRules.append(rule);
}

void highligther::addCustom(QString custom)
{
	HighlightingRule rule;
	rule.pattern = QRegExp("\\b" + custom + "\\b");
	rule.format = typeFormat;
	highlightingRules.append(rule);
}

void highligther::addOperator(QString custom)
{
	HighlightingRule rule;
	rule.pattern = QRegExp(custom);
	rule.format = typeFormat;
	highlightingRules.append(rule);
}

void highligther::clear()
{
	highlightingRules.clear();
}

void highligther::reload()
{
	this->rehighlight();
}


void highligther::setUpFormat()
{

	keywordFormat.setForeground(Qt::magenta);
	keywordFormat.setFontWeight(QFont::Bold);
	commentFormat.setForeground(Qt::green);
	typeFormat.setForeground(Qt::red);
	numericFormat.setForeground(Qt::darkBlue);
	preprocessorFormat.setForeground(Qt::gray);
	operatorFormat.setForeground(Qt::red);
	fixedFormat.setForeground(Qt::darkBlue);
	fixedFormat.setFontWeight(QFont::Bold);

}

void highligther::highlightBlock(const QString &text)
{
	foreach (const HighlightingRule &rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}


	foreach (const HighlightingRule &rule, fixedRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}


	enum { NormalState = -1, CStyleComment };

	int state = previousBlockState();
	int start = 0;

	for (int i = 0; i < text.length(); ++i)
	{

		if (state == CStyleComment)
		{
			if (text.mid(i, 2) == "*/")
			{
				state = NormalState;
				setFormat(start, i - start + 2, Qt::blue);
			}
		} else {
			if (text.mid(i, 2) == "//")
			{
				setFormat(i, text.length() - i, Qt::red);
				break;
			}
			else if (text.mid(i, 2) == "/*")
			{
				start = i;
				state = CStyleComment;
			}
		}
	}
}
