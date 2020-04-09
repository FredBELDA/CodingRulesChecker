#include <QDebug>

#include "aboutdialog.h"
#include "commonelements.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *p_parent) :
  QDialog(p_parent),
  ui(new Ui::AboutDialog)
{
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
}

AboutDialog::~AboutDialog()
{
  if(nullptr != ui)
  {
    delete ui;
    ui = nullptr;
  }
}

/**
 * @brief AboutDialog::windowParameter
 * Parameter the popup (size, title, ...)
 *
 * @param p_widget : the popup object
 */
void AboutDialog::windowParameter(QWidget *p_widget)
{
  if(nullptr != p_widget)
  {
    p_widget->setWindowTitle(ABOUT_POPUP_TITLE);
    p_widget->resize(ABOUT_POPUP_WIDTH, ABOUT_POPUP_HEIGHT);
    p_widget->setFixedSize(QSize(ABOUT_POPUP_WIDTH, ABOUT_POPUP_HEIGHT));
  }
  else
  {
    qDebug() << "AboutDialog::windowParameter() => p_widget is null !";
  }
}

/**
 * @brief AboutDialog::initWidgets
 * Init text for popup
 */
void AboutDialog::initWidgets(void)
{
  ui->pushButton_Valider->setText(VALIDATE);
  ui->label_About->setAlignment(Qt::AlignCenter);
  ui->label_About->setText(ABOUT_POPUP_CONTAINT);
}

/**
 * @brief AboutDialog::connectWidgets : Connect widgets to actions
 */
void AboutDialog::connectWidgets(void)
{
  connect(ui->pushButton_Valider, SIGNAL(clicked()), this, SLOT(accept()));
}
