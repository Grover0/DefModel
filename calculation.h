#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>
#include <QPointF>

class Calculation : public QObject
{
    Q_OBJECT

    QVector<QVector<double>> m_concreteArea;
    QVector<QVector<QPointF>> m_concreteCenter;
    QVector<double> m_reinfArea;
    QVector<QPointF> m_reinfCenter;
    uint nXdivisions;    //Number of divisions for concrete section
    uint nYdivisions;

public:
    explicit Calculation(QObject *parent = nullptr);
    void setXdivision(uint);
    void setYdivision(uint);
    void setConcreteArea(const QVector<QVector<double>>&);
    void setConcreteCenter(const QVector<QVector<QPointF>>&);
    void setReinfArea(const QVector<QPair<uint,QPointF>>&);

signals:

public slots:
};

#endif // CALCULATION_H
