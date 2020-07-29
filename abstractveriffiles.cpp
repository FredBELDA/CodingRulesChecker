#include "abstractveriffiles.h"
#include "verifyaccolade.h"
#include "verifytodo.h"
#include "verifymagicnumber.h"
#include "verifycamelcase.h"
#include "verifypointer.h"
#include "verifyconditions.h"

AbstractVerifFiles::AbstractVerifFiles()
{
  m_accoladeProblemNumber = false;
  m_magicNumberProblem = false;
  m_camelCaseProblem = false;
  m_todoProblem = false;
  m_pointersProblem = false;
}

void AbstractVerifFiles::verifyAccolade(void)
{
  VerifyAccolade *l_verifAccolade = new VerifyAccolade(m_fileToAnalyse, m_outputLogsPath);
  if(nullptr != l_verifAccolade)
  {
    l_verifAccolade->checkForAccolade();
    l_verifAccolade->generateReport();

    if(0 == l_verifAccolade->getNbError())
    {
      m_accoladeProblemNumber = false;
    }
    else
    {
      m_accoladeProblemNumber = true;
    }
  }
}

void AbstractVerifFiles::verifyMagicNumber(void)
{
  VerifyMagicNumber *l_verifMagicNumber = new VerifyMagicNumber(m_fileToAnalyse, m_outputLogsPath);
  if(nullptr != l_verifMagicNumber)
  {
    l_verifMagicNumber->checkForMagicNumber();
    l_verifMagicNumber->generateReport();

    if(0 == l_verifMagicNumber->getNbError())
    {
      m_magicNumberProblem = false;
    }
    else
    {
      m_magicNumberProblem = true;
    }
  }
}

void AbstractVerifFiles::verifyCamelCase(void)
{
  VerifyCamelCase *l_verifCamelCase = new VerifyCamelCase(m_fileToAnalyse, m_outputLogsPath);
  if(nullptr != l_verifCamelCase)
  {
    l_verifCamelCase->checkForCamelCase();
    l_verifCamelCase->generateReport();

    if(0 == l_verifCamelCase->getNbError())
    {
      m_camelCaseProblem = false;
    }
    else
    {
      m_camelCaseProblem = true;
    }
  }
}

void AbstractVerifFiles::verifyToDo(void)
{
  VerifyToDo *verifToDo = new VerifyToDo(m_fileToAnalyse, m_outputLogsPath);
  if(nullptr != verifToDo)
  {
    verifToDo->checkForToDo();
    verifToDo->generateReport();

    if(0 == verifToDo->getNbError())
    {
      m_todoProblem = false;
    }
    else
    {
      m_todoProblem = true;
    }
  }
}

void AbstractVerifFiles::verifyPointers(const QStringList p_pointerDeclaration)
{
  qDebug() << "verifyPointers";

  if(!p_pointerDeclaration.isEmpty())
  {
    VerifyPointer *l_verifPointer = new VerifyPointer(m_fileToAnalyse, m_outputLogsPath);
    if(nullptr != l_verifPointer)
    {
      l_verifPointer->checkForPointer(p_pointerDeclaration);
      l_verifPointer->generateReport();

      if(0 == l_verifPointer->getNbError())
      {
        m_pointersProblem = false;
      }
      else
      {
        m_pointersProblem = true;
      }
    }
  }
}

void AbstractVerifFiles::verifyConditions(void)
{
  qDebug() << "verifyConditions";
  VerifyConditions *l_verifConditions = new VerifyConditions(m_fileToAnalyse, m_outputLogsPath);
  if(nullptr != l_verifConditions)
  {
    l_verifConditions->checkForConditions();
    l_verifConditions->generateReport();

    if(0 == l_verifConditions->getNbError())
    {
      m_conditionsProblem = false;
    }
    else
    {
      m_conditionsProblem = true;
    }
  }
}

bool AbstractVerifFiles::hasAccoladeProblem(void)
{
  return m_accoladeProblemNumber;
}

bool AbstractVerifFiles::hasMagicNumberProblem(void)
{
  return m_magicNumberProblem;
}

bool AbstractVerifFiles::hasCamelCaseProblem(void)
{
  return m_camelCaseProblem;
}

bool AbstractVerifFiles::hasToDoProblem(void)
{
  return m_todoProblem;
}

bool AbstractVerifFiles::hasPointersProblem(void)
{
  return m_pointersProblem;
}

bool AbstractVerifFiles::hasConditionsProblem(void)
{
  return m_conditionsProblem;
}
