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
  applyStyle();
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

    if(nullptr != ui)
    {
      ui->verticalLayout->setGeometry(QRect(X_SHIFT,
                                            Y_SHIFT,
                                            RULE_CHOICE_POPUP_VERTICAL_LAYOUT_WIDTH,
                                            RULE_CHOICE_POPUP_VERTICAL_LAYOUT_HEIGHT)
                                      );
    }
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
  if(nullptr != ui)
  {
    ui->label_separator->setText("");
    ui->pushButton_valider->setText(SAVE);
    ui->pushButton_annuler->setText(QUIT);

    // Force display the first tab
    ui->tabWidget->setCurrentIndex(0);
  }
}

/**
 * @brief RuleChoiceDialog::connectWidgets : Connect widgets to actions
 */
void RuleChoiceDialog::connectWidgets(void)
{
  if(nullptr != ui)
  {
    connect(ui->pushButton_valider, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_annuler, SIGNAL(clicked()), this, SLOT(reject()));
  }
}

/**
 * @brief RuleChoiceDialog::applyStyle
 * Apply different style on widget (label and button)
 */
void RuleChoiceDialog::applyStyle(void)
{
  //Apply font on labels
  applyFontsOnLabels();
  // Apply font on pushButton
  applyFontsOnButtons();
  // Apply font on checkbox
  applyFontsOnCheckboxes();
  // Apply font on tabs
  applyFontsOnTabs();
}

/**
 * @brief RuleChoiceDialog::applyFontsOnLabels
 * Apply font on all tabs for this popup
 */
void RuleChoiceDialog::applyFontsOnTabs(void)
{
  QFont l_fontTab;
  l_fontTab.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontTab.setPointSize(TAB_FONT_SIZE);

  if(nullptr != ui)
  {
    ui->tab_C->setFont(l_fontTab);
    ui->tab_Cpp->setFont(l_fontTab);
    ui->tab_Java->setFont(l_fontTab);
  }
}

/**
 * @brief RuleChoiceDialog::applyFontsOnLabels
 * Apply font on all labels for this popup
 */
void RuleChoiceDialog::applyFontsOnLabels(void)
{
  QFont l_fontEnonce;
  l_fontEnonce.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontEnonce.setPointSize(ENONCE_FONT_SIZE);
  l_fontEnonce.setBold(true);

  if(nullptr != ui)
  {
    ui->label_commonRules->setFont(l_fontEnonce);
    ui->label_specificRules->setFont(l_fontEnonce);
    ui->label_commonRules->setStyleSheet(LABEL_COLOR);
    ui->label_specificRules->setStyleSheet(LABEL_COLOR);

    ui->label_separator->setStyleSheet(LABEL_SEPARATOR);
  }
}

/**
 * @brief RuleChoiceDialog::applyFontsOnButtons
 * Apply font on all buttons for this popup
 */
void RuleChoiceDialog::applyFontsOnButtons(void)
{
  QFont l_fontQPushButton;
  l_fontQPushButton.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQPushButton.setPointSize(PUSHBUTTON_FONT_SIZE);

  if(nullptr != ui)
  {
    ui->pushButton_valider->setFont(l_fontQPushButton);
    ui->pushButton_annuler->setFont(l_fontQPushButton);
  }
}

/**
 * @brief RuleChoiceDialog::applyFontsOnCheckboxes
 * Apply font on all checkboxes for this popup
 */
void RuleChoiceDialog::applyFontsOnCheckboxes(void)
{
  QFont l_fontQCheckbox;
  l_fontQCheckbox.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQCheckbox.setPointSize(CHECKBOX_FONT_SIZE);

  if(nullptr != ui)
  {
    ui->checkBox_accoladeVerification->setFont(l_fontQCheckbox);
    ui->checkBox_camelCaseVerification->setFont(l_fontQCheckbox);
    ui->checkBox_conditionVerification->setFont(l_fontQCheckbox);
    ui->checkBox_magicNumberVerification->setFont(l_fontQCheckbox);
    ui->checkBox_orphanFunctionsVerification->setFont(l_fontQCheckbox);
    ui->checkBox_pointerVerification->setFont(l_fontQCheckbox);
    ui->checkBox_toDoVerification->setFont(l_fontQCheckbox);

    ui->checkBox_hFileVerificationForC->setFont(l_fontQCheckbox);
    ui->checkBox_hFileVerificationForCpp->setFont(l_fontQCheckbox);
  }
}

bool RuleChoiceDialog::getAccoladeCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_accoladeVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setAccoladeCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_accoladeVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getMagicNumberCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_magicNumberVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setMagicNumberCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_magicNumberVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getCamelCaseCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_camelCaseVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setCamelCaseCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_camelCaseVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getConditionCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_conditionVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setConditionCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_conditionVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getOrphanFunctionCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_orphanFunctionsVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setOrphanFunctionCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_orphanFunctionsVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getPointerCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_pointerVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setPointerCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_pointerVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getToDoCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_toDoVerification->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setToDoCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_toDoVerification->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getHFileForCCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_hFileVerificationForC->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setHFileForCCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_hFileVerificationForC->setChecked(p_checked);
  }
}

bool RuleChoiceDialog::getHFileForCppCheckBoxState(void)
{
  bool l_returnValue = false;
  if(nullptr != ui)
  {
    l_returnValue = ui->checkBox_hFileVerificationForCpp->isChecked();
  }
  return l_returnValue;
}

void RuleChoiceDialog::setHFileForCppCheckBoxState(const bool p_checked)
{
  if(nullptr != ui)
  {
    ui->checkBox_hFileVerificationForCpp->setChecked(p_checked);
  }
}
