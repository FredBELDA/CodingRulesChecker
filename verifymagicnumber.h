#ifndef VERIFYMAGICNUMBER_H
#define VERIFYMAGICNUMBER_H

#include "abstractveriffilerules.h"

class VerifyMagicNumber : public AbstractVerifFileRules
{
public:
  VerifyMagicNumber(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForMagicNumber(void);
};

#endif // VERIFYMAGICNUMBER_H
