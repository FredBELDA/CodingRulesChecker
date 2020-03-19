#include "abstractveriffilerules.h"
#include "commonelements.h"
#include "ruledialog.h"

AbstractVerifFileRules::AbstractVerifFileRules()
{
  m_rulePopup = new RuleDialog();
}

AbstractVerifFileRules::~AbstractVerifFileRules()
{
  if(nullptr != m_rulePopup)
  {
    delete(m_rulePopup);
    m_rulePopup = nullptr;
  }
}

void AbstractVerifFileRules::generateReport(void)
{
  if(!m_todoList.isEmpty())
  {
    bool l_openFile = false;
    QFile l_file(m_reportFile);
    // QTextStream object creation from QFile object
    QTextStream l_flux(&l_file);
    // We fix codec before writting
    l_flux.setCodec(CODEC_FOR_EXCEL_FILE);
    if(l_file.exists())
    {
      if(!l_file.open(QFile::Append | QFile::Text))
      {
        qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_WRITING;
      }
      else
      {
        l_openFile = true;
      }
    }
    else
    {
      if(!l_file.open(QFile::WriteOnly | QFile::Text))
      {
        qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_WRITING;
      }
      else
      {
        l_openFile = true;
        l_flux << QString(REPORT_HEADER_FILE) << endl;
      }
    }

    if(l_openFile)
    {
      foreach(QString ligne, m_todoList)
      {
        QStringList l_split = ligne.split(FILE_SEPARATOR);
        l_flux << m_fileToAnalyse << SEARCH_FOR_SEMICOLON;
        for(int i = 0; i < l_split.size(); ++i)
        {
          l_flux << l_split[i];
          if(l_split.size() - 1 > i)
          {
            l_flux << SEARCH_FOR_SEMICOLON;
          }
        }
      }
      l_file.close();
    }
  }
  else
  {
    qDebug() << NO_PROBLEM_FOUND << " " << m_reportFile;
  }
}

int AbstractVerifFileRules::getNbError(void)
{
  return m_todoList.size();
}
