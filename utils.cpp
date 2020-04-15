#include <QDebug>
#include <QFile>
#include <QString>

#include "utils.h"

QString Utils::formatPath(const QString p_path)
{
  QString returnValue = p_path;
  if(returnValue.contains("\\"))
  {
    returnValue.replace("\\", "/");
  }
  return returnValue;
}

QString Utils::formatPathForCmd(const QString p_path)
{
  QString returnValue = p_path;
  if(returnValue.contains("/"))
  {
    returnValue.replace("/", "\\");
  }
  return returnValue;
}

QString Utils::extractFileName(const QString p_path)
{
  QString returnValue = "";
  int lastIndexOf = 0;
  if(p_path.contains("\\"))
  {
    lastIndexOf = p_path.lastIndexOf("\\");
  }
  if(p_path.contains("/"))
  {
    lastIndexOf = p_path.lastIndexOf("/");
  }
  returnValue = p_path.mid(lastIndexOf + 1);
  return returnValue;
}

void Utils::launchCppCheck(const QString p_cppCheckPath, const QString p_pathToCheck)
{
  QString l_cppCheckQString = QString(p_cppCheckPath);
  QString l_cppCheckPath = l_cppCheckQString.replace("\"", "");
  QFile l_cppCheckPathFile(formatPath(l_cppCheckPath));
  if(l_cppCheckPathFile.exists())
  {
    QString l_cppCheck = QString(p_cppCheckPath) + " " + p_pathToCheck;
    system(l_cppCheck.toStdString().c_str());
  }
}

void Utils::launchCheckStyle(const QString p_checkStylePath, const QString p_pathToCheck)
{
  qDebug() << "Utils::launchCheckStyle => p_checkStylePath = " << p_checkStylePath << " - p_pathToCheck = " << p_pathToCheck;
  QString l_checkStyleQString = QString(p_checkStylePath);
  QString l_checkStylePath = l_checkStyleQString.replace("\"", "");
  QFile l_checkStylePathFile(formatPath(l_checkStylePath));
  if(l_checkStylePathFile.exists())
  {
    QString l_checkStyle = QString(l_checkStylePath) + " " + p_pathToCheck;
    system(l_checkStyle.toStdString().c_str());
  }
}

void Utils::launchExcel(const QString p_excelPath, const QString p_excelFile)
{
  qDebug() << "Utils::launchExcel => p_excelPath = " << p_excelPath << " - p_excelFile = " << p_excelFile;
  QString l_excelQString = QString(p_excelPath);
  QString l_excelPath = l_excelQString.replace("\"", "");
  QFile l_excelPathFile(formatPath(l_excelPath));
  if(l_excelPathFile.exists())
  {
    QString l_excel = QString(l_excelPath) + " " + p_excelFile;
    system(l_excel.toStdString().c_str());
  }
}

bool Utils::isComment(const QString p_line)
{
  bool l_returnValue = false;
  if(p_line.startsWith("/*") || p_line.startsWith("*") || p_line.endsWith("*/") || p_line.startsWith("//"))
  {
    l_returnValue = true;
  }

  return l_returnValue;
}

bool Utils::isImport(const QString p_line)
{
  bool l_returnValue = false;
  if(p_line.startsWith("#include"))
  {
    l_returnValue = true;
  }

  return l_returnValue;
}

bool Utils::isDigit(const QString p_line)
{
  bool l_ok;
  // We check the value is 10 base value
  int l_value = p_line.toInt(&l_ok, 10);
  if(!l_ok)
  {
    // We check the value is 16 base value
    l_value = p_line.toInt(&l_ok, 16);
  }

  if(0 == l_value)
  {
    l_ok = false;
  }
  return l_ok;
}

