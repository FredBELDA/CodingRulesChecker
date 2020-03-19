#ifndef VERIFFILERULES_H
#define VERIFFILERULES_H

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

#include "ruledialog.h"

class AbstractVerifFileRules
{
public:
  explicit AbstractVerifFileRules();
  ~AbstractVerifFileRules();

  void generateReport(void);
  int getNbError(void);

protected:
  QString m_fileToAnalyse;
  QString m_reportFile;
  QStringList m_todoList;

  RuleDialog *m_rulePopup;
};

#endif // VERIFFILERULES_H
