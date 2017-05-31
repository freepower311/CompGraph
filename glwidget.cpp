#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{
    time = 1;
    isShaderOn = false;
    for(int i = 0; i < 50 ;i++){
        arc[i][0] = 0;
        arc[i][1] = 0;
        arc[i][2] = 0;
    }
    curMousePosX = 0;
    curMousePosY = 0;
    rotateX = 90;
    rotateZ = 180;
    translateX = 0;
    translateY = -0.5;
    translateZ = -2.5;
    isRotate    = false;
    isTranslate = false;
    countArc = 32;
    arcTess = 10;
    mode = GL_POINTS;


}
void GLWidget::calculateArc(){
    double step = 1.0/(arcTess -1);
    for(int i = 0; i < arcTess ;i++){
        arc[i][0] = sin(M_PI/2 * i * step) * 0.2;
        arc[i][1] = 0;
        arc[i][2] = cos(M_PI/2 * i * step) * 0.1;
    }
}

void GLWidget::initializeGL(){

    initializeOpenGLFunctions();
    //glClearColor(0, 0, 0, 1);
    glViewport(0, 0, 500, 500);
    initShaders();
    calculateArc();
    glClearColor(1,1,1,1);
    float ambient[] = {0.1,0.1,0.1,1.0};
    float diffuse[] = {0.9,0.9,0.9,1.0};
    float spec[] = {1.0,1.0,1.0,1.0};
    float specref[] = {1.0,1.0,1.0,1.0};
    float lpos[] = {0.0,0.5,0.0,1.0};
    float black[] = {0.0,0.0,0.0,1.0};
    //float spotdir[] = {-1.0,0.0,-1.0};
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
    //glMateriali(GL_FRONT,GL_SHININESS,128);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,0.01);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.1);

    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdir);
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,10);
    glEnable(GL_NORMALIZE);

    gluPerspective(60.0f, 1, 20.0, 0);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_DEPTH);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_SRC_COLOR);


}

void GLWidget::drawArc(double angle){

    //glPushMatrix();
    //glTranslatef(0,0,0);
    double angleRad = angle/360*2*M_PI;
    double sinAngle = sin(angleRad);
    double cosAngle = cos(angleRad);

    glRotatef(angle,0,0,1);
    glBegin(GL_TRIANGLE_STRIP);//GL_TRIANGLE_STRIP GL_POINTS GL_TRIANGLE_STRIP GL_TRIANGLE_FAN
    for(int j = 0; j < arcTess ;j++){
        glVertex3d(arc[j][0],arc[j][1],arc[j][2]);
        glVertex3d(arc[j][0] * cosAngle,arc[j][0] * sinAngle,arc[j][2]);
        //glVertex3d(arc[j+1][0] * cosAngle,arc[j+1][0] * sinAngle,arc[j+1][2]);
    }
    glEnd();
    //glPopMatrix();

}

void GLWidget::drawArc2(double angle){

    //glPushMatrix();
    //glTranslatef(0,0,0);
    double angleRad = angle/360*2*M_PI;
    double sinAngle = sin(angleRad);
    double cosAngle = cos(angleRad);

    glRotatef(angle,0,0,1);
    glBegin(GL_TRIANGLE_STRIP);//GL_TRIANGLE_STRIP GL_POINTS GL_TRIANGLE_STRIP GL_TRIANGLE_FAN
    for(int j = 0; j < arcTess ;j++){
        glVertex3d(arc[j][0]              * 1.5,arc[j][1]              * 1.5,arc[j][2]   * 0.4 + 0.05);
        glVertex3d(arc[j][0] * cosAngle   * 1.5,arc[j][0] * sinAngle   * 1.5,arc[j][2]   * 0.4 + 0.05);
        //glVertex3d(arc[j+1][0] * cosAngle * 1.5,arc[j+1][0] * sinAngle * 2,arc[j+1][2] * 0.4 + 0.05);
    }
    glEnd();
    //glPopMatrix();

}

void GLWidget::drawFrontFrame(){
    int tesselation = 15;
    int tesselationCircle = tesselation * 2;
    double hight = 0.5;
    double radius = 0.4;

    double angleRad = M_PI * 1.0/(tesselation -1) * 0.6;
    double angleRadCircle = M_PI * 1.0/(tesselationCircle -1)*0.6;
    //double sinAngle = sin(angleRad);
    //double cosAngle = cos(angleRad);
    glBegin(GL_LINES);
    for(int j = 0; j < tesselation ;j++){
        glVertex3d(0,0,0);
        glVertex3d(radius * cos(angleRad * j),radius * sin(angleRad * j),hight);
    }
    glEnd();

    for(int j = 0; j < tesselation ;j++){
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i<tesselationCircle;i++){
            glVertex3d(radius *j * 1.0/(tesselation -1) * cos(angleRadCircle * i),radius *j * 1.0/(tesselation -1) * sin(angleRadCircle * i),hight*j * 1.0/(tesselation -1));
        }
        glEnd();
    }


}

