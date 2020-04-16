#include <QCloseEvent>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QFile>
#include <QIcon>
#include <QSettings>
#include <QTextStream>

#include "abstractveriffiles.h"

#include "cveriffile.h"
#include "cppveriffile.h"
#include "hveriffile.h"
#include "javaveriffile.h"
#include "iniveriffile.h"
#include "utils.h"

#include "commonelements.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
  initVariables();
  applyStyle();
  // Load config file
  loadConfigurationFile();
}

MainWindow::~MainWindow()
{
  if(nullptr != ui)
  {
    delete ui;
    ui = nullptr;
  }
  if(nullptr != m_accoladeRuleDialog)
  {
    delete m_accoladeRuleDialog;
    m_accoladeRuleDialog = nullptr;
  }
  if(nullptr != m_camelCaseRuleDialog)
  {
    delete m_camelCaseRuleDialog;
    m_camelCaseRuleDialog = nullptr;
  }
  if(nullptr != m_conditionsRuleDialog)
  {
    delete m_conditionsRuleDialog;
    m_conditionsRuleDialog = nullptr;
  }
  if(nullptr != m_hFileRuleDialog)
  {
    delete m_hFileRuleDialog;
    m_hFileRuleDialog = nullptr;
  }
  if(nullptr != m_magicNumberRuleDialog)
  {
    delete m_magicNumberRuleDialog;
    m_magicNumberRuleDialog = nullptr;
  }
  if(nullptr != m_orphanFunctionsRuleDialog)
  {
    delete m_orphanFunctionsRuleDialog;
    m_orphanFunctionsRuleDialog = nullptr;
  }
  if(nullptr != m_pointerRuleDialog)
  {
    delete m_pointerRuleDialog;
    m_pointerRuleDialog = nullptr;
  }
  if(nullptr != m_todoRuleDialog)
  {
    delete m_todoRuleDialog;
    m_todoRuleDialog = nullptr;
  }
  if(nullptr != m_ruleChoiceDialog)
  {
    delete m_ruleChoiceDialog;
    m_ruleChoiceDialog = nullptr;
  }
  if(nullptr != m_toolParameterDialog)
  {
    delete m_toolParameterDialog;
    m_toolParameterDialog = nullptr;
  }
}

/**
 * @brief MainWindow::windowParameter
 *
 * @param p_mainWindow : the main window to parameter (title, size, ...)
 */
void MainWindow::windowParameter(QMainWindow *p_mainWindow)
{
  if(nullptr != p_mainWindow)
  {
    QIcon l_applicationIcon(":/images/CodingRulesChecker_Logo.png");
    p_mainWindow->setWindowTitle(WINDOW_TITLE);
    p_mainWindow->setWindowIcon(l_applicationIcon);
    p_mainWindow->resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    p_mainWindow->setFixedSize(QSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT));

    ui->verticalLayoutWidget->setGeometry(QRect(X_SHIFT,
                                                Y_SHIFT,
                                                MAIN_VERTICAL_LAYOUT_WIDTH,
                                                MAIN_VERTICAL_LAYOUT_HEIGHT)
                                          );
  }
  else
  {
    qDebug() << "MainWindow::windowParameter() => p_mainWindow is null !";
  }
}

/**
 * @brief MainWindow::initWidgets : Initialize all widget text
 *
 * \param void.
 * \return void.
 */
void MainWindow::initWidgets(void)
{
  QString l_version = "V ";
  l_version.append(VERSION);

  // Initialisation des textes du menu
  ui->menuFichier->setTitle(FILE_MENU);
  ui->actionOuvrir_la_configuration->setText(OPEN_CONFIGURATION_FILE);
  ui->actionEnregistrer_la_configuration->setText(SAVE_CONFIGURATION_FILE);
  ui->actionQuitter->setText(EXIT);

  ui->menuConfiguration->setTitle(CONFIGURATION_MENU);
  ui->actionParametrage_des_regles_de_codage->setText(CODING_RULES_PARAMETERS);
  ui->actionParametrage_des_outils_externes->setText(EXTERNAL_TOOL_PARAMETERS);

  ui->menuCheckList->setTitle(CHECKLIST_MENU);
  ui->actionOuvrir_le_fichier_checklist->setText(OPEN_CHECKLIST_FILE);

  ui->menuAide->setTitle(HELP_MENU);
  ui->actionA_propos->setText(ABOUT);

  // Initialisation de la fenêtre principale
  ui->label_inputPath->setText(INPUT_LABEL_TEXT);
  ui->label_outputLogs->setText(OUTPUT_LABEL_TEXT);
  ui->label_mergeAllReports->setText(CHECKBOX_MERGE_REPORTS);
  ui->label_logoAKKA->setText("");
  ui->label_logoThales->setText("");
  QPixmap l_logo_AKKA(":/images/AKKA_Logo.png");
  int l_logo_AKKA_Width = ui->label_logoAKKA->width();
  int l_logo_AKKA_Height = ui->label_logoAKKA->height();
  ui->label_logoAKKA->setPixmap(l_logo_AKKA.scaled(l_logo_AKKA_Width,
                                                   l_logo_AKKA_Height,
                                                   Qt::KeepAspectRatio)
                                );
  ui->label_logoAKKA->setAlignment(Qt::AlignCenter);
  QPixmap l_logo_Thales(":/images/Thales_Logo.png");
  int l_logo_Thales_Width = ui->label_logoThales->width();
  int l_logo_Thales_Height = ui->label_logoThales->height();
  ui->label_logoThales->setPixmap(l_logo_Thales.scaled(l_logo_Thales_Width,
                                                       l_logo_Thales_Height,
                                                       Qt::KeepAspectRatio)
                                  );
  ui->label_logoThales->setAlignment(Qt::AlignCenter);
  ui->pushButton_browseInputFolder->setText(BROWSE_FOLDER);
  ui->pushButton_browserOutputLogs->setText(BROWSE_FOLDER);
  ui->pushButton_launchChecks->setText(LAUNCH_CHECK);

  ui->label_version->setText(l_version);
  ui->label_version->setAlignment(Qt::AlignRight);

  ui->progressBar_checkRules->setValue(0);

  // Création de la popup RuleChoiceDialog
  m_ruleChoiceDialog = new RuleChoiceDialog(this);
  // Création de la popup ExternalToolParameterDialog
  m_toolParameterDialog = new ExternalToolParameterDialog(this);
}

