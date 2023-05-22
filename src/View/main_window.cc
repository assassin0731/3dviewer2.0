#include "main_window.h"
#include "ui_main_window.h"
#include <time.h>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->line_type->addItem("Сплошная", QVariant(static_cast<int>(LineType::kUsual)));
  ui->line_type->addItem("Пунктирная", QVariant(static_cast<int>(LineType::kStriple)));
  setFocusPolicy(Qt::StrongFocus);
  LoadSettings();
  ChangePointColor();
  connect(ui->load_object, SIGNAL(clicked()), this, SLOT(LoadObject()));
  connect(ui->rotate_button, SIGNAL(clicked()), this, SLOT(Rotation()));
  connect(ui->scale_button, SIGNAL(clicked()), this, SLOT(Scaling()));
  connect(ui->move_button, SIGNAL(clicked()), this, SLOT(Moving()));
  connect(ui->parallel_proect, SIGNAL(clicked()), this, SLOT(SetParallel()));
  connect(ui->central_proect, SIGNAL(clicked()), this, SLOT(SetCentral()));
  connect(ui->red_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ChangeColor()));
  connect(ui->green_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ChangeColor()));
  connect(ui->blue_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ChangeColor()));
  connect(ui->bg_color, SIGNAL(clicked()), this, SLOT(BgColorButtonClick()));
  connect(ui->line_color, SIGNAL(clicked()), this, SLOT(LineColorButtonClick()));
  connect(ui->line_type, SIGNAL(currentIndexChanged(int)), this,
          SLOT(ChooseLineType()));
  connect(ui->width_slider, SIGNAL(valueChanged(int)), this, SLOT(ChangeLineWidth()));
  connect(ui->point_size_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ChangePointSize()));
  connect(ui->no_point, SIGNAL(clicked()), this, SLOT(SetNoPoint()));
  connect(ui->circle_point, SIGNAL(clicked()), this, SLOT(SetCirclePoint()));
  connect(ui->square_point, SIGNAL(clicked()), this, SLOT(SetSquarePoint()));
  connect(ui->point_color_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ChangePointColor()));
  connect(ui->point_bright, SIGNAL(valueChanged(int)), this,
          SLOT(ChangePointBright()));
  connect(ui->save_image, SIGNAL(clicked()), this, SLOT(SaveImage()));
  connect(ui->save_gif, SIGNAL(clicked()), this, SLOT(SaveGif()));
  connect(ui->x_rotate, SIGNAL(valueChanged(int)), this,
          SLOT(RotationSlider()));
  connect(ui->y_rotate, SIGNAL(valueChanged(int)), this,
          SLOT(RotationSlider()));
  connect(ui->z_rotate, SIGNAL(valueChanged(int)), this,
          SLOT(RotationSlider()));
  connect(ui->scale_slider, SIGNAL(valueChanged(int)), this,
          SLOT(ScalingSlider()));
  connect(ui->x_move_slider, SIGNAL(valueChanged(int)), this,
          SLOT(MovingSlider()));
  connect(ui->y_move_slider, SIGNAL(valueChanged(int)), this,
          SLOT(MovingSlider()));
  connect(ui->z_move_slider, SIGNAL(valueChanged(int)), this,
          SLOT(MovingSlider()));
}

MainWindow::~MainWindow() {
    SaveSettings();
    delete gif_;
    delete ui;
}

void MainWindow::set_controller(Controller *controller) {
    ui->openGLWidget->set_controller(controller);
    ui->openGLWidget->set_settings(&settings_);
    controller_ = controller;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Z) {
        controller_->UndoPreviousChange();
        ui->openGLWidget->update();
    }
}

