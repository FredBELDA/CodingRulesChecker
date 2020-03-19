#ifndef VERIFYCAMELCASE_H
#define VERIFYCAMELCASE_H

#include "abstractveriffilerules.h"

class VerifyCamelCase : public AbstractVerifFileRules
{
public:
  VerifyCamelCase(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForCamelCase(void);
};

#endif // VERIFYCAMELCASE_H
