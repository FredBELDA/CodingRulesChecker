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
