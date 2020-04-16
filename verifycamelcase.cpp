#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "utils.h"
#include "verifycamelcase.h"

VerifyCamelCase::VerifyCamelCase(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + CAMEL_CASE_FILE_NAME;
}

void VerifyCamelCase::checkForCamelCase(void)
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
        QStringList l_declaration = Utils::scanForVariableDeclaration(l_line);
        if(!l_declaration.isEmpty())
        {
          foreach(QString l_elt, l_declaration)
          {
            // We forgot cast declaration for example : (int) toto
            if(!l_elt.contains(SEARCH_FOR_OPENED_PARENTHESIS) && !l_elt.contains(SEARCH_FOR_CLOSED_PARENTHESIS) &&
               !l_elt.contains(SEARCH_FOR_COMMA) && !l_elt.contains(SEARCH_FOR_SEMICOLON) && !l_elt.isEmpty() &&
               NB_MAX_DECLARATION_SIZE >= l_declaration.size()
              )
            {
              l_elt = l_elt.trimmed();
              // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
              // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
              l_elt = l_elt.simplified();
              qDebug() << "l_elt = " << l_elt;
              QStringList l_variableDeclaration = l_elt.split(SEARCH_FOR_COMMA);
              if(!l_variableDeclaration.isEmpty())
              {
                foreach(QString l_variableElt, l_variableDeclaration)
                {
                  QStringList l_variables = l_variableElt.split(SEARCH_FOR_SPACE);
                  if(!l_variables.isEmpty())
                  {
                    foreach(QString l_variableName, l_variables)
                    {
                      qDebug() << "foreach : l_variableName = " << l_variableName;
                      if(l_variableName.contains(CONST_DECLARATION)    ||
                         l_variableName.contains(POINTER_DECLARATION) ||
                         l_variableName.contains(UNSIGNED_DECLARATION) ||
                         l_variableName.contains(UINT_DECLARATION)     ||
                         l_variableName.contains(INT_DECLARATION)      ||
                         l_variableName.contains(DOUBLE_DECLARATION)   ||
                         l_variableName.contains(SHORT_DECLARATION)    ||
                         l_variableName.contains(FLOAT_DECLARATION)    ||
                         l_variableName.contains(BOOL_DECLARATION)     ||
                         l_variableName.contains(CHAR_DECLARATION)     ||
                         l_variableName.contains(LONG_DECLARATION)     ||
                         (l_variableName.contains(UINT_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(INT_DECLARATION)    && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(DOUBLE_DECLARATION) && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(SHORT_DECLARATION)  && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(FLOAT_DECLARATION)  && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(BOOL_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(CHAR_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
                         (l_variableName.contains(LONG_DECLARATION)   && l_variableName.contains(POINTER_DECLARATION)) ||
                         // For Qt object
                         (l_variableName.startsWith("Q") && l_variableName.at(1).isUpper()))
                      {
                        // Do nothing
                      }
                      else
                      {
                        qDebug() << "else check for declaration : l_variableName = " << l_variableName;
                        QChar l_firstCharacter = '\0';
                        QStringList l_splitDeclaration = l_variableName.split(SEARCH_FOR_UNDERSCORE);
                        qDebug() << "Split l_variableName on _ => size = " << l_splitDeclaration.size();
                        if(1 == l_splitDeclaration.size())
                        {
                          QString l_variableComplementaryDeclaration = l_splitDeclaration.at(0);
                          qDebug() << "l_variableComplementaryDeclaration = " << l_variableComplementaryDeclaration;
                          l_firstCharacter = l_variableComplementaryDeclaration.at(0);
                          if(l_firstCharacter.isPunct())
                          {
                            if(1 < l_variableComplementaryDeclaration.size())
                            {
                              l_firstCharacter = l_variableComplementaryDeclaration.at(1);
                            }
                          }
                          if(!l_firstCharacter.isLower())
                          {
                            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                              l_variableComplementaryDeclaration + FILE_SEPARATOR + CRITIC + FILE_SEPARATOR +
                                              DOES_NOT_RESPECT_CAMEL_CASE_SYNTAX + "\n");
                          }
                        }
                        else if(2 == l_splitDeclaration.size())
                        {
                          QString l_prefix = l_splitDeclaration.at(0);
                          QString l_variableComplementaryDeclaration = l_splitDeclaration.at(1);
                          qDebug() << "l_prefix = " << l_prefix;
                          qDebug() << "l_variableComplementaryDeclaration = " << l_variableComplementaryDeclaration;
                          l_firstCharacter = l_variableComplementaryDeclaration.at(0);
                          if(0 == l_prefix.compare("l", Qt::CaseInsensitive) || 0 == l_prefix.compare("g", Qt::CaseInsensitive) ||
                             0 == l_prefix.compare("m", Qt::CaseInsensitive) || 0 == l_prefix.compare("p", Qt::CaseInsensitive)
                             )
                          {
                            // Do nothing
                          }
                          else
                          {
                            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                              l_variableName + FILE_SEPARATOR + CRITIC + FILE_SEPARATOR +
                                              DOES_NOT_RESPECT_PERIMETER_SYNTAX + "\n");
                          }
                          if(!l_firstCharacter.isLower())
                          {
                            m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                              l_variableName + FILE_SEPARATOR + CRITIC + FILE_SEPARATOR +
                                              DOES_NOT_RESPECT_CAMEL_CASE_SYNTAX + "\n");
                          }
                        }
                        else
                        {
                          qDebug() << "else : l_variableName = " << l_variableName;
                          m_todoList.append(QString::number(l_lineNumber) + FILE_SEPARATOR +
                                            l_variableName + FILE_SEPARATOR + CRITIC + FILE_SEPARATOR +
                                            DOES_NOT_RESPECT_CAMEL_CASE_SYNTAX + "\n");
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          qDebug() << "----------------------------------";
        }
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
