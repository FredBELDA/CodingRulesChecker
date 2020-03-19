#ifndef VERIFYCONDITIONS_H
#define VERIFYCONDITIONS_H

#include "abstractveriffilerules.h"

class VerifyConditions : public AbstractVerifFileRules
{
public:
  VerifyConditions(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForConditions(void);
};

#endif // VERIFYCONDITIONS_H
