#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>

#include "ruledialog.h"
#include "rulechoicedialog.h"

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
  void checkInputFolder(const QString p_inputFolder);
  void checkOutputFolder(const QString p_outputFolder);
  // slots for menubar
  void loadConfigurationFile(void);
  void saveConfigurationFile(void);
  void saveConfigurationFileAndQuit(void);
  void manageCodingRules(void);
  void displayAbout(void);
  // slots to determine which popup to display
  void displayNextRule(const QString p_popupTitle);

signals:
  void inputFolderChoiceDone(QString);
  void filesListed(QStringList);
  void launchCheckFiles(void);

protected:
  void closeEvent(QCloseEvent *p_event) override;

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
  RuleChoiceDialog *m_ruleChoiceDialog;

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
  void applyStyle(void);
  void applyFontsOnMenu(void);
  void applyFontsOnLabels(void);
  void applyFontsOnButtons(void);
  void applyFontsOnLineEdits(void);

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
