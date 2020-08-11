#ifndef UTILS_H
#define UTILS_H

#include <QFile>
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
  static bool isConstant(const QString p_line);
  static bool isDefine(const QString p_line);
  static bool isImport(const QString p_line);
  static bool isDigit(const QString p_line);
  static bool isPointerTest(const QString p_line);
  static bool isVariableDeclaration(const QString p_line);
  static bool isPointerInit(const QString p_line);
  static QStringList scanForVariableDeclaration(const QString p_line);
  static QStringList scanForPointerDeclaration(const QString p_line);
  static bool scanForMagicNumber(const QString p_line);
  static QString scanForDefineDeclaration(const QString p_line);
  static QStringList getPointerDeclarationList(QFile &p_file);
  static QStringList splitConditions(const QStringList p_stringList);
  static QStringList cleanSplitedConditons(const QStringList p_stringList);

  static QString scanForFunctionDeclaration(const QString p_line);
  // Check launcher
  static void launchCppCheck(const QString p_cppCheckPath, const QString p_pathToCheck);
  static void launchCheckStyle(const QString p_checkStylePath, const QString p_pathToCheck);
  static void launchExcel(const QString p_excelPath, const QString p_excelFile);

private:
  static void genericLaunchApplication(const QString p_path, const QString p_fileToOpen);
};

#endif // UTILS_H
