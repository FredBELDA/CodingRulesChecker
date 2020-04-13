#ifndef VERIFYPOINTER_H
#define VERIFYPOINTER_H

#include "abstractveriffilerules.h"

class VerifyPointer : public AbstractVerifFileRules
{
public:
  VerifyPointer(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForPointer(const QStringList p_pointerDeclaration);
};

#endif // VERIFYPOINTER_H
