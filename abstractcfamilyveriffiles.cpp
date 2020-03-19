#include "abstractcfamilyveriffiles.h"
#include "verifyhfile.h"

AbstractCFamilyVerifFiles::AbstractCFamilyVerifFiles()
{
  m_HFileProblem = false;
}

void AbstractCFamilyVerifFiles::verifyHFile(const QStringList p_hFilesList)
{
  VerifyHFile *l_verifHFile = new VerifyHFile(m_fileToAnalyse, m_outputLogsPath, p_hFilesList);
  if(nullptr != l_verifHFile)
  {
    l_verifHFile->checkForHFile();
    l_verifHFile->generateReport();

    if(0 == l_verifHFile)
    {
      m_HFileProblem = false;
    }
    else
    {
      m_HFileProblem = true;
    }
  }
}

bool AbstractCFamilyVerifFiles::hasHFileProblem(void)
{
  return m_HFileProblem;
}
