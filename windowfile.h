#ifndef WINDOWFILE_H
#define WINDOWFILE_H

#include <QFile>
#include <QTextStream>
#include <vector>

class TWindowFile
{
public:
    explicit TWindowFile(QString filename);
    ~TWindowFile();

    void setMaxLines(int maxLines);
    void setMaxLineLength(int maxLineLength);

    //return i-th line, but no more maxLineLength symbols.
    QString getLine(qsizetype i);

    //return lines [first .. min(last, first + maxLines) ), and every line no ore maxLines symbol.
    QString getLines(qsizetype first, qsizetype last);

    void moveUp(qsizetype lines);
    void moveDown(qsizetype lines);

    static constexpr int DEFAULT_MAX_LINES = 256;
    static constexpr int DEFAULT_MAX_LINE_LENGTH = 1024;
private:
    void read(); // read maxLines lines from currentPosition
private:
    int maxLines;
    int maxLineLength;
    QString filename;
    QFile file;
    QTextStream in;

    std::vector<QString> lines;
    qsizetype totalLines;
    qsizetype currentPosition;
};

#endif // WINDOWFILE_H
