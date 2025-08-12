#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsItem>
#include <bits/stdc++.h>
using namespace std;
class Element : public QGraphicsItem
{
public:
    Element();
    QRectF boundingRect() const override;
    QPointF firstLead;
    QPointF secondLead;

    // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    string name;
    string value;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


};

class Resistor : public Element {
    public:
    Resistor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class Capacitor : public Element {
    public:
    Capacitor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class Inductor : public Element {
public:
    Inductor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class Gnd : public Element {
public:
    Gnd();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class IdealDiode : public Element {
public:
    IdealDiode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class SiliconDiode : public IdealDiode {
public:
    SiliconDiode():IdealDiode(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class DCVoltageSource : public Element {
public:
    DCVoltageSource();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class ACVoltageSource : public Element {
public:
    ACVoltageSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class DCCurrentSource : public Element {
public:
    DCCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class ACCurrentSource : public Element {
public:
    ACCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class VCVS : public Element {
public:
    VCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class VCCS : public Element {
public:
    VCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class CCVS : public Element {
public:
    CCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class CCCS : public Element {
public:
    CCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif // ELEMENTS_H
