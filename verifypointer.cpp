#include <QDebug>
#include <QFile>
#include <QMap>
#include <QTextStream>

#include "commonelements.h"
#include "utils.h"
#include "verifypointer.h"

VerifyPointer::VerifyPointer(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + POINTER_FILE_NAME;
}

void VerifyPointer::checkForPointer(const QStringList p_pointerDeclaration)
{
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
      QMap<QString, int> l_mapIfStatements;
      int l_lineNumber = 1;
      int l_braceCounter = 0;
      while(! l_in.atEnd())
      {
        l_line = l_in.readLine();
        l_line = l_line.trimmed();
        l_line = l_line.simplified();
        if(!Utils::isComment(l_line) &&
           !Utils::isDefine(l_line) &&
           !Utils::isImport(l_line)
           )
        {
          if(l_line.contains(SEARCH_FOR_OPENED_ACCOLADE))
          {
            l_braceCounter += 1;
          }
          if(l_line.contains(SEARCH_FOR_CLOSED_ACCOLADE))
          {
            l_braceCounter -= 1;
            QMapIterator<QString, int> i(l_mapIfStatements);
            while (i.hasNext())
            {
              i.next();
              if(i.value() > l_braceCounter)
              {
                l_mapIfStatements.remove(i.key());
              }
            }
          }
          if(Utils::isPointerTest(l_line))
          {
            l_mapIfStatements.insert(l_line, l_braceCounter + 1);
          }
          else
          {
            foreach (QString ptr, p_pointerDeclaration)
            {
              if(l_line.contains(ptr) &&
                 !Utils::isVariableDeclaration(l_line) &&
                 !Utils::isPointerInit(l_line))
              {
                if(l_mapIfStatements.keys().filter(ptr).isEmpty())
                {
                  m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                    l_line + FILE_SEPARATOR + MAJOR + FILE_SEPARATOR +
                                    + POINTER_IS_NOT_TESTED + "\n");
                }
              }
            }
          }
        }
        l_lineNumber += 1;
      }
      l_file.close();
    }
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }
}
