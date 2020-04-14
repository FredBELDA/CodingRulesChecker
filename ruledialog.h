#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include <QDialog>

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
                      const QString p_rule = QString(""),
                      const QString p_example = QString(""),
                      const QString p_explanation = QString(""));
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
  void applyStyle(void);
  void applyFontsOnLabels(void);
  void applyFontsOnButtons(void);

  Ui::RuleDialog *ui;
  QString m_popupTitle;
  QString m_popupRule;
  QString m_popupExample;
  QString m_popupExplanation;
};

#endif // RULEDIALOG_H
