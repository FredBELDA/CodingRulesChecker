#include <QDebug>

#include "commonelements.h"
#include "ruledialog.h"
#include "ui_ruledialog.h"

RuleDialog::RuleDialog(QWidget *p_parent,
                       const QString p_windowTitle,
                       const QString p_rule,
                       const QString p_example,
                       const QString p_explanation) :
  QDialog(p_parent),
  ui(new Ui::RuleDialog)
{
  m_popupTitle = p_windowTitle;
  m_popupRule = p_rule;
  m_popupExample = p_example;
  m_popupExplanation = p_explanation;
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

    ui->verticalLayout->setGeometry(QRect(X_SHIFT,
                                          Y_SHIFT,
                                          RULE_POPUP_VERTICAL_LAYOUT_WIDTH,
                                          RULE_POPUP_VERTICAL_LAYOUT_HEIGHT)
                                    );
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
  ui->pushButton_valider->setText(VALIDATE);
  ui->label_rule->setAlignment(Qt::AlignCenter);
  ui->label_rule->setText(m_popupRule);
  ui->label_example->setText(m_popupExample);
  ui->label_explanation->setAlignment(Qt::AlignCenter);
  ui->label_explanation->setText(m_popupExplanation);
}

/**
 * @brief RuleDialog::connectWidgets : Connect widgets to actions
 */
void RuleDialog::connectWidgets(void)
{
  connect(ui->pushButton_valider, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui->pushButton_valider, SIGNAL(clicked()), this, SLOT(emitSignal()));
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

  ui->label_rule->setFont(l_fontEnonce);
  ui->label_example->setFont(l_fontEnonce);
  ui->label_example->setStyleSheet(LABEL_EXAMPLE);
  ui->label_explanation->setFont(l_fontEnonce);
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

  ui->pushButton_valider->setFont(l_fontQPushButton);
}

/**
 * @brief RuleDialog::setRule
 * Set the complete rule to advice developper
 *
 * @param p_rule : the rule to display
 */
void RuleDialog::setRule(const QString p_rule)
{
  ui->label_rule->setText(p_rule);
}

/**
 * @brief RuleDialog::emitSignal
 * Emit the window title to identify the current rule, to identify which rule to display
 */
void RuleDialog::emitSignal(void)
{
  emit popupRead(this->windowTitle());
}
