#include <QDebug>

#include "commonelements.h"
#include "ruledialog.h"
#include "ui_ruledialog.h"

RuleDialog::RuleDialog(QWidget *p_parent,
                       const QString p_windowTitle,
                       const QString p_rule) :
  QDialog(p_parent),
  ui(new Ui::RuleDialog)
{
  m_popupTitle = p_windowTitle;
  m_popupRule = p_rule;
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
  applyStyle();
}

RuleDialog::~RuleDialog()
{
  if(nullptr != ui)
  {
    delete ui;
    ui = nullptr;
  }
}

/**
 * @brief RuleDialog::windowParameter
 * Parameter the popup (size, title, ...)
 *
 * @param p_widget : the popup object
 */
void RuleDialog::windowParameter(QWidget *p_widget)
{
  if(nullptr != p_widget)
  {
    p_widget->setWindowTitle(m_popupTitle);
    p_widget->resize(RULE_POPUP_WIDTH, RULE_POPUP_HEIGHT);
    p_widget->setFixedSize(QSize(RULE_POPUP_WIDTH, RULE_POPUP_HEIGHT));

    ui->verticalLayout->setGeometry(QRect(10, 10, RULE_POPUP_VERTICAL_LAYOUT_WIDTH, RULE_POPUP_VERTICAL_LAYOUT_HEIGHT));
  }
  else
  {
    qDebug() << "RuleDialog::windowParameter() => p_widget is null !";
  }
}

/**
 * @brief RuleDialog::initWidgets
 * Init text for popup
 */
void RuleDialog::initWidgets(void)
{
  ui->pushButton_Valider->setText(VALIDATE);
}

/**
 * @brief RuleDialog::connectWidgets : Connect widgets to actions
 */
void RuleDialog::connectWidgets(void)
{
  connect(ui->pushButton_Valider, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui->pushButton_Valider, SIGNAL(clicked()), this, SLOT(emitSignal()));
}

/**
 * @brief RuleDialog::applyStyle
 * Apply different style on widget (label and button)
 */
void RuleDialog::applyStyle(void)
{
  //Apply font on labels
  applyFontsOnLabels();
  // Apply font on pushButton
  applyFontsOnButtons();
}

/**
 * @brief RuleDialog::applyFontsOnLabels
 * Apply font on all labels for this popup
 */
void RuleDialog::applyFontsOnLabels(void)
{
  QFont l_fontEnonce;
  l_fontEnonce.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontEnonce.setPointSize(ENONCE_FONT_SIZE);

  ui->label_Rule->setFont(l_fontEnonce);
}

/**
 * @brief RuleDialog::applyFontsOnButtons
 * Apply font on all buttons for this popup
 */
void RuleDialog::applyFontsOnButtons(void)
{
  QFont l_fontQPushButton;
  l_fontQPushButton.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQPushButton.setPointSize(PUSHBUTTON_FONT_SIZE);

  ui->pushButton_Valider->setFont(l_fontQPushButton);
}

/**
 * @brief RuleDialog::setRule
 * Set the complete rule to advice developper
 *
 * @param p_rule : the rule to display
 */
void RuleDialog::setRule(const QString p_rule)
{
  ui->label_Rule->setText(p_rule);
}

/**
 * @brief RuleDialog::emitSignal
 * Emit the window title to identify the current rule, to identify which rule to display
 */
void RuleDialog::emitSignal(void)
{
  emit popupRead(this->windowTitle());
}
