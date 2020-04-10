#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

#define ABOUT_POPUP_HEIGHT 190
#define ABOUT_POPUP_WIDTH 450

#define ABOUT_POPUP_VERTICAL_LAYOUT_HEIGHT ABOUT_POPUP_HEIGHT - 80
#define ABOUT_POPUP_VERTICAL_LAYOUT_WIDTH ABOUT_POPUP_WIDTH - 30

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
