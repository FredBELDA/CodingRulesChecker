#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

#define ABOUT_POPUP_HEIGHT 191
#define ABOUT_POPUP_WIDTH 398

#define ABOUT_POPUP_VERTICAL_LAYOUT_HEIGHT ABOUT_POPUP_HEIGHT - 80
#define ABOUT_POPUP_VERTICAL_LAYOUT_WIDTH ABOUT_POPUP_WIDTH - 30

#define ABOUT_POPUP_TITLE "Au sujet de"
#define ABOUT_POPUP_CONTAINT "Le projet CodingRulesChecker a été déveoppé dans le but\nd'assurer une conformité des livraisons\n \
pour le compte de Thales TSIS, dans leurs projets internes.\n \
Ce projet a été réalisé avec le framework Qt5.7"

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

  Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