/**
 * \brief Connect all signals to slots.
 *
 * \param void.
 * \return void.
 */
void MainWindow::connectWidgets(void)
{
  // Widget connexion
  QObject::connect(ui->pushButton_browseInputFolder, SIGNAL(clicked()), this, SLOT(fillInputFolder()));
  QObject::connect(ui->pushButton_browserOutputLogs, SIGNAL(clicked()), this, SLOT(fillOutputLogs()));
  QObject::connect(ui->pushButton_launchChecks, SIGNAL(clicked()), this, SLOT(parseFolder()));
  QObject::connect(ui->pushButton_openOutputLogs, SIGNAL(clicked()), this, SLOT(openFolder()));
  QObject::connect(ui->lineEdit_inputFolder, SIGNAL(textChanged(QString)), this, SLOT(checkInputFolder(QString)));
  QObject::connect(ui->lineEdit_outputLogs, SIGNAL(textChanged(QString)), this, SLOT(checkOutputFolder(QString)));
  QObject::connect(ui->progressBar_checkRules, SIGNAL(valueChanged(int)), this, SLOT(couldDisplayFirstRule(int)));
  // File menu connexion
  QObject::connect(ui->actionOuvrir_la_configuration, SIGNAL(triggered(bool)), this, SLOT(loadConfigurationFile()));
  QObject::connect(ui->actionEnregistrer_la_configuration, SIGNAL(triggered(bool)), this, SLOT(saveConfigurationFile()));
  QObject::connect(ui->actionQuitter, SIGNAL(triggered(bool)), this, SLOT(saveConfigurationFileAndQuit()));
  // Configuration menu connexion
  QObject::connect(ui->actionParametrage_des_regles_de_codage, SIGNAL(triggered(bool)), this, SLOT(manageCodingRules()));
  QObject::connect(ui->actionParametrage_des_outils_externes, SIGNAL(triggered(bool)), this, SLOT(manageExternalTools()));
  // CheckList menu connexion
  QObject::connect(ui->actionOuvrir_le_fichier_checklist, SIGNAL(triggered(bool)), this, SLOT(downloadCheckListFile()));
  // Help menu connexion
  QObject::connect(ui->actionA_propos, SIGNAL(triggered(bool)), this, SLOT(displayAbout()));
  // Signal connexion
  QObject::connect(this, SIGNAL(filesListed(QStringList)), this, SLOT(sortFiles(QStringList)));
  QObject::connect(this, SIGNAL(launchCheckFiles()), this, SLOT(checkFiles()));
}

void MainWindow::initVariables(void)
{
  m_cFiles.clear();
  m_cppFiles.clear();
  m_hFiles.clear();
  m_javaFiles.clear();
  m_iniFiles.clear();
  m_otherFiles.clear();

  m_pointerDeclaration.clear();

  m_displayAccoladeRule = false;
  m_displayCamelCaseRule = false;
  m_displayConditionsRule = false;
  m_displayHRule = false;
  m_displayMagicNumberRule = false;
  m_displayOrphanFunctionsRule = false;
  m_displayPointerRule = false;
  m_displayToDoRule = false;

  m_accoladeRuleDialog = nullptr;
  m_camelCaseRuleDialog = nullptr;
  m_conditionsRuleDialog = nullptr;
  m_hFileRuleDialog = nullptr;
  m_magicNumberRuleDialog = nullptr;
  m_orphanFunctionsRuleDialog = nullptr;
  m_pointerRuleDialog = nullptr;
  m_todoRuleDialog = nullptr;

  m_counterFileChecked = 0;

  checkOutputFolder(ui->lineEdit_outputLogs->text());
}

/**
 * @brief MainWindow::applyStyle
 * Apply different style on widget (label and button)
 */
void MainWindow::applyStyle(void)
{
  //Apply font on labels
  applyFontsOnLabels();
  // Apply font on pushButton
  applyFontsOnButtons();
  // Apply font on LineEdit
  applyFontsOnLineEdits();
  // Apply font on menu
  applyFontsOnMenu();
}

/**
 * \brief Browse folder to parse.
 *
 * \param void.
 * \return void.
 */
void MainWindow::fillInputFolder(void)
{
  QFileDialog l_dialog;
  QString l_path = "";

  l_dialog.setViewMode(QFileDialog::Detail);
  l_path = QFileDialog::getExistingDirectory(this,
                                             INPUT_FOLDER_TO_CHECK,
                                             ui->lineEdit_inputFolder->text().isEmpty() ? QDir::currentPath() : ui->lineEdit_inputFolder->text(),
                                             QFileDialog::ShowDirsOnly
                                             );

  if(0 < l_path)
  {
    ui->lineEdit_inputFolder->setText(l_path);
    QString l_formatedOutputFolder = Utils::formatPath(l_path + QDir::separator() + LOGS_FOLDER + QDir::separator()
                                                       + QDate::currentDate().toString("yyyyMMdd") + QDir::separator());
    ui->lineEdit_outputLogs->setText(l_formatedOutputFolder);
  }
}