void MainWindow::LoadSettings() {
  QString dir_path = QApplication::applicationDirPath();
  QSettings settings(dir_path + "/../../../settings.ini", QSettings::IniFormat);

  settings.beginGroup("Settings");
  settings_.red = settings.value("red", 1.0).toDouble();
  settings_.green = settings.value("green", 1.0).toDouble();
  settings_.blue = settings.value("blue", 1.0).toDouble();

  ui->red_slider->setValue(settings.value("red_bg", 0).toDouble() * 255);
  ui->green_slider->setValue(settings.value("green_bg", 0).toDouble() * 255);
  ui->blue_slider->setValue(settings.value("blue_bg", 0).toDouble() * 255);

  settings_.red_bg = settings.value("red_bg", 0).toDouble();
  settings_.green_bg = settings.value("green_bg", 0).toDouble();
  settings_.blue_bg = settings.value("blue_bg", 0).toDouble();

  settings_.line_width = settings.value("line_width", 1).toInt();
  ui->line_type->setCurrentIndex(settings.value("stripple_line", 0).toInt());
  ui->width_slider->setValue(settings.value("line_width", 1).toInt());
  ui->point_size_slider->setValue(settings.value("size_point", 0).toInt());
  settings_.point_size = settings.value("size_point", 0).toInt();

  ui->point_color_slider->setValue(settings.value("point_color", 255).toInt());
  ui->point_bright->setValue(settings.value("point_bright", 0).toInt());
  if (settings.value("proect_type", 1).toInt() == static_cast<int>(ProectionType::kParallel)) {
    ui->parallel_proect->setChecked(true);
  } else {
    ui->central_proect->setChecked(true);
  }
  if (settings.value("point", 1).toInt() == static_cast<int>(PointType::kNoPoint)) {
    ui->no_point->setChecked(true);
  } else if (settings.value("point", 1).toInt() == static_cast<int>(PointType::kCircle)) {
    ui->circle_point->setChecked(true);
  } else if (settings.value("point", 1).toInt() == static_cast<int>(PointType::kSquare)) {
    ui->square_point->setChecked(true);
  }
  settings.endGroup();
}

void MainWindow::SetEnabled() {
    QRadioButton *buttons[6] = {ui->line_color, ui->no_point,  ui->circle_point, ui->square_point, ui->square_point,
                               ui->bg_color};
    QSlider *sliders[11] = {ui->point_size_slider, ui->width_slider, ui->point_color_slider,  ui->point_bright,
                           ui->scale_slider, ui->x_move_slider, ui->y_move_slider, ui->z_move_slider,
                           ui->x_rotate, ui->y_rotate, ui->z_rotate};
    QSpinBox *spin_box[4] = {ui->x_axis, ui->y_axis, ui->z_axis, ui->scale};
    QPushButton *push_button[5] = {ui->save_gif, ui->save_image, ui->scale_button,  ui->move_button, ui->rotate_button};
    QDoubleSpinBox *double_spin_box[3] = {ui->x_move, ui->y_move, ui->z_move};
    for (auto it : buttons) {
        it->setDisabled(false);
    }
    for (auto it : sliders) {
        it->setDisabled(false);
    }
    for (auto it : spin_box) {
        it->setDisabled(false);
    }
    for (auto it : push_button) {
        it->setDisabled(false);
    }
    for (auto it : double_spin_box) {
        it->setDisabled(false);
    }
  ui->line_type->setDisabled(false);
}

void MainWindow::RefreshVariables() {
  delete gif_;
  gif_ = new QGifImage;
  old_scale_ = 0;
  int *old_var[7] = {&gif_counter_, &old_x_, &old_y_, &old_z_, &old_x_move_, &old_y_move_, &old_z_move_};
  for (auto it : old_var) {
      *it = 0;
  }
  QSpinBox *spin_box[4] = {ui->x_axis, ui->y_axis, ui->z_axis, ui->scale};
  QSlider *slider[7] = {ui->x_rotate, ui->y_rotate, ui->z_rotate, ui->scale_slider,
                       ui->x_move_slider, ui->y_move_slider, ui->z_move_slider};
  QDoubleSpinBox *double_spin_box[3] = {ui->x_move, ui->y_move, ui->z_move};
  for (auto it : spin_box) {
      it->setValue(0);
  }
  for (auto it : slider) {
      it->setValue(0);
  }
  for (auto it : double_spin_box) {
      it->setValue(0);
  }
  ui->gif_record->clear();
  //settings_.x_pos = 0;
  //settings_.y_pos = 0;
  //settings_.angle_x = 0;
  //settings_.angle_y = 0;
}

void MainWindow::LoadObject() {
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"),
      QApplication::applicationDirPath() + "../../../../../Models",
      tr("Objects (*.obj)"));
  QFile f(file_name);
  QFileInfo file_info(f.fileName());
  QString name_of_file(file_info.fileName());
  QByteArray path = file_name.toLocal8Bit();
  if (path.size() != 0) {
    //ui->openGLWidget->tStart = clock();
    RefreshVariables();
    controller_->ParseObjFile(path.data());
    ui->lineEdit->setText(file_name);
    this->setWindowTitle(name_of_file);
    SetProectionType();
    SetLineType();
    SetPointType();
    SetSliderValues();
    PrintNumberOfVertexIndex();
    ui->openGLWidget->update();
    SetEnabled();
    //settings_.start = false;
    //ui->openGLWidget->tEnd = clock();
    //ui->vertex_edge->setText(QString::number((double)(ui->openGLWidget->tEnd - ui->openGLWidget->tStart)/CLOCKS_PER_SEC));

  }
}

