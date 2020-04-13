#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "commonelements.h"
#include "hveriffile.h"
#include "utils.h"

HVerifFile::HVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_outputLogsPath = p_outputLogsPath;
}

QStringList HVerifFile::getPointerDeclarationList(void)
{
  QStringList l_returnValue = QStringList();
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
          l_line = l_line.simplified();
          // Filter lines to exclude comment and functions declaration
          if(!Utils::isComment(l_line) &&
             !l_line.contains(SEARCH_FOR_OPENED_PARENTHESIS) &&
             !l_line.contains(SEARCH_FOR_CLOSED_PARENTHESIS)
             )
          {
            QStringList l_declaration = Utils::scanForPointerDeclaration(l_line);
            if(!l_declaration.isEmpty())
            {
              // We keep only the name declaration
              QStringList l_names = l_line.split(POINTER_DECLARATION);
              if(!l_names.isEmpty())
              {
                // We keep the declaration
                // char* l_params; => variable name = l_params; => Suppress ";"
                QString l_variableName = l_names.at(1);
                l_variableName = l_variableName.replace(SEARCH_FOR_SEMICOLON, "");
                l_returnValue.append(l_variableName);
              }
            }
          }

          l_lineNumber += 1;
      }
    }
    l_file.close();
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }

  return l_returnValue;
}