/**
 * \brief Browse folder for logs.
 *
 * \param void.
 * \return void.
 */
void MainWindow::fillOutputLogs(void)
{
  QFileDialog l_dialog;
  QString l_path = "";

  l_dialog.setViewMode(QFileDialog::Detail);
  l_path = QFileDialog::getExistingDirectory(this,
                                             OUTPUT_FOLDER_TO_CHECK,
                                             ui->lineEdit_outputLogs->text().isEmpty() ? QDir::currentPath() : ui->lineEdit_outputLogs->text(),
                                             QFileDialog::ShowDirsOnly
                                             );

  if(0 < l_path)
  {
    ui->lineEdit_outputLogs->setText(l_path);
  }
}

/**
 * \brief Parse folder to get a list of all files.
 *
 * \param void.
 * \return void.
 */
void MainWindow::parseFolder(void)
{
  QStringList l_fileList;
  const QString l_inputFolder = ui->lineEdit_inputFolder->text();
  QDirIterator l_dirIterator(l_inputFolder, QDir::Files);
  while(l_dirIterator.hasNext())
  {
    l_fileList.append(l_dirIterator.next());
  }
  emit filesListed(l_fileList);
}

/**
 * \brief Open output logs folder.
 *
 * \param void.
 * \return void.
 */
void MainWindow::openFolder(void)
{
  QString l_explorer = QString(EXPLORER_CMD) + " " + Utils::formatPathForCmd(ui->lineEdit_outputLogs->text());
  system(l_explorer.toStdString().c_str());
}

/**
 * \brief Sort all files by extension.
 *
 * \param list of files.
 * \return void.
 */
void MainWindow::sortFiles(QStringList p_list)
{
  bool l_folderCreated = false;
  foreach (QString l_file, p_list)
  {
    QFileInfo l_fileInfo(l_file);
    if(0 == l_fileInfo.completeSuffix().toLower().compare(CPP_FILE_EXTENSION, Qt::CaseInsensitive))
    {
      m_cppFiles.append(l_file);
    }
    else if(0 == l_fileInfo.completeSuffix().toLower().compare(C_FILE_EXTENSION, Qt::CaseInsensitive))
    {
      m_cFiles.append(l_file);
    }
    else if(0 == l_fileInfo.completeSuffix().toLower().compare(H_FILE_EXTENSION, Qt::CaseInsensitive))
    {
      m_hFiles.append(l_file);
    }
    else if(0 == l_fileInfo.completeSuffix().toLower().compare(JAVA_FILE_EXTENSION, Qt::CaseInsensitive))
    {
      m_javaFiles.append(l_file);
    }
    else if(0 == l_fileInfo.completeSuffix().toLower().compare(INI_FILE_EXTENSION, Qt::CaseInsensitive))
    {
      m_iniFiles.append(l_file);
    }
    else
    {
      m_otherFiles.append(l_file);
    }
  }

  // Put maximum value to progressBar
  ui->progressBar_checkRules->setMinimum(0);
  qDebug() << "max value for progressbar = " << (m_cppFiles.size() + m_cFiles.size() + m_hFiles.size() + m_javaFiles.size() + m_iniFiles.size());
  ui->progressBar_checkRules->setMaximum(m_cppFiles.size() + m_cFiles.size() +
                                         m_hFiles.size() + m_javaFiles.size() +
                                         m_iniFiles.size()
                                         );

  // Create output folder to store reports
  QString l_outputFolderPath = ui->lineEdit_outputLogs->text();
  QDir l_reportFolder(l_outputFolderPath);
  if(!l_reportFolder.exists())
  {
    if(!l_reportFolder.mkpath(l_outputFolderPath))
    {
      qDebug() << CANNOT_CREATE_FOLDER << l_outputFolderPath;
    }
    else
    {
      l_folderCreated = true;
    }
  }
  else
  {
    l_folderCreated = true;
  }

  if(l_folderCreated)
  {
    // Verify checkbox to create a global report
    if(ui->checkBox_mergeAllReports->isChecked())
    {
      // We create the global report
      QString l_reportName = ui->lineEdit_outputLogs->text() + GLOBAL_REPORT_NAME;
      m_mergedReport = new QFile(l_reportName);
      if(!m_mergedReport->open(QFile::WriteOnly | QFile::Text))
      {
        qDebug() << CANNOT_OPENED_FILE << m_mergedReport->fileName() << FOR_WRITING;
      }
      else
      {
        // QTextStream object creation from QFile object
        QTextStream l_flux(m_mergedReport);
        // We fix codec before writting
        l_flux.setCodec(CODEC_FOR_EXCEL_FILE);
        // Write info into file
        QString l_currentDate = QDate::currentDate().toString("dd/MM/yyyy");
        l_flux << GENERATED_REPORT << l_currentDate << endl;
        l_flux << NUMBER_OF_FILES_FOUND << ui->lineEdit_inputFolder->text()
               << " : " << p_list.size() << endl;
      }
    }
    emit launchCheckFiles();
  }
}

/**
 * \brief Launch check on files.
 *
 * \param void.
 * \return void.
 */