void MainWindow::SetProectionType() {
    if (ui->parallel_proect->isChecked()) {
      settings_.proection_type = ProectionType::kParallel;
    } else {
      settings_.proection_type = ProectionType::kCentral;
    }
}

void MainWindow::SetLineType() {
    int line = ui->line_type->currentData().toInt();
    if (line == static_cast<int>(LineType::kStriple)) {
      settings_.striple_line = LineType::kStriple;
    } else {
      settings_.striple_line = LineType::kUsual;
    }
}

void MainWindow::SetPointType() {
    if (ui->circle_point->isChecked()) {
      settings_.point_type = PointType::kCircle;
    } else if (ui->square_point->isChecked()) {
      settings_.point_type = PointType::kSquare;
    } else {
      settings_.point_type = PointType::kNoPoint;
    }
}

void MainWindow::PrintNumberOfVertexIndex() {
    QString str = "Vertexes: ";
    str += QString::number(controller_->get_elements()->vertex.size() / 3);
    str += "\n";
    str += "Edges: ";
    str += QString::number(controller_->get_elements()->index.size() / 2);
    ui->vertex_edge->setText(str);
}


void MainWindow::SetSliderValues() {
  ui->x_move_slider->setMaximum(controller_->get_elements()->max_value * 1000);
  ui->x_move_slider->setMinimum(-controller_->get_elements()->max_value * 1000);
  ui->y_move_slider->setMaximum(controller_->get_elements()->max_value * 1000);
  ui->y_move_slider->setMinimum(-controller_->get_elements()->max_value * 1000);
  ui->z_move_slider->setMaximum(controller_->get_elements()->max_value * 1000);
  ui->z_move_slider->setMinimum(-controller_->get_elements()->max_value * 1000);
  ui->x_move->setSingleStep(controller_->get_elements()->max_value / 10);
  ui->y_move->setSingleStep(controller_->get_elements()->max_value / 10);
  ui->z_move->setSingleStep(controller_->get_elements()->max_value / 10);
}

void MainWindow::Rotation() {
  double x = ui->x_axis->value() / 57.3;
  double y = ui->y_axis->value() / 57.3;
  double z = ui->z_axis->value() / 57.3;
 // ui->openGLWidget->tStart = clock();
  controller_->RotateCoordinates(x, y, z);

  ui->openGLWidget->update();
  //ui->vertex_edge->setText(QString::number((double)(ui->openGLWidget->tEnd - ui->openGLWidget->tStart)/CLOCKS_PER_SEC));
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }
}

void MainWindow::RotationSlider() {
  double x = (ui->x_rotate->value() - old_x_) / 57.3;
  double y = (ui->y_rotate->value() - old_y_) / 57.3;
  double z = (ui->z_rotate->value() - old_z_) / 57.3;
  controller_->RotateCoordinates(x, y, z);
  ui->openGLWidget->update();
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }

  old_x_ = ui->x_rotate->value();
  old_y_ = ui->y_rotate->value();
  old_z_ = ui->z_rotate->value();
}

void MainWindow::ScalingSlider() {
  double scaler = ui->scale_slider->value() / 100. + 1;
  double scaler_old = (old_scale_ + old_scaler_) / 100. + 1;
  controller_->ScaleCoordinates(scaler / scaler_old);
  ui->openGLWidget->update();
  old_scale_ = ui->scale_slider->value();
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }
}

void MainWindow::Scaling() {
  double scaler = ui->scale->value() / 100. + 1;
  controller_->ScaleCoordinates(scaler);
  ui->openGLWidget->update();
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }
  //ui->vertex_edge->setText(QString::number(controller_->get_elements()->vertex[0]));
  old_scaler_ +=  ui->scale->value() / 100.;
}

void MainWindow::Moving() {
  double x = ui->x_move->value();
  double y = ui->y_move->value();
  double z = ui->z_move->value();
  controller_->MoveCoordinates(x, y, z);
  ui->openGLWidget->update();
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }
}

