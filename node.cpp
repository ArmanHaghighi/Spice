#include "node.h"
#include "elements.h"
#include <QPainter>

Node::Node(Element* parent)
    : QGraphicsEllipseItem(-2, -2, 4, 4, parent)
{

    setPen(QPen(Qt::darkBlue));
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Node::setName(const QString& name) {
    m_name = name;
    setToolTip(name);  // Show name on hover
}

QString Node::name() const {
    return m_name;
}

void Node::connect(Element* element) {
    if (element) m_connections.insert(element);
}

double Node::voltage() const {
    return m_voltage;
}

void Node::setVoltage(double voltage) {
    m_voltage = voltage;
    update();  // Redraw to show voltage
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QGraphicsEllipseItem::paint(painter, option, widget);

    if (!m_connections.isEmpty()) {
        setPen(QPen(Qt::NoPen));
        QGraphicsEllipseItem::paint(painter, option, widget);
    }

    // Show name and voltage
    painter->setPen(Qt::black);
    QString text = m_name;
    painter->setFont(QFont("tahoma",6,3));
    painter->drawText(boundingRect().topRight()+QPointF{3,-3}, text);
}