#ifndef CPP3_3VIEWER_V2_0_VIEW_OBJECT_WINDOW_H_
#define CPP3_3VIEWER_V2_0_VIEW_OBJECT_WINDOW_H_

#define GL_SILENCE_DEPRECATION
#include "../Controller/controller.h"
#include "../Model/settings.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <gl.h>
#include <glu.h>
#include <time.h>

class ObjectWindow : public QOpenGLWidget {
public:
  ObjectWindow(QWidget *parent = nullptr);
  ~ObjectWindow();
  //void mousePressEvent(QMouseEvent *);
 // void mouseMoveEvent(QMouseEvent *);
  //void mouseReleaseEvent(QMouseEvent *);
  //GLfloat y_pos = 0, x_pos = 0;
  //GLfloat angle_x = 0, angle_y = 0;
  void set_controller(Controller *controller);
  void set_settings(ModelSettings *settings);
clock_t tStart;
clock_t tEnd;



private:
  Controller *controller_;
  ModelSettings *settings_;
  void initializeGL();
  void ResizeWindow();
  void paintGL();
  void ApplySettings();
  void DrawObject();
  void DrawPoints();
};

#endif // CPP3_3VIEWER_V2_0_VIEW_OBJECT_WINDOW_H_
