#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "verifyaccolade.h"

VerifyAccolade::VerifyAccolade(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + ACCOLADE_FILE_NAME;
}

void VerifyAccolade::checkForAccolade(void)
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
          if(l_line.contains(OPENED_ACCOLADE) && ! l_line.startsWith(OPENED_ACCOLADE))
          {
            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                              l_line + FILE_SEPARATOR +
                              ACCOLADE_IS_NOT_ONLY + "\n");
          }
          if(l_line.contains(CLOSED_ACCOLADE) && ! l_line.startsWith(CLOSED_ACCOLADE))
          {
            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                              l_line + FILE_SEPARATOR +
                              ACCOLADE_IS_NOT_ONLY + "\n");
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
