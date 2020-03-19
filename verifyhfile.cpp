#include <QFileInfo>

#include "commonelements.h"
#include "utils.h"
#include "verifyhfile.h"

VerifyHFile::VerifyHFile(const QString p_fileToAnalyse, const QString p_outputLogsPath, const QStringList p_hFilesList)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + H_FILE_NAME;
  m_hFilesList = p_hFilesList;
}

void VerifyHFile::checkForHFile(void)
{
  if(!m_fileToAnalyse.isEmpty())
  {
    QFileInfo l_fileToAnalyseInfo(m_fileToAnalyse);
    if(!l_fileToAnalyseInfo.baseName().compare("main"))
    {
      bool l_found = false;
      foreach(QString l_HFile, m_hFilesList)
      {
        QFileInfo l_hFileToAnalyseInfo(l_HFile);
        if(l_fileToAnalyseInfo.baseName().compare(l_hFileToAnalyseInfo.baseName()))
        {
          l_found = true;
          break;
        }
      }
      if(!l_found)
      {
        m_todoList.append(m_fileToAnalyse + FILE_SEPARATOR +
                          DOES_NOT_CONTAINS_H_FILE + "\n");
      }
    }
  }
  else
  {
    qDebug() << "m_reportFileName is empty !";
  }
}
