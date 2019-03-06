#ifndef DROPLETIDPAGE_H
#define DROPLETIDPAGE_H

#include <QMainWindow>

namespace Ui {
class DropletIdPage;
}

class DropletIdPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit DropletIdPage(QWidget *parent = nullptr);
    ~DropletIdPage();

private:
    Ui::DropletIdPage *ui;
};

#endif // DROPLETIDPAGE_H
