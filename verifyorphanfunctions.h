#ifndef VERIFYORPHANFUNCTIONS_H
#define VERIFYORPHANFUNCTIONS_H

#include "abstractveriffilerules.h"

class VerifyOrphanFunctions : public AbstractVerifFileRules
{
public:
  VerifyOrphanFunctions(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForOrphanFunctions(QMap<QString, int>);
};

#endif // VERIFYORPHANFUNCTIONS_H
