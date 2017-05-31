#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(16);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT( updateScene() ));
    //ui->checkBox->hide();
    ui->horizontalSlider->setMinimum(2);
    ui->horizontalSlider->setMaximum(128);
    ui->horizontalSlider->setValue(32);
    ui->horizontalSlider_2->setMinimum(2);
    ui->horizontalSlider_2->setMaximum(50);
    ui->horizontalSlider_2->setValue(10);

    ui->horizontalSlider->hide();
    ui->horizontalSlider_2->hide();
    ui->comboBox->hide();
    ui->comboBox->addItem("GL_POINTS");
    ui->comboBox->addItem("GL_LINES");
    ui->comboBox->addItem("GL_LINE_STRIP");
    ui->comboBox->addItem("GL_LINE_LOOP");
    ui->comboBox->addItem("GL_TRIANGLES");
    ui->comboBox->addItem("GL_TRIANGLE_STRIP");
    ui->comboBox->addItem("GL_TRIANGLE_FAN");
    ui->comboBox->addItem("GL_QUADS");
    ui->comboBox->addItem("GL_QUAD_STRIP");
    ui->comboBox->addItem("GL_POLYGON");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_activated(int index)
{
    ui->widget->setMode(index);
}

void MainWindow::on_comboBox_2_activated(int index)
{

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->widget->setArcCount(position);
}

void MainWindow::on_comboBox_3_activated(int index)
{

}

void MainWindow::on_comboBox_4_activated(int index)
{

}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ui->widget->setArcTess(position);
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{

}

void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{

}

void MainWindow::on_horizontalSlider_5_sliderMoved(int position)
{

}

void  MainWindow::updateScene(){
    ui->widget->updateGL();
}


void MainWindow::on_checkBox_clicked()
{
    ui->widget->setLighting(ui->checkBox->isChecked());
}
