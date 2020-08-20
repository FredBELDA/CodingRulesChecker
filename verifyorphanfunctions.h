#ifndef VERIFYORPHANFUNCTIONS_H
#define VERIFYORPHANFUNCTIONS_H

#include "abstractveriffilerules.h"

class VerifyOrphanFunctions : public AbstractVerifFileRules
{
public:
  VerifyOrphanFunctions(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  QMap<QString, int> checkForOrphanFunctions(QMap<QString, int> p_functionsMap);

  void UpdateTodoList(QMap<QString, int> p_functionsMap);
};

#endif // VERIFYORPHANFUNCTIONS_H
