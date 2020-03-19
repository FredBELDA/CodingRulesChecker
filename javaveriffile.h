#ifndef JAVAVERIFFILE_H
#define JAVAVERIFFILE_H

#include "abstractveriffiles.h"

class JavaVerifFile : public AbstractVerifFiles
{
public:
  JavaVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void launchCheckStyle(void);
};

#endif // JAVAVERIFFILE_H
