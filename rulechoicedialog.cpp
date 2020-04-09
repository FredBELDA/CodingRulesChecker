#include <QDebug>

#include "commonelements.h"
#include "rulechoicedialog.h"
#include "ui_rulechoicedialog.h"

RuleChoiceDialog::RuleChoiceDialog(QWidget *p_parent) :
  QDialog(p_parent),
  ui(new Ui::RuleChoiceDialog)
{
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
}

RuleChoiceDialog::~RuleChoiceDialog()
{
  if(nullptr != ui)
  {
    delete ui;
    ui = nullptr;
  }
}

/**
 * @brief RuleChoiceDialog::windowParameter
 * Parameter the popup (size, title, ...)
 *
 * @param p_widget : the popup object
 */
void RuleChoiceDialog::windowParameter(QWidget *p_widget)
{
  if(nullptr != p_widget)
  {
    p_widget->setWindowTitle(RULE_CHOICE_POPUP_TITLE);
    p_widget->resize(RULE_CHOICE_POPUP_WIDTH, RULE_CHOICE_POPUP_HEIGHT);
    p_widget->setFixedSize(QSize(RULE_CHOICE_POPUP_WIDTH, RULE_CHOICE_POPUP_HEIGHT));
  }
  else
  {
    qDebug() << "RuleChoiceDialog::windowParameter() => p_widget is null !";
  }
}

/**
 * @brief RuleChoiceDialog::initWidgets
 * Init text for popup
 */
void RuleChoiceDialog::initWidgets(void)
{
  ui->pushButton_Valider->setText(VALIDATE);
  ui->pushButton_Annuler->setText(CANCEL);
}

/**
 * @brief RuleChoiceDialog::connectWidgets : Connect widgets to actions
 */
void RuleChoiceDialog::connectWidgets(void)
{
  connect(ui->pushButton_Valider, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui->pushButton_Annuler, SIGNAL(clicked()), this, SLOT(reject()));
}

bool RuleChoiceDialog::getAccoladeCheckBoxState(void)
{
  return ui->checkBox_AccoladeVerification->isChecked();
}

void RuleChoiceDialog::setAccoladeCheckBoxState(const bool p_checked)
{
  ui->checkBox_AccoladeVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getMagicNumberCheckBoxState(void)
{
  return ui->checkBox_MagicNumberVerification->isChecked();
}

void RuleChoiceDialog::setMagicNumberCheckBoxState(const bool p_checked)
{
  ui->checkBox_MagicNumberVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getCamelCaseCheckBoxState(void)
{
  return ui->checkBox_CamelCaseVerification->isChecked();
}

void RuleChoiceDialog::setCamelCaseCheckBoxState(const bool p_checked)
{
  ui->checkBox_CamelCaseVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getConditionCheckBoxState(void)
{
  return ui->checkBox_ConditionVerification->isChecked();
}

void RuleChoiceDialog::setConditionCheckBoxState(const bool p_checked)
{
  ui->checkBox_ConditionVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getOrphanFunctionCheckBoxState(void)
{
  return ui->checkBox_OrphanFunctionsVerification->isChecked();
}

void RuleChoiceDialog::setOrphanFunctionCheckBoxState(const bool p_checked)
{
  ui->checkBox_OrphanFunctionsVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getPointerCheckBoxState(void)
{
  return ui->checkBox_PointerVerification->isChecked();
}

void RuleChoiceDialog::setPointerCheckBoxState(const bool p_checked)
{
  ui->checkBox_PointerVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getToDoCheckBoxState(void)
{
  return ui->checkBox_ToDoVerification->isChecked();
}

void RuleChoiceDialog::setToDoCheckBoxState(const bool p_checked)
{
  ui->checkBox_ToDoVerification->setChecked(p_checked);
}

bool RuleChoiceDialog::getHFileForCCheckBoxState(void)
{
  return ui->checkBox_HFileVerificationForC->isChecked();
}

void RuleChoiceDialog::setHFileForCCheckBoxState(const bool p_checked)
{
  ui->checkBox_HFileVerificationForC->setChecked(p_checked);
}

bool RuleChoiceDialog::getHFileForCppCheckBoxState(void)
{
  return ui->checkBox_HFileVerificationForCpp->isChecked();
}

void RuleChoiceDialog::setHFileForCppCheckBoxState(const bool p_checked)
{
  ui->checkBox_HFileVerificationForCpp->setChecked(p_checked);
}
