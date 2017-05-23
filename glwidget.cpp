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
    rotateY = 0;
    translateX = 0;
    translateY = 0;
    translateZ = 0.1;
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

    //****
    /*
    // Устанавливаем параметры источника света
        static float ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        static float diffuse[] = {1.0, 1.0, 1.0, 1.0};
        static float specular[] = { 1.0, 1.0, 1.0, 1.0 };
        static float position[] = {100.0, 60.0, 150.0, 0.0};

        // Определяем свойства материала лицевой поверхности
        static float front_mat_shininess[] = {10.0};
        static float front_mat_specular[] = {0.5, 0.4, 0.4, 0.1};
        static float front_mat_diffuse[] = {0.0, 0.9, 0.3, 0.1};

        // Определяем свойства материала обратной поверхности
        static float back_mat_shininess[] = {3.2};
        static float back_mat_specular[] = {0.07568, 0.61424, 0.07568, 1.0};
        static float back_mat_diffuse[] = {0.633, 0.727811, 0.633, 1.0};

        static float lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
        static float lmodel_twoside[] = {GL_TRUE};

        // Определяем цвет фона используемый по умолчанию
        glClearColor(1.0f, 0.96f, 0.866f, 1.0f);
        // Включаем различные тесты
        glDepthFunc(GL_LEQUAL);
        //glEnable(GL_DEPTH);
        glDepthFunc(GL_ALWAYS);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_SRC_COLOR);

        // Задаем источник света
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

        // Разрешаем освещение и включаем источник света
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Устанавливаем параметры материалов
        glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
        glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
        glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
        glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
        glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
*/
    //***



/*
    // Устанавливаем параметры источника света
        static float ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        static float diffuse[] = {1.0, 1.0, 1.0, 1.0};
        static float specular[] = { 1.0, 1.0, 1.0, 1.0 };
        static float position[] = {100.0, 60.0, 150.0, 0.0};

        // Определяем свойства материала лицевой поверхности
        static float front_mat_shininess[] = {10.0};
        static float front_mat_specular[] = {0.5, 0.4, 0.4, 0.1};
        static float front_mat_diffuse[] = {0.0, 0.9, 0.3, 0.1};

        // Определяем свойства материала обратной поверхности
        static float back_mat_shininess[] = {3.2};
        static float back_mat_specular[] = {0.07568, 0.61424, 0.07568, 1.0};
        static float back_mat_diffuse[] = {0.633, 0.727811, 0.633, 1.0};

        static float lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
        static float lmodel_twoside[] = {GL_TRUE};

    // Определяем цвет фона используемый по умолчанию
       // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Включаем различные тесты
        glDepthFunc(GL_LEQUAL);
        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_SRC_COLOR);

        // Задаем источник света
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

        // Разрешаем освещение и включаем источник света
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Устанавливаем параметры материалов
        glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
        glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
        glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
        glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
        glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);*/

        //glEnable(GL_LIGHTING);
        //glDisable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);
        GLfloat light2_diffuse[] = {1, 1, 1};
        GLfloat light2_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);

        /*GLfloat light3_diffuse[] = {1, 1, 1};
                    GLfloat light3_position[] = {0.0, 0.0, 1.0, 1.0};
                    GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
                    glEnable(GL_LIGHT3);
                    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
                    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
                    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
                    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);*/
        //glDepthFunc(GL_GEQUAL);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CCW);
        /*GLfloat light1_diffuse[] = {1, 1, 1};
        GLfloat light1_position[] = {1.0, 0.0,1.5, 1.0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


        GLfloat light2_diffuse[] = {1, 1, 1};
        GLfloat light2_position[] = {0.0, 1.0,1.5, 1.0};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
*/

        // Коды и координаты источников света
        GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        // Активизируем согласование цветов
        glEnable(GL_COLOR_MATERIAL);
        // Свойства материалов согласуются с кодами glColor
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        // С этого момента все материалы имеют максимальный коэффициент
        // зеркального отражения
        glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
        glMateriali(GL_FRONT, GL_SHININESS, 128);

        /*GLfloat light3_diffuse[] = {0.4, 0.7, 0.2};
                    GLfloat light3_position[] = {0.0, 0.0, 1.0, 1.0};
                    GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
                    glEnable(GL_LIGHT3);
                    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
                    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
                    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 10);
                    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);*/
        GLfloat light5_diffuse[] = {1.0, 1.0, 1.0};
                    //GLfloat light5_position[] = {0.5 * cos(0.0), 0.5 * sin(0.0), 0.5, 1.0};
                    GLfloat light5_position[] = {0,0,0, 1.0};
                    glEnable(GL_LIGHT5);
                    glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
                    glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
                    glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0);
                    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.4);
                    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.8);
                    /*GLfloat light6_diffuse[] = {1.0, 1.0, 1.0};
                    GLfloat light6_position[] = {0.5 * cos(2 * M_PI / 3), 0.5 * sin(2 * M_PI / 3), 0.5, 1.0};
                    glEnable(GL_LIGHT6);
                    glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
                    glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
                    glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0);
                    glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.4);
                    glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.8);
                    GLfloat light7_diffuse[] = {1.0, 1.0, 1.0};
                    GLfloat light7_position[] = {0.5 * cos(4 * M_PI / 3), 0.5 * sin(4 * M_PI / 3), 0.5, 1.0};
                    glEnable(GL_LIGHT7);
                    glLightfv(GL_LIGHT7, GL_DIFFUSE, light7_diffuse);
                    glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
                    glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.0);
                    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.4);
                    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.8);*/

                    //glMatrixMode(GL_PROJECTION);
                    //glLoadIdentity();
                    //gluPerspective(10.0, 1, 1.0, 100.0);

        //glDepthFunc(GL_ALWAYS);
        //glEnable(GL_DEPTH_TEST);
        //gluLookAt(0,0,-1,0,0,0,0,0,0);

        /*
        glViewport(0, 0, 500, 500);
        GLfloat fAspect = (GLfloat)500/(GLfloat)500;
        // Обновляет систему координат
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Генерирует перспективную проекцию
        gluPerspective(60.0f, fAspect, 1.0, 400.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();*/
        //glViewport(0, 0, 500, 500);
        //glMatrixMode(GL_PROJECTION);
        gluPerspective(60.0f, 1, 20.0, 0);
        gluLookAt(0,0,1,0,0,0,0,1,0);
        /*glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH);*/
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_SRC_COLOR);



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
    double angleOfRotation = 360.0/countArc; //Расчет угла разбиения
    for(int i = 0; i< countArc;i++){
        drawArc(angleOfRotation);
    }
}

