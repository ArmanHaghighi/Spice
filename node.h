#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QSet>

class Element;

class Node : public QGraphicsEllipseItem {
public:
    explicit Node(Element* parent);

    // Identification
    void setName(const QString& name);
    QString name() const;

    // Connection management
    void connect(Element* element);

    // Electrical properties
    double voltage() const;
    void setVoltage(double voltage);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString m_name;
    double m_voltage = 0.0;
    QSet<Element*> m_connections;
};

#endif // NODE_H