#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "verifyconditions.h"
#include "utils.h"

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
      bool l_appendCondition = false;
      int l_previousSize = 0;
      int l_lineNumber = 1;
      int l_parenthesisCounter = 0;
      int l_previouslSplitedConditionsSize = 0;
      while(! l_in.atEnd())
      {
          l_line = l_in.readLine();
          l_line = l_line.trimmed();
          // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
          // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
          l_line = l_line.simplified();

          if(!Utils::isComment(l_line))
          {
              if(l_appendCondition)
              {
                  l_parenthesisCounter += l_line.count(SEARCH_FOR_OPENED_PARENTHESIS) -
                                        l_line.count(SEARCH_FOR_CLOSED_PARENTHESIS);

                  l_conditionsStatements[l_conditionsStatements.size()-1].append(l_line);
                  if(0 == l_parenthesisCounter)
                  {
                      l_appendCondition = false;
                  }
              }


              //if(l_line.contains(IF_INSTRUCTION) || l_line.contains(ELIF_INSTRUCTION) || l_line.contains(WHILE_INSTRUCTION))
              if(l_line.contains(QRegExp(REGEX_FOR_INSTRUCTIONS)))
              {
                l_parenthesisCounter = l_line.count(SEARCH_FOR_OPENED_PARENTHESIS) -
                                       l_line.count(SEARCH_FOR_CLOSED_PARENTHESIS);

                //Si besoin pour séparer les for(int i =.... ; cond ; inc)
                //Ajouter que  [1 et 2] ou même la déclaration de variable ?
                QStringList forSplit = l_line.split(SEARCH_FOR_SEMICOLON);
                if(forSplit.size() > 1)
                {
                    l_conditionsStatements.append(forSplit.at(1));
                }
                else
                {
                    l_conditionsStatements.append(forSplit);
                }


                if(0 != l_parenthesisCounter)
                {
                    l_appendCondition = true;
                }
              }
          }
          //qDebug() <<  "l_conditionsStatements: " << l_conditionsStatements;


          if(!l_conditionsStatements.isEmpty() && !l_appendCondition)
          {
              // on fait les tests seulements si un if & à était réellement ajouté
              if(l_previousSize < l_conditionsStatements.size())
              {

                QStringList l_splitedConditions = Utils::splitConditions(l_conditionsStatements);
                l_splitedConditions = Utils::cleanSplitedConditons(l_splitedConditions);
                //qDebug() << "l_splitedConditions: " << l_splitedConditions;

                for(int i = l_previouslSplitedConditionsSize; i < l_splitedConditions.size() && l_previouslSplitedConditionsSize < l_splitedConditions.size(); i++ )
                {
                    QString l_equalCondition = l_splitedConditions.at(i);

                    if(l_equalCondition.contains(QRegExp(REGEX_FOR_CONDITIONS)))
                    {
                        qDebug() << "l_equalCondition condition : " << l_equalCondition;
                    }
                    if(l_equalCondition.count(SEARCH_FOR_EQUALS) >= NB_MIN_ELTS)
                    {
                         QStringList l_checkCondition = l_equalCondition.split(SEARCH_FOR_EQUALS_TEST);

                         if(l_checkCondition.size() >= NB_MIN_ELTS)
                         {
                             //qDebug() << "l_checkCondition: " << l_checkCondition;
                             QString leftPart = l_checkCondition[0];
                             QString rightPart = l_checkCondition[1];
                             bool checkRightPart = rightPart.isUpper() || Utils::isDigit(rightPart) ||
                                     rightPart.contains(FALSE_VALUE) || rightPart.contains(TRUE_VALUE);

                             if(checkRightPart)
                             {
                                 m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                                   l_equalCondition + FILE_SEPARATOR + MINOR + FILE_SEPARATOR +
                                                   + WRONG_CONDITION_ORDER + "\n");
                             }
                         }
                    }
                    else if(!l_equalCondition.contains(QRegExp(REGEX_FOR_CONDITIONS)))
                    {
                        m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                          l_equalCondition + FILE_SEPARATOR + MINOR + FILE_SEPARATOR +
                                          + POSSIBLE_CONDITION_ERROR + "\n");
                    }




                }
                l_previouslSplitedConditionsSize = l_splitedConditions.size();

              }
              l_previousSize = l_conditionsStatements.size();
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
