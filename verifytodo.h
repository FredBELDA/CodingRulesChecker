#ifndef VERIFYTODO_H
#define VERIFYTODO_H

#include <QFile>

#include "abstractveriffilerules.h"

class VerifyToDo : public AbstractVerifFileRules
{
public:
  VerifyToDo(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForToDo(void);
};
#endif // VERIFYTODO_H
