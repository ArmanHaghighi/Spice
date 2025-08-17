#include "mainwindow.h"

#include <qlistwidget.h>

#include "./ui_mainwindow.h"
#include "elements.h"
#include <QShortcut>
#include <QMessageBox>
#include <ui_addelementdialog.h>
#include <ui_trandialog.h>

#include "trandialog.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (QAction *action : ui->menuFile->actions()) {
        action->setIconVisibleInMenu(false);  // Hides icons in menus
    }
    escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escapeShortcut, &QShortcut::activated, this, &MainWindow::on_actionEscape_triggered);

    connect(ui->schematicView,  &SchematicView::mousePressed,
                this, &MainWindow::placeElementOnClick);
    schematic = new SchematicView(this);

}

MainWindow::~MainWindow()
{   delete escapeShortcut;
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
    schView->setResizeAnchor(AnchorUnderMouse);
    QPen gridPen(QColor(220, 220, 220),1,Qt::PenStyle::DotLine);
    for(double x = -10000; x <= 10000; x += GRID_SIZE) {
        schematicScene->addLine(x, -10000, x, 10000, gridPen);
    }
    for(double y = -10000; y <= 10000; y += GRID_SIZE) {
        schematicScene->addLine(-10000, y, 10000, y, gridPen);
    }
}

SchematicView::SchematicView(QWidget *wid)
{

}

void SchematicView::resizeEvent(QResizeEvent *event) {

    QGraphicsView::resizeEvent(event);

}

void SchematicView::mousePressEvent(QMouseEvent *event) {
    emit mousePressed(event);
    QGraphicsView::mousePressEvent(event);
}

void SchematicView::mouseReleaseEvent(QMouseEvent *event) {
    emit mouseReleased(event);
    QGraphicsView::mouseReleaseEvent(event);
}

void SchematicView::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() .testFlag(Qt::ControlModifier)) {
        const double scaleFactor =1.15;

        if (event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        }
        else
            scale(1/scaleFactor, 1/scaleFactor);
    }
    else
        QGraphicsView::wheelEvent(event);
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
    TranDialog d;
    QString iStop, iStart, iStep;
    if(d.exec()==QDialog::Accepted)
    {
        iStop = d.ui->inputStop->text();
        iStart = d.ui->inputStart->text();
        iStep = d.ui->inputStep->text();
    }
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


void MainWindow::placeElementOnClick(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || currentTool == ToolType::None)
        return;

    QPointF screenPos = ui->schematicView->mapToScene(event->pos());
    qreal x,y;
         x = qRound(screenPos.x()/25)*25;
         y = qRound(screenPos.y()/25)*25;
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
        case ToolType::IdealDiode:
            newElement = new IdealDiode();
            break;
        case ToolType::SiliconDiode:
            newElement = new SiliconDiode();
            break;
        case ToolType::DCVoltageSource:
            newElement = new DCVoltageSource();
            break;
        case ToolType::ACVoltageSource:
            newElement = new ACVoltageSource();
            break;
        case ToolType::DCCurrentSource:
            newElement = new DCCurrentSource();
            break;
        case ToolType::ACCurrentSource:
            newElement = new ACCurrentSource();
            break;
        case ToolType::VCVS:
            newElement = new VCVS();
            break;
        case ToolType::VCCS:
            newElement = new VCCS();
            break;
        case ToolType::CCVS:
            newElement = new CCVS();
            break;
        case ToolType::CCCS:
            newElement = new CCCS();
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


void MainWindow::on_actionDelete_toggled(bool checked)
{
    if (checked) {
        currentTool = ToolType::None; // Not really a tool, but we need to handle selection

        // Disable other actions
        for (QAction *a : ui->toolBar->actions()) {
            if (a != ui->actionDelete) {
                a->setChecked(false);
            }
        }

        ui->schematicView->setCursor(Qt::ForbiddenCursor);

        // Connect selection changed signal
        connect(ui->schematicView, &SchematicView::mouseReleased,
                this, &MainWindow::deleteSelectedItems);
    } else {
        // Disconnect the signal when delete mode is turned off
        disconnect(ui->schematicView, &SchematicView::mouseReleased,
                   this, &MainWindow::deleteSelectedItems);
    }
}

