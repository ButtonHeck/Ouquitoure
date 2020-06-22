#pragma once

#include <QOpenGLWidget>
#include <QString>

namespace Ouquitoure
{
    class OpenGLWidgetBase : public QOpenGLWidget
    {
    public:
        explicit OpenGLWidgetBase( const QString & name, QWidget * parent = nullptr );
        ~OpenGLWidgetBase();

        const QString & getName() const noexcept;

    private:
        QString name;
    };

} // namespace Ouquitoure