void GLWidget::drawPillow(){
    int tesselation = 33;
    double radius = 0.3;
    double hight = 0.05;
    double angleRad = M_PI * 1.0/(tesselation -1) * 2;
    //double angleOfRotation = 360.0/countArc; //Расчет угла разбиения
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i< countArc;i++){


        for(int i = 0; i<tesselation;i++){
            glVertex3d(radius * cos(angleRad * i),radius * sin(angleRad * i),0);
            glVertex3d(radius  * cos(angleRad * i),radius  * sin(angleRad * i),hight);
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
    double angleOfRotation = 360.0/countArc; //Расчет угла разбиения
    for(int i = 0; i< countArc;i++){
        drawArc2(angleOfRotation);
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
    glClear(GL_COLOR_BUFFER_BIT);

    /*if ( !m_program->bind() )
        return;
    time++;
    if (time > 360) time = 0;
    if(!isShaderOn) m_program->release();
    m_program->setUniformValue(m_time, time);
    m_program->release();
    //glTranslated(0,0,-0.1);
    //GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

*/
    /*
    double angleRad = angleOfRotation/360*2*M_PI;
    glBegin(GL_POLYGON);
        for(int i = 0; i < countArc; i++){
            glVertex3d(arc[49][0]*cos(angleRad * i),arc[49][0]*sin(angleRad * i),arc[49][2]);
        }
    glEnd();*/

    /*glBegin(GL_POLYGON);
        glVertex3d(arc[49][0],0,0);
        glVertex3d(0,arc[49][0],0);
        glVertex3d(-arc[49][0],0,0);
        glVertex3d(0,-arc[49][0],0);
    glEnd();*/




    glPushMatrix();
    //Управляющие повороты и смещения
    glTranslatef(translateX,translateY,translateZ);
    glRotatef(-rotateX,1,0,0);
    glRotatef(-rotateY,0,0,1);
    //gluLookAt(0,1,0,rotateX,rotateY,0,0.0,0,1);
    //Подставка
    glBegin(GL_QUADS);
        glColor4d(0.4,0.4,0.4,1.0);
        glVertex3d( 0.9, 0.9,-0.04);
        glVertex3d( 0.9,-0.9,-0.04);
        glVertex3d(-0.9,-0.9,-0.04);
        glVertex3d(-0.9, 0.9,-0.04);
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
    glPopMatrix();
    //gluLookAt(0,0,0,0,0,0,0,1,0);
    /*glPointSize(5);
    glBegin(GL_POINTS);
        glColor4d(0.0,0.0,0.9,1.0); //y blue
        glVertex3d(0.5 * cos(0.0),0.5 * cos(0.0),0.5);
        glColor4d(0.3,0.0,0.7,1.0); //z pink
        glVertex3d(0.5 * cos(2 * M_PI / 3), 0.5 * sin(2 * M_PI / 3), 0.5);
        glColor4d(0.9,0.0,0.0,1.0); //x red
        glVertex3d(0.5 * cos(4 * M_PI / 3), 0.5 * sin(4 * M_PI / 3), 0.5);
        glVertex3d(0, 0, 0);
    glEnd();
    glPopMatrix();*/

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
    m_time = m_program->uniformLocation( "time" );
    glEnable(GL_PROGRAM_POINT_SIZE);
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
        rotateY += (curMousePosX - event->x())/1.0;
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