void GLWidget::drawBackFrame(){
    int tesselation = 15;
    int tesselationCircle = tesselation * 2;
    double hight = 0.5;
    double radius = 0.4;

    double angleRad = M_PI * 1.0/(tesselation -1)*1.4;
    double angleRadCircle = M_PI * 1.0/(tesselationCircle -1)*1.4;
    double sinAngle = sin(angleRad);
    double cosAngle = cos(angleRad);
    glBegin(GL_LINES);
    for(int j = 0; j < tesselation ;j++){
        double newRadius = radius;// * (2 - pow( 1 - j * 2.0/(tesselation-1),2));
        double newHight = hight * (2 - pow( 1 - j * 2.0/(tesselation-1),2));
        glVertex3d(0,0,0);
        glVertex3d(newRadius * cos(angleRad * j),newRadius * sin(angleRad * j),newHight);
    }
    glEnd();

    for(int j = 0; j < tesselation ;j++){
        glBegin(GL_LINE_STRIP);

        for(int i = 0; i<tesselationCircle;i++){
            double newRadius = radius;// * (2 - pow( 1 - i * 2.0/(tesselationCircle-1),2));
            double newHight = hight * (2 - pow( 1 - i * 2.0/(tesselationCircle-1),2));
            glVertex3d(newRadius *j * 1.0/(tesselation -1) * cos(angleRadCircle * i),newRadius *j * 1.0/(tesselation -1) * sin(angleRadCircle * i),newHight*j * 1.0/(tesselation -1));
        }
        glEnd();
    }


}

void GLWidget::drawUpPillow(){
    double angle = 360.0/countArc;
    double angleRad = angle/360*2*M_PI;
    for(int i = 0; i< countArc;i++){

    glBegin(GL_QUADS);//GL_TRIANGLE_STRIP GL_POINTS GL_TRIANGLE_STRIP GL_TRIANGLE_FAN
        glVertex3d(arc[0][0] * cos(angleRad*i),arc[0][0] * sin(angleRad*i),arc[0][2]);
        glVertex3d(arc[0][0] * cos(angleRad*(i + 1)),arc[0][0] * sin(angleRad*(i + 1)),arc[0][2]);
        for(int j = 1; j < 50 ;j++){

            glNormal3d(arc[j][0] * cos(angleRad*i),arc[j][0] * sin(angleRad*i),arc[j][2]);
            glVertex3d(arc[j][0] * cos(angleRad*i),arc[j][0] * sin(angleRad*i),arc[j][2]);


            glNormal3d(arc[j][0] * cos(angleRad*(i + 1)),arc[j][0] * sin(angleRad*(i + 1)),arc[j][2]);
            glVertex3d(arc[j][0] * cos(angleRad*(i + 1)),arc[j][0] * sin(angleRad*(i + 1)),arc[j][2]);
            glVertex3d(arc[j][0] * cos(angleRad*(i + 1)),arc[j][0] * sin(angleRad*(i + 1)),arc[j][2]);


            glNormal3d(arc[j][0] * cos(angleRad*i),arc[j][0] * sin(angleRad*i),arc[j][2]);
            glVertex3d(arc[j][0] * cos(angleRad*i),arc[j][0] * sin(angleRad*i),arc[j][2]);
        }
    glEnd();
    }
}

