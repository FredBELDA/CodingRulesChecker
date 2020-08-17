#ifndef ABSTRACTVERIFFILES_H
#define ABSTRACTVERIFFILES_H

#include <QDebug>
#include <QString>

class AbstractVerifFiles
{
public:
  explicit AbstractVerifFiles();

  void verifyAccolade(void);
  void verifyMagicNumber(void);
  void verifyCamelCase(void);
  void verifyToDo(void);
  void verifyPointers(const QStringList p_pointerDeclaration);
  void verifyConditions(void);
  void verifyOrphanFunctions(QMap<QString, int> p_functionsMap);

  bool hasAccoladeProblem(void);
  bool hasMagicNumberProblem(void);
  bool hasCamelCaseProblem(void);
  bool hasToDoProblem(void);
  bool hasPointersProblem(void);
  bool hasConditionsProblem(void);
  bool hasOrphanFunctionsProblem(void);

protected:
  QString m_fileToAnalyse;
  QString m_outputLogsPath;

  bool m_accoladeProblemNumber;
  bool m_magicNumberProblem;
  bool m_camelCaseProblem;
  bool m_todoProblem;
  bool m_pointersProblem;
  bool m_conditionsProblem;
  bool m_orphanFunctionsProblem;
};

#endif // ABSTRACTVERIFFILES_H
