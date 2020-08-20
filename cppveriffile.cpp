#include "cppveriffile.h"
#include "verifyorphanfunctions.h"

CppVerifFile::CppVerifFile(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
    m_fileToAnalyse = p_fileToAnalyse;
    m_outputLogsPath = p_outputLogsPath;
}

void CppVerifFile::functionsTodoList(QMap<QString, int> p_functionsMap)
{
    qDebug() << "functionsTodoList: " << p_functionsMap;
    VerifyOrphanFunctions *l_verifOrphanFunctions = new VerifyOrphanFunctions(m_fileToAnalyse, m_outputLogsPath);
    l_verifOrphanFunctions->UpdateTodoList(p_functionsMap);

    l_verifOrphanFunctions->generateReport();

    if(0 == l_verifOrphanFunctions->getNbError())
    {
      m_orphanFunctionsProblem = false;
    }
    else
    {
      m_orphanFunctionsProblem = true;
    }

}
