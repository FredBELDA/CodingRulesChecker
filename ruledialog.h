#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include <QDialog>

#define POPUP_HEIGHT 310
#define POPUP_WIDTH 675

#define POPUP_VERTICAL_LAYOUT_HEIGHT POPUP_HEIGHT - 80
#define POPUP_VERTICAL_LAYOUT_WIDTH POPUP_WIDTH - 30

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