void MainWindow::MovingSlider() {
  double x = (static_cast<double>(ui->x_move_slider->value()) - old_x_move_) / 1000.;
  double y = (static_cast<double>(ui->y_move_slider->value()) - old_y_move_) / 1000.;
  double z = (static_cast<double>(ui->z_move_slider->value()) - old_z_move_) / 1000.;
  controller_->MoveCoordinates(x, y, z);
  ui->openGLWidget->update();
  if (!ui->save_gif->isEnabled()) {
    RecordGif();
  }
  old_x_move_ = ui->x_move_slider->value();
  old_y_move_ = ui->y_move_slider->value();
  old_z_move_ = ui->z_move_slider->value();
}

void MainWindow::SetParallel() {
  settings_.proection_type = ProectionType::kParallel;
  //settings_.start = false;
  ui->openGLWidget->update();
}

void MainWindow::SetCentral() {
  settings_.proection_type = ProectionType::kCentral;
  //settings_.start = false;
  ui->openGLWidget->update();
}

void MainWindow::ChangeColor() {
  if (ui->bg_color->isChecked()) {
    settings_.red_bg = static_cast<float>(ui->red_slider->value()) / 255.;
    settings_.green_bg = static_cast<float>(ui->green_slider->value()) / 255.;
    settings_.blue_bg = static_cast<float>(ui->blue_slider->value()) / 255.;
  } else {
    settings_.red = static_cast<float>(ui->red_slider->value()) / 255.;
    settings_.green = static_cast<float>(ui->green_slider->value()) / 255.;
    settings_.blue = static_cast<float>(ui->blue_slider->value()) / 255.;
  }
  ui->openGLWidget->update();
}

void MainWindow::BgColorButtonClick() {
  int red = settings_.red_bg * 255;
  int green = settings_.green_bg * 255;
  int blue = settings_.blue_bg * 255;
  ui->red_slider->setValue(red);
  ui->green_slider->setValue(green);
  ui->blue_slider->setValue(blue);
}

void MainWindow::LineColorButtonClick() {
  int red = settings_.red * 255;
  int green = settings_.green * 255;
  int blue = settings_.blue * 255;
  ui->red_slider->setValue(red);
  ui->green_slider->setValue(green);
  ui->blue_slider->setValue(blue);
}

void MainWindow::ChooseLineType() {
  int line = ui->line_type->currentData().toInt();
  if (line == static_cast<int>(LineType::kStriple)) {
    settings_.striple_line = LineType::kStriple;
  } else {
    settings_.striple_line = LineType::kUsual;
  }
  ui->openGLWidget->update();
}

void MainWindow::ChangeLineWidth() {
  settings_.line_width = ui->width_slider->value();
  ui->openGLWidget->update();
}