void MainWindow::deleteSelectedItems() {
    if (!ui->actionDelete->isChecked())
        return;

    auto selection =schematic->schematicScene->selectedItems();
    if (selection.empty())
        return;
    bool del=false;
    if (selection.size() >1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Elements",
                                     "Are you sure you want to delete the selected elements?",
                                     QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
            del=true;
    }
    if (selection.size()<=1) del=true;
    if (del) {
        // Delete all selected items
        for (QGraphicsItem* item : selection) {
            Element* element = dynamic_cast<Element*>(item);
            if (element) {
                // Remove from our elements vector
                elements.erase(std::remove(elements.begin(), elements.end(), element),
                             elements.end());

                // Remove from scene
                schematic->schematicScene->removeItem(element);

                // Delete the object
                delete element;
            }
        }
    }
    schematic->schematicScene->clearSelection();
}


void MainWindow::on_actionWire_toggled(bool arg1)
{

}


    void MainWindow::on_actionAdd_Element_toggled(bool arg1)
    {
        if (!arg1) {
            ui->actionAdd_Element->setChecked(false);
            currentTool = ToolType::None;
            ui->schematicView->setCursor(Qt::ArrowCursor);
            return;
        }

        // Disable other actions
        for(QAction *a : ui->toolBar->actions()) {
            if (a != ui->actionAdd_Element) {
                a->setChecked(false);
                currentTool = ToolType::None;
                ui->schematicView->setCursor(Qt::ArrowCursor);
            }
        }

        AddElementDialog* addElementDialog = new AddElementDialog(this);
        if (addElementDialog->exec() == QDialog::Accepted) {
            QListWidgetItem* selectedItem = addElementDialog->getUi()->listWidget->currentItem();
            if (selectedItem) {
                QString elementName = selectedItem->text();

                if (elementName == "Resistor") {
                    currentTool = ToolType::Resistor;
                }
                else if (elementName == "Capacitor") {
                    currentTool = ToolType::Capacitor;
                }
                else if (elementName == "Inductor") {
                    currentTool = ToolType::Inductor;
                }
                else if (elementName == "Ground") {
                    currentTool = ToolType::Gnd;
                }
                else if (elementName.contains("Ideal_Diode")) {
                    currentTool = ToolType::IdealDiode;
                }
                else if (elementName.contains("Silicon_Diode")) {
                    currentTool = ToolType::SiliconDiode;
                }
                else if (elementName == "DC_Voltage_Source") {
                    currentTool = ToolType::DCVoltageSource;
                }
                else if (elementName == "AC_Voltage_Source") {
                    currentTool = ToolType::ACVoltageSource;
                } else if (elementName == "DC_Current_Source") {
                    currentTool = ToolType::DCCurrentSource;
                }
                else if (elementName == "AC_Current_Source") {
                    currentTool = ToolType::ACCurrentSource;
                }
                else if (elementName == "VCVS") {
                    currentTool = ToolType::VCVS;
                }
                else if (elementName == "VCCS") {
                    currentTool = ToolType::VCCS;
                }
                else if (elementName == "CCVS") {
                    currentTool = ToolType::CCVS;
                }
                else if (elementName == "CCCS") {
                    currentTool = ToolType::CCCS;
                }


                ui->schematicView->setCursor(Qt::CrossCursor);
            }
        } else {
            ui->actionAdd_Element->setChecked(false);
            currentTool = ToolType::None;
        }

        delete addElementDialog;
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

void MainWindow::handleMouseRelease(QMouseEvent *event) {
}

