#include "commonelements.h"
#include "verifyorphanfunctions.h"

VerifyOrphanFunctions::VerifyOrphanFunctions(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
  m_fileToAnalyse = p_fileToAnalyse;
  m_reportFile = p_outputLogsPath + ORPHAN_FUNCTIONS_FILE_NAME;
}

void VerifyOrphanFunctions::checkForOrphanFunctions(void)
{

}
