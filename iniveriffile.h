#ifndef INIVERFIFILE_H
#define INIVERFIFILE_H

#include "abstractverifconfigfiles.h"

class IniVerifFile : public AbstractVerifConfigFiles
{
public:
  IniVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  bool isIniFile(void);
};

#endif // INIVERFIFILE_H
