#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    qtGray = QColor::fromRgbF(0.5,0.5,0.5);
    qtBlue = QColor::fromRgbF(0.0,0.5,1.0);

    quadratic = gluNewQuadric();                // Create A Pointer To The Quadric Object
    gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(320,240);
}

void GLWidget::setBallCoords(const double coords[])
{
    for (int i=0; i<3; i++)
        ballCoords[i] = coords[i];
}

void GLWidget::setBallDiameter(double diameter)
{
    ballDiameter = diameter;
}

void GLWidget::setDisplayFOV(double fov)
{
    displayFOV = fov;
}

void GLWidget::initializeGL()
{
    qglClearColor(qtGray);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    glTranslatef( ballCoords[0], ballCoords[1], -1*ballCoords[2]);

    gluSphere(quadratic, ballDiameter, 16, 8);
}

void GLWidget::resizeGL(int width, int height)
{
    double halffov = displayFOV*3.1416/360;
	int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-halffov, +halffov, -halffov, +halffov, 0.5, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}
