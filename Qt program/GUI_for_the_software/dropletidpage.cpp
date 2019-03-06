#include "dropletidpage.h"
#include "ui_dropletidpage.h"

DropletIdPage::DropletIdPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DropletIdPage)
{
    ui->setupUi(this);
}

DropletIdPage::~DropletIdPage()
{
    delete ui;
}
