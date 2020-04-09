#ifndef RULECHOICEDIALOG_H
#define RULECHOICEDIALOG_H

#include <QDialog>

#define RULE_CHOICE_POPUP_HEIGHT 530
#define RULE_CHOICE_POPUP_WIDTH 847

#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_POPUP_HEIGHT - 80
#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_POPUP_WIDTH - 30

#define RULE_CHOICE_POPUP_TITLE "Configuration des règles à analyser"

namespace Ui
{
  class RuleChoiceDialog;
}

class RuleChoiceDialog : public QDialog
{
  Q_OBJECT

public:
  RuleChoiceDialog(QWidget *p_parent = nullptr);
  ~RuleChoiceDialog();

  bool getAccoladeCheckBoxState(void);
  void setAccoladeCheckBoxState(const bool p_checked);
  bool getMagicNumberCheckBoxState(void);
  void setMagicNumberCheckBoxState(const bool p_checked);
  bool getCamelCaseCheckBoxState(void);
  void setCamelCaseCheckBoxState(const bool p_checked);
  bool getConditionCheckBoxState(void);
  void setConditionCheckBoxState(const bool p_checked);
  bool getOrphanFunctionCheckBoxState(void);
  void setOrphanFunctionCheckBoxState(const bool p_checked);
  bool getPointerCheckBoxState(void);
  void setPointerCheckBoxState(const bool p_checked);
  bool getToDoCheckBoxState(void);
  void setToDoCheckBoxState(const bool p_checked);

  bool getHFileForCCheckBoxState(void);
  void setHFileForCCheckBoxState(const bool p_checked);

  bool getHFileForCppCheckBoxState(void);
  void setHFileForCppCheckBoxState(const bool p_checked);

private:
  void windowParameter(QWidget *p_widget);
  void initWidgets(void);
  void connectWidgets(void);

  Ui::RuleChoiceDialog *ui;
};

#endif // RULECHOICEDIALOG_H
