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
  static bool isComment(const QString p_line);
  static bool isImport(const QString p_line);
  static bool isDigit(const QString p_line);
  static QStringList scanForVariableDeclaration(const QString p_line);
  static QStringList scanForPointerDeclaration(const QString p_line);
  static bool scanForMagicNumber(const QString p_line);
  // Check launcher
  static void launchCppCheck(const QString p_cppCheckPath, const QString p_pathToCheck);
  static void launchCheckStyle(const QString p_checkStylePath, const QString p_pathToCheck);
  static void launchExcel(const QString p_excelPath, const QString p_excelFile);
};

#endif // UTILS_H
