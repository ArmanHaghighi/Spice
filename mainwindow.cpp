#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (QAction *action : ui->menuFile->actions()) {
        action->setIconVisibleInMenu(false);  // Hides icons in menus
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
