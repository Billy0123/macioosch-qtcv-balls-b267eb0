#include <QDir>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matqimage.h"
#include "cv_balls.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displaytimer.start(33);

    connect(&cameratimer,SIGNAL(timeout()),
            this,SLOT(getFrame()));
    connect(&displaytimer,SIGNAL(timeout()),
            this,SLOT(displayGraphics()));
    connect(ui->diameterDoubleSpinBox,SIGNAL(valueChanged(double)),
            ui->visGLWidget,SLOT(setBallDiameter(double)));
    connect(ui->fovDoubleSpinBox,SIGNAL(valueChanged(double)),
            ui->visGLWidget,SLOT(setDisplayFOV(double)));

    QScrollBar* scrollbars[] =
    {
        ui->hueScrollBar,
        ui->parHueScrollBar,
        ui->parSatScrollBar,
        ui->parValScrollBar,
        ui->parOpenScrollBar,
        ui->parCloseScrollBar
    };

    const int scrollbars_num = 6;

    for (int i=0; i<scrollbars_num; i++)
        connect(scrollbars[i], SIGNAL(valueChanged(int)), this, SLOT(showChangedValue(int)));

    ui->visGLWidget->setBallDiameter(ui->diameterDoubleSpinBox->value());
    ui->visGLWidget->setDisplayFOV(ui->fovDoubleSpinBox->value());
    startRecording();
}

MainWindow::~MainWindow()
{
    stopRecording();
    delete ui;
}

bool MainWindow::startRecording()
{
    //camera.open(0);
    cameratimer.start(33);
    cameralock=false;
    return true;
}

bool MainWindow::stopRecording()
{
    cameratimer.stop();
    camera.release();
    return true;
}

bool MainWindow::getFrame()
{
    if (    cameralock
        || !camera.isOpened()
        || !cameratimer.isActive()
       )
        return false;

    cv::Mat frame;

    cameralock = true;

    camera >> frame;

    if (frame.empty())
        return false;

    input_width = frame.size[0];

    if (ui->mirrorCheckBox->isChecked())
        cv::flip(frame,frame,1);

    ui->picWidget->matrix = drawAsCirc(frame
        , ui->hueScrollBar->value()
        , ui->parHueScrollBar->value()
        , ui->parSatScrollBar->value()
        , ui->parValScrollBar->value()
        , ui->parOpenScrollBar->value()
        , ui->parCloseScrollBar->value()
        , ball_pos_image
        );

    ui->picWidget->update();

    cameralock = false;

    return true;
}

bool MainWindow::displayGraphics()
{
    ballRealPos( ball_pos_image, ui->diameterDoubleSpinBox->value(), ui->fovDoubleSpinBox->value(),
                 input_width, ball_pos_real);

    // display ball's coordinates

    ui->outTextBrowser->clear();

    ui->outTextBrowser->append("Coordinates on image (in pixels):");
    ui->outTextBrowser->append(QString().sprintf("x: %d\n"
                                                 "y: %d\n"
                                                 "diameter: %d",
        ball_pos_image[0],ball_pos_image[1],ball_pos_image[2]));

    ui->outTextBrowser->append("\nReal coordinates (in cm):");
    ui->outTextBrowser->append(QString().sprintf("x: %f\n"
                                                 "y: %f\n"
                                                 "z: %f",
        ball_pos_real[0],ball_pos_real[1],ball_pos_real[2]));

    // send parameters to the 3d visualisation

    ui->visGLWidget->setBallCoords(ball_pos_real);
    ui->visGLWidget->updateGL();

    return true;
}

void MainWindow::showChangedValue(int value)
{
    ui->statusBar->showMessage(QString().sprintf("Value: %d.", value), 3000);
}

void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.*)"));
        camera.open(fileName.toStdString());
    } //else camera.open(0);
}