void MainWindow::SaveSettings() {
  QString dir_path = QApplication::applicationDirPath();
  QSettings settings(dir_path + "/../../../settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("red", settings_.red);
  settings.setValue("green", settings_.green);
  settings.setValue("blue", settings_.blue);
  settings.setValue("red_bg", settings_.red_bg);
  settings.setValue("green_bg", settings_.green_bg);
  settings.setValue("blue_bg", settings_.blue_bg);
  settings.setValue("line_width", settings_.line_width);
  settings.setValue("stripple_line", ui->line_type->currentIndex());
  settings.setValue("size_point", ui->point_size_slider->value());
  settings.setValue("point_color", ui->point_color_slider->value());
  settings.setValue("point_bright", ui->point_bright->value());
  if (ui->parallel_proect->isChecked()) {
    settings.setValue("proect_type", static_cast<int>(ProectionType::kParallel));
  } else {
    settings.setValue("proect_type", static_cast<int>(ProectionType::kCentral));
  }
  if (ui->no_point->isChecked()) {
    settings.setValue("point", static_cast<int>(PointType::kNoPoint));
  } else if (ui->circle_point->isChecked()) {
    settings.setValue("point", static_cast<int>(PointType::kCircle));
  } else {
    settings.setValue("point", static_cast<int>(PointType::kSquare));
  }
  settings.endGroup();
}

void MainWindow::SetNoPoint() {
  settings_.point_type = PointType::kNoPoint;
  ui->openGLWidget->update();
}

void MainWindow::SetCirclePoint() {
  settings_.point_type = PointType::kCircle;
  ui->openGLWidget->update();
}

void MainWindow::SetSquarePoint() {
  settings_.point_type = PointType::kSquare;
  ui->openGLWidget->update();
}

void MainWindow::ChangePointSize() {
  settings_.point_size = ui->point_size_slider->value();
  ui->openGLWidget->update();
}

void MainWindow::ChangePointColor() {
  float new_value = 0.0;
  if (ui->point_color_slider->value() >= 255 &&
      ui->point_color_slider->value() < 510) {
    settings_.red_point = 1.0;
    new_value = static_cast<float>(ui->point_color_slider->value()) - 255;
    settings_.green_point = new_value / 255;
    settings_.blue_point = 0.0;
  } else if (ui->point_color_slider->value() >= 510 &&
             ui->point_color_slider->value() < 765) {
    new_value = static_cast<float>(ui->point_color_slider->value()) - 510.;
    settings_.red_point = 1.0 - new_value / 255.;
    settings_.green_point = 1.0;
    settings_.blue_point = 0;
  } else if (ui->point_color_slider->value() >= 765 &&
             ui->point_color_slider->value() < 1020) {
    new_value = static_cast<float>(ui->point_color_slider->value()) - 765.;
    settings_.red_point = 0.0;
    settings_.green_point = 1.0;
    settings_.blue_point = new_value / 255.;
  } else if (ui->point_color_slider->value() >= 1020 &&
             ui->point_color_slider->value() < 1275) {
    new_value = static_cast<float>(ui->point_color_slider->value()) - 1020.;
    settings_.red_point = 0;
    settings_.green_point = 1.0 - new_value / 255.;
    settings_.blue_point = 1.0;
  } else if (ui->point_color_slider->value() >= 1275 &&
             ui->point_color_slider->value() < 1530) {
    new_value = static_cast<float>(ui->point_color_slider->value()) - 1275.;
    settings_.red_point = new_value / 255.;
    settings_.green_point = 0.0;
    settings_.blue_point = 1.0;
  } else if (ui->point_color_slider->value() >= 1530 &&
             ui->point_color_slider->value() < 1785) {
    new_value = static_cast<float>(ui->point_color_slider->value()) - 1530.;
    settings_.red_point = 1.0;
    settings_.green_point = 0;
    settings_.blue_point = 1.0 - new_value / 255.;
  }
  settings_.red_point_remember = settings_.red_point;
  settings_.green_point_remember = settings_.green_point;
  settings_.blue_point_remember = settings_.blue_point;
  ChangePointBright();
  ui->openGLWidget->update();
}

void MainWindow::ChangePointBright() {
  if (ui->point_bright->value() >= 0) {
    settings_.red_point =
        settings_.red_point_remember +
        (1.0 - settings_.red_point_remember) *
            (1. - (1. - static_cast<float>(ui->point_bright->value()) / 100));
    settings_.green_point =
        settings_.green_point_remember +
        (1.0 - settings_.green_point_remember) *
            (1. - (1. - static_cast<float>(ui->point_bright->value()) / 100));
    settings_.blue_point =
        settings_.blue_point_remember +
        (1.0 - settings_.blue_point_remember) *
            (1. - (1. - static_cast<float>(ui->point_bright->value()) / 100));
  } else {
    settings_.red_point =
        settings_.red_point_remember -
        settings_.red_point_remember *
            (1. - (1. + static_cast<float>(ui->point_bright->value()) / 100));
    settings_.green_point =
        settings_.green_point_remember -
        settings_.green_point_remember *
            (1. - (1. + static_cast<float>(ui->point_bright->value()) / 100));
    settings_.blue_point =
        settings_.blue_point_remember -
        settings_.blue_point_remember *
            (1. - (1. + static_cast<float>(ui->point_bright->value()) / 100));
  }
  ui->openGLWidget->update();
}

void MainWindow::SaveImage() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...",
      QApplication::applicationDirPath() + "../../../../../Images",
      "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->openGLWidget->grabFramebuffer().save(file, NULL, 100);
}

void MainWindow::SaveGif() {
  ui->save_gif->setDisabled(true);
  QString str = "Frames to save: ";
  str += QString::number(50 - gif_counter_);
  ui->gif_record->setText(str);
}

void MainWindow::RecordGif() {
  gif_->setDefaultDelay(100);
  QImage image =ui->openGLWidget->grabFramebuffer().scaled(640, 360);
  ++gif_counter_;
  QString str = "Frames to save: ";
  str += QString::number(50 - gif_counter_);
  ui->gif_record->setText(str);
  gif_->addFrame(image, QPoint(0, 0));
  if (gif_counter_ == 50) {
      QString file = QFileDialog::getSaveFileName(
          this, "Save as...",
          QApplication::applicationDirPath() + "../../../../../name",
          "GIF (*.gif)");
    gif_->save(file);
    ui->save_gif->setDisabled(false);
    gif_counter_ = 0;
    str = "Gif saved";
    ui->gif_record->setText(str);
    delete gif_;
    gif_ = nullptr;
  }
}
