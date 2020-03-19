#ifndef ABSTRACTVERFICONFIGFILES_H
#define ABSTRACTVERFICONFIGFILES_H

#include <QDebug>
#include <QString>

class AbstractVerifConfigFiles
{
public:
  explicit AbstractVerifConfigFiles();

protected:
  QString m_fileToAnalyse;
  QString m_outputLogsPath;
};

#endif // ABSTRACTVERFICONFIGFILES_H
