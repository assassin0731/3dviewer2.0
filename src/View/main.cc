#include "object_window.h"
#include "main_window.h"
#include "../Model/geometry.h"
#include "../Controller/controller.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  Facade facade;
  Controller controller(&facade);

  //w.SetModel(&model);
  w.set_controller(&controller);
  w.show();
  return a.exec();
}
