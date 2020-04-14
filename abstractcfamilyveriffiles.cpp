#include "abstractcfamilyveriffiles.h"
#include "verifyhfile.h"

AbstractCFamilyVerifFiles::AbstractCFamilyVerifFiles()
{
  m_hFileProblem = false;
}

void AbstractCFamilyVerifFiles::verifyHFile(const QStringList p_hFilesList)
{
  if(!p_hFilesList.isEmpty())
  {
    VerifyHFile *l_verifHFile = new VerifyHFile(m_fileToAnalyse, m_outputLogsPath, p_hFilesList);
    if(nullptr != l_verifHFile)
    {
      l_verifHFile->checkForHFile();
      l_verifHFile->generateReport();

      if(0 == l_verifHFile)
      {
        m_hFileProblem = false;
      }
      else
      {
        m_hFileProblem = true;
      }
    }
  }
}

bool AbstractCFamilyVerifFiles::hasHFileProblem(void)
{
  return m_hFileProblem;
}
