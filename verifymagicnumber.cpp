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
        QStringList l_declaration = Utils::scanForLine(l_line);
        if(!l_declaration.isEmpty())
        {
          QString l_decl = l_declaration.at(0);
          QString l_value = l_declaration.at(1);
          bool l_ok;
          l_value = l_value.trimmed();
          qDebug() << "VerifyMagicNumber::checkForMagicNumber => l_decl = "
                   << l_decl << " l_value = " << l_value;
          l_value = l_value.mid(0, l_value.indexOf(SEARCH_FOR_SEMICOLON));
          qDebug() << "l_value = " << l_value;
          // We check the value is 10 base value
          l_value.toInt(&l_ok, 10);
          qDebug() << "base 10 ok => " << l_ok;
          if(!l_ok)
          {
            // We check the value is 16 base value
            l_value.toInt(&l_ok, 16);
            qDebug() << "base 16 ok => " << l_ok;
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
              // Check if the initialize value is 0, we admit it, otherwise, we detect a magic number
              if(0 != l_value.toInt(0,16))
              {
                m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                  l_decl + " = " + l_value + FILE_SEPARATOR +
                                  IS_MAGIC_NUMBER + "\n");
              }
            }
          }
          else
          {
            // Check if the initialize value is 0, we admit it, otherwise, we detect a magic number
            if(0 != l_value.toInt(0,10))
            {
              m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                l_decl + " = " + l_value + FILE_SEPARATOR +
                                IS_MAGIC_NUMBER + "\n");
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
