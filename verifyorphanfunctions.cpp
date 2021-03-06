#include "commonelements.h"
#include "verifyorphanfunctions.h"
#include "utils.h"

VerifyOrphanFunctions::VerifyOrphanFunctions(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
    m_fileToAnalyse = p_fileToAnalyse;
    m_reportFile = p_outputLogsPath + ORPHAN_FUNCTIONS_FILE_NAME;
}

void VerifyOrphanFunctions::checkForOrphanFunctions(void)
{
    if(!m_fileToAnalyse.isEmpty())
    {
        QFile l_file(m_fileToAnalyse);
        if(!l_file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << CANNOT_OPENED_FILE << l_file.fileName() << FOR_READING;
        }
        else
        {
            QTextStream l_in(&l_file);
            QString l_line;
            int l_lineNumber = 1;
            while(! l_in.atEnd())
            {
                l_line = l_in.readLine();
                l_line = l_line.trimmed();
                // Replace all spaces by one space ('\t', '\n', '\v', '\f', '\r', and ' ')
                // Example : "QDir    l_currentSRSWorkspace" => "QDir l_currentSRSWorkspace"
                l_line = l_line.simplified();
                // Lire le fichier .h
                // Trouver les lignes de declarations de fonction
                // Donc forme type nom_fonction(params);
                // Different de type nom_variable;
                // Donc la dif est sur les parentheses des parametres
                if(!Utils::isComment(l_line) &&
                        !Utils::isDefine(l_line) &&
                        !Utils::isImport(l_line))
                {
                    qDebug() << "l_line: " << l_line;
                }
                l_lineNumber += 1;
            }
            l_file.close();
        }
    }

    else
    {
        qDebug() << "m_reportFileName is empty !";
    }
}
