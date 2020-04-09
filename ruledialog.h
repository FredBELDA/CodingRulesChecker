#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include <QDialog>

#define RULE_POPUP_HEIGHT 310
#define RULE_POPUP_WIDTH 675

#define RULE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_POPUP_HEIGHT - 80
#define RULE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_POPUP_WIDTH - 30

namespace Ui
{
  class RuleDialog;
}

class RuleDialog : public QDialog
{
  Q_OBJECT

public:
  explicit RuleDialog(QWidget *p_parent = nullptr,
                      const QString p_windowTitle = QString(""),
                      const QString p_rule = QString(""));
  ~RuleDialog();

  void setRule(const QString p_rule);

public slots:
  void emitSignal(void);

signals:
  void popupRead(const QString p_ruleRead);

private:
  void windowParameter(QWidget *p_widget);
  void initWidgets(void);
  void connectWidgets(void);

  Ui::RuleDialog *ui;
  QString m_popupTitle;
  QString m_popupRule;
};

#endif // RULEDIALOG_H
