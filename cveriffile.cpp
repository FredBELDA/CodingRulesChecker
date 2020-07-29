#include <QStringList>
#include <QFile>

#include "cveriffile.h"
#include "utils.h"

CVerifFile::CVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_outputLogsPath = p_outputLogsPath;
}

QStringList CVerifFile::getPointerDeclarationList(void)
{
    qDebug() << "CVerifFile::GetPointerDecclarationList" ;
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
        l_returnValue = Utils::getPointerDeclarationList(&l_file);
      }
      l_file.close();
    }
    else
    {
      qDebug() << "m_reportFileName is empty !";
    }
    qDebug() << "CVerifFile l_returnValue: " << l_returnValue;
    return l_returnValue;
}
