#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "utils.h"
#include "verifytodo.h"

VerifyToDo::VerifyToDo(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + TODO_FILE_NAME;
}

void VerifyToDo::checkForToDo(void)
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
      int l_lineNumber = 1;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
          // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
          l_line = l_line.simplified();
          if(Utils::isComment(l_line) &&
             (l_line.toLower().contains(SEARCH_FOR_TODO) || l_line.toLower().contains(SEARCH_FOR_TODO_SECOND))
            )
          {
            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                              l_line + FILE_SEPARATOR +
                              TODO_MUST_SUPPRESS + "\n");
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
