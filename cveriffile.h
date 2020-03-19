#ifndef CVERIFFILE_H
#define CVERIFFILE_H

#include "abstractcfamilyveriffiles.h"

class CVerifFile : public AbstractCFamilyVerifFiles
{
public:
  CVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath);
};

#endif // CVERIFFILE_H
