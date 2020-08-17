#include "commonelements.h"
#include "verifyorphanfunctions.h"
#include "utils.h"

VerifyOrphanFunctions::VerifyOrphanFunctions(const QString p_fileToAnalyse, const QString p_outputLogsPath)
{
    m_fileToAnalyse = p_fileToAnalyse;
    m_reportFile = p_outputLogsPath + ORPHAN_FUNCTIONS_FILE_NAME;
}

void VerifyOrphanFunctions::checkForOrphanFunctions(QMap<QString, int> p_functionsMap)
{
    qDebug() << "checkForOphanFunctions: "  << p_functionsMap;
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
                        !Utils::isDefine(l_line) &&
                        !Utils::isImport(l_line))
                {
                    // Pour le c++
                    // Si la ligne correspond
                    // On split par "::" pour recuperer la declaration de fonction
                    // void Voiture::avancer(void) -> avancer()
                    if(l_line.contains(SEARCH_FOR_METHOD) &&
                            Utils::isVariableDeclaration(l_line))
                    {
                        // Nettoyage de la ligne
                        l_line = l_line.split(SEARCH_FOR_METHOD).at(1);
                        l_line = l_line.split(SEARCH_FOR_OPENED_PARENTHESIS).at(0);

                    }
                    foreach(QString l_function, p_functionsMap.keys())
                    {
                        if(l_line.contains(l_function))
                        {
                            qDebug() << "l_line: " << l_line;
                            qDebug() << "l_function: " << l_function;
                            int l_functionValue = p_functionsMap.value(l_function);
                            qDebug() << "l_functionValue: " << l_functionValue;
                            p_functionsMap.insert(l_function, l_functionValue - 1);

                        }
                    }


                }
                l_lineNumber += 1;
            }
            l_file.close();

            // Rapport pour les fonctions
            foreach(QString l_function, p_functionsMap.keys())
            {


                int l_functionValue = p_functionsMap.value(l_function);
                qDebug() << "l_function: " << l_function << " Value: " << l_functionValue;
                if(1 == l_functionValue )
                {
                    m_todoList.append(QString::number(0) + FILE_SEPARATOR +
                                      l_function + FILE_SEPARATOR + MAJOR + FILE_SEPARATOR +
                                      + "Fonction declarée dans le .h mais pas implementée" + "\n");
                }
                else if(0 == l_functionValue)
                {
                    m_todoList.append(QString::number(0) + FILE_SEPARATOR +
                                      l_function + FILE_SEPARATOR + MAJOR + FILE_SEPARATOR +
                                      + "Fonction implementée mais non utilisé dans le projet " + "\n");
                }

            }

        }
    }

    else
    {
        qDebug() << "m_reportFileName is empty !";
    }
}
