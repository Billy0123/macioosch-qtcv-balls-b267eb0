#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer cameratimer;
    QTimer displaytimer;

    cv::VideoCapture camera;

    int ball_pos_image[3];
    double ball_pos_real[3];
    int input_width;

public slots:

private slots:
    bool startRecording();
    bool stopRecording();
    bool getFrame();
    bool displayGraphics();
    void showChangedValue(int value);

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
    bool cameralock;
};

#endif // MAINWINDOW_H
