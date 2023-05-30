#include "RenderWindowUISingleInheritance.h"
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkVersion.h>
#include <vtkLight.h>

#include <QFile.h>
#include <qDebug.h>

#include <array>
#include <string>
#include <algorithm>
#include <random>


#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance(
    QWidget* parent)
  : QMainWindow(parent), ui(new Ui::RenderWindowUISingleInheritance)
{
  this->ui->setupUi(this);

  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  this->ui->qvtkWidget->setRenderWindow(renderWindow);
#else
  this->ui->qvtkWidget->SetRenderWindow(renderWindow);
#endif

  // Sphere
  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->Update();
  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());
   
  sphereActor->GetProperty()->SetDiffuseColor(1, 0, 0); // farba telesa
  sphereActor->GetProperty()->SetDiffuse(1); // difuzny koeficient
  sphereActor->GetProperty()->SetSpecular(1); // koeficient odrazu
  sphereActor->GetProperty()->SetSpecularPower(3.0); // ostrost zrkadloveho odrazu
  sphereActor->GetProperty()->SetAmbient(0.2); // ambientny koeficient - okolite svetlo
  // moznosti interpolacie
  // sphereActor->GetProperty()->SetInterpolationToGouraud();
  sphereActor->GetProperty()->SetInterpolationToPhong();
  // sphereActor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
  light->SetLightTypeToSceneLight();
  light->SetColor(1.0, 1.0, 1.0); // Set light color - farba dopadajuceho luca
  light->SetIntensity(0.8); // Set light intensity - intenzita
  light->SetPosition(1.0, 1.0, 1.0); // Set light position - zdroj osvetlenia
  light->SetFocalPoint(0.0, 0.0, 0.0); // Set light focal point - pozicia kamery

  // VTK Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);
 renderer->AddLight(light);

  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

  // VTK/Qt wedded
#if VTK890
  this->ui->qvtkWidget->renderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->renderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#else
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#endif
  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

RenderWindowUISingleInheritance::~RenderWindowUISingleInheritance()
{
  delete this->ui;
}

void RenderWindowUISingleInheritance::slotExit()
{
  qApp->exit();
}