void GLWidget::drawPillow(){
    int tesselation = 33;
    double radius = 0.3;
    double hight = 0.05;
    double angleRad1 = M_PI * 1.0/(tesselation -1) * 2;
    //double angleOfRotation = 360.0/countArc; //Расчет угла разбиения
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i< countArc;i++){


        for(int i = 0; i<tesselation;i++){
            glNormal3d(radius * cos(angleRad1 * i),radius * sin(angleRad1 * i),0);
            glVertex3d(radius * cos(angleRad1 * i),radius * sin(angleRad1 * i),0);
            glVertex3d(radius  * cos(angleRad1 * i),radius  * sin(angleRad1 * i),hight);
        }

    }
    glEnd();
    /*glBegin(GL_LINE_STRIP);
    for(int i = 0; i< countArc;i++){


        for(int i = 0; i<tesselation;i++){
            glVertex3d(radius * cos(angleRad * i),radius * sin(angleRad * i),0);

        }
        for(int i = 0; i<tesselation;i++){

            glVertex3d(radius  * cos(angleRad * i),radius  * sin(angleRad * i),hight);
        }

    }
    glEnd();*/
    double angle = 360.0/countArc;
    double angleRad = angle/360*2*M_PI;
    for(int i = 0; i< countArc;i++){

    glBegin(GL_QUADS);//GL_TRIANGLE_STRIP GL_POINTS GL_TRIANGLE_STRIP GL_TRIANGLE_FAN
        glVertex3d(arc[0][0] * cos(angleRad*i)* 1.5,arc[0][0] * sin(angleRad*i)* 1.5,arc[0][2]   * 0.4 + 0.05);
        glVertex3d(arc[0][0] * cos(angleRad*(i + 1))* 1.5,arc[0][0] * sin(angleRad*(i + 1))* 1.5,arc[0][2]   * 0.4 + 0.05);
        for(int j = 1; j < 50 ;j++){

            glNormal3d(arc[j][0] * cos(angleRad*i)* 1.5,arc[j][0] * sin(angleRad*i)* 1.5,arc[j][2]   * 0.4 + 0.05);
            glVertex3d(arc[j][0] * cos(angleRad*i)* 1.5,arc[j][0] * sin(angleRad*i)* 1.5,arc[j][2]   * 0.4 + 0.05);


            glNormal3d(arc[j][0] * cos(angleRad*(i + 1))* 1.5,arc[j][0] * sin(angleRad*(i + 1))* 1.5,arc[j][2]   * 0.4 + 0.05);
            glVertex3d(arc[j][0] * cos(angleRad*(i + 1))* 1.5,arc[j][0] * sin(angleRad*(i + 1))* 1.5,arc[j][2]   * 0.4 + 0.05);
            glVertex3d(arc[j][0] * cos(angleRad*(i + 1))* 1.5,arc[j][0] * sin(angleRad*(i + 1))* 1.5,arc[j][2]   * 0.4 + 0.05);


            glNormal3d(arc[j][0] * cos(angleRad*i)* 1.5,arc[j][0] * sin(angleRad*i)* 1.5,arc[j][2]* 0.4 + 0.05);
            glVertex3d(arc[j][0] * cos(angleRad*i)* 1.5,arc[j][0] * sin(angleRad*i)* 1.5,arc[j][2]* 0.4 + 0.05);
        }
    glEnd();
    }
}

void GLWidget::drawPinch(){
    int pinchTess = 12;
    double hight = 0.03;
    double length = 0.4;
    double step = 1.0/(pinchTess -1);
    for(int i = 0; i < pinchTess ;i++){
        pinch[i][0] = 0;
        pinch[i][1] = cos(M_PI * i * step) * hight * 0.5;
        pinch[i][2] = sin(M_PI * i * step) * hight;
    }
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < pinchTess ;i++){
         glVertex3d(pinch[i][0],pinch[i][1],pinch[i][2]);
         glVertex3d(pinch[i][0] + length,pinch[i][1] * 0.5,pinch[i][2] * 0.5 - length*0.1);
    }
    glVertex3d(pinch[0][0],pinch[0][1],pinch[0][2]);
    glVertex3d(pinch[0][0] + length,pinch[0][1] * 0.5,pinch[0][2] * 0.5  - length*0.1);
    glEnd();
}

