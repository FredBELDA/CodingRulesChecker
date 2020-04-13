#ifndef VERIFYACCOLADE_H
#define VERIFYACCOLADE_H

#include <QFile>

#include "abstractveriffilerules.h"

class VerifyAccolade : public AbstractVerifFileRules
{
public:
  VerifyAccolade(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForAccolade(void);
};

#endif // VERIFYACCOLADE_H
