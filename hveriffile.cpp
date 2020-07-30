#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "hveriffile.h"
#include "utils.h"

HVerifFile::HVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_outputLogsPath = p_outputLogsPath;
}

QStringList HVerifFile::getPointerDeclarationList(void)
{
  qDebug() << "HVerifFile::getPointerDeclarationList" ;
  QStringList l_returnValue = QStringList();
  if(!m_fileToAnalyse.isEmpty())
  {
    QString l_fromNativeSeparators = QDir::fromNativeSeparators(m_fileToAnalyse);
    QFile l_file(l_fromNativeSeparators);
    if(!l_file.exists())
    {
      qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_READING;
    }
    else
    {
      l_returnValue = Utils::getPointerDeclarationList(l_file);
    }
    l_file.close();
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }

  return l_returnValue;
}

QStringList HVerifFile::getFunctionDeclarationList(void)
{
  QStringList l_returnValue = QStringList();
  if(!m_fileToAnalyse.isEmpty())
  {
    QFile l_file(m_fileToAnalyse);
    if(!l_file.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_READING;
    }
    else
    {
      QTextStream l_in(&l_file);
      QString l_line;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          l_line = l_line.simplified();
          // Filter lines to exclude comment and functions declaration
          if(!Utils::isComment(l_line) &&
             l_line.contains(SEARCH_FOR_OPENED_PARENTHESIS) &&
             l_line.contains(SEARCH_FOR_CLOSED_PARENTHESIS)
             )
          {
            QStringList l_declaration = Utils::scanForVariableDeclaration(l_line);
            if(!l_declaration.isEmpty())
            {
              l_returnValue.append(l_line);
            }
          }
      }
    }
    l_file.close();
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }

  return l_returnValue;
}

QStringList HVerifFile::getDefineDeclarationList(void)
{
  QStringList l_returnValue = QStringList();
  if(!m_fileToAnalyse.isEmpty())
  {
    QFile l_file(m_fileToAnalyse);
    if(!l_file.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_READING;
    }
    else
    {
      QTextStream l_in(&l_file);
      QString l_line;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          l_line = l_line.simplified();
          // Filter lines to exclude comment and functions declaration
          if(Utils::isDefine(l_line))
          {
            QString l_defineDeclaration = Utils::scanForDefineDeclaration(l_line);
            if(!l_defineDeclaration.isEmpty())
            {
              l_returnValue.append(l_line);
            }
          }
      }
    }
    l_file.close();
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }

  return l_returnValue;
}
