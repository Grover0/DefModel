#ifndef SCENE_H
#define SCENE_H

#include "calculation.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsItemGroup>
#include <QAbstractGraphicsShapeItem>
#include "excelinouthelper.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

    Calculation* myCalc;
    int idTimer;
    enum drawMode{NONE, LINE, RECT, POINT};
    drawMode m_drawMode=NONE;
    bool m_doneConcretePath=false;
    bool m_doneReinforcement=false;
    QVector<QPointF> m_concretePoints;  //Points of concrete section in GraphicsScene coordinats
    QVector<QVector<QPointF>> m_dividedPoints;   //Points of divided elements in GraphicsScene coordinats
    QVector<QVector<QVector<QPointF>>> m_dividedRegions;   //Points of divided regions in GraphicsScene coordinats
    QVector<QVector<QVector<QVector<int>>>> m_dividedFaces;          //Numbers of points for every face of divided rectangular
    QVector<QPair<uint,QPointF>> m_reinfCircles;    //container to store diameter and point of every reinforcement bar
    QPainterPath* m_concretePath;       //Path to draw concrete section
    uint m_currDiam=10;                    //current reinforcement diameter
    QPen pen;
    QBrush brush;
    uint m_pointSize=5;
    QGraphicsEllipseItem* m_currentItem;
    QList<QGraphicsItem*> m_pointsItems;    //List to store points of concrete section
    QList<QGraphicsRectItem*> m_divisionItems;    //List to store divided rectangles of concrete section
    QList<QGraphicsPathItem*> m_divisionPaths;    //List to store divided paths of concrete section
    QList<QGraphicsEllipseItem*> m_reinfItems;      //List to store reinforcement circles
    QVector<QVector<double>> m_concreteArea;        //Areas of the divided elements
    QVector<QVector<double>> m_concreteJx;          //Moments of inertia about X axis of the divided elements
    QVector<QVector<double>> m_concreteJy;          //Moments of inertia about Y axis of the divided elements
    QVector<QVector<QPointF>> m_concreteCenter;     //Point in center of the divided elements
    //QGraphicsItemGroup* m_pointsGroup;
    QPointF m_basePoint;                    //Point to transform coordinats for display
    double m_recWidth;      //Actual size of concrete section
    double m_recHeight;
    double lowX;            //boundaries of the section
    double highX;
    double lowY;
    double highY;
    uint nXdivisions=10;    //Number of divisions for concrete section
    uint nYdivisions=10;
    uint m_viewMargin=20;
    bool m_isRect;
    bool m_leftToRight;
    bool m_NIsSet=false;
    bool m_MxIsSet=false;
    bool m_MyIsSet=false;

    QPointF toSceneCoord(const QPointF&);   //Transform coordinats methods
    QPointF fromSceneCoord(const QPointF&);
    void drawPoint(const QPointF&);         //Draw points of concrete section method
    void getSectSizes();
    void drawDivisions();
    bool isBetween(QPointF, QPointF, QPointF);
    void Divide();
    void checkForces();
    void switchPoint(QPointF&, QPointF&);

public:
    explicit Scene(QWidget *parent = nullptr);
    drawMode getDrawMode();
    void setBasePoint(QPointF);
    int getCurrDiam();
    void loadData();

signals:
    void signalDrawMode(bool);
    void signalPointAdded(QPointF);
    void signalSceneInit();
    void signalCoordChanged(QPointF);
    void signalSceneCleared(bool);
    void signalSceneDivided(bool);
    void signalSectDone(bool);
    void signalReinfDone(bool);
    void signalReinfCleared(bool);
    void signalFitView();
    void signalForcesDone(bool);
    //void signalGetRDiameter(int);
    void signalSetEb(double);
    void signalSetEs(double);
    void signalSetRb(double);
    void signalSetRbt(double);
    void signalSetRs(double);

public slots:
    void setDrawLine();
    void setDrawRect();
    void setDrawPoint();
    void slotGetCommand(QString);
    void slotSceneInit();
    void slotNewSection();
    void slotDivideX(uint);
    void slotDivideY(uint);
    void slotSetRDiameter(int);
    void slotNewReinf();
    void slotCalculate();
    void slotFitView();
    void slotSetN(QString);
    void slotSetMx(QString);
    void slotSetMy(QString);
    void slotSetEb(double);
    void slotSetEs(double);
    void slotSetRb(double);
    void slotSetRbt(double);
    void slotSetRs(double);
    void slotImportPoints();
    void slotExportPoints();

    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void timerEvent(QTimerEvent *event);
};

#endif // SCENE_H
