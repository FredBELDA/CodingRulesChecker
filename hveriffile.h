#ifndef HVERIFFILE_H
#define HVERIFFILE_H

#include "abstractcfamilyveriffiles.h"

class HVerifFile : public AbstractCFamilyVerifFiles
{
public:
  HVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  QStringList getPointerDeclaration(void);
};

#endif // HVERIFFILE_H
