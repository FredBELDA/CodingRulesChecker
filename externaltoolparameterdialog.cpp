#include <QDebug>
#include <QFileDialog>

#include "commonelements.h"
#include "externaltoolparameterdialog.h"
#include "ui_externaltoolparameterdialog.h"
#include "utils.h"

ExternalToolParameterDialog::ExternalToolParameterDialog(QWidget *p_parent) :
  QDialog(p_parent),
  ui(new Ui::ExternalToolParameterDialog)
{
  ui->setupUi(this);
  windowParameter(this);
  initWidgets();
  connectWidgets();
  applyStyle();
}

ExternalToolParameterDialog::~ExternalToolParameterDialog()
{
  if(nullptr != ui)
  {
    delete ui;
    ui = nullptr;
  }
}

/**
 * @brief ExternalToolParameterDialog::windowParameter
 * Parameter the popup (size, title, ...)
 *
 * @param p_widget : the popup object
 */
void ExternalToolParameterDialog::windowParameter(QWidget *p_widget)
{
  if(nullptr != p_widget)
  {
    p_widget->setWindowTitle(EXTERNAL_TOOL_POPUP_TITLE);
    p_widget->resize(EXTERNAL_TOOL_POPUP_WIDTH, EXTERNAL_TOOL_POPUP_HEIGHT);
    p_widget->setFixedSize(QSize(EXTERNAL_TOOL_POPUP_WIDTH, EXTERNAL_TOOL_POPUP_HEIGHT));

    ui->verticalLayout->setGeometry(QRect(X_SHIFT,
                                          Y_SHIFT,
                                          EXTERNAL_TOOL_POPUP_VERTICAL_LAYOUT_WIDTH,
                                          EXTERNAL_TOOL_POPUP_VERTICAL_LAYOUT_HEIGHT)
                                    );
  }
  else
  {
    qDebug() << "RuleChoiceDialog::windowParameter() => p_widget is null !";
  }
}

/**
 * @brief ExternalToolParameterDialog::initWidgets
 * Init text for popup
 */
void ExternalToolParameterDialog::initWidgets(void)
{
  ui->label_excelPath->setText(EXCEL_PATH_LABEL);
  ui->label_cppCheckPath->setText(CPP_CHECK_PATH_LABEL);
  ui->label_checkStylePath->setText(CHECK_STYLE_PATH_LABEL);
  ui->pushButton_parcourirExcel->setText(BROWSE_FOLDER);
  ui->pushButton_parcourirCPPCheck->setText(BROWSE_FOLDER);
  ui->pushButton_parcourirCheckStyle->setText(BROWSE_FOLDER);
  ui->pushButton_valider->setText(SAVE);
  ui->pushButton_annuler->setText(QUIT);
}

/**
 * @brief ExternalToolParameterDialog::connectWidgets : Connect widgets to actions
 */
