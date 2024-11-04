#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hamsystem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ham = new HamSystem(ui);
}

MainWindow::~MainWindow()
{
    delete ham;
    delete ui;
}
