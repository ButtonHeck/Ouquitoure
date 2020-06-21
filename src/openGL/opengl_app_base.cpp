#include "OpenGLApps/OpenGLAppBase"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QDockWidget>
#include <QOpenGLWidget>
#include <QResizeEvent>

namespace Ouquitoure
{

    OpenGLAppBase::OpenGLAppBase(QWidget * parent)
        : QMainWindow(parent)
    {
        setWindowTitle("OpenGL Application");

        QWidget * centralWidget = new QWidget{this};
        QHBoxLayout * mainLayout = new QHBoxLayout();
        setCentralWidget(centralWidget);
        centralWidget->setLayout(mainLayout);

        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        centralWidget->setSizePolicy(sizePolicy);

        QHBoxLayout * appLayout = new QHBoxLayout();
        QGroupBox * controlsGroupBox = new QGroupBox("Controls");
        controlsGroupBox->setSizePolicy(sizePolicy);
        controlsGroupBox->setMinimumSize(480, 480);

        viewDockWidget = new QDockWidget(centralWidget);
        viewDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        viewDockWidget->setWindowTitle("View");
        QOpenGLWidget * viewOpenGLWidget = new QOpenGLWidget();
        viewDockWidget->setWidget(viewOpenGLWidget);
        viewOpenGLWidget->setMinimumSize(640, 480);
        viewOpenGLWidget->setSizePolicy(sizePolicy);
        addDockWidget(Qt::RightDockWidgetArea, viewDockWidget);

        appLayout->addWidget(controlsGroupBox);

        mainLayout->addLayout(appLayout);
    }

    void OpenGLAppBase::resizeEvent(QResizeEvent * event)
    {
        resizeDocks({viewDockWidget}, {event->size().width() / 2}, Qt::Horizontal);
    }

    const AppInfo & OpenGLAppBase::getInfo() const noexcept
    {
        return info;
    }

}