void ExternalToolParameterDialog::connectWidgets(void)
{
  connect(ui->pushButton_parcourirExcel, SIGNAL(clicked()), this, SLOT(fillExcelPath()));
  connect(ui->pushButton_parcourirCPPCheck, SIGNAL(clicked()), this, SLOT(fillCPPCheckPath()));
  connect(ui->pushButton_parcourirCheckStyle, SIGNAL(clicked()), this, SLOT(fillCheckStylePath()));
  connect(ui->lineEdit_excelPath, SIGNAL(textChanged(QString)), this, SLOT(checkExcelPath(QString)));
  connect(ui->lineEdit_cppCheckPath, SIGNAL(textChanged(QString)), this, SLOT(checkCPPCheckPath(QString)));
  connect(ui->lineEdit_checkStylePath, SIGNAL(textChanged(QString)), this, SLOT(checkCheckStylePath(QString)));
  connect(ui->pushButton_valider, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui->pushButton_annuler, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * @brief ExternalToolParameterDialog::applyStyle
 * Apply different style on widget (label and button)
 */
void ExternalToolParameterDialog::applyStyle(void)
{
  //Apply font on labels
  applyFontsOnLabels();
  // Apply font on pushButton
  applyFontsOnButtons();
}

/**
 * @brief ExternalToolParameterDialog::applyFontsOnLabels
 * Apply font on all labels for this popup
 */
void ExternalToolParameterDialog::applyFontsOnLabels(void)
{
  QFont l_fontEnonce;
  l_fontEnonce.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontEnonce.setPointSize(ENONCE_FONT_SIZE);
  l_fontEnonce.setBold(true);

  ui->label_excelPath->setFont(l_fontEnonce);
  ui->label_cppCheckPath->setFont(l_fontEnonce);
  ui->label_checkStylePath->setFont(l_fontEnonce);
  ui->label_excelPath->setStyleSheet(LABEL_COLOR);
  ui->label_cppCheckPath->setStyleSheet(LABEL_COLOR);
  ui->label_checkStylePath->setStyleSheet(LABEL_COLOR);
}

/**
 * @brief ExternalToolParameterDialog::applyFontsOnButtons
 * Apply font on all buttons for this popup
 */
void ExternalToolParameterDialog::applyFontsOnButtons(void)
{
  QFont l_fontQPushButton;
  l_fontQPushButton.setFamily(QStringLiteral(FONT_DECLARATION));
  l_fontQPushButton.setPointSize(PUSHBUTTON_FONT_SIZE);

  ui->pushButton_parcourirExcel->setFont(l_fontQPushButton);
  ui->pushButton_parcourirCPPCheck->setFont(l_fontQPushButton);
  ui->pushButton_parcourirCheckStyle->setFont(l_fontQPushButton);
  ui->pushButton_valider->setFont(l_fontQPushButton);
  ui->pushButton_annuler->setFont(l_fontQPushButton);
}

/**
 * \brief Browse folder to Excel application.
 *
 * \param void.
 * \return void.
 */
void ExternalToolParameterDialog::fillExcelPath(void)
{
  QFileDialog l_dialog;
  QString l_path = "";

  l_dialog.setViewMode(QFileDialog::Detail);
  l_path = QFileDialog::getOpenFileName(this,
                                        INPUT_EXCEL_PATH,
                                        ui->lineEdit_excelPath->text().isEmpty() ? QDir::currentPath() : ui->lineEdit_excelPath->text(),
                                        EXCEL_FILTER
                                        );

  if(0 < l_path)
  {
    ui->lineEdit_excelPath->setText(l_path);
  }
}

/**
 * \brief Browse folder to CPP_Check application.
 *
 * \param void.
 * \return void.
 */
void ExternalToolParameterDialog::fillCPPCheckPath(void)
{
  QFileDialog l_dialog;
  QString l_path = "";

  l_dialog.setViewMode(QFileDialog::Detail);
  l_path = QFileDialog::getOpenFileName(this,
                                        INPUT_CPP_CHECK_PATH,
                                        ui->lineEdit_cppCheckPath->text().isEmpty() ? QDir::currentPath() : ui->lineEdit_cppCheckPath->text(),
                                        CPP_CHECK_FILTER
                                        );

  if(0 < l_path)
  {
    ui->lineEdit_cppCheckPath->setText(l_path);
  }
}

/**
 * \brief Browse folder to CheckStyle application.
 *
 * \param void.
 * \return void.
 */
void ExternalToolParameterDialog::fillCheckStylePath(void)
{
  QFileDialog l_dialog;
  QString l_path = "";

  l_dialog.setViewMode(QFileDialog::Detail);
  l_path = QFileDialog::getOpenFileName(this,
                                        INPUT_CHECK_STYLE_PATH,
                                        ui->lineEdit_checkStylePath->text().isEmpty() ? QDir::currentPath() : ui->lineEdit_checkStylePath->text(),
                                        CHECK_STYLE_FILTER
                                        );

  if(0 < l_path)
  {
    ui->lineEdit_checkStylePath->setText(l_path);
  }
}

void ExternalToolParameterDialog::checkExcelPath(const QString p_excelPath)
{
  genericCheckPath(ui->lineEdit_excelPath, p_excelPath, EXCEL_PATH_NOT_EXISTS);
}

void ExternalToolParameterDialog::checkCPPCheckPath(const QString p_cppCheckPath)
{
  genericCheckPath(ui->lineEdit_cppCheckPath, p_cppCheckPath, CPP_CHECK_PATH_NOT_EXISTS);
}

void ExternalToolParameterDialog::checkCheckStylePath(const QString p_checkStylePath)
{
  genericCheckPath(ui->lineEdit_checkStylePath, p_checkStylePath, CHECK_STYLE_PATH_NOT_EXISTS);
}

void ExternalToolParameterDialog::genericCheckPath(QLineEdit *p_lineEdit, const QString p_pathToCheck, const QString p_errorMessage)
{
  if(nullptr != p_lineEdit)
  {
    QPalette l_palette = p_lineEdit->palette();
    if(p_pathToCheck.isEmpty())
    {
      l_palette.setColor(QPalette::Text, QColor(255,0,0));
    }
    else
    {
      QFile l_checkStyleFile(p_pathToCheck);
      if(l_checkStyleFile.exists())
      {
        p_lineEdit->setToolTip("");
        l_palette.setColor(QPalette::Text, QColor(0,0,0));
      }
      else
      {
        p_lineEdit->setToolTip(p_errorMessage);
        l_palette.setColor(QPalette::Text, QColor(255,0,0));
      }
    }
    p_lineEdit->setPalette(l_palette);
  }
  else
  {
    qDebug() << "ExternalToolParameterDialog::genericCheckPath => p_lineEdit is null";
  }
}

QString ExternalToolParameterDialog::getExcelPath(void)
{
  return ui->lineEdit_excelPath->text();
}

void ExternalToolParameterDialog::setExcelPath(const QString p_excelPath)
{
  ui->lineEdit_excelPath->setText(p_excelPath);
}

QString ExternalToolParameterDialog::getCPPCheckPath(void)
{
  return ui->lineEdit_cppCheckPath->text();
}

void ExternalToolParameterDialog::setCPPCheckPath(const QString p_cppCheckPath)
{
  ui->lineEdit_cppCheckPath->setText(p_cppCheckPath);
}

QString ExternalToolParameterDialog::getCheckStylePath(void)
{
  return ui->lineEdit_checkStylePath->text();
}

void ExternalToolParameterDialog::setCheckStylePath(const QString p_checkStylePath)
{
  ui->lineEdit_checkStylePath->setText(p_checkStylePath);
}
