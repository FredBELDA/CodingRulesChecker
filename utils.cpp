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

void Utils::launchCppCheck(const QString p_pathToCheck)
{
  QString l_cppCheckQString = QString(CPP_CHECK_PATH);
  QString l_cppCheckPath = l_cppCheckQString.replace("\"", "");
  QFile l_cppCheckPathFile(formatPath(l_cppCheckPath));
  if(l_cppCheckPathFile.exists())
  {
    QString l_cppCheck = QString(CPP_CHECK_PATH) + " " + p_pathToCheck;
    system(l_cppCheck.toStdString().c_str());
  }
}

void Utils::launchCheckStyle(const QString p_pathToCheck)
{
  qDebug() << "Utils::launchCheckStyle " << p_pathToCheck;
}

QStringList Utils::scanForLine(const QString p_line)
{
  QStringList l_returnValue;
  QStringList l_list = p_line.split(SEARCH_FOR_EQUALS);
  QString l_declaration = "";
  if(NB_MIN_ELTS <= l_list.size())
  {
    l_declaration = l_list.at(0);
    QStringList l_list2 = l_declaration.split(SEARCH_FOR_SPACE);
    if(!l_list2.isEmpty())
    {
      foreach(QString l_elt, l_list2)
      {
        if(l_elt.contains(UINT_DECLARATION)   ||
           l_elt.contains(INT_DECLARATION)    ||
           l_elt.contains(DOUBLE_DECLARATION) ||
           l_elt.contains(SHORT_DECLARATION)  ||
           l_elt.contains(FLOAT_DECLARATION)  ||
           l_elt.contains(BOOL_DECLARATION)   ||
           l_elt.contains(CHAR_DECLARATION)   ||
           l_elt.contains(LONG_DECLARATION)   ||
           (l_elt.contains(UINT_DECLARATION)   && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(INT_DECLARATION)    && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(DOUBLE_DECLARATION) && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(SHORT_DECLARATION)  && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(FLOAT_DECLARATION)  && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(BOOL_DECLARATION)   && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(CHAR_DECLARATION)   && l_elt.contains(POINTEUR_DECLARATION)) ||
           (l_elt.contains(LONG_DECLARATION)   && l_elt.contains(POINTEUR_DECLARATION)) ||
           // For Qt object
           (l_elt.startsWith("Q") && l_elt.at(1).isUpper())
          )
        {
          l_returnValue.append(l_list);
        }
      }
    }
  }
  return l_returnValue;
}