void MainWindow::checkFiles(void)
{
  if(nullptr != m_ruleChoiceDialog)
  {
    // Launch cppCheck if c or cpp files
    if(!m_cFiles.isEmpty() || !m_cppFiles.isEmpty())
    {
      foreach (QString l_hFile, m_hFiles)
      {
        HVerifFile *l_hVerifFile = new HVerifFile(l_hFile, ui->lineEdit_outputLogs->text());
        if(nullptr != l_hVerifFile)
        {
          launchCommonCheck(l_hVerifFile);
          QStringList l_pointerDeclaration = l_hVerifFile->getPointerDeclarationList();
          if(!l_pointerDeclaration.isEmpty())
          {
            m_pointerDeclaration.append(l_pointerDeclaration);
          }
        }
        else
        {
          qDebug() << "l_hVerifFile is not created !";
        }

        // Increment progressBar
        incrementProgressBar();
      }
    }

    foreach (QString l_cFile, m_cFiles)
    {
      CVerifFile *l_cVerifFile = new CVerifFile(l_cFile, ui->lineEdit_outputLogs->text());
      if(nullptr != l_cVerifFile)
      {
        launchCommonCheck(l_cVerifFile);
        if(m_ruleChoiceDialog->getHFileForCCheckBoxState())
        {
          // Check for H file presence
          l_cVerifFile->verifyHFile(m_hFiles);
          // Set a boolean to display the popup if rule is not respected
          m_displayHRule |= l_cVerifFile->hasHFileProblem();
        }
        if(m_ruleChoiceDialog->getPointerCheckBoxState())
        {
          // Check for TODO problem into code
          l_cVerifFile->verifyPointers(m_pointerDeclaration);
          // Set a boolean to display the popup if rule is not respected
          m_displayPointerRule |= l_cVerifFile->hasPointersProblem();
        }
      }
      else
      {
        qDebug() << "l_cVerifFile is not created !";
      }

      // Increment progressBar
      incrementProgressBar();
    }

    foreach (QString l_cppFile, m_cppFiles)
    {
      CppVerifFile *l_cppVerifFile = new CppVerifFile(l_cppFile, ui->lineEdit_outputLogs->text());
      if(nullptr != l_cppVerifFile)
      {
        launchCommonCheck(l_cppVerifFile);
        if(m_ruleChoiceDialog->getHFileForCppCheckBoxState())
        {
          // Check for H file presence
          l_cppVerifFile->verifyHFile(m_hFiles);
          // Set a boolean to display the popup if rule is not respected
          m_displayHRule |= l_cppVerifFile->hasHFileProblem();
        }
        if(m_ruleChoiceDialog->getPointerCheckBoxState())
        {
          // Check for TODO problem into code
          l_cppVerifFile->verifyPointers(m_pointerDeclaration);
          // Set a boolean to display the popup if rule is not respected
          m_displayPointerRule |= l_cppVerifFile->hasPointersProblem();
        }
      }
      else
      {
        qDebug() << "l_cppVerifFile is not created !";
      }

      // Increment progressBar
      incrementProgressBar();
    }

    foreach (QString l_javaFile, m_javaFiles)
    {
      JavaVerifFile *l_javaVerifFile = new JavaVerifFile(l_javaFile, ui->lineEdit_outputLogs->text());
      if(nullptr != l_javaVerifFile)
      {
        launchCommonCheck(l_javaVerifFile);
      }
      else
      {
        qDebug() << "l_javaVerifFile is not created !";
      }

      // Increment progressBar
      incrementProgressBar();
    }

    foreach (QString l_iniFile, m_iniFiles)
    {
      IniVerifFile *l_iniVerifFile = new IniVerifFile(l_iniFile, ui->lineEdit_outputLogs->text());
      if(nullptr != l_iniVerifFile)
      {
        l_iniVerifFile->isIniFile();
      }
      else
      {
        qDebug() << "l_iniVerifFile is not created !";
      }

      // Increment progressBar
      incrementProgressBar();
    }

    if(ui->checkBox_mergeAllReports->isChecked())
    {
      // QTextStream object creation from QFile object
      QTextStream l_flux(m_mergedReport);
      // We fix codec before writting
      l_flux.setCodec(CODEC_FOR_EXCEL_FILE);
      // Write info into file
      l_flux << NUMBER_OF_C_FILES << m_cFiles.size() << endl;
      l_flux << NUMBER_OF_CPP_FILES << m_cppFiles.size() << endl;
      l_flux << NUMBER_OF_H_FILES << m_hFiles.size() << endl;
      l_flux << NUMBER_OF_JAVA_FILES << m_javaFiles.size() << endl;
      l_flux << NUMBER_OF_INI_FILES << m_iniFiles.size() << endl;
      l_flux << NUMBER_OF_NOT_MANAGED_FILES << m_otherFiles.size() << endl;

      // We close the global report
      m_mergedReport->close();
    }

    // Check for output folder logs creation
    checkOutputFolder(ui->lineEdit_outputLogs->text());
  }
  else
  {
    qDebug() << "MainWindow::checkFiles => m_ruleChoiceDialog is null";
  }
}

void MainWindow::launchCommonCheck(AbstractVerifFiles *p_verifFile)
{
  if(m_ruleChoiceDialog->getAccoladeCheckBoxState())
  {
    // Check for accolade problem into code
    p_verifFile->verifyAccolade();
    // Set a boolean to display the popup if rule is not respected
    m_displayAccoladeRule |= p_verifFile->hasAccoladeProblem();
  }
  if(m_ruleChoiceDialog->getCamelCaseCheckBoxState())
  {
    // Check for camel case problem into code
    p_verifFile->verifyCamelCase();
    // Set a boolean to display the popup if rule is not respected
    m_displayCamelCaseRule |= p_verifFile->hasCamelCaseProblem();
  }
  if(m_ruleChoiceDialog->getMagicNumberCheckBoxState())
  {
    // Check for magic number problem into code
    p_verifFile->verifyMagicNumber();
    // Set a boolean to display the popup if rule is not respected
    m_displayMagicNumberRule |= p_verifFile->hasMagicNumberProblem();
  }
  if(m_ruleChoiceDialog->getToDoCheckBoxState())
  {
    // Check for TODO problem into code
    p_verifFile->verifyToDo();
    // Set a boolean to display the popup if rule is not respected
    m_displayToDoRule |= p_verifFile->hasToDoProblem();
  }
  // TODO FBE : Add pointer check
}

