#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>

#include "ruledialog.h"

#define MAINWINDOW_HEIGHT 310
#define MAINWINDOW_WIDTH 675
#define WINDOW_TITLE "Coding rules checker"

#define MAIN_VERTICAL_LAYOUT_HEIGHT MAINWINDOW_HEIGHT - 80
#define MAIN_VERTICAL_LAYOUT_WIDTH MAINWINDOW_WIDTH - 30

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void fillInputFolder(void);
  void fillOutputLogs(void);
  void parseFolder(void);
  void openFolder(void);
  void sortFiles(QStringList p_list);
  void checkFiles(void);
  void checkOutputFolder(const QString p_outputFolder);
  // slots for menubar
  void loadConfigurationFile(const bool p_isChecked);
  void saveConfigurationFile(const bool p_isChecked);
  void displayAbout(const bool p_isChecked);
  // slots to determine which popup to display
  void displayNextRule(const QString p_popupTitle);

signals:
  void inputFolderChoiceDone(QString);
  void filesListed(QStringList);
  void launchCheckFiles(void);

private:
  Ui::MainWindow *ui;
  RuleDialog *m_accoladeRuleDialog;
  RuleDialog *m_camelCaseRuleDialog;
  RuleDialog *m_conditionsRuleDialog;
  RuleDialog *m_hFileRuleDialog;
  RuleDialog *m_magicNumberRuleDialog;
  RuleDialog *m_orphanFunctionsRuleDialog;
  RuleDialog *m_pointerRuleDialog;
  RuleDialog *m_todoRuleDialog;
  QStringList m_cFiles;
  QStringList m_cppFiles;
  QStringList m_hFiles;
  QStringList m_javaFiles;
  QStringList m_iniFiles;
  QStringList m_otherFiles;
  QFile *m_mergedReport;

  bool m_displayAccoladeRule;
  bool m_displayCamelCaseRule;
  bool m_displayConditionsRule;
  bool m_displayHRule;
  bool m_displayMagicNumberRule;
  bool m_displayOrphanFunctionsRule;
  bool m_displayPointerRule;
  bool m_displayTODORule;

  void initWidgets(void);
  void windowParameter(QMainWindow *p_mainWindow);
  void connectWidgets(void);
  void initVariables(void);

  void displayFirstRule(void);
  void displayAccoladePopupRule(void);
  void displayCamelCaseRule(void);
  void displayMagicNumberRule(void);
  void displayTODORule(void);
  void displayHRule(void);

  void launchCppCheck(void);
  void launchCheckStyle(void);
};

#endif // MAINWINDOW_H
