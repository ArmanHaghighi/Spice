#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsItem>

class Element : public QGraphicsItem
{
public:
    Element();
    QRectF boundingRect() const override;
    QPointF firstLead;
    QPointF secondLead;
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
#endif // ELEMENTS_H
