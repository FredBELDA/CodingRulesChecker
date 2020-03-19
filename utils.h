#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>

#include "commonelements.h"

class Utils
{
public:
  static QString formatPath(const QString p_path);
  static QString formatPathForCmd(const QString p_path);
  static QString extractFileName(const QString p_path);
  static QStringList scanForLine(const QString p_line);
  // Check launcher
  static void launchCppCheck(const QString p_pathToCheck);
  static void launchCheckStyle(const QString p_pathToCheck);
};

#endif // UTILS_H
