#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include <QString>

// Version
#define VERSION "1.0"
#define RELEASE_DATE "2020/04/11"

// Font management
#define FONT_DECLARATION "Arial"
#define MENU_FONT_SIZE 12
#define ENONCE_FONT_SIZE 12
#define TAB_FONT_SIZE 10
#define LINEEDIT_FONT_SIZE 10
#define PUSHBUTTON_FONT_SIZE 10
#define CHECKBOX_FONT_SIZE 10
#define LABEL_COLOR "QLabel { color : #1e3687; }"

// Window size
#define X_SHIFT 5
#define Y_SHIFT 5
#define HEIGHT_MARGING 20
#define WIDTH_MARGING 20

#define MAINWINDOW_HEIGHT 300
#define MAINWINDOW_WIDTH 675
#define MAIN_VERTICAL_LAYOUT_HEIGHT MAINWINDOW_HEIGHT - HEIGHT_MARGING
#define MAIN_VERTICAL_LAYOUT_WIDTH MAINWINDOW_WIDTH - WIDTH_MARGING

// Popup sizes
#define ABOUT_POPUP_HEIGHT 190
#define ABOUT_POPUP_WIDTH 450
#define ABOUT_POPUP_VERTICAL_LAYOUT_HEIGHT ABOUT_POPUP_HEIGHT - HEIGHT_MARGING
#define ABOUT_POPUP_VERTICAL_LAYOUT_WIDTH ABOUT_POPUP_WIDTH - WIDTH_MARGING

#define RULE_CHOICE_POPUP_HEIGHT 370
#define RULE_CHOICE_POPUP_WIDTH 847
#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_CHOICE_POPUP_HEIGHT - HEIGHT_MARGING
#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_CHOICE_POPUP_WIDTH - WIDTH_MARGING

#define RULE_POPUP_HEIGHT 330
#define RULE_POPUP_WIDTH 700
#define RULE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_POPUP_HEIGHT - HEIGHT_MARGING
#define RULE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_POPUP_WIDTH - WIDTH_MARGING

// Menu Fichier
#define FILE_MENU "Fichier"
#define OPEN_CONFIGURATION_FILE "Ouvrir la configuration"
#define SAVE_CONFIGURATION_FILE "Sauvegarder la configuration"
#define EXIT "Quitter"

// Menu Configuration
#define CONFIGURATION_MENU "Configuration"
#define CODING_RULES_PARAMETERS "Paramétrage des règles de codage"

// Menu Aide
#define HELP_MENU "Aide"
#define ABOUT "à propos"

// Configuration File
#define CONFIG_HMI "ConfigHMI"
#define INPUT_FOLDER_CONFIGURATION "inputFolder"
#define REPORT_FOLDER_CONFIGURATION "reportFolder"

#define CONFIG_RULES "ConfigRules"
#define VERIFY_ACCOLADE_CONFIGURATION "verifAccolade"
#define VERIFY_MAGIC_NUMBER_CONFIGURATION "verifMagicNumber"
#define VERIFY_CAMEL_CASE_CONFIGURATION "verifCamelCase"
#define VERIFY_CONDITION_CONFIGURATION "verifCondition"
#define VERIFY_ORPHAN_FUNCTION_CONFIGURATION "verifOrphanFunction"
#define VERIFY_POINTER_CONFIGURATION "verifPointer"
#define VERIFY_TODO_CONFIGURATION "verifToDo"

#define VERIFY_H_FILE_FOR_C "verifHFileForC"
#define VERIFY_H_FILE_FOR_CPP "verifHFileForCpp"

// Fenêtre principale
#define WINDOW_TITLE "Coding rules checker"

// Main panel
#define INPUT_LABEL_TEXT "Veuillez renseigner le répertoire à analyser :"
#define INPUT_FOLDER_TO_CHECK "Sélectionner le répertoire à analyser"
#define OUTPUT_LABEL_TEXT "Veuillez renseigner le répertoire de destination des logs :"
#define OUTPUT_FOLDER_TO_CHECK "Sélectionner le répertoire ou stocker les logs"
#define CHECKBOX_MERGE_REPORTS "Voulez-vous fusionner tous les rapports ?"
#define BROWSE_FOLDER "Parcourir"
#define LAUNCH_CHECK "Lancer les vérifications"
#define LOGS_FOLDER "logs"
#define GLOBAL_REPORT_NAME "report.csv"
#define CPP_FILE_EXTENSION "cpp"
#define C_FILE_EXTENSION "c"
#define H_FILE_EXTENSION "h"
#define JAVA_FILE_EXTENSION "java"
#define INI_FILE_EXTENSION "ini"
#define GENERATED_REPORT "Rapport genere le : "
#define NUMBER_OF_FILES_FOUND "Nombre de fichiers trouves dans "
#define NUMBER_OF_C_FILES "Nombre de fichiers C : "
#define NUMBER_OF_CPP_FILES "Nombre de fichiers Cpp : "
#define NUMBER_OF_H_FILES "Nombre de fichiers h : "
#define NUMBER_OF_JAVA_FILES "Nombre de fichiers Java : "
#define NUMBER_OF_INI_FILES "Nombre de fichiers ini : "
#define NUMBER_OF_NOT_MANAGED_FILES "Nombre de fichier non geres : "
#define CANNOT_CREATE_FOLDER "Impossible de créer le répertoire !"

// Buttons
#define VALIDATE "Valider"
#define CANCEL "Annuler"

