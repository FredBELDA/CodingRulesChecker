#include "commonelements.h"
#include "verifyconditions.h"

VerifyConditions::VerifyConditions(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + CONDITIONS_FILE_NAME;
}

void VerifyConditions::checkForConditions(void)
{

}
