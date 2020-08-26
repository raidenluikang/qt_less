#include "windowfile.h"

#include <exception>
#include <stdexcept>

int maxLines;
int maxLineLength;
QString filename;
QFile file;
QTextStream in;

std::vector<QString> lines;
qsizetype totalLines;
qsizetype currentPosition;


TWindowFile::TWindowFile(QString filename)
    : maxLines(DEFAULT_MAX_LINES)
    , maxLineLength(DEFAULT_MAX_LINE_LENGTH)
    , filename(filename)
    , file(filename)
    , in()
    , lines()
    , totalLines(0)
    , currentPosition(0)
{
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        throw std::runtime_error("File not found!");
    }
    in.setDevice(&file);

    read();
}

TWindowFile::~TWindowFile()
{
    file.close();
}

void TWindowFile::setMaxLines(int maxLines)
{
    if (maxLines == 0)
        this->maxLines = DEFAULT_MAX_LINES;
    else
        this->maxLines = maxLines;
}

void TWindowFile::setMaxLineLength(int maxLineLength)
{
    if (maxLineLength == 0)
        this->maxLineLength = DEFAULT_MAX_LINE_LENGTH;
    else
        this->maxLineLength = maxLineLength;
}

QString TWindowFile::getLine(qsizetype i)
{
    if (i < currentPosition)
        moveDown(currentPosition - i);
    else if (i >= currentPosition + maxLines)
        moveUp(i - (currentPosition + maxLines) + 1);

    //  currentPosition <= i < currentPosition + maxLines
    return lines[ i - currentPosition];
}

QString TWindowFile::getLines(qsizetype first, qsizetype last)
{
    if (last <= first)
        return QString();
    last = std::min<qsizetype>(last, first + maxLines);
    if (first < currentPosition)
        moveDown(currentPosition - first);
    else if (first >= currentPosition + maxLines)
        moveUp(first - (currentPosition + maxLines) + 1);


    // currentPosition <= first < last <= currentPosition + maxLines
    QString result;
    for (; first < last; ++first){
        result.append(lines[first]);
        result.append(QChar::fromLatin1('\n'));
    }
    return result;
}

void TWindowFile::moveUp(qsizetype lines)
{
    currentPosition += lines;
    if (currentPosition > totalLines)
        currentPosition = totalLines;
    read();
}

void TWindowFile::moveDown(qsizetype lines)
{
    if (currentPosition < lines)
        currentPosition = 0;
    else
        currentPosition -= lines;

    read();
}

void TWindowFile::read(){
    QString l = in.readLine(maxLineLength);
}

