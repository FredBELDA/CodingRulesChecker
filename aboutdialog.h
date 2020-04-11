#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui
{
  class AboutDialog;
}

class AboutDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AboutDialog(QWidget *p_parent = nullptr);
  ~AboutDialog();

private:
  void windowParameter(QWidget *p_widget);
  void initWidgets(void);
  void connectWidgets(void);
  void applyStyle(void);
  void applyFontsOnLabels(void);
  void applyFontsOnButtons(void);

  Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
