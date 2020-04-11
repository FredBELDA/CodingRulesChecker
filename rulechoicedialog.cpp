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

    ui->verticalLayout->setGeometry(QRect(X_SHIFT,
                                          Y_SHIFT,
                                          RULE_CHOICE_POPUP_VERTICAL_LAYOUT_WIDTH,
                                          RULE_CHOICE_POPUP_VERTICAL_LAYOUT_HEIGHT)
                                    );
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

  // Force display the first tab
  ui->tabWidget->setCurrentIndex(0);
}

/**
 * @brief RuleChoiceDialog::connectWidgets : Connect widgets to actions
 */
void RuleChoiceDialog::connectWidgets(void)
{
  connect(ui->pushButton_Valider, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui->pushButton_Annuler, SIGNAL(clicked()), this, SLOT(reject()));
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

  ui->tab_C->setFont(l_fontTab);
  ui->tab_Cpp->setFont(l_fontTab);
  ui->tab_Java->setFont(l_fontTab);
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

  ui->label_CommonRules->setFont(l_fontEnonce);
  ui->label_SpecificRules->setFont(l_fontEnonce);
  ui->label_CommonRules->setStyleSheet(LABEL_COLOR);
  ui->label_SpecificRules->setStyleSheet(LABEL_COLOR);
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

  ui->pushButton_Valider->setFont(l_fontQPushButton);
  ui->pushButton_Annuler->setFont(l_fontQPushButton);
}

/**
 * @brief RuleChoiceDialog::applyFontsOnLabels
 * Apply font on all checkboxes for this popup
 */
void RuleChoiceDialog::applyFontsOnCheckboxes(void)
{
  QFont l_fontQCheckbox;
  l_fontQCheckbox.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQCheckbox.setPointSize(CHECKBOX_FONT_SIZE);

  ui->checkBox_AccoladeVerification->setFont(l_fontQCheckbox);
  ui->checkBox_CamelCaseVerification->setFont(l_fontQCheckbox);
  ui->checkBox_ConditionVerification->setFont(l_fontQCheckbox);
  ui->checkBox_MagicNumberVerification->setFont(l_fontQCheckbox);
  ui->checkBox_OrphanFunctionsVerification->setFont(l_fontQCheckbox);
  ui->checkBox_PointerVerification->setFont(l_fontQCheckbox);
  ui->checkBox_ToDoVerification->setFont(l_fontQCheckbox);

  ui->checkBox_HFileVerificationForC->setFont(l_fontQCheckbox);
  ui->checkBox_HFileVerificationForCpp->setFont(l_fontQCheckbox);
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
