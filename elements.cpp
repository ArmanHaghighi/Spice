#include "elements.h"

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <qpainter.h>
#include <QPixmap>

#include "properties.h"
#include "ui_properties.h"

Element::Element() {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    firstLead = {Element::boundingRect().right(), 0};
    secondLead = {Element::boundingRect().left(), 0};
    setTransformOriginPoint(Element::boundingRect().center());
}

QRectF Element::boundingRect() const {
    return {-25, -10, 50, 20};
}

QVariant Element::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        newPos.setX(qRound(newPos.x() / 25) * 25);
        newPos.setY(qRound(newPos.y() / 25) * 25);
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
        this->setRotation(rotation() + 90);

        QTransform transform;
        transform.rotate(90);
        firstLead = transform.map(firstLead);
        secondLead = transform.map(secondLead);

        event->accept();
    } else
        QGraphicsItem::mousePressEvent(event);
}

void Element::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto *properties = new Properties(dynamic_cast<QWidget *>(this));
        properties->getUi()->NameTxt->setText(name);
        properties->getUi()->ValTxt->setText(value);
        if (properties->exec() == QDialog::Accepted) {
            this->setName(properties->getUi()->NameTxt->text());
            this->setValue(properties->getUi()->ValTxt->text());
        }

        event->accept();
    } else
        QGraphicsItem::mouseDoubleClickEvent(event);
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black));
    painter->drawText(boundingRect().topLeft(), name);
    painter->drawText(QPointF{boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y() + 10}, value);
}

void Element::setName(QString name) {
    this->name = name;
}


void Element::setValue(QString value) {
    if (value.isEmpty())
        return;
    this->value = value;
}

Resistor::Resistor() : Element() {
}

void Resistor::setName(QString name) {
    if (name.isEmpty())
        return;
    if (name.at(0) != 'R') {
        name.insert(0, "R");
    }
    this->name = name;
}

void Resistor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);
    static const QPointF points[] = {
        {-25, 0},
        {-15, 0},
        {-12, 10},
        {-6, -10},
        {0, 10},
        {6, -10},
        {12, 10},
        {15, 0},
        {25, 0}
    };
    painter->setPen(Qt::black);
    painter->drawPolyline(points, 9);
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

Capacitor::Capacitor() : Element() {
}

void Capacitor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    static const QPointF pointsPairs[] = {
        {-25, 0}, {-5, 0},
        {-5, 10}, {-5, -10},
        {5, 10}, {5, -10},
        {25, 0}, {5, 0}

    };
    painter->setPen(Qt::black);
    painter->drawLines(pointsPairs, 4);
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void Capacitor::setName(QString name) {
    if (name.isEmpty())
        return;
    char const c = 'C';
    if (name.at(0) != c) {
        name.insert(0, c);
    }
    this->name = name;
}

Inductor::Inductor() : Element() {
}

void Inductor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath painterPath({-25, 0});

    painterPath.lineTo(-15, 0);
    painterPath.arcTo({-15, -5, 10, 10}, 180, -180);
    painterPath.arcTo({-5, -5, 10, 10}, 180, -180);
    painterPath.arcTo({5, -5, 10, 10}, 180, -180);
    painterPath.lineTo(25, 0);

    painter->setPen(Qt::black);
    painter->drawPath(painterPath);
    // Optional: Draw component selection highlight
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void Inductor::setName(QString name) {
    if (name.isEmpty())
        return;
    char const c = 'I';
    if (name.at(0) != c) {
        name.insert(0, c);
    }
    this->name = name;
}

Gnd::Gnd() : Element() {
}

QRectF Gnd::boundingRect() const {
    return {-12.5, 0, 25, 30};
}

void Gnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    static const QPointF pointsPairs[] = {
        {0, 0}, {0, 20},
        {-12.5, 20}, {12.5, 20},
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

void Gnd::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();
}

// Ideal Diode
IdealDiode::IdealDiode() : Element() {
}

