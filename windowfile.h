#ifndef WINDOWFILE_H
#define WINDOWFILE_H

#include <QFile>
#include <QTextStream>

class TWindowFile
{
public:
    explicit TWindowFile(QString filename);
    ~TWindowFile();

    void setMaxLines(int maxLines);
    void setMaxLineLength(int maxLineLength);

    //return i-th line, but no more maxLineLength symbols.
    QString line(qsizetype i);

    //return lines [first .. min(last, first + maxLines) ), and every line no ore maxLines symbol.
    QString lines(qsizetype first, qsizetype last);

    void moveUp(int lines);
    void moveDown(int lines);
private:
    int maxLines;
    int maxLineLength;
    QString filename;
    QFile file;
    QTextStream in;
};

#endif // WINDOWFILE_H
