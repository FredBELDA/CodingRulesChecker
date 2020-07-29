#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "verifyconditions.h"

VerifyConditions::VerifyConditions(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + CONDITIONS_FILE_NAME;
}

void VerifyConditions::checkForConditions(void)
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
      QStringList l_conditionsStatements;
      int l_lineNumber = 1;
      int l_parenthesisCounter = 0;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
          // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
          l_line = l_line.simplified();

          if(l_parenthesisCounter > 0)
          {
              l_conditionsStatements[l_conditionsStatements.size()-1].append(l_line);

              l_parenthesisCounter = l_line.count(SEARCH_FOR_OPENED_PARENTHESIS) -
                      l_line.count(SEARCH_FOR_CLOSED_PARENTHESIS);
              if(-1 == l_parenthesisCounter)
              {
                  l_parenthesisCounter = 0;
              }
          }
          qDebug() <<  "l_conditionsStatements: " << l_conditionsStatements;
          if(l_line.contains(IF_INSTRUCTION) || l_line.contains(ELIF_INSTRUCTION) || l_line.contains(WHILE_INSTRUCTION))
          {
              l_parenthesisCounter = l_line.count(SEARCH_FOR_OPENED_PARENTHESIS) -
                      l_line.count(SEARCH_FOR_CLOSED_PARENTHESIS);

              //todo il faut tester les fins de lignes si elle contiennent assez de () et qu'elles ne finissent pas par | ou &
              l_conditionsStatements.append(l_line);
            qDebug() << "l_line: " << l_line;
            qDebug() << "l_parenthesisCounter: " << l_parenthesisCounter;

          }
          if(l_line.contains(FOR_INSTRUCTION))
          {
            // TODO
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
