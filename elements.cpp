#include "elements.h"

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <qpainter.h>
#include <QPixmap>
Element::Element() {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    firstLead={Element::boundingRect().right(),0};
    secondLead={Element::boundingRect().left(),0};
    setTransformOriginPoint(Element::boundingRect().center());
}

QRectF Element::boundingRect() const {
    return {-25,-10,50,20};

}

QVariant Element::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange&&scene()) {
        QPointF newPos = value.toPointF();
            newPos.setX(qRound(newPos.x()/25)*25);
            newPos.setY(qRound(newPos.y()/25)*25);
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}


// void Element::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//     QPointF screenPos = mapToScene(event->pos());
//     qreal x = qRound(screenPos.x()/50)*50;
//     qreal y = qRound(screenPos.y()/50)*50;
//
//     this->setPos(x,y);}

void Element::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        this->setRotation(rotation()+90);
    }
    QGraphicsItem::mousePressEvent(event);
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
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
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

Gnd::Gnd() :Element(){
}

QRectF Gnd::boundingRect() const {
    return {-12.5, 0, 25, 30};
}

void Gnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    static const QPointF pointsPairs[] = {
        {0, 0}, {0,20 },
        {-12.5,20},{12.5,20},
        {-7, 25}, {7, 25},
        {-3, 30}, {3, 30}
    };

    painter->setPen(Qt::black);
    painter->drawLines(pointsPairs, 4);

    // Optional selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }

}

