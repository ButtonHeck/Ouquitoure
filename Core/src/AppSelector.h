#pragma once

#include <QWidget>

namespace Ui
{
    class AppSelector;
}

class AppSelector : public QWidget
{
    Q_OBJECT
public:
    explicit AppSelector( QWidget *parent = nullptr );
    ~AppSelector();

private:
    Ui::AppSelector *ui;
};
