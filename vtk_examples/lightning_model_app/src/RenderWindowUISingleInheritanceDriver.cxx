#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "RenderWindowUISingleInheritance.h"
 
int main( int argc, char** argv )
{

  // QT Stuff
  QApplication app( argc, argv );

  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
 
  RenderWindowUISingleInheritance renderWindowUISingleInheritance;
  renderWindowUISingleInheritance.show();
 
  return app.exec();
}
