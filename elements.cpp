#include "elements.h"

#include <qpainter.h>
#include <QPixmap>
Element::Element() {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    firstLead={Element::boundingRect().right(),0};
    secondLead={Element::boundingRect().left(),0};
}

QRectF Element::boundingRect() const {
    return {-25,-10,50,20};

}

Resistor::Resistor() :Element(){
}

void Resistor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    static const QPointF points[] = {
        {-25,0},
        {-15,0},
        {-12,10},
        {-6,-10},
        {0,10},
        {6,-10},
        {12,10},
        {15,0},
        {25,0}
    };
    painter->setPen(Qt::black);
    painter->drawPolyline(points,9);
}

Capacitor::Capacitor() :Element(){
}

void Capacitor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    static const QPointF pointsPairs[] = {
        {-25,0},{-5,0},
        {-5,10},{-5,-10},
        {5,10},{5,-10},
        {25,0},{5,0}

    };
    painter->setPen(Qt::black);
    painter->drawLines(pointsPairs,4);
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

Inductor::Inductor() :Element(){
}

void Inductor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath painterPath({-25,0});

    painterPath.lineTo(-15,0);
    painterPath.arcTo({-15,-5,10,10},180,-180);
    painterPath.arcTo({-5,-5,10,10},180,-180);
    painterPath.arcTo({5,-5,10,10},180,-180);
    painterPath.lineTo(25,0);

    painter->setPen(Qt::black);
    painter->drawPath(painterPath);
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

