#ifndef CPP3_3VIEWER_V2_0_VIEW_MAIN_WINDOW_H_
#define CPP3_3VIEWER_V2_0_VIEW_MAIN_WINDOW_H_

#include "qgifimage.h"
#include "../Controller/controller.h"
#include "../Model/settings.h"
#include <QColor>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QPalette>
#include <QKeyEvent>
#include <QWidget>
#include <QtOpenGL>
#include <algorithm>
#include <gl.h>
#include <glu.h>
#include <iostream>
#include <iterator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void set_controller(Controller *controller);


private:
  Ui::MainWindow *ui;
  Controller *controller_;
  void keyPressEvent(QKeyEvent *event);
  void LoadSettings();
  void SetProectionType();
  void SetLineType();
  void SetPointType();
  void PrintNumberOfVertexIndex();
  void SetEnabled();
  void RefreshVariables();
  void SetSliderValues();
  int gif_counter_ = 0;
  QGifImage *gif_ = nullptr;
  void RecordGif();
  int old_x_ = 0;
  int old_y_ = 0;
  int old_z_ = 0;
  double old_scale_ = 0;
  double old_scaler_ = 0;
  int old_x_move_ = 0;
  int old_y_move_ = 0;
  int old_z_move_ = 0;
  ModelSettings settings_;

public slots:
  void LoadObject();
  void Rotation();
  void Scaling();
  void Moving();
  void SetParallel();
  void SetCentral();
  void ChangeColor();
  void BgColorButtonClick();
  void LineColorButtonClick();
  void ChooseLineType();
  void ChangeLineWidth();
  void SaveSettings();
  void SetNoPoint();
  void SetCirclePoint();
  void SetSquarePoint();
  void ChangePointSize();
  void ChangePointColor();
  void ChangePointBright();
  void SaveImage();
  void SaveGif();
  void RotationSlider();
  void ScalingSlider();
  void MovingSlider();
};
#endif // CPP3_3VIEWER_V2_0_VIEW_MAIN_WINDOW_H_