/**
 * @brief MainWindow::checkInputFolder
 * Each time you modify the input folder path, we check if the input folder exists
 * A tooltip appears and we disable the launchButton when input folder does not exist
 *
 * @param p_inputFolder : the input folder path changed into widget
 */
void MainWindow::checkInputFolder(const QString p_inputFolder)
{
  QPalette l_palette = ui->lineEdit_inputFolder->palette();
  QDir l_inputFolder(p_inputFolder);
  if(l_inputFolder.exists())
  {
    l_palette.setColor(QPalette::Text, QColor(0,0,0));
    ui->lineEdit_inputFolder->setToolTip("");
    ui->pushButton_launchChecks->setEnabled(true);
  }
  else
  {
    l_palette.setColor(QPalette::Text, QColor(255,0,0));
    ui->lineEdit_inputFolder->setToolTip(INPUT_FOLDER_DOES_NOT_EXISTS);
    ui->pushButton_launchChecks->setEnabled(false);
  }
  ui->lineEdit_inputFolder->setPalette(l_palette);
}

/**
 * @brief MainWindow::checkOutputFolder
 * Each time you modify the output folder log path, we check if the output folder exists
 *
 * @param p_outputFolder : the output logs folder path changed into widget
 */
void MainWindow::checkOutputFolder(const QString p_outputFolder)
{
  QPalette l_palette = ui->lineEdit_outputLogs->palette();
  if(p_outputFolder.isEmpty())
  {
    ui->pushButton_openOutputLogs->setEnabled(false);
    ui->pushButton_launchChecks->setEnabled(false);
    l_palette.setColor(QPalette::Text, QColor(255,0,0));
  }
  else
  {
    QDir l_outputFolder(p_outputFolder);
    ui->pushButton_launchChecks->setEnabled(true);
    if(l_outputFolder.exists())
    {
      ui->pushButton_openOutputLogs->setEnabled(true);
      l_palette.setColor(QPalette::Text, QColor(0,0,0));
      ui->lineEdit_outputLogs->setToolTip("");
    }
    else
    {
      ui->pushButton_openOutputLogs->setEnabled(false);
      l_palette.setColor(QPalette::Text, QColor(255,0,0));
      ui->lineEdit_outputLogs->setToolTip(OUTPUT_FOLDER_DOES_NOT_EXISTS);
    }
  }
  ui->lineEdit_outputLogs->setPalette(l_palette);
}

