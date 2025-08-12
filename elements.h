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
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class SiliconeDiode : public Element {
public:
    SiliconeDiode();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class VoltageSource : public Element {
public:
    VoltageSource();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif // ELEMENTS_H
