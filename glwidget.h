#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <GL/glut.h>

class GLWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GLWidget(QWidget *parent = 0);
		~GLWidget();

		QSize minimumSizeHint() const;
        QSize sizeHint() const;

        void setBallCoords(const double coords[]);

    public slots:
        void setBallDiameter(double diameter);
        void setDisplayFOV(double fov);

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);

	private:
        QColor qtGray;
        QColor qtBlue;
        double ballCoords[3];
        double ballDiameter;
        double displayFOV;
        GLUquadricObj *quadratic;
};

#endif