void MainWindow::displayAccoladePopupRule(void)
{
  // Check for m_display boolean to display popup with rules
  if(m_displayAccoladeRule)
  {
    m_accoladeRuleDialog = new RuleDialog(this,
                                          ACCOLADE_RULE_POPUP_TITLE,
                                          ACCOLADE_RULE_POPUP);
    if(nullptr != m_accoladeRuleDialog)
    {
      QObject::connect(m_accoladeRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_accoladeRuleDialog->show();
      // To avoid rule display loop
      m_displayAccoladeRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayAccoladePopupRule => m_accoladeRuleDialog is null !";
    }
  }
}

void MainWindow::displayCamelCaseRule(void)
{
  if(m_displayCamelCaseRule)
  {
    m_camelCaseRuleDialog = new RuleDialog(this,
                                           CAMEL_CASE_RULE_POPUP_TITLE,
                                           CAMEL_CASE_RULE_POPUP);
    if(nullptr != m_camelCaseRuleDialog)
    {
      QObject::connect(m_camelCaseRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_camelCaseRuleDialog->show();
      // To avoid rule display loop
      m_displayCamelCaseRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayCamelCaseRule => m_camelCaseRuleDialog is null !";
    }
  }
}

void MainWindow::displayMagicNumberRule(void)
{
  if(m_displayMagicNumberRule)
  {
    m_magicNumberRuleDialog = new RuleDialog(this,
                                             MAGIC_NUMBER_RULE_POPUP_TITLE,
                                             MAGIC_NUMBER_RULE_POPUP,
                                             MAGIC_NUMBER_RULE_EXAMPLE,
                                             MAGIC_NUMBER_RULE_EXPLANATION);
    if(nullptr != m_magicNumberRuleDialog)
    {
      QObject::connect(m_magicNumberRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_magicNumberRuleDialog->show();
      // To avoid rule display loop
      m_displayMagicNumberRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayMagicNumberRule => m_magicNumberRuleDialog is null !";
    }
  }
}

void MainWindow::displayToDoRule(void)
{
  if(m_displayToDoRule)
  {
    m_todoRuleDialog = new RuleDialog(this,
                                      TODO_RULE_POPUP_TITLE,
                                      TODO_RULE_POPUP);
    if(nullptr != m_todoRuleDialog)
    {
      QObject::connect(m_todoRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_todoRuleDialog->show();
      // To avoid rule display loop
      m_displayToDoRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayTODORule => m_todoRuleDialog is null !";
    }
  }
}

void MainWindow::displayPointerRule(void)
{
  if(m_displayPointerRule)
  {
    m_pointerRuleDialog = new RuleDialog(this,
                                         POINTER_RULE_POPUP_TITLE,
                                         POINTER_RULE_POPUP);
    if(nullptr != m_pointerRuleDialog)
    {
      QObject::connect(m_pointerRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_pointerRuleDialog->show();
      // To avoid rule display loop
      m_displayPointerRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayPointerRule => m_pointerRuleDialog is null !";
    }
  }
}

void MainWindow::displayHRule(void)
{
  if(m_displayHRule)
  {
    m_hFileRuleDialog = new RuleDialog(this,
                                       H_RULE_POPUP_TITLE,
                                       H_RULE_POPUP);
    if(nullptr != m_hFileRuleDialog)
    {
      QObject::connect(m_hFileRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(couldDisplayNextRule(QString)));
      m_hFileRuleDialog->show();
      // To avoid rule display loop
      m_displayHRule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayHRule => m_todoRuleDialog is null !";
    }
  }
}

// TODO add missing rules
//...

void MainWindow::displayFirstRule(void)
{
  bool l_firstRuleToDisplay = false;
  if(m_displayAccoladeRule)
  {
    l_firstRuleToDisplay = true;
    displayAccoladePopupRule();
  }
  if(!l_firstRuleToDisplay)
  {
    if(m_displayCamelCaseRule)
    {
      l_firstRuleToDisplay = true;
      displayCamelCaseRule();
    }
  }
  if(!l_firstRuleToDisplay)
  {
    if(m_displayHRule)
    {
      l_firstRuleToDisplay = true;
      displayHRule();
    }
  }
  if(!l_firstRuleToDisplay)
  {
    if(m_displayMagicNumberRule)
    {
      l_firstRuleToDisplay = true;
      displayMagicNumberRule();
    }
  }
  if(!l_firstRuleToDisplay)
  {
    if(m_displayToDoRule)
    {
      l_firstRuleToDisplay = true;
      displayToDoRule();
    }
  }
  if(!l_firstRuleToDisplay)
  {
    if(m_displayPointerRule)
    {
      l_firstRuleToDisplay = true;

    }
  }
  // TODO Add missing rules
}

void MainWindow::couldDisplayFirstRule(const int p_progressBarValue)
{
  if(ui->progressBar_checkRules->maximum() == p_progressBarValue)
  {
    displayFirstRule();
  }
}

void MainWindow::couldDisplayNextRule(const QString p_popupTitle)
{
  qDebug() << "MainWindow::couldDisplayNextRule => p_popupTitle = " << p_popupTitle;
  bool l_nextRuleToDisplay = false;
  if(0 == p_popupTitle.compare(ACCOLADE_RULE_POPUP_TITLE))
  {
    if(m_displayCamelCaseRule)
    {
      l_nextRuleToDisplay = true;
      displayCamelCaseRule();
    }
  }
  if(!l_nextRuleToDisplay || 0 == p_popupTitle.compare(CAMEL_CASE_RULE_POPUP_TITLE))
  {
    if(m_displayHRule)
    {
      l_nextRuleToDisplay = true;
      displayHRule();
    }
  }
  if(!l_nextRuleToDisplay || 0 == p_popupTitle.compare(H_RULE_POPUP_TITLE))
  {
    if(m_displayMagicNumberRule)
    {
      l_nextRuleToDisplay = true;
      displayMagicNumberRule();
    }
  }
  if(!l_nextRuleToDisplay || 0 == p_popupTitle.compare(MAGIC_NUMBER_RULE_POPUP_TITLE))
  {
    if(m_displayToDoRule)
    {
      l_nextRuleToDisplay = true;
      displayToDoRule();
    }
  }
  // TODO Add missing rules
  if(!l_nextRuleToDisplay || 0 == p_popupTitle.compare(TODO_RULE_POPUP_TITLE))
  {
    if(!m_cFiles.isEmpty() || !m_cppFiles.isEmpty())
    {
      launchCppCheck();
    }
    if(!m_javaFiles.isEmpty())
    {
      launchCheckStyle();
    }
  }
}

/**
 * @brief MainWindow::launchCppCheck
 * Launch cppCheck for C and Cpp projects
 */
void MainWindow::launchCppCheck(void)
{
  if(nullptr != m_toolParameterDialog)
  {
    QString l_cppCheckPath = m_toolParameterDialog->getCPPCheckPath();
    if(l_cppCheckPath.isEmpty())
    {
      l_cppCheckPath = CPP_CHECK_DEFAULT_PATH;
    }
    Utils::launchCppCheck(l_cppCheckPath, ui->lineEdit_inputFolder->text());
  }
}

/**
 * @brief MainWindow::launchCheckStyle
 * Launch checkStyle for Java projects
 */
void MainWindow::launchCheckStyle(void)
{
  if(nullptr != m_toolParameterDialog)
  {
    QString l_checkStylePath = m_toolParameterDialog->getCheckStylePath();
    if(l_checkStylePath.isEmpty())
    {
      l_checkStylePath = CHECK_STYLE_DEFAULT_PATH;
    }
    Utils::launchCheckStyle(l_checkStylePath, ui->lineEdit_inputFolder->text());
  }
}

/**
 * @brief MainWindow::displayAbout
 * Display about popup
 */
void MainWindow::displayAbout(void)
{
  AboutDialog *l_aboutDialog = new AboutDialog(this);
  if(nullptr != l_aboutDialog)
  {
    l_aboutDialog->show();
  }
}

/**
 * @brief MainWindow::loadConfigurationFile
 * Load info into HMI from config file
 */
void MainWindow::loadConfigurationFile(void)
{
  //QSettings l_settings(":/ConfigFile.ini", QSettings::IniFormat);
  QSettings l_settings("config/config.ini", QSettings::IniFormat);
  l_settings.beginGroup(CONFIG_HMI);
  QString l_inputFolder = l_settings.value(INPUT_FOLDER_CONFIGURATION).toString();
  if(!l_inputFolder.isEmpty())
  {
    ui->lineEdit_inputFolder->setText(l_inputFolder);
  }
  QString l_outputLogsFolder = l_settings.value(REPORT_FOLDER_CONFIGURATION).toString();
  if(!l_outputLogsFolder.isEmpty())
  {
    ui->lineEdit_outputLogs->setText(l_outputLogsFolder);
  }
  l_settings.endGroup();

  // External tools configuration
  l_settings.beginGroup(CONFIG_EXTERNAL_TOOL);
  QString l_excelPath = l_settings.value(INPUT_EXCEL_PATH_CONFIGURATION).toString();
  QString l_cppCheckPath = l_settings.value(INPUT_CPP_CHECK_PATH_CONFIGURATION).toString();
  QString l_checkStylePath = l_settings.value(INPUT_CHECK_STYLE_PATH_CONFIGURATION).toString();
  if(nullptr != m_toolParameterDialog)
  {
    if(!l_excelPath.isEmpty())
    {
      m_toolParameterDialog->setExcelPath(l_excelPath);
    }
    if(!l_cppCheckPath.isEmpty())
    {
      m_toolParameterDialog->setCPPCheckPath(l_cppCheckPath);
    }
    if(!l_checkStylePath.isEmpty())
    {
      m_toolParameterDialog->setCheckStylePath(l_checkStylePath);
    }
  }
  l_settings.endGroup();

  l_settings.beginGroup(CONFIG_RULES);
  // Common rules
  bool l_accoladeCheckBoxState = l_settings.value(VERIFY_ACCOLADE_CONFIGURATION).toBool();
  bool l_magicNumberCheckBoxState = l_settings.value(VERIFY_MAGIC_NUMBER_CONFIGURATION).toBool();
  bool l_camelCaseCheckBoxState = l_settings.value(VERIFY_CAMEL_CASE_CONFIGURATION).toBool();
  bool l_conditionCheckBoxState = l_settings.value(VERIFY_CONDITION_CONFIGURATION).toBool();
  bool l_orphanFunctionCheckBoxState = l_settings.value(VERIFY_ORPHAN_FUNCTION_CONFIGURATION).toBool();
  bool l_pointerCheckBoxState = l_settings.value(VERIFY_POINTER_CONFIGURATION).toBool();
  bool l_toDoCheckBoxState = l_settings.value(VERIFY_TODO_CONFIGURATION).toBool();

  // C specific rules
  bool l_hFileForCCheckBoxState = l_settings.value(VERIFY_H_FILE_FOR_C).toBool();

  // Cpp specific rules
  bool l_hFileForCppCheckBoxState = l_settings.value(VERIFY_H_FILE_FOR_CPP).toBool();
  if(nullptr != m_ruleChoiceDialog)
  {
    m_ruleChoiceDialog->setAccoladeCheckBoxState(l_accoladeCheckBoxState);
    m_ruleChoiceDialog->setMagicNumberCheckBoxState(l_magicNumberCheckBoxState);
    m_ruleChoiceDialog->setCamelCaseCheckBoxState(l_camelCaseCheckBoxState);
    m_ruleChoiceDialog->setConditionCheckBoxState(l_conditionCheckBoxState);
    m_ruleChoiceDialog->setOrphanFunctionCheckBoxState(l_orphanFunctionCheckBoxState);
    m_ruleChoiceDialog->setPointerCheckBoxState(l_pointerCheckBoxState);
    m_ruleChoiceDialog->setToDoCheckBoxState(l_toDoCheckBoxState);

    m_ruleChoiceDialog->setHFileForCCheckBoxState(l_hFileForCCheckBoxState);

    m_ruleChoiceDialog->setHFileForCppCheckBoxState(l_hFileForCppCheckBoxState);
  }
  l_settings.endGroup();
}

/**
 * @brief MainWindow::saveConfigurationFile
 * Save information from HMI to config file
 */
void MainWindow::saveConfigurationFile(void)
{
  if(!ui->lineEdit_inputFolder->text().isEmpty())
  {
    QSettings l_settings("config/config.ini", QSettings::IniFormat);
    l_settings.beginGroup(CONFIG_HMI);
    l_settings.setValue(INPUT_FOLDER_CONFIGURATION, ui->lineEdit_inputFolder->text());
    l_settings.setValue(REPORT_FOLDER_CONFIGURATION, ui->lineEdit_outputLogs->text());
    l_settings.endGroup();

    // External tools configuration
    l_settings.beginGroup(CONFIG_EXTERNAL_TOOL);
    if(nullptr != m_toolParameterDialog)
    {
      l_settings.setValue(INPUT_EXCEL_PATH_CONFIGURATION, m_toolParameterDialog->getExcelPath());
      l_settings.setValue(INPUT_CPP_CHECK_PATH_CONFIGURATION, m_toolParameterDialog->getCPPCheckPath());
      l_settings.setValue(INPUT_CHECK_STYLE_PATH_CONFIGURATION, m_toolParameterDialog->getCheckStylePath());
    }
    l_settings.endGroup();

    l_settings.beginGroup(CONFIG_RULES);
    if(nullptr != m_ruleChoiceDialog)
    {
      // Common rules
      l_settings.setValue(VERIFY_ACCOLADE_CONFIGURATION, m_ruleChoiceDialog->getAccoladeCheckBoxState());
      l_settings.setValue(VERIFY_MAGIC_NUMBER_CONFIGURATION, m_ruleChoiceDialog->getMagicNumberCheckBoxState());
      l_settings.setValue(VERIFY_CAMEL_CASE_CONFIGURATION, m_ruleChoiceDialog->getCamelCaseCheckBoxState());
      l_settings.setValue(VERIFY_CONDITION_CONFIGURATION, m_ruleChoiceDialog->getConditionCheckBoxState());
      l_settings.setValue(VERIFY_ORPHAN_FUNCTION_CONFIGURATION, m_ruleChoiceDialog->getOrphanFunctionCheckBoxState());
      l_settings.setValue(VERIFY_POINTER_CONFIGURATION, m_ruleChoiceDialog->getPointerCheckBoxState());
      l_settings.setValue(VERIFY_TODO_CONFIGURATION, m_ruleChoiceDialog->getToDoCheckBoxState());

      // C specific rules
      l_settings.setValue(VERIFY_H_FILE_FOR_C, m_ruleChoiceDialog->getHFileForCCheckBoxState());

      // Cpp specific rules
      l_settings.setValue(VERIFY_H_FILE_FOR_CPP, m_ruleChoiceDialog->getHFileForCppCheckBoxState());
    }
    else
    {
      qDebug() << "m_ruleChoiceDialog is null !";
    }
    l_settings.endGroup();
  }
}

/**
 * @brief MainWindow::saveConfigurationFileAndQuit
 * Call saveConfigurationFile to save IHM modification and quit application
 */
void MainWindow::saveConfigurationFileAndQuit(void)
{
  saveConfigurationFile();
  QApplication::quit();
}

/**
 * @brief MainWindow::closeEvent
 * Catch close event from close button and Menu->Quitter
 *
 * @param p_event
 */
void MainWindow::closeEvent(QCloseEvent *p_event)
{
  p_event->accept();
  saveConfigurationFile();
}

/**
 * @brief MainWindow::manageCodingRules
 * Display the Coding rules popup, to permit choice on rules to check
 */
void MainWindow::manageCodingRules(void)
{
  if(nullptr != m_ruleChoiceDialog)
  {
    m_ruleChoiceDialog->show();
  }
  else
  {
    qDebug() << "MainWindow::manageCodingRules => m_ruleChoiceDialog is null !";
  }
}

/**
 * @brief MainWindow::manageCodingRules
 * Display the external popup, to permit choice the path to different tools
 */
void MainWindow::manageExternalTools(void)
{
  if(nullptr != m_toolParameterDialog)
  {
    m_toolParameterDialog->show();
  }
  else
  {
    qDebug() << "MainWindow::manageExternalTools => m_toolParameterDialog is null !";
  }
}

/**
 * @brief MainWindow::downloadCheckListFile
 * Download checkFile, to be filled by developper
 */
void MainWindow::downloadCheckListFile(void)
{
  if(nullptr != m_toolParameterDialog)
  {
    QString l_excelPath = m_toolParameterDialog->getExcelPath();
    if(l_excelPath.isEmpty())
    {
      l_excelPath = EXCEL_DEFAULT_PATH;
    }
    QFile l_checkListFile(":/input/CheckListFile");
    if(l_checkListFile.exists())
    {
      Utils::launchExcel(l_excelPath, l_checkListFile.fileName());
    }
    else
    {
      qDebug() << "Le fichier Checklist n'existe pas dans " << l_checkListFile.fileName();
    }
  }
}

/**
 * @brief MainWindow::applyFontsOnMenu
 * Apply font on menu for this main window
 */
void MainWindow::applyFontsOnMenu(void)
{
  QFont l_fontMenu;
  l_fontMenu.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontMenu.setPointSize(MENU_FONT_SIZE);

  ui->menuFichier->setFont(l_fontMenu);
  ui->menuConfiguration->setFont(l_fontMenu);
  ui->menuAide->setFont(l_fontMenu);
  ui->actionEnregistrer_la_configuration->setFont(l_fontMenu);
  ui->actionOuvrir_la_configuration->setFont(l_fontMenu);
  ui->actionQuitter->setFont(l_fontMenu);
  ui->actionParametrage_des_regles_de_codage->setFont(l_fontMenu);
  ui->actionA_propos->setFont(l_fontMenu);
}

/**
 * @brief MainWindow::applyFontsOnLabels
 * Apply font on all labels for this main window
 */
void MainWindow::applyFontsOnLabels(void)
{
  QFont l_fontEnonce;
  l_fontEnonce.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontEnonce.setPointSize(ENONCE_FONT_SIZE);
  l_fontEnonce.setBold(true);

  ui->label_inputPath->setFont(l_fontEnonce);
  ui->label_outputLogs->setFont(l_fontEnonce);
  ui->label_mergeAllReports->setFont(l_fontEnonce);
  ui->label_inputPath->setStyleSheet(LABEL_COLOR);
  ui->label_outputLogs->setStyleSheet(LABEL_COLOR);
  ui->label_mergeAllReports->setStyleSheet(LABEL_COLOR);
}

/**
 * @brief MainWindow::applyFontsOnButtons
 * Apply font on all buttons for this main window
 */
void MainWindow::applyFontsOnButtons(void)
{
  QFont l_fontQPushButton;
  l_fontQPushButton.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQPushButton.setPointSize(PUSHBUTTON_FONT_SIZE);

  ui->pushButton_browseInputFolder->setFont(l_fontQPushButton);
  ui->pushButton_browserOutputLogs->setFont(l_fontQPushButton);
  ui->pushButton_openOutputLogs->setFont(l_fontQPushButton);
  ui->pushButton_launchChecks->setFont(l_fontQPushButton);
}

/**
 * @brief MainWindow::applyFontsOnLineEdits
 * Apply font on lineEdit for this main window
 */
void MainWindow::applyFontsOnLineEdits(void)
{
  QFont l_fontQLineEdit;
  l_fontQLineEdit.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQLineEdit.setPointSize(LINEEDIT_FONT_SIZE);

  ui->lineEdit_inputFolder->setFont(l_fontQLineEdit);
  ui->lineEdit_outputLogs->setFont(l_fontQLineEdit);
}

/**
 * @brief MainWindow::incrementProgressBar
 * Increment each time a file is parsed
 */
void MainWindow::incrementProgressBar(void)
{
  m_counterFileChecked = m_counterFileChecked + 1;
  ui->progressBar_checkRules->setValue(m_counterFileChecked);
}
