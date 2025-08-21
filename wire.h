#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsPathItem>
#include <QGraphicsObject>
#include "node.h"

class Wire :  public QGraphicsObject{
    Q_OBJECT
public:
    Wire(Node* startNode, Node* endNode, QGraphicsItem* parent = nullptr);

    // Connection management
    Node* startNode() const;
    Node* endNode() const;

    // Update visual representation
    void updatePath();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateConnection();
    template <class Archive>
    void serialize(Archive& ar) {
        ar(std::shared_ptr<Node>( startNode()),std::shared_ptr<Node>( endNode()));
    }
    Wire()=default;
    signals:
        void connectionChanged();

private:
    QGraphicsPathItem* pathItem;
    Node* m_startNode;
    Node* m_endNode;
};

#endif // WIRE_H