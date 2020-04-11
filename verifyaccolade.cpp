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
      bool l_beforeOpenedAccolade = false;
      bool l_afterOpenedAccolade = false;
      bool l_beforeClosedAccolade = false;
      bool l_afterClosedAccolade = false;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
          // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
          l_line = l_line.simplified();
          l_beforeOpenedAccolade = false;
          l_afterOpenedAccolade = false;
          l_beforeClosedAccolade = false;
          l_afterClosedAccolade = false;
          if(l_line.contains(OPENED_ACCOLADE))
          {
            // First, we detect if it is into expression, like regexp
            // This expression is surrounded by quotes
            int l_indexOfOpenedAccolade = l_line.indexOf(OPENED_ACCOLADE);
            int l_indexOfQString = 0;
            for (int l_i = 0; l_i < l_line.count(SEARCH_FOR_QUOTATION_MARKS); ++l_i)
            {
              int l_indexOfQuotationMarks = l_line.indexOf(SEARCH_FOR_QUOTATION_MARKS, l_indexOfQString);
              l_indexOfQString = l_indexOfQuotationMarks + 1;
              if(l_indexOfQuotationMarks < l_indexOfOpenedAccolade)
              {
                l_beforeOpenedAccolade = true;
              }
              if(l_indexOfQuotationMarks > l_indexOfOpenedAccolade)
              {
                l_afterOpenedAccolade = true;
              }
              l_i++;
            }
            qDebug() << "VerifyAccolade::checkForAccolade => l_line = " << l_line;
            qDebug() << "l_beforeOpenedAccolade = " << l_beforeOpenedAccolade;
            qDebug() << "l_afterOpenedAccolade = " << l_afterOpenedAccolade;
            if(!l_beforeOpenedAccolade && !l_afterOpenedAccolade)
            {
              qDebug() << "start with accolade = " << l_line.startsWith(OPENED_ACCOLADE);
              // It is not an expression, we check if it start with opened accolade
              if(!l_line.startsWith(OPENED_ACCOLADE))
              {
                m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                  l_line + FILE_SEPARATOR +
                                  ACCOLADE_IS_NOT_ALONE + "\n");
              }
            }
          }
          if(l_line.contains(CLOSED_ACCOLADE))
          {
            // First, we detect if it is into expression, like regexp
            // This expression is surrounded by quotes
            int l_indexOfClosedAccolade = l_line.indexOf(CLOSED_ACCOLADE);
            int l_indexOfQString = 0;
            for (int l_i = 0; l_i < l_line.count(SEARCH_FOR_QUOTATION_MARKS); ++l_i)
            {
              int l_indexOfQuotationMarks = l_line.indexOf(SEARCH_FOR_QUOTATION_MARKS, l_indexOfQString);
              l_indexOfQString = l_indexOfClosedAccolade + 1;
              if(l_indexOfQuotationMarks < l_indexOfClosedAccolade)
              {
                l_beforeClosedAccolade = true;
              }
              if(l_indexOfQuotationMarks > l_indexOfClosedAccolade)
              {
                l_afterClosedAccolade = true;
              }
              l_i++;
            }
            qDebug() << "VerifyAccolade::checkForAccolade => l_line = " << l_line;
            qDebug() << "l_beforeClosedAccolade = " << l_beforeClosedAccolade;
            qDebug() << "l_afterClosedAccolade = " << l_afterClosedAccolade;
            if(!l_beforeClosedAccolade && !l_afterClosedAccolade)
            {
              qDebug() << "start with accolade = " << l_line.startsWith(CLOSED_ACCOLADE);
              // It is not an expression, we check if it start with closed accolade
              if(! l_line.startsWith(CLOSED_ACCOLADE))/* && l_line.contains(SEARCH_FOR_QUOTATION_MARKS))*/
              {
                m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                  l_line + FILE_SEPARATOR +
                                  ACCOLADE_IS_NOT_ALONE + "\n");
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
