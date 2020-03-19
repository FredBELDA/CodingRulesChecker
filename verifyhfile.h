#ifndef VERIFYHFILE_H
#define VERIFYHFILE_H

#include "abstractveriffilerules.h"

class VerifyHFile : public AbstractVerifFileRules
{
public:
  VerifyHFile(const QString p_fileToAnalyse, const QString p_outputLogsPath, const QStringList p_hFilesList);

  void checkForHFile(void);

private:
  QStringList m_hFilesList;
};

#endif // VERIFYHFILE_H
