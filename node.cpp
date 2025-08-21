#include "node.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <qgraphicssceneevent.h>
#include <QLabel>
#include <qlayout.h>
#include <QLineEdit>
#include <QInputDialog>
#include "elements.h"
#include <QPainter>
#include <QSet>
#include <QQueue>



Node::Node(Element* parent,NodeType type)
    :QGraphicsObject(parent)
,ellipse(new QGraphicsEllipseItem()) {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    ellipse->setFlag(ItemIsSelectable);
    if (type==NodeType::Junction){
        // ellipse->setFlag(ItemIsMovable);
        // ellipse->setBrush(Qt::green);
    }
}

QRectF Node::boundingRect() const {
    return ellipse->boundingRect();
}

void Node::setName(const QString& name) {
    m_name = name;
    setToolTip(name);  // Show name on hover
}

QString Node::name() const {
    return m_name;
}

void Node::connectElement(Element* element) {
    if (element) {
        m_connections.insert(element);
    }
}

double Node::voltage() const {
    return m_voltage;
}

void Node::setVoltage(double voltage) {
    m_voltage = voltage;
    update();  // Redraw to show voltage
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

    if (!m_connections.isEmpty()||isSelected()) {
        ellipse->setPen(QPen(Qt::NoPen));
    }
    else
        ellipse->setPen(QPen(Qt::darkBlue));

    QPointF newPos = pos();
    newPos.setX(qRound(newPos.x() / GRID_SIZE) * GRID_SIZE);
    newPos.setY(qRound(newPos.y() / GRID_SIZE) * GRID_SIZE);
    setPos(newPos);
    ellipse->setRect(-3,-3,6,6);
    ellipse->paint(painter, option, widget);

    // Show name and voltage
    painter->setPen(Qt::black);
    QString text = m_name;
    painter->setFont(QFont("tahoma",6,3));
    painter->drawText(boundingRect().topRight()+QPointF{3,-3}, text);
}


QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value) {
     if (change == ItemPositionChange && scene()) {
         // Snap to grid
         QPointF newPos = value.toPointF();
         newPos.setX(qRound(newPos.x() / GRID_SIZE) * GRID_SIZE);
         newPos.setY(qRound(newPos.y() / GRID_SIZE) * GRID_SIZE);
         return newPos;
     }
     if (change == ItemPositionHasChanged || change == ItemScenePositionHasChanged) {
        emit scenePositionChanged();
    }
    return QGraphicsObject::itemChange(change, value);
}

void Node::setScenePosition(const QPointF& pos) {
    // Convert to parent coordinates if needed
    if (parentItem()) {
        setPos(parentItem()->mapFromScene(pos));
    } else {
        setPos(pos);
    }
    emit scenePositionChanged();
    emit positionChanged();
}
void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        bool ok;
        QString newName = QInputDialog::getText(nullptr, "Set Name", "Name:",
                                               QLineEdit::Normal, name(), &ok);
        if (ok && !newName.isEmpty()) {
            setName(newName);
            setHasCustomName(true);
            emit namePropagationRequested(this, newName);
        }
        event->accept();
    } else {
        QGraphicsObject::mouseDoubleClickEvent(event);
    }
}

bool Node::hasCustomName() const {
    return m_hasCustomName;
}

void Node::setHasCustomName(bool custom) {
    m_hasCustomName = custom;
}

void Node::propagateNameToConnectedNodes(const QString& name) {
    if (this->name() == name || this->name() == "Gnd") return;

    setName(name);
    setHasCustomName(false);

    // Propagate to all connected nodes
    for (Node* connectedNode : m_connectedNodes) {
        if (!connectedNode->hasCustomName() && connectedNode->name() != name && connectedNode->name() != "Gnd") {
            connectedNode->setName(name);
            connectedNode->setHasCustomName(false);
        }
    }
}