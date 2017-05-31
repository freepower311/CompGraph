#ifndef GLWIDGET_H
#define GLWIDGET_H
//#include <QtOpenGL/QGLWidget>
//#include <QOpenGLShaderProgram>
//#include <QMouseEvent>
//#include <QOpenGLFunctions>

//#include <QtMath>

//#include <QOpenGLWidget>

#include <GL/glu.h>
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <math.h>

#include <QVector3D>
#include <QVector4D>

#include <QWheelEvent>



class GLWidget : public QGLWidget, public QOpenGLFunctions
{
    int time;
    bool isShaderOn;
    GLuint m_time;
    double arc[50][3];
    int curMousePosX;
    int curMousePosY;
    double rotateX;
    double rotateZ;
    double translateX;
    double translateY;
    double translateZ;
    bool isRotate;
    bool isTranslate;
    int countArc;
    int arcTess;
    GLenum mode;
    double pinch[12][3];


private:
    QOpenGLShaderProgram *m_program;
    void initShaders();

public:
    GLWidget(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL(int w,int h);
    void setShader(bool isOn);
    void calculateArc();
    void drawArc(double angle);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void setArcCount(int count);
    void setArcTess(int count);
    void setMode(int index);
    void setLighting(bool isOn);
    void drawFrontFrame();
    void drawBackFrame();
    void drawUpPillow();
    void drawPillow();
    void drawArc2(double angle);
    void drawPinch();


};




#endif // GLWIDGET_H