void IdealDiode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Triangle (anode)
    QPolygonF triangle;
    triangle << QPointF(-15, -8) << QPointF(5, 0) << QPointF(-15, 8);

    painter->setPen(Qt::black);
    painter->drawPolygon(triangle);

    // Bar (cathode)
    painter->drawLine(QPointF(5, -8), QPointF(5, 8));

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-15, 0));
    painter->drawLine(QPointF(5, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void IdealDiode::setName(QString name) {
    if (name.isEmpty())
        return;
    char const c = 'D';
    if (name.at(0) != c) {
        name.insert(0, c);
    }
    this->name = name;
}

// Silicon Diode (similar but with different symbol)
void SiliconDiode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    IdealDiode::paint(painter, option, widget);

    QPolygonF triangle;
    triangle << QPointF(-15, -8) << QPointF(5, 0) << QPointF(-15, 8);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawPolygon(triangle, Qt::OddEvenFill);
    painter->setBrush(Qt::NoBrush);
}

void SiliconDiode::setName(QString name) {
    if (name.isEmpty())
        return;
    char const c = 'D';
    if (name.at(0) != c) {
        name.insert(0, c);
    }
    this->name = name;
}

DCVoltageSource::DCVoltageSource() : Element() {
}

// DC Voltage Source
void DCVoltageSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Circle
    painter->drawEllipse(-10, -10, 20, 20);

    // Plus/minus signs
    painter->drawLine(QPointF(-5, -5), QPointF(-5, -1));
    painter->drawLine(QPointF(-7, -3), QPointF(-3, -3));

    painter->drawLine(QPointF(-5, 1), QPointF(-5, 5));
    painter->drawLine(QPointF(-7, 3), QPointF(-3, 3));

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void DCVoltageSource::setName(QString name) {
    if (name.isEmpty())
        return;
    char const c = 'D';
    if (name.at(0) != c) {
        name.insert(0, c);
    }
    this->name = name;
}

// AC Voltage Source
void ACVoltageSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Circle
    painter->drawEllipse(-10, -10, 20, 20);

    // Sine wave
    QPainterPath wave;
    wave.moveTo(-5, 0);
    wave.cubicTo(-2.5, -7, 2.5, 7, 5, 0);
    painter->drawPath(wave);

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void ACVoltageSource::setName(QString name) {
    // if (name.isEmpty())                  //TODO:implement naming system based on the netlist system
    //     return;
    // string const c="Vsin";
    // if (name.at(0) != c) {
    //     name.insert(0, c);
    // }
    // this->name=name;
}

// DC Current Source
void DCCurrentSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Circle
    painter->drawEllipse(-10, -10, 20, 20);

    // Arrow inside
    painter->drawLine(QPointF(0, -5), QPointF(0, 5));
    painter->drawLine(QPointF(0, 5), QPointF(-3, 2));
    painter->drawLine(QPointF(0, 5), QPointF(3, 2));

    // "DC" label
    painter->drawText(QRectF(-5, -3, 10, 6), Qt::AlignCenter, "DC");

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void DCCurrentSource::setName(QString name) {
    Element::setName(name);
}

// AC Current Source
void ACCurrentSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Circle
    painter->drawEllipse(-10, -10, 20, 20);

    // Arrow inside
    painter->drawLine(QPointF(0, -5), QPointF(0, 5));
    painter->drawLine(QPointF(0, 5), QPointF(-3, 2));
    painter->drawLine(QPointF(0, 5), QPointF(3, 2));

    // "~" symbol
    QPainterPath wave;
    wave.moveTo(-3, 0);
    wave.cubicTo(-1.5, -3, 1.5, 3, 3, 0);
    painter->drawPath(wave);

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void ACCurrentSource::setName(QString name) {
    Element::setName(name);
}

// Dependent sources (diamond shape)
void VCVS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Diamond shape
    QPolygonF diamond;
    diamond << QPointF(0, -10) << QPointF(10, 0) << QPointF(0, 10) << QPointF(-10, 0);
    painter->drawPolygon(diamond);

    // Label
    painter->drawText(QRectF(-8, -5, 16, 10), Qt::AlignCenter, "VCVS");

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void VCVS::setName(QString name) {
    Element::setName(name);
}

void VCCS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Diamond shape
    QPolygonF diamond;
    diamond << QPointF(0, -10) << QPointF(10, 0) << QPointF(0, 10) << QPointF(-10, 0);
    painter->drawPolygon(diamond);

    // Label
    painter->drawText(QRectF(-8, -5, 16, 10), Qt::AlignCenter, "VCCS");

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void VCCS::setName(QString name) {
    Element::setName(name);
}

void CCVS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Diamond shape
    QPolygonF diamond;
    diamond << QPointF(0, -10) << QPointF(10, 0) << QPointF(0, 10) << QPointF(-10, 0);
    painter->drawPolygon(diamond);

    // Label
    painter->drawText(QRectF(-8, -5, 16, 10), Qt::AlignCenter, "CCVS");

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void CCVS::setName(QString name) {
    Element::setName(name);
}

void CCCS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Element::paint(painter, option, widget);

    // Diamond shape
    QPolygonF diamond;
    diamond << QPointF(0, -10) << QPointF(10, 0) << QPointF(0, 10) << QPointF(-10, 0);
    painter->drawPolygon(diamond);

    // Label
    painter->drawText(QRectF(-8, -5, 16, 10), Qt::AlignCenter, "CCCS");

    // Leads
    painter->drawLine(QPointF(-25, 0), QPointF(-10, 0));
    painter->drawLine(QPointF(10, 0), QPointF(25, 0));

    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void CCCS::setName(QString name) {
    Element::setName(name);
}
