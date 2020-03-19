#ifndef UTILS_H
#define UTILS_H

#include <QFile>

#include "abstractveriffilerules.h"

class VerifyToDo : public AbstractVerifFileRules
{
public:
  VerifyToDo(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForToDo(void);
};
#endif // UTILS_H
