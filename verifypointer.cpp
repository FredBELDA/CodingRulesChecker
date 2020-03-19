#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "utils.h"
#include "verifypointer.h"

VerifyPointer::VerifyPointer(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + POINTER_FILE_NAME;
}

void VerifyPointer::checkForPointer(void)
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
        // TODO

        l_lineNumber += 1;
      }

      l_file.close();
    }
    qDebug() << "TODO VerifyCamelCase::checkForCamelCase";
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }
}
