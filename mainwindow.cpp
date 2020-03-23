#include <QDate>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <string.h>

#include "cveriffile.h"
#include "cppveriffile.h"
#include "hveriffile.h"
#include "javaveriffile.h"
#include "iniveriffile.h"
#include "utils.h"

#include "commonelements.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
  initVariables();
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
    p_mainWindow->setWindowTitle(WINDOW_TITLE);
    p_mainWindow->resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    p_mainWindow->setFixedSize(QSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT));

    ui->verticalLayoutWidget->setGeometry(QRect(10, 10, MAIN_VERTICAL_LAYOUT_WIDTH, MAIN_VERTICAL_LAYOUT_HEIGHT));
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
  ui->label_inputPath->setText(INPUT_LABEL_TEXT);
  ui->label_outputLogs->setText(OUTPUT_LABEL_TEXT);
  ui->label_mergeAllReports->setText(CHECKBOX_MERGE_REPORTS);
  ui->label_logoAKKA->setText("");
  ui->label_logoThales->setText("");
  QPixmap l_logo_AKKA(":/AKKA_Logo.png");
  int l_logo_AKKA_Width = ui->label_logoAKKA->width();
  int l_logo_AKKA_Height = ui->label_logoAKKA->height();
  ui->label_logoAKKA->setPixmap(l_logo_AKKA.scaled(l_logo_AKKA_Width,
                                                   l_logo_AKKA_Height,
                                                   Qt::KeepAspectRatio)
                                );
  ui->label_logoAKKA->setAlignment(Qt::AlignCenter);
  QPixmap l_logo_Thales(":/Thales_Logo.png");
  int l_logo_Thales_Width = ui->label_logoThales->width();
  int l_logo_Thales_Height = ui->label_logoThales->height();
  ui->label_logoThales->setPixmap(l_logo_Thales.scaled(l_logo_Thales_Width,
                                                       l_logo_Thales_Height,
                                                       Qt::KeepAspectRatio)
                                  );
  ui->label_logoThales->setAlignment(Qt::AlignCenter);
  ui->pushButton_browseInputFolder->setText(BROWSE_FOLDER);
  ui->pushButton_browserOutputLogs->setText(BROWSE_FOLDER);
  ui->pushButton_LaunchChecks->setText(LAUNCH_CHECK);
}

/**
 * \brief Connect all signals to slots.
 *
 * \param void.
 * \return void.
 */
void MainWindow::connectWidgets(void)
{
  QObject::connect(ui->pushButton_browseInputFolder, SIGNAL(clicked()), this, SLOT(fillInputFolder()));
  QObject::connect(ui->pushButton_browserOutputLogs, SIGNAL(clicked()), this, SLOT(fillOutputLogs()));
  QObject::connect(ui->pushButton_LaunchChecks, SIGNAL(clicked()), this, SLOT(parseFolder()));
  QObject::connect(ui->pushButton_OpenOutputLogs, SIGNAL(clicked()), this, SLOT(openFolder()));
  QObject::connect(ui->lineEdit_outputLogs, SIGNAL(textChanged(QString)), this, SLOT(checkOutputFolder(QString)));
  // File menu
  QObject::connect(ui->actionOuvrir_la_configuration, SIGNAL(triggered(bool)), this, SLOT(loadConfigurationFile(bool)));
  QObject::connect(ui->actionEnregistrer_la_configuration, SIGNAL(triggered(bool)), this, SLOT(saveConfigurationFile(bool)));
  // Help menu
  QObject::connect(ui->actionA_propos, SIGNAL(triggered(bool)), this, SLOT(displayAbout(bool)));

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

  m_displayAccoladeRule = false;
  m_displayCamelCaseRule = false;
  m_displayConditionsRule = false;
  m_displayHRule = false;
  m_displayMagicNumberRule = false;
  m_displayOrphanFunctionsRule = false;
  m_displayPointerRule = false;
  m_displayTODORule = false;

  m_accoladeRuleDialog = nullptr;
  m_camelCaseRuleDialog = nullptr;
  m_conditionsRuleDialog = nullptr;
  m_hFileRuleDialog = nullptr;
  m_magicNumberRuleDialog = nullptr;
  m_orphanFunctionsRuleDialog = nullptr;
  m_pointerRuleDialog = nullptr;
  m_todoRuleDialog = nullptr;

  checkOutputFolder(ui->lineEdit_outputLogs->text());
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
                                             QDir::currentPath(),
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
                                             QDir::currentPath(),
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
    if(ui->checkBox_MergeAllReports->isChecked())
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
  foreach (QString l_cFile, m_cFiles)
  {
    CVerifFile *l_cVerifFile = new CVerifFile(l_cFile, ui->lineEdit_outputLogs->text());
    if(nullptr != l_cVerifFile)
    {
      // Check for accolade problem into code
      l_cVerifFile->verifyAccolade();
      // Set a boolean to display the popup if rule is not respected
      m_displayAccoladeRule |= l_cVerifFile->hasAccoladeProblem();
      // Check for camel case problem into code
      l_cVerifFile->verifyCamelCase();
      // Set a boolean to display the popup if rule is not respected
      m_displayCamelCaseRule |= l_cVerifFile->hasCamelCaseProblem();
      // Check for H file presence
      l_cVerifFile->verifyHFile(m_hFiles);
      // Set a boolean to display the popup if rule is not respected
      m_displayHRule |= l_cVerifFile->hasHFileProblem();
      // Check for magic number problem into code
      l_cVerifFile->verifyMagicNumber();
      // Set a boolean to display the popup if rule is not respected
      m_displayMagicNumberRule |= l_cVerifFile->hasMagicNumberProblem();
      // Check for TODO problem into code
      l_cVerifFile->verifyTODO();
      m_displayTODORule |= l_cVerifFile->hasTODOProblem();
    }
    else
    {
      qDebug() << "l_cVerifFile is not created !";
    }
  }

  foreach (QString l_cppFile, m_cppFiles)
  {
    CppVerifFile *l_cppVerifFile = new CppVerifFile(l_cppFile, ui->lineEdit_outputLogs->text());
    if(nullptr != l_cppVerifFile)
    {
      // Check for accolade problem into code
      l_cppVerifFile->verifyAccolade();
      // Set a boolean to display the popup if rule is not respected
      m_displayAccoladeRule |= l_cppVerifFile->hasAccoladeProblem();
      // Check for camel case problem into code
      l_cppVerifFile->verifyCamelCase();
      // Set a boolean to display the popup if rule is not respected
      m_displayCamelCaseRule |= l_cppVerifFile->hasCamelCaseProblem();
      // Check for H file presence
      l_cppVerifFile->verifyHFile(m_hFiles);
      // Set a boolean to display the popup if rule is not respected
      m_displayHRule |= l_cppVerifFile->hasHFileProblem();
      // Check for magic number problem into code
      l_cppVerifFile->verifyMagicNumber();
      // Set a boolean to display the popup if rule is not respected
      m_displayMagicNumberRule |= l_cppVerifFile->hasMagicNumberProblem();
      // Check for TODO problem into code
      l_cppVerifFile->verifyTODO();
      // Set a boolean to display the popup if rule is not respected
      m_displayTODORule |= l_cppVerifFile->hasTODOProblem();
    }
    else
    {
      qDebug() << "l_cppVerifFile is not created !";
    }
  }

  foreach (QString l_javaFile, m_javaFiles)
  {
    JavaVerifFile *l_javaVerifFile = new JavaVerifFile(l_javaFile, ui->lineEdit_outputLogs->text());
    if(nullptr != l_javaVerifFile)
    {
      // Check for accolade problem into code
      l_javaVerifFile->verifyAccolade();
      // Set a boolean to display the popup if rule is not respected
      m_displayAccoladeRule |= l_javaVerifFile->hasAccoladeProblem();
      // Check for camel case problem into code
      l_javaVerifFile->verifyCamelCase();
      // Set a boolean to display the popup if rule is not respected
      m_displayCamelCaseRule |= l_javaVerifFile->hasCamelCaseProblem();
      // Check for magic number problem into code
      l_javaVerifFile->verifyMagicNumber();
      m_displayMagicNumberRule |= l_javaVerifFile->hasMagicNumberProblem();
      // Check for TODO problem into code
      l_javaVerifFile->verifyTODO();
      // Set a boolean to display the popup if rule is not respected
      m_displayTODORule |= l_javaVerifFile->hasTODOProblem();
    }
    else
    {
      qDebug() << "l_javaVerifFile is not created !";
    }
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
  }

  // Launch cppCheck if c or cpp files
  if(!m_cFiles.isEmpty() || !m_cppFiles.isEmpty())
  {
    foreach (QString l_hFile, m_hFiles)
    {
      HVerifFile *l_hVerifFile = new HVerifFile(l_hFile, ui->lineEdit_outputLogs->text());
      if(nullptr != l_hVerifFile)
      {
        l_hVerifFile->verifyAccolade();
        l_hVerifFile->verifyCamelCase();
        l_hVerifFile->verifyMagicNumber();
        l_hVerifFile->verifyTODO();
      }
      else
      {
        qDebug() << "l_hVerifFile is not created !";
      }
    }
  }

  displayFirstRule();

  if(ui->checkBox_MergeAllReports->isChecked())
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

/**
 * @brief MainWindow::checkOutputFolder
 * Each time you modify the output folder log path, we check if the output folder exists
 *
 * @param p_outputFolder : the output logs folder path changed into widget
 */
void MainWindow::checkOutputFolder(const QString p_outputFolder)
{
  qDebug() << "MainWindow::checkOutputFolder => p_outputFolder = " << p_outputFolder;
  if(p_outputFolder.isEmpty())
  {
    ui->pushButton_OpenOutputLogs->setEnabled(false);
    ui->pushButton_LaunchChecks->setEnabled(false);
  }
  else
  {
    QDir l_outputFolder(p_outputFolder);
    qDebug() << "MainWindow::checkOutputFolder => l_outputFolder.exists() = " << l_outputFolder.exists();
    ui->pushButton_LaunchChecks->setEnabled(true);
    if(l_outputFolder.exists())
    {
      ui->pushButton_OpenOutputLogs->setEnabled(true);
    }
    else
    {
      ui->pushButton_OpenOutputLogs->setEnabled(false);
    }
  }
}

void MainWindow::displayAccoladePopupRule(void)
{
  // Check for m_display boolean to display popup with rules
  if(m_displayAccoladeRule)
  {
    m_accoladeRuleDialog = new RuleDialog(this, ACCOLADE_RULE_POPUP_TITLE, ACCOLADE_RULE_POPUP);
    if(nullptr != m_accoladeRuleDialog)
    {
      QObject::connect(m_accoladeRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(displayNextRule(QString)));
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
    m_camelCaseRuleDialog = new RuleDialog(this, CAMEL_CASE_RULE_POPUP_TITLE, CAMEL_CASE_RULE_POPUP);
    if(nullptr != m_camelCaseRuleDialog)
    {
      QObject::connect(m_camelCaseRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(displayNextRule(QString)));
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
    m_magicNumberRuleDialog = new RuleDialog(this, MAGIC_NUMBER_RULE_POPUP_TITLE, MAGIC_NUMBER_RULE_POPUP);
    if(nullptr != m_magicNumberRuleDialog)
    {
      QObject::connect(m_magicNumberRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(displayNextRule(QString)));
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

void MainWindow::displayTODORule(void)
{
  if(m_displayTODORule)
  {
    m_todoRuleDialog = new RuleDialog(this, TODO_RULE_POPUP_TITLE, TODO_RULE_POPUP);
    if(nullptr != m_todoRuleDialog)
    {
      QObject::connect(m_todoRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(displayNextRule(QString)));
      m_todoRuleDialog->show();
      // To avoid rule display loop
      m_displayTODORule = false;
    }
    else
    {
      qDebug() << "MainWindow::displayTODORule => m_todoRuleDialog is null !";
    }
  }
}

void MainWindow::displayHRule(void)
{
  if(m_displayHRule)
  {
    m_hFileRuleDialog = new RuleDialog(this, H_RULE_POPUP_TITLE, H_RULE_POPUP);
    if(nullptr != m_hFileRuleDialog)
    {
      QObject::connect(m_hFileRuleDialog, SIGNAL(popupRead(QString)), this, SLOT(displayNextRule(QString)));
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
    if(m_displayTODORule)
    {
      l_firstRuleToDisplay = true;
      displayTODORule();
    }
  }
  // TODO Add missing rules
}

void MainWindow::displayNextRule(const QString p_popupTitle)
{
  qDebug() << "MainWindow::displayNextRule => p_popupTitle = " << p_popupTitle;
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
    if(m_displayTODORule)
    {
      l_nextRuleToDisplay = true;
      displayTODORule();
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

void MainWindow::launchCppCheck(void)
{
  Utils::launchCppCheck(ui->lineEdit_inputFolder->text());
}

void MainWindow::launchCheckStyle(void)
{
  Utils::launchCheckStyle(ui->lineEdit_inputFolder->text());
}

void MainWindow::displayAbout(const bool p_isChecked)
{
  // TODO FBE : do an about popup
  qDebug() << "MainWindow::displayAbout(void) => p_isChecked=" << p_isChecked;
}

void MainWindow::loadConfigurationFile(const bool p_isChecked)
{
  // TODO FBE
  qDebug() << "MainWindow::loadConfigurationFile(void) => p_isChecked=" << p_isChecked;
}

void MainWindow::saveConfigurationFile(const bool p_isChecked)
{
  // TODO FBE
  qDebug() << "MainWindow::saveConfigurationFile(void) => p_isChecked=" << p_isChecked;
}
