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
        QStringList l_declaration = Utils::scanForLine(l_line);
        if(!l_declaration.isEmpty())
        {
          QString l_decl = l_declaration.at(0);
          QString l_value = l_declaration.at(1);
          bool l_ok;
          l_value = l_value.trimmed();
          l_value = l_value.mid(0, l_value.indexOf(SEARCH_FOR_SEMICOLON));
          l_value.toInt(&l_ok, 10);
          if(!l_ok)
          {
            l_value.toInt(&l_ok, 16);
            if(!l_ok)
            {
              if(l_value.compare(FALSE_VALUE, Qt::CaseInsensitive) || l_value.compare(TRUE_VALUE, Qt::CaseInsensitive))
              {
                // Do nothing
              }
              else
              {
                qDebug() << "l_value : " << l_value << " is not recognized !";
              }
            }
            else
            {
              m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                l_decl + " = " + l_value + FILE_SEPARATOR +
                                IS_MAGIC_NUMBER + "\n");
            }
          }
          else
          {
            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                              l_decl + " = " + l_value + FILE_SEPARATOR +
                              IS_MAGIC_NUMBER + "\n");
          }
          qDebug() << "VerifyMagicNumber::checkForMagicNumber => l_value = " << l_value;
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