QStringList Utils::scanForVariableDeclaration(const QString p_line)
{
  QStringList l_returnValue;
  QStringList l_list = p_line.split(SEARCH_FOR_EQUALS);
  QString l_declaration = "";
  if(NB_MIN_ELTS <= l_list.size())
  {
    l_declaration = l_list.at(0);
    QStringList l_variables = l_declaration.split(SEARCH_FOR_SPACE);
    if(!l_variables.isEmpty())
    {
      foreach(QString l_variableName, l_variables)
      {
        if(l_variableName.contains(UINT_DECLARATION)   ||
           l_variableName.contains(INT_DECLARATION)    ||
           l_variableName.contains(DOUBLE_DECLARATION) ||
           l_variableName.contains(SHORT_DECLARATION)  ||
           l_variableName.contains(FLOAT_DECLARATION)  ||
           l_variableName.contains(BOOL_DECLARATION)   ||
           l_variableName.contains(CHAR_DECLARATION)   ||
           l_variableName.contains(LONG_DECLARATION)   ||
           (l_variableName.contains(UINT_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(INT_DECLARATION)    && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(DOUBLE_DECLARATION) && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(SHORT_DECLARATION)  && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(FLOAT_DECLARATION)  && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(BOOL_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(CHAR_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
           (l_variableName.contains(LONG_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
           // For Qt object
           (l_variableName.startsWith("Q") && l_variableName.at(1).isUpper())
          )
        {
          l_returnValue.append(l_list);
        }
      }
    }
  }
  return l_returnValue;
}

QStringList Utils::scanForPointerDeclaration(const QString p_line)
{
  QStringList l_returnValue;
  bool l_isDeclaration = false;
  bool l_isPointer = false;
  QStringList l_variables = p_line.split(SEARCH_FOR_SPACE);
  if(!l_variables.isEmpty())
  {
    foreach(QString l_variableName, l_variables)
    {
      // We check one element of line is a declaration
      if((l_variableName.contains(UINT_DECLARATION))  ||
         (l_variableName.contains(INT_DECLARATION))   ||
         (l_variableName.contains(DOUBLE_DECLARATION))||
         (l_variableName.contains(SHORT_DECLARATION)) ||
         (l_variableName.contains(FLOAT_DECLARATION)) ||
         (l_variableName.contains(BOOL_DECLARATION))  ||
         (l_variableName.contains(CHAR_DECLARATION))  ||
         (l_variableName.contains(LONG_DECLARATION))  ||
         // For Qt object
         (l_variableName.startsWith("Q") && l_variableName.at(1).isUpper())
        )
      {
        l_isDeclaration = true;
      }
      // We check one element of line is a pointer
      // char* toto or char *toto or char * toto
      if(l_variableName.contains(POINTER_DECLARATION))
      {
        l_isPointer = true;
      }
    }
    if(l_isPointer && l_isDeclaration)
    {
      qDebug() << "Utils::scanForPointerDeclaration => p_line = " << p_line;
      l_returnValue.append(p_line);
    }
  }
  return l_returnValue;
}

bool Utils::scanForMagicNumber(const QString p_line)
{
  bool l_returnValue = false;
  if(!Utils::isImport(p_line) && !Utils::isComment(p_line))
  {
    QStringList l_variables = p_line.split(SEARCH_FOR_SEMICOLON);
    if(!l_variables.isEmpty())
    {
      foreach(QString l_variableName, l_variables)
      {
        QStringList l_rightValue = l_variableName.split(SEARCH_FOR_EQUALS);
        if(NB_MIN_ELTS <= l_rightValue.size())
        {
          l_returnValue = Utils::isDigit(l_rightValue.at(1));
        }
        l_rightValue = l_variableName.split(SEARCH_FOR_INFERIOR);
        if(NB_MIN_ELTS <= l_rightValue.size())
        {
          l_returnValue = Utils::isDigit(l_rightValue.at(1));
        }
        l_rightValue = l_variableName.split(SEARCH_FOR_SUPERIOR);
        if(NB_MIN_ELTS <= l_rightValue.size())
        {
          l_returnValue = Utils::isDigit(l_rightValue.at(1));
        }
      }
    }
  }

  return l_returnValue;
}
