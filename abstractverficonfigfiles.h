#ifndef ABSTRACTVERFICONFIGFILES_H
#define ABSTRACTVERFICONFIGFILES_H

#include <QDebug>
#include <QFile>
#include <QString>

class AbstractVerfiConfigFiles
{
public:
  AbstractVerfiConfigFiles();

protected:

  QString m_fileToAnalyse;
  QFile m_fileToCheck;
};

#endif // ABSTRACTVERFICONFIGFILES_H
