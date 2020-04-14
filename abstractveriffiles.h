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

  bool hasAccoladeProblem(void);
  bool hasMagicNumberProblem(void);
  bool hasCamelCaseProblem(void);
  bool hasToDoProblem(void);
  bool hasPointersProblem(void);

protected:
  QString m_fileToAnalyse;
  QString m_outputLogsPath;

  bool m_accoladeProblemNumber;
  bool m_magicNumberProblem;
  bool m_camelCaseProblem;
  bool m_todoProblem;
  bool m_pointersProblem;
};

#endif // ABSTRACTVERIFFILES_H
