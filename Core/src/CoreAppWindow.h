#pragma once

#include <QMainWindow>

namespace Ui
{
    class CoreAppWindow;
}

namespace Ouquitoure
{
    class CoreAppWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit CoreAppWindow( QWidget *parent = nullptr );
        ~CoreAppWindow();

    private:
        Ui::CoreAppWindow *ui;
    };
}

