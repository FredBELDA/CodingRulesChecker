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
  applyStyle();
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

    ui->verticalLayout->setGeometry(QRect(X_SHIFT,
                                          Y_SHIFT,
                                          ABOUT_POPUP_VERTICAL_LAYOUT_WIDTH,
                                          ABOUT_POPUP_VERTICAL_LAYOUT_HEIGHT)
                                    );
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

/**
 * @brief AboutDialog::applyStyle
 * Apply different style on widget (label and button)
 */
void AboutDialog::applyStyle(void)
{
  //Apply font on labels
  applyFontsOnLabels();
  // Apply font on pushButton
  applyFontsOnButtons();
}

/**
 * @brief AboutDialog::applyFontsOnLabels
 * Apply font on all labels for this popup
 */
void AboutDialog::applyFontsOnLabels(void)
{
  QFont l_fontEnonce;
  l_fontEnonce.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontEnonce.setPointSize(ENONCE_FONT_SIZE);

  ui->label_About->setFont(l_fontEnonce);
}

/**
 * @brief AboutDialog::applyFontsOnButtons
 * Apply font on all buttons for this popup
 */
void AboutDialog::applyFontsOnButtons(void)
{
  QFont l_fontQPushButton;
  l_fontQPushButton.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQPushButton.setPointSize(PUSHBUTTON_FONT_SIZE);

  ui->pushButton_Valider->setFont(l_fontQPushButton);
}
