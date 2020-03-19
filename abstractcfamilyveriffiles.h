#ifndef ABSTRACTCFAMILYVERIFFILES_H
#define ABSTRACTCFAMILYVERIFFILES_H

#include "abstractveriffiles.h"

class AbstractCFamilyVerifFiles : public AbstractVerifFiles
{
public:
  explicit AbstractCFamilyVerifFiles();

  void verifyHFile(const QStringList p_hFilesList);
  bool hasHFileProblem(void);

protected:
  bool m_HFileProblem;
};

#endif // ABSTRACTCFAMILYVERIFFILES_H
