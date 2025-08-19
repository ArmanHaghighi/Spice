#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsItem>
#include <bits/stdc++.h>


class Node;
using namespace std;

constexpr double GRID_SIZE =12.5;
class Element : public QGraphicsItem
{
public:
    explicit Element(QGraphicsScene* parent=nullptr);
    QRectF boundingRect() const override;


    QVector<Node*> nodes{};
    virtual void addNodes();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void setName(QString name);
    virtual void setValue(QString value);
    signals:
    void elementMoved();

    protected:
    QPointF firstLead;
    QPointF secondLead;

    QString name;
    QString value;
};

class Resistor : public Element {
    public:
    Resistor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
class Capacitor : public Element {
    public:
    Capacitor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
class Inductor : public Element {
public:
    Inductor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
class Gnd : public Element {
public:
    Gnd();
    void addNodes() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};
class IdealDiode : public Element {
public:
    IdealDiode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
class SiliconDiode : public IdealDiode {
public:
    SiliconDiode():IdealDiode(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class DCVoltageSource : public Element {
public:
    DCVoltageSource();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class ACVoltageSource : public Element {
public:
    ACVoltageSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QString phase;
    QString offset;
};

class DCCurrentSource : public Element {
public:
    DCCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class ACCurrentSource : public Element {
public:
    ACCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
class DependantSource : virtual public Element {
    public:
    QPointF thirdLead;
    QPointF fourthLead;
    DependantSource();

    QRectF boundingRect() const override;
    void addNodes() override;
};
class VCVS : public DependantSource {
public:
    VCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class VCCS : public DependantSource {
public:
    VCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class CCVS : public DependantSource {
public:
    CCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};

class CCCS : public DependantSource {
public:
    CCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
};
#endif // ELEMENTS_H
