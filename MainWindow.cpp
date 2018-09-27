﻿#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtDebug>
#include <QSettings>
#include <QClipboard>

#include "ExportUntranslated.h"
#include "ExportNew.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widget_language1, SIGNAL(sig_result(QString)), this, SLOT(onLanguageResult(QString)));
    connect(ui->widget_language1, SIGNAL(sig_cursorPositionChanged(int,QString)), ui->widget_language2, SLOT(onSetCursorPosition(int,QString)));

    QSettings setting("./setting.ini", QSettings::IniFormat);
    QString strPath1 = setting.value("FilePath1").toString();
    QString strPath2 = setting.value("FilePath2").toString();
    ui->widget_language1->setIndex(0);
    ui->widget_language1->loadFile(strPath1);
    ui->widget_language2->setIndex(1);
    ui->widget_language2->loadFile(strPath2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLanguageResult(const QString &str)
{
    ui->lineEdit_result->setText(str);
}

void MainWindow::on_pushButton_copy_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->lineEdit_result->text());
}

void MainWindow::on_action_exportUntranslated_triggered()
{
    ExportUntranslated exportDialog(this);
    exportDialog.exec();
}

void MainWindow::on_action_exportNew_triggered()
{
    ExportNew exportDialog(this);
    exportDialog.exec();
}