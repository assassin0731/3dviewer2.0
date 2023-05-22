#include "object_window.h"



ObjectWindow::ObjectWindow(QWidget *parent) : QOpenGLWidget(parent) {}

ObjectWindow::~ObjectWindow() {}

void ObjectWindow::initializeGL() {
  //glClearColor(settings_->red_bg, settings_->green_bg, settings_->blue_bg, 0);
  glEnable(GL_DEPTH_TEST);
}

void ObjectWindow::ResizeWindow() {
  if (settings_->proection_type == ProectionType::kParallel) {
    glOrtho(-controller_->get_elements()->max_value, controller_->get_elements()->max_value,
            -controller_->get_elements()->max_value * 9 / 16, controller_->get_elements()->max_value * 9 / 16,
            -controller_->get_elements()->max_value, controller_->get_elements()->max_value);
  }
  if (settings_->proection_type == ProectionType::kCentral) {
    float fov = 60.0 * M_PI / 180; // 60 угол в градусах
    float heapHeight = controller_->get_elements()->max_value / 2 / (2 * tan(fov / 2));
    glFrustum(-controller_->get_elements()->max_value * 16 / 9 / 4, controller_->get_elements()->max_value * 16 / 9 / 4,
              -controller_->get_elements()->max_value / 4, controller_->get_elements()->max_value  / 4, heapHeight,
              controller_->get_elements()->max_value * 5);
    glTranslated(0, 0, -heapHeight * 4);
  }
  //settings_->start = true;
  //update();
}

void ObjectWindow::paintGL() {
    //tStart = clock();
    ApplySettings();
    //glRotatef(angle_x, 1, 0, 0);
    //glRotatef(angle_y, 0, 1, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    DrawObject();
    DrawPoints();
    glDisableClientState(GL_VERTEX_ARRAY);
    //tEnd = clock();
}

void ObjectWindow::ApplySettings()  {
   // if (!settings_->start) {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      ResizeWindow();
    //}
    glClearColor(settings_->red_bg, settings_->green_bg, settings_->blue_bg, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glColor3d(settings_->red, settings_->green, settings_->blue);
    if (settings_->striple_line == LineType::kStriple) {
      glLineStipple(controller_->get_elements()->max_value * 20, 0x3333);
      glEnable(GL_LINE_STIPPLE);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(settings_->line_width);
}

void ObjectWindow::DrawObject()  {
   // tStart = clock();
    /*
    glBegin(GL_LINES);
    for (int j = 0; j < controller_->get_elements()->index.size(); ++j) {
      glVertex3f(static_cast<GLfloat>(controller_->get_elements()->vertex[controller_->get_elements()->index[j]*3]),
                 static_cast<GLfloat>(controller_->get_elements()->vertex[controller_->get_elements()->index[j]*3+1]),
                 static_cast<GLfloat>(controller_->get_elements()->vertex[controller_->get_elements()->index[j]*3+2]));
    }
    glEnd();
    */
    //tEnd = clock();
    glVertexPointer(3, GL_DOUBLE, 0, &controller_->get_elements()->vertex[0]);
    glDrawElements(GL_LINES, controller_->get_elements()->index.size(), GL_UNSIGNED_INT, &controller_->get_elements()->index[0]);
   // tEnd = clock();
}

void ObjectWindow::DrawPoints()  {
    if (settings_->point_type != PointType::kNoPoint) {
      int type;
      if (settings_->point_type == PointType::kCircle) {
        type = GL_POINT_SMOOTH;
      } else {
        type = GL_POINT;
      }
      glEnable(type);
      glColor3d(settings_->red_point, settings_->green_point, settings_->blue_point);
      glPointSize(settings_->point_size);
      glDrawArrays(GL_POINTS, 0, controller_->get_elements()->vertex.size() / 3);
      glDisable(type);
    }
}
/*
void ObjectWindow::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    x_pos = e->x();
    y_pos = e->y();
  }
}

void ObjectWindow::mouseMoveEvent(QMouseEvent *e) {
  angle_x += 180 * (GLfloat(e->y()) - y_pos) / width();
  angle_y += 180 * (GLfloat(e->x()) - x_pos) / height();
  x_pos = e->x();
  y_pos = e->y();
  update();
}

void ObjectWindow::mouseReleaseEvent(QMouseEvent *e) {
  // QMessageBox::information(0,"fds",QString::number(angle_x));
  // RotationC(&elements, angle_x/57.3, angle_y/57.3, 0);
}
*/
void ObjectWindow::set_controller(Controller *controller) {
    controller_ = controller;
}

void ObjectWindow::set_settings(ModelSettings *settings) {
    settings_ = settings;
}
