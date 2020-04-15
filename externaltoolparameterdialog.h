#ifndef TOOLPARAMETERDIALOG_H
#define TOOLPARAMETERDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui
{
  class ExternalToolParameterDialog;
}

class ExternalToolParameterDialog : public QDialog
{
  Q_OBJECT

public:
  ExternalToolParameterDialog(QWidget *p_parent = nullptr);
  ~ExternalToolParameterDialog();

  QString getExcelPath(void);
  void setExcelPath(const QString p_excelPath);
  QString getCPPCheckPath(void);
  void setCPPCheckPath(const QString p_cppCheckPath);
  QString getCheckStylePath(void);
  void setCheckStylePath(const QString p_checkStylePath);

public slots:
  void fillExcelPath(void);
  void fillCPPCheckPath(void);
  void fillCheckStylePath(void);
  void checkExcelPath(const QString p_excelPath);
  void checkCPPCheckPath(const QString p_cppCheckPath);
  void checkCheckStylePath(const QString p_checkStylePath);

private:
  void windowParameter(QWidget *p_widget);
  void initWidgets(void);
  void connectWidgets(void);
  void applyStyle(void);
  void applyFontsOnLabels(void);
  void applyFontsOnButtons(void);

  void genericCheckPath(QLineEdit *p_lineEdit, const QString p_pathToCheck, const QString p_errorMessage);

  Ui::ExternalToolParameterDialog *ui;
};

#endif // TOOLPARAMETERDIALOG_H
