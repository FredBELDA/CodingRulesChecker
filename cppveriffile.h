#ifndef CPPVERIFFILE_H
#define CPPVERIFFILE_H

#include "abstractcfamilyveriffiles.h"

class CppVerifFile : public AbstractCFamilyVerifFiles
{
public:
  CppVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath);
};

#endif // CPPVERIFFILE_H
