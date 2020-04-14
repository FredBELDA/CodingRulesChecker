#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "utils.h"
#include "verifymagicnumber.h"

VerifyMagicNumber::VerifyMagicNumber(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + MAGIC_NUMBER_FILE_NAME;
}

void VerifyMagicNumber::checkForMagicNumber(void)
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
        bool l_hasMagicNumber = Utils::scanForMagicNumber(l_line);
        if(l_hasMagicNumber)
        {
          m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                            l_line + FILE_SEPARATOR +
                            IS_MAGIC_NUMBER + "\n");
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
