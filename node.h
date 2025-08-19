#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QSet>
#include <QGraphicsObject>


class Element;

class Node : public QGraphicsObject{
    Q_OBJECT
public:
    enum NodeType { Default, Junction };
    explicit Node(Element* parent=nullptr,NodeType type=Default);
    QRectF boundingRect() const override;
    // Identification
    void setName(const QString& name);
    QString name() const;

    // Connection management
    void connectElement(Element* element);

    // Electrical properties
    double voltage() const;
    void setVoltage(double voltage);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QGraphicsEllipseItem* ellipse;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    NodeType type=Default;
    void setScenePosition(const QPointF& pos);
 public slots:
    // void handleParentMoved();
signals:
    void positionChanged();
    void scenePositionChanged();


private:
    QString m_name;
    double m_voltage = 0.0;
    QSet<Element*> m_connections;
};

#endif // NODE_H