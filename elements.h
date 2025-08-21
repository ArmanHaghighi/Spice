#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsItem>
#include <bits/stdc++.h>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

class Node;
using namespace std;

constexpr double GRID_SIZE =12.5;
class Element : public QGraphicsItem
{
public:
    explicit Element(QGraphicsScene* parent=nullptr);
    QRectF boundingRect() const override;

    // Serialization function
    template <class Archive>
    void serialize(Archive& ar);

    QVector<Node*> nodes{};
    virtual void addNodes();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void setName(QString name);
    virtual void setValue(QString value);
    // Virtual function to get type name
    virtual QString getTypeName() const = 0;
    signals:
    void elementMoved();

    protected:
    QPointF firstLead;
    QPointF secondLead;

    QString name;
    QString value;
};

template<class Archive>
void Element::serialize(Archive &ar) {
    ar(name, value, firstLead, secondLead);
}

class Resistor : public Element {
    public:
    Resistor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override;
};
class Capacitor : public Element {
    public:
    Capacitor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "Capacitor";}
};
class Inductor : public Element {
public:
    Inductor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "Inductor";}
};
class Gnd : public Element {
public:
    Gnd();
    void addNodes() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QString getTypeName() const override{return "Gnd";}
};
class IdealDiode : public Element {
public:
    IdealDiode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "IdealDiode";}
};
class SiliconDiode : public IdealDiode {
public:
    SiliconDiode():IdealDiode(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "SiliconDiode";}
};

class DCVoltageSource : public Element {
public:
    DCVoltageSource();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "DCVoltageSource";}
};

class ACVoltageSource : public Element {
public:
    ACVoltageSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QString getTypeName() const override{return "ACVoltageSource";}
private:
    QString phase;
    QString offset;
};

class DCCurrentSource : public Element {
public:
    DCCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "DCCurrentSource";}
};

class ACCurrentSource : public Element {
public:
    ACCurrentSource():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "ACCurrentSource";}
};
class DependantSource : virtual public Element {
    public:
    QPointF thirdLead;
    QPointF fourthLead;
    DependantSource();

    QRectF boundingRect() const override;
    void addNodes() override;
    QString getTypeName() const override{return "DependantSource";}
};
class VCVS : public DependantSource {
public:
    VCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "VCVS";}
};

class VCCS : public DependantSource {
public:
    VCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "VCCS";}
};

class CCVS : public DependantSource {
public:
    CCVS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "CCVS";}
};

class CCCS : public DependantSource {
public:
    CCCS():Element(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setName(QString name) override;
    QString getTypeName() const override{return "CCCS";}
};


// Serialization for QPointF
namespace cereal {
    template <class Archive>
    void serialize(Archive& ar, QPointF& point) {
        ar(point.x(), point.y());
    }
}
// Serialization for QString
namespace cereal {
    template <class Archive>
    void save(Archive& ar, const QString& str) {
        ar(str.toStdString());
    }

    template <class Archive>
    void load(Archive& ar, QString& str) {
        std::string s;
        ar(s);
        str = QString::fromStdString(s);
    }
}
// Register polymorphic types for Cereal
CEREAL_REGISTER_TYPE(Resistor);
CEREAL_REGISTER_TYPE(Capacitor);
CEREAL_REGISTER_TYPE(Inductor);
CEREAL_REGISTER_TYPE(Gnd);
CEREAL_REGISTER_TYPE(IdealDiode);
CEREAL_REGISTER_TYPE(SiliconDiode);
CEREAL_REGISTER_TYPE(DCVoltageSource);
CEREAL_REGISTER_TYPE(ACVoltageSource);
CEREAL_REGISTER_TYPE(DCCurrentSource);
CEREAL_REGISTER_TYPE(ACCurrentSource);
CEREAL_REGISTER_TYPE(VCVS);
CEREAL_REGISTER_TYPE(VCCS);
CEREAL_REGISTER_TYPE(CCVS);
CEREAL_REGISTER_TYPE(CCCS);

// Register base class
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Resistor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Capacitor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,Inductor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,Gnd);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,IdealDiode);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,SiliconDiode);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,DCVoltageSource);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,ACVoltageSource);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,DCCurrentSource);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,ACCurrentSource);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,VCVS);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,VCCS);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,CCVS);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element,CCCS);
#endif // ELEMENTS_H