// Reports
#define REPORT_HEADER_FILE "Fichier;Numéro de ligne;ligne;Problème rencontré"
#define CODEC_FOR_EXCEL_FILE "ISO 8859-1"
#define NB_MIN_ELTS 2
#define NB_MAX_DECLARATION_SIZE 8
#define FILE_SEPARATOR " / "

#define ACCOLADE_FILE_NAME "Accolade.csv"
#define TODO_FILE_NAME "ToDo.csv"
#define H_FILE_NAME "HFile.csv"
#define MAGIC_NUMBER_FILE_NAME "MagicNumber.csv"
#define CAMEL_CASE_FILE_NAME "CamelCase.csv"
#define POINTER_FILE_NAME "Pointer.csv"
#define ORPHAN_FUNCTIONS_FILE_NAME "OrphanFunctions.csv"
#define CONDITIONS_FILE_NAME "Conditions.csv"

// Errors
#define INPUT_FOLDER_DOES_NOT_EXISTS "Le répertoire d'entrée du projet n'existe pas !"
#define OUTPUT_FOLDER_DOES_NOT_EXISTS "Le répertoire de logs n'existe pas, il sera créé automatiquement !"

// TODO complete rules contains
#define ACCOLADE_RULE_POPUP_TITLE "Règle de codage concernant les accolades"
#define ACCOLADE_RULE_POPUP ""
#define TODO_RULE_POPUP_TITLE "Règle de codage concernant les ToDo"
#define TODO_RULE_POPUP ""
#define H_RULE_POPUP_TITLE "Règle de codage concernant les fichiers H"
#define H_RULE_POPUP ""
#define MAGIC_NUMBER_RULE_POPUP_TITLE "Règle de codage concernant les Magic Number"
#define MAGIC_NUMBER_RULE_POPUP ""
#define CAMEL_CASE_RULE_POPUP_TITLE "Règle de codage concernant la déclaration de variables en CamelCase"
#define CAMEL_CASE_RULE_POPUP ""
#define POINTER_RULE_POPUP_TITLE "Règle de codage concernant les pointeurs"
#define POINTER_RULE_POPUP ""
#define ORPHAN_FUNCTIONS_RULE_POPUP_TITLE "Règle de codage concernant les fonctions orphelines"
#define ORPHAN_FUNCTIONS_RULE_POPUP ""
#define CONDITIONS_RULE_POPUP_TITLE "Règle de codage concernant les conditions"
#define DEFAULT_RULE_POPUP_TITLE "Règle par défaut : non gérée !"
#define DEFAULT_RULE_POPUP ""

#define SEARCH_FOR_TODO "todo"
#define SEARCH_FOR_TODO_SECOND "to do"
#define SEARCH_FOR_EQUALS "="
#define SEARCH_FOR_SPACE " "
#define SEARCH_FOR_COMMA ","
#define SEARCH_FOR_SEMICOLON ";"
#define SEARCH_FOR_UNDERSCORE "_"
#define SEARCH_FOR_OPENED_PARENTHESIS "("
#define SEARCH_FOR_CLOSED_PARENTHESIS ")"

#define CONST_DECLARATION "const"
#define INT_DECLARATION "int"
#define UINT_DECLARATION "uint"
#define UNSIGNED_DECLARATION "unsigned"
#define DOUBLE_DECLARATION "double"
#define SHORT_DECLARATION "short"
#define FLOAT_DECLARATION "float"
#define BOOL_DECLARATION "bool"
#define CHAR_DECLARATION "char"
#define LONG_DECLARATION "long"
#define IFSTREAM_DECLARATION "ifstream"
#define OFSTREAM_DECLARATION "ofstream"
#define POINTEUR_DECLARATION "*"

#define FALSE_VALUE "false"
#define TRUE_VALUE "true"

#define CANNOT_OPENED_FILE "Impossible d'ouvrir le fichier : "
#define FOR_READING "en lecture !"
#define FOR_WRITING "en écriture !"
#define DOES_NOT_CONTAINS_H_FILE "ne dispose pas de son fichier h !"
#define DOES_NOT_RESPECT_CAMEL_CASE_SYNTAX "Ne repect pas la synthaxe camelCase !"
#define DOES_NOT_RESPECT_PERIMETER_SYNTAX "Ne repect pas la synthaxe de périmètre de la variable !"
#define ACCOLADE_IS_NOT_ONLY "L'accolade ne se trouve pas tout seul sur une ligne : Veuillez faire un retour charriot !"
#define TODO_MUST_SUPPRESS "Les TODO doivent être enlever du code !"
#define IS_MAGIC_NUMBER "Est un magic number, il faut le remplacer par un define ou un enum !"

#define NO_PROBLEM_FOUND "Aucun problème rencontré !"

#define CPP_CHECK_PATH "\"C:/Program Files/Cppcheck/cppcheckgui.exe\""
#define EXPLORER_CMD "explorer.exe"

// About popup
#define ABOUT_POPUP_TITLE "Au sujet de"
#define ABOUT_POPUP_CONTAINT "CodingRulesChecker " + QString(VERSION) + " du " + \
QString(RELEASE_DATE) + "\na été déveoppé dans le but d'assurer une conformité des\n \
livraisons pour le compte de Thales TSIS, dans leurs \n \
projets internes.\n\n \
Ce projet a été réalisé avec le framework Qt" + QT_VERSION_STR

// Coding rule parameter popup
#define RULE_CHOICE_POPUP_TITLE "Configuration des règles à analyser"

#endif // COMMONELEMENTS_H
