#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMouseEvent>
#include <bits/stdc++.h>
#include "elements.h"
#include "addelementdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class SchematicView;
class QShortcut;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    Ui::MainWindow *ui;
    void deleteSelectedItems();

    void tileSubWindowsVertically() const ;

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionTransient_triggered();

    void on_actionAc_Sweep_triggered();

    void on_actionDc_Sweep_triggered();

    void on_actionPhase_triggered();

    void on_actionEscape_triggered();


    void on_actionResistor_toggled(bool arg1);

    void on_actionInductor_toggled(bool arg1);

    void on_actionDuplicate_toggled(bool arg1);

    void on_actionDelete_toggled(bool arg1);

    void on_actionWire_toggled(bool arg1);

    void on_actionCapacitor_toggled(bool arg1);

    void on_actionAdd_Element_toggled(bool arg1);

    void on_actionGnd_toggled(bool arg1);

    void handleMouseRelease(QMouseEvent* event);
private:
    SchematicView* schematic=nullptr;
    QShortcut *escapeShortcut;
    std::vector<Element*> elements;

    enum class ToolType {
        None,
        Resistor,
        Capacitor,
        Inductor,
        Wire,
        Gnd,
        IdealDiode,
        SiliconDiode,
        DCVoltageSource,
        ACVoltageSource
    };
    ToolType currentTool = ToolType::None;

    void placeElementOnClick(QMouseEvent *event);
};

class SchematicView :public QGraphicsView{
    Q_OBJECT
public:
    QGraphicsScene* schematicScene;

    explicit SchematicView(MainWindow* mainWindow);
    SchematicView(QWidget* wid);
    ~SchematicView() override{
        delete schematicScene;
    }
signals:
    void mousePressed(QMouseEvent* event);
    void mouseReleased(QMouseEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event) override ;
    void mouseReleaseEvent(QMouseEvent* event) override;
};
#endif // MAINWINDOW_H
