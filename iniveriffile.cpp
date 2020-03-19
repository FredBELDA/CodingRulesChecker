#include <QSettings>

#include "iniveriffile.h"

IniVerifFile::IniVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_outputLogsPath = p_outputLogsPath;
}

bool IniVerifFile::isIniFile(void)
{
  bool l_returnValue = false;
  QSettings l_settingsFile(m_fileToAnalyse, QSettings::IniFormat);
  QStringList l_keys = l_settingsFile.allKeys();
  if(!l_keys.isEmpty())
  {
    l_returnValue = true;
  }
  return l_returnValue;
}
