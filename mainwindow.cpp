#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());

}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open the file"));
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file : ") + file.errorString());
        return ;
    }

    currentFile = filename;
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save as"));
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Warning"), tr("Cannot save file : ") + file.errorString());
        return ;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName(tr("Printer name"));
    QPrintDialog pDialog(&printer, this);

    if (pDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot access printer"));
        return ;
    }

    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
