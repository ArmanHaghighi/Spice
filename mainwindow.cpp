#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "elements.h"
#include <QShortcut>
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (QAction *action : ui->menuFile->actions()) {
        action->setIconVisibleInMenu(false);  // Hides icons in menus
    }
    // In MainWindow constructor
    QShortcut *escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escapeShortcut, &QShortcut::activated, this, &MainWindow::on_actionEscape_triggered);

    connect(ui->schematicView,  &SchematicView::mousePressed,
                this, &MainWindow::placeElementOnClick);
    schematic = new SchematicView(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}

SchematicView::SchematicView(MainWindow *mainWindow) {
    mainWindow->tileSubWindowsVertically();
    schematicScene=new QGraphicsScene(mainWindow);
    schematicScene->setSceneRect(-10000,-10000,20000,20000);

    auto schView =mainWindow->ui->schematicView;
    schView->setScene(schematicScene);
    schView->setRenderHint(QPainter::Antialiasing);
    schView->setDragMode(RubberBandDrag);
    schView->setViewportUpdateMode(FullViewportUpdate);

    QPen gridPen(QColor(220, 220, 220),1,Qt::PenStyle::DotLine);
    for(int x = -10025; x <= 10000; x += 50) {
        schematicScene->addLine(x, -10000, x, 10000, gridPen);
    }
    for(int y = -10000; y <= 10000; y += 50) {
        schematicScene->addLine(-10000, y, 10000, y, gridPen);
    }
}

SchematicView::SchematicView(QWidget *wid)
{

}

void SchematicView::mousePressEvent(QMouseEvent *event) {
    emit mousePressed(event);
    QGraphicsView::mousePressEvent(event);
}



void MainWindow::on_actionResistor_toggled(bool checked)
    {
        std::cout<<"Resistor"<<std::endl;
        if(checked) {
            currentTool=ToolType::Resistor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionResistor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Resistor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }
void MainWindow::on_actionCapacitor_toggled(bool checked)
    {
        std::cout<<"Cap"<<std::endl;
        if(checked) {
            currentTool=ToolType::Capacitor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionCapacitor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Capacitor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }
    void MainWindow::on_actionInductor_toggled(bool checked)
    {
        std::cout<<"Ind"<<std::endl;
        if(checked) {
            currentTool=ToolType::Inductor;
            // disableing other actions
            for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionInductor)
                    a->setChecked(false);
            }
            ui->schematicView->setCursor(Qt::CrossCursor);
        }
        else if(currentTool==ToolType::Inductor) {
            ui->schematicView->setCursor(Qt::ArrowCursor);
            currentTool=ToolType::None;
            // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
            //                   this, &MainWindow::placeElementOnClick);
        }
    }





    void MainWindow::on_actionNew_triggered()
    {

    }


    void MainWindow::on_actionOpen_triggered()
    {

    }


    void MainWindow::on_actionSave_triggered()
    {

    }


    // void MainWindow::on_actionAdd_Element_triggered()
    // {
    //     std::cout<<"AddE"<<std::endl;
    //     // disableing other actions
    //
    //     }
    // }


    // void MainWindow::on_actionDuplicate_triggered()
    // {
    //     std::cout<<"Dup"<<std::endl;
    //     // disableing other actions
    //     for(QAction *a:ui->toolBar->actions()){
    //         if (a!=ui->actionDuplicate)
    //             a->setChecked(false);
    //     }
    //
    // }
    //
    //
    // void MainWindow::on_actionDelete_triggered()
    // {
    //     std::cout<<"Del"<<std::endl;
    //     // disableing other actions
    //     for(QAction *a:ui->toolBar->actions()){
    //         if (a!=ui->actionDelete)
    //             a->setChecked(false);
    //     }
    //
    // }


    void MainWindow::on_actionEscape_triggered()
    {
        std::cout<<"Esc"<<std::endl;
        // disableing other actions
        for(QAction *a:ui->toolBar->actions()){
                a->setChecked(false);
        }
    currentTool=ToolType::None;
    ui->schematicView->setCursor(Qt::ArrowCursor);
    }







    void MainWindow::on_actionTransient_triggered()
    {

    }


    void MainWindow::on_actionAc_Sweep_triggered()
    {

    }


    void MainWindow::on_actionDc_Sweep_triggered()
    {

    }


    void MainWindow::on_actionPhase_triggered()
    {

    }



void MainWindow::tileSubWindowsVertically() const {
    ui->mdiArea->tileSubWindows();
}

// void MainWindow::placeElementOnClick(QMouseEvent *event,Element* e,QAction* action) {
//     if (event->button()==Qt::LeftButton&&action->isChecked()) {
//         QPointF screenPos = ui->schematicView->mapToScene(event->pos());
//
//         qreal x =round(screenPos.x()/50)*50;
//         qreal y =round(screenPos.y()/50)*50;
//
//         e->setPos(x,y);
//         schematic->schematicScene->addItem(e);
//
//         elements.emplace_back(e);
//     }
// }


void MainWindow::
placeElementOnClick(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || currentTool == ToolType::None)
        return;

    QPointF screenPos = ui->schematicView->mapToScene(event->pos());
    qreal x,y;
    if (ToolType::Gnd==currentTool) {
         x = qRound(screenPos.x()/50)*50+25;
         y = qRound(screenPos.y()/50)*50;
    }else {
         x = qRound(screenPos.x()/50)*50;
         y = qRound(screenPos.y()/50)*50;
    }
    Element* newElement = nullptr;

    switch(currentTool) {
        case ToolType::Resistor:
            newElement = new Resistor();
            break;
        case ToolType::Capacitor:
            newElement = new Capacitor();
            break;
        case ToolType::Inductor:
            newElement = new Inductor();
            break;
        case ToolType::Gnd:
            newElement = new Gnd();
            break;
        case ToolType::Wire:
            // newElement = new Wire();
            break;
        default:
            return;
    }

    if (newElement) {
        newElement->setPos(x, y);
        schematic->schematicScene->addItem(newElement);
        elements.emplace_back(newElement);
    }
}


void MainWindow::on_actionDuplicate_toggled(bool arg1)
{

}


void MainWindow::on_actionDelete_toggled(bool arg1)
{

}


void MainWindow::on_actionWire_toggled(bool arg1)
{

}


void MainWindow::on_actionAdd_Element_toggled(bool arg1)
{
    for(QAction *a:ui->toolBar->actions()){
                if (a!=ui->actionAdd_Element)
            a->setChecked(false);
    }
    AddElementDialog* addElementdDialog = new AddElementDialog;
    if (addElementdDialog->exec() == QDialog::Accepted) {
        cout<<"Add Element"<<endl;
    }
    else {
        ui->actionAdd_Element->setChecked(false);
    }

    delete addElementdDialog;
}


void MainWindow::on_actionGnd_toggled(bool checked)
{
    std::cout<<"Gnd"<<std::endl;
    if(checked) {
        currentTool=ToolType::Gnd;
        // disableing other actions
        for(QAction *a:ui->toolBar->actions()){
            if (a!=ui->actionGnd)
                a->setChecked(false);
        }
        ui->schematicView->setCursor(Qt::CrossCursor);
    }
    else if(currentTool==ToolType::Gnd) {
        ui->schematicView->setCursor(Qt::ArrowCursor);
        currentTool=ToolType::None;
        // disconnect(ui->schematicView, &QGraphicsView::mousePressEvent,
        //                   this, &MainWindow::placeElementOnClick);
    }
}

