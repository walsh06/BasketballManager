#ifndef MATCHSCREEN_H
#define MATCHSCREEN_H

#include <QWidget>

namespace Ui {
class MatchScreen;
}

class MatchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MatchScreen(QWidget *parent = 0);
    ~MatchScreen();

private:
    Ui::MatchScreen *ui;
};

#endif // MATCHSCREEN_H