void GLWidget::paintGL(){
    calculateArc();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    //Управляющие повороты и смещения

    glTranslatef(translateX,translateY,translateZ);
    glRotatef(-rotateX,1,0,0);
    glRotatef(-rotateZ,0,0,1);
    time++;
    if (time > 360) time = 0;
    float lpos[] = {cos(time/180.0*M_PI),0,sin(time/180.0*M_PI),1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    //Подставка
    glBegin(GL_QUADS);
        glNormal3d(0,0,1);
        glColor4d(0.4,0.4,0.4,1.0);
        glVertex3d( 0.9, 0.9,-0.04);
        glVertex3d( 0.9,-0.9,-0.04);
        glVertex3d(-0.9,-0.9,-0.04);
        glVertex3d(-0.9, 0.9,-0.04);
    glEnd();
    //Система координат
    glBegin(GL_LINES);
        glColor4d(0.0,0.0,0.9,1.0); //y blue
        glVertex3d(0.6,0,0);
        glVertex3d(0.6,0.2,0);
        glColor4d(0.3,0.0,0.7,1.0); //z pink
        glVertex3d(0.6,0,0);
        glVertex3d(0.6,0,0.2);
        glColor4d(0.9,0.0,0.0,1.0); //x red
        glVertex3d(0.6,0,0);
        glVertex3d(0.8,0,0.0);
    glEnd();
    //Каркас спереди
    glColor4f(0.2,0.2,0.2,1);
    glPushMatrix();
    glRotatef(36,0,0,1);

    drawFrontFrame();

    glPopMatrix();

    //Каркас сзади
    glColor4f(0.2,0.2,0.2,1);
    glPushMatrix();
    glRotatef(180*0.6 + 36,0,0,1);

    drawBackFrame();

    glPopMatrix();

    //Ножки
    glPushMatrix();
    glRotatef(0,0,0,1);
    drawPinch();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,0,1);
    drawPinch();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,0,1);
    drawPinch();
    glPopMatrix();

    glPushMatrix();
    glRotatef(270,0,0,1);
    drawPinch();
    glPopMatrix();

    //Подушка


    glColor4f(0.7,0.1,0.1,1);
    glPushMatrix();
    glTranslatef(0.0,0.1,0.49);

    drawPillow();

    glPopMatrix();
    //Верхняя подушка
    glColor4f(0.7,0.1,0.1,1);
    glPushMatrix();
    glTranslatef(0.0,-0.25,0.80);
    glRotatef(-70,1,0,0);
    glRotatef(0,0,1,0);

    drawUpPillow();

    glPopMatrix();

    glPopMatrix();

}

void GLWidget::resizeGL(int w,int h){

}

void GLWidget::initShaders() {
    const GLubyte *extensions;
    extensions = glGetString(GL_EXTENSIONS);
    int i = 0;
    QString extensionsString;
    while (extensions[i] != 0) {
        extensionsString += extensions[i];
        i++;
    }
    if (!extensionsString.contains("GL_ARB_vertex_shader") ||
            !extensionsString.contains("GL_ARB_fragment_shader") ||
            !extensionsString.contains("GL_ARB_shader_objects") ||
            !extensionsString.contains("GL_ARB_shading_language_100"))
    {
        exit(0);
    }

    //compile shaders
    m_program = new QOpenGLShaderProgram( this );
    m_program->addShaderFromSourceFile( QOpenGLShader::Vertex, ":/vshader.glsl" );
    m_program->addShaderFromSourceFile( QOpenGLShader::Fragment, ":/fshader.glsl" );
    if ( !m_program->link() )
    {
        qWarning( "Error: unable to link a shader program" );
        return;
    }
}

void GLWidget::setShader(bool isOn){
    isShaderOn = isOn;
    this->updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    curMousePosX = event->x();
    curMousePosY = event->y();
    if( event->button() == Qt::RightButton ) isRotate = true;
    if( event->button() == Qt::LeftButton ) isTranslate = true;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    if( isRotate ){
        rotateZ += (curMousePosX - event->x())/1.0;
        rotateX += (curMousePosY - event->y())/1.0;
    }
    if( isTranslate ){
        translateX += (-curMousePosX + event->x())/250.0;
        translateY += (curMousePosY - event->y())/250.0;
    }
    curMousePosX = event->x();
    curMousePosY = event->y();
    this->updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    isRotate = false;
    isTranslate = false;
}

void GLWidget::wheelEvent(QWheelEvent *event){
    translateZ += event->angleDelta().y()/1000.0;
    updateGL();
}

void GLWidget::setArcCount(int count){
    countArc = count;
    updateGL();
}

void GLWidget::setArcTess(int count){
    arcTess = count;
    updateGL();
}

void GLWidget::setMode(int index){
    switch (index) {
    case 0:
        mode = GL_POINTS;
        break;
    case 1:
        mode = GL_LINES;
        break;
    case 2:
        mode = GL_LINE_STRIP;
        break;
    case 3:
        mode = GL_LINE_LOOP;
        break;
    case 4:
        mode = GL_TRIANGLES;
        break;
    case 5:
        mode = GL_TRIANGLE_STRIP;
        break;
    case 6:
        mode = GL_TRIANGLE_FAN;
        break;
    case 7:
        mode = GL_QUADS;
        break;
    case 8:
        mode = GL_QUAD_STRIP;
        break;
    case 9:
        mode = GL_POLYGON;
        break;
    default:
        break;
    }
    updateGL();
}

void GLWidget::setLighting(bool isOn){
    if(isOn){
        glEnable(GL_LIGHTING);

    } else {
        glDisable(GL_LIGHTING);
    }
    updateGL();
}


