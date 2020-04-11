#ifndef VERIFYACCOLADE_H
#define VERIFYACCOLADE_H

#include <QFile>

#include "abstractveriffilerules.h"

#define FOR_INSTRUCTION "for"
#define WHILE_INSTRUCTION "while"
#define IF_INSTRUCTION "if"
#define ELSE_INSTRUCTION "else"
#define ELIF_INSTRUCTION "elif"
#define FOREACH_INSTRUCTION "foreach"

#define OPENED_ACCOLADE "{"
#define CLOSED_ACCOLADE "}"

class VerifyAccolade : public AbstractVerifFileRules
{
public:
  VerifyAccolade(const QString p_fileToAnalyse, const QString p_outputLogsPath);

  void checkForAccolade(void);
};

#endif // VERIFYACCOLADE_H
