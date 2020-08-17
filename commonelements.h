#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

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
#define LABEL_EXAMPLE "QLabel { font-style: italic; color : #FF0000; }"
#define LABEL_SEPARATOR "QLabel { background: qlineargradient( x1:0 y1:0, x2:1 y2:0," \
                                  "stop:0 #BBBBBB, \
                                   stop:0.3 #999999, \
                                   stop:0.5 #333333, \
                                   stop:0.7 #999999, \
                                   stop:1 #BBBBBB); \
                                }"

// Window size
#define X_SHIFT 5
#define Y_SHIFT 5
#define HEIGHT_MARGING 20
#define WIDTH_MARGING 20

#define MAINWINDOW_HEIGHT 340
#define MAINWINDOW_WIDTH 675
#define MAIN_VERTICAL_LAYOUT_HEIGHT MAINWINDOW_HEIGHT - HEIGHT_MARGING
#define MAIN_VERTICAL_LAYOUT_WIDTH MAINWINDOW_WIDTH - WIDTH_MARGING

// Menu Fichier
#define FILE_MENU "Fichier"
#define OPEN_CONFIGURATION_FILE "Ouvrir la configuration"
#define SAVE_CONFIGURATION_FILE "Sauvegarder la configuration"
#define EXIT "Quitter"

// Menu Configuration
#define CONFIGURATION_MENU "Paramètres"
#define CODING_RULES_PARAMETERS "Paramétrage des règles de codage"
#define EXTERNAL_TOOL_PARAMETERS "Paramétrage des outils externes"

// Menu CheckList
#define CHECKLIST_MENU "CheckList"
#define OPEN_CHECKLIST_FILE "Ouvrir le fichier checklist"

// Menu Aide
#define HELP_MENU "Aide"
#define ABOUT "A propos"

// Configuration File
#define CONFIG_HMI "ConfigHMI"
#define INPUT_FOLDER_CONFIGURATION "inputFolder"
#define REPORT_FOLDER_CONFIGURATION "reportFolder"

#define CONFIG_EXTERNAL_TOOL "ConfigExternalTool"
#define INPUT_EXCEL_PATH_CONFIGURATION "inputExcelPath"
#define INPUT_CPP_CHECK_PATH_CONFIGURATION "inputCppCheckPath"
#define INPUT_CHECK_STYLE_PATH_CONFIGURATION "inputCheckStylePath"

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
#define SAVE "Enregistrer"
#define QUIT "Quitter"

// Reports
#define REPORT_HEADER_FILE "Fichier;Numéro de ligne;Contenu de la ligne;Criticité;Problème rencontré"
#define CODEC_FOR_EXCEL_FILE "ISO 8859-1"
#define NB_MIN_ELTS 2
#define NB_DEFINE_CONSTANT_ELTS 3
#define NB_MAX_DECLARATION_SIZE 8
#define FILE_SEPARATOR " / "

#define MAJOR "Majeur"
#define MINOR "Mineur"
#define CRITIC "Critique"

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
#define RULE_POPUP_HEIGHT 600
#define RULE_POPUP_WIDTH 700
#define RULE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_POPUP_HEIGHT - HEIGHT_MARGING
#define RULE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_POPUP_WIDTH - WIDTH_MARGING

#define ACCOLADE_RULE_POPUP_TITLE "Règle de codage concernant les accolades"
#define ACCOLADE_RULE_POPUP ""
#define ACCOLADE_RULE_EXAMPLE ""
#define ACCOLADE_RULE_EXPLANATION ""
#define TODO_RULE_POPUP_TITLE "Règle de codage concernant les ToDo"
#define TODO_RULE_POPUP "On peut mettre des ToDo dans le code,\n \
lorsque l'on développe une fonctionnalité.\n \
C'est un pense bête, pour revenir dessus plus tard,\n \
soit à cause d'une fonction à appeler, qui n'existe pas,\n \
soit à cause d'un point à éclaircir auprès d'un architecte.\n\n \
Avant de livrer, il faut impérativement faire une passe\n \
sur le projet, pour vérifier qu'il n'en existe plus."
#define TODO_RULE_EXAMPLE ""
#define TODO_RULE_EXPLANATION ""
#define H_RULE_POPUP_TITLE "Règle de codage concernant les fichiers H"
#define H_RULE_POPUP "Chaque fichier .c ou .cpp, doit avoir son fichier .h\n \
associé. Ce fichier .h permet de définir les prototypes de fonction\n \
de votre classe ou bibliothèque.\n\n \
Vous pouvez avoir plus de fichiers .h que de fichiers .c ou .cpp\n \
Ces fichiers .h peuvent vous permettre de centraliser\n \
toutes les constantes de votre projet,\n \
tous vos textes de l'IHM,\n \
..."
#define H_RULE_EXAMPLE ""
#define H_RULE_EXPLANATION ""
#define MAGIC_NUMBER_RULE_POPUP_TITLE "Règle de codage concernant les Magic Number"
#define MAGIC_NUMBER_RULE_POPUP "Les magic number sont à proscrire d'un code.\n\n \
Il vaut mieux créer une constante ou un define dans un fichier .h, et ensuite l'appeler\n \
La constante ou le define, a le mérite de porter un nommage\n \
compréhensible de tout le monde.\n\n"
#define MAGIC_NUMBER_RULE_EXAMPLE "if(i == 2)\n \
{\n \
  printf(\"%d\", i);\n \
}"
#define MAGIC_NUMBER_RULE_EXPLANATION "Que veut dire 2 ? Pourquoi ? \n \
Est-ce un exigence du client ?\nUne constante arbitraire ?\nValeur prise sur un coup de tête ?\n\n \
Définir un define avec #define NB_ELT_TO_PARSE 2 est plus parlant.\n \
Le relecteur comprendra de quoi vous parlez !\n\n \
De plus en centralisant vos constantes dans un seul fichier, vous fera\n \
gagner du temps lors des modifications de valeurs."
#define CAMEL_CASE_RULE_POPUP_TITLE "Règle de codage concernant la déclaration de variables en CamelCase"
#define CAMEL_CASE_RULE_POPUP "Il existe une règle à respecter, pour le nommage de\n \
vos variables. Cette règle est le camelCase.\n \
La règle est simple :"
#define CAMEL_CASE_RULE_EXAMPLE " - Première lettre en minuscule.\n \
 - Première lettre de chaque mot suivant en majuscule.\n \
 - Pas d'abréviation. \n \
StepResult => Pas camelCase\n \
stepResult => camelCase"
#define CAMEL_CASE_RULE_EXPLANATION "Si on veut déclarer une variable dite globale à un fichier\n \
on doit le préfixer d'un \"g_\".\n \
Pour les paramètres de fonction, on utilise les préfixes pour signaler\n \
si la variable est considérée comme un entrée ou une sortie.\n \
  int toto(int i_aa, int i_bb, char *o_cc)\n \
    \"i_\" = paramètre d'entrée de la fonction.\n \
    \"o_\" = paramètre de sortie de la fonction.\n \
    \"io_\" = paramètre d'entrée et de sortie de la fonction.\n \
  une variable nommée \"o_\" ou \"io_\" sera forcément un pointeur.\n \
  la variable \"o_\" sera mise à jour par la fonction.\n \
Si on déclare une variable dans une classe, elle est dite membre\n \
à la classe, on doit la préfixer d'un \"m_\".\n \
Si on déclare une variable dans une fonction, elle est dite locale\n \
à la fonction, on doit la préfixer d'un \"l_\"."
#define POINTER_RULE_POPUP_TITLE "Règle de codage concernant les pointeurs"
#define POINTER_RULE_POPUP "Un pointeur est avant tout une zone mémoire de votre système.\n \
Vous devez allouer de la mémoire, pour stocker votre pointeur.\n \
Le problème des systèmes multiservices, c'est qu'on ne maitrise pas\n \
les autres systèmes, et ce qu'ils font sur la mémoire.\n \
Il pourrait très bien effacer une partie de la mémoir\n \
que vous venez d'allouer. Votre pointeur se retrouverait verrolé.\n \
Ou plus vicieux, toute la zone allouée a été écrasée, ou pas instancié\n \
(oubli de faire un new). Du coup au moment d'utiliser votre pointeur,\n \
vous allez faire crasher le système, car votre objet n'existera pas, ou sera\n \
verrolé."
#define POINTER_RULE_EXAMPLE "Toto* m_test = new Toto();\n \
Au moment ou j'utilise la variable m_test, je la vérifie.\n \
if(nullptr != m_test)\n \
{\n \
  ...\n \
}"
#define POINTER_RULE_EXPLANATION "Je ne sais pas si mon pointeur a été écrasé par quelqu'un entre\n \
mon instanciation (avec le new), et le moment, ou je vais l'utiliser.\n \
Par conséquent, à chaque fois, que je vais devoir interagir avec lui,\n \
je le teste avant."
#define ORPHAN_FUNCTIONS_RULE_POPUP_TITLE "Règle de codage concernant les fonctions orphelines"
#define ORPHAN_FUNCTIONS_RULE_POPUP ""

#define ORPHAN_FUNCTIONS_RULE_EXAMPLE ""
#define ORPHAN_FUNCTIONS_RULE_EXPLANATION ""
#define CONDITIONS_RULE_POPUP_TITLE "Règle de codage concernant les conditions"
#define CONDITIONS_RULE_POPUP "Les conditions sont importantes dans votre code. \n \
Attention tout de même à l'ordre dans lequel vous les tester.\n \
En effet une faute de frappe sur un test d'égalité et votre  \n \
variable se retrouve ré-affecté. \n \
Pour eviter cela il faut donc inverser votre test d'égalité, \n \
ce qui ne changera rien au comportement \
inital."
#define CONDITIONS_RULE_EXAMPLE "if(l_variable = 0) \n \
ici on prend le risque d'une erreur de frappe et donc d'affecter 0  \n à notre variable. \n \
la bonne pratique est donc d'inverser 0 et l_variable. \n \
if(0 == l_variable)"
#define CONDITIONS_RULE_EXPLANATION "En faisant cela, si une erreur de frappe est présente, le compilateur \n \
nous le signalera automatiquement et \n \
provoquera une erreur plus facilement detectable."
#define DEFAULT_RULE_POPUP_TITLE "Règle par défaut : non gérée !"
#define DEFAULT_RULE_POPUP ""
#define DEFAULT_RULE_EXAMPLE ""
#define DEFAULT_RULE_EXPLANATION ""

#define SEARCH_FOR_TODO "todo"
#define SEARCH_FOR_TODO_SECOND "to do"
#define SEARCH_FOR_EQUALS "="
#define SEARCH_FOR_SPACE " "
#define SEARCH_FOR_COMMA ","
#define SEARCH_FOR_SEMICOLON ";"
#define SEARCH_FOR_UNDERSCORE "_"
#define SEARCH_FOR_OPENED_PARENTHESIS "("
#define SEARCH_FOR_CLOSED_PARENTHESIS ")"
#define SEARCH_FOR_QUOTATION_MARKS "\""
#define SEARCH_FOR_OPENED_ACCOLADE "{"
#define SEARCH_FOR_CLOSED_ACCOLADE "}"
#define SEARCH_FOR_INFERIOR "<"
#define SEARCH_FOR_SUPERIOR ">"
#define SEARCH_FOR_NEW "new"
#define SEARCH_FOR_OR "||"
#define SEARCH_FOR_AND "&&"
#define SEARCH_FOR_EQUALS_TEST "=="
#define SEARCH_FOR_DESTRUCTOR "~"
#define SEARCH_FOR_EXPLICIT "explicit"
#define SEARCH_FOR_STATIC "static"
#define SEARCH_FOR_METHOD "::"

#define FOR_INSTRUCTION "for"
#define WHILE_INSTRUCTION "while"
#define IF_INSTRUCTION "if"
#define ELSE_INSTRUCTION "else"
#define ELIF_INSTRUCTION "elif"
#define FOREACH_INSTRUCTION "foreach"

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
#define POINTER_DECLARATION "*"

#define NULLPOINTER_DECLARATION "nullptr"
#define NULL_DECLARATION "null"
#define ZERO_POINTER 0

#define REGEX_FOR_POINTERS "0|null|nullptr"
#define REGEX_FOR_FUNDAMENTAL_TYPE "^(void|bool|char|short|int|uint|long|unsigned|double|float)"
#define REGEX_FOR_EQUALS "==|="
#define REGEX_FOR_INSTRUCTIONS "^(if|while|for|else if)"
#define REGEX_FOR_CONDITIONS "<|>|!|>=|<="



#define FALSE_VALUE "false"
#define TRUE_VALUE "true"

#define CANNOT_OPENED_FILE "Impossible d'ouvrir le fichier : "
#define FOR_READING "en lecture !"
#define FOR_WRITING "en écriture !"
#define DOES_NOT_CONTAINS_H_FILE "ne dispose pas de son fichier h !"
#define DOES_NOT_RESPECT_CAMEL_CASE_SYNTAX "Ne repect pas la synthaxe camelCase !"
#define DOES_NOT_RESPECT_PERIMETER_SYNTAX "Ne repect pas la synthaxe de périmètre de la variable !"
#define ACCOLADE_IS_NOT_ALONE "L'accolade ne se trouve pas tout seul sur une ligne : Veuillez faire un retour charriot !"
#define TODO_MUST_SUPPRESS "Les TODO doivent être enlever du code !"
#define IS_MAGIC_NUMBER "Est un magic number, il faut le remplacer par un define ou un enum !"

#define NO_PROBLEM_FOUND "Aucun problème rencontré !"
#define POINTER_IS_NOT_TESTED "Le pointeur n'est pas entouré d'un block if !"
#define WRONG_CONDITION_ORDER "Attention la condition n'est pas dans l'ordre CONST == var."
#define POSSIBLE_CONDITION_ERROR "Attention vous assigner peut-être une variable dans une instruction."

// About popup
#define ABOUT_POPUP_HEIGHT 190
#define ABOUT_POPUP_WIDTH 450
#define ABOUT_POPUP_VERTICAL_LAYOUT_HEIGHT ABOUT_POPUP_HEIGHT - HEIGHT_MARGING
#define ABOUT_POPUP_VERTICAL_LAYOUT_WIDTH ABOUT_POPUP_WIDTH - WIDTH_MARGING

#define ABOUT_POPUP_TITLE "Au sujet de"
#define ABOUT_POPUP_CONTAINT "CodingRulesChecker " + QString(VERSION) + " du " + \
QString(RELEASE_DATE) + "\na été déveoppé dans le but d'assurer une conformité des\n \
livraisons pour le compte de Thales TSIS, dans leurs \n \
projets internes.\n\n \
Ce projet a été réalisé avec le framework Qt" + QT_VERSION_STR

// Coding rule parameter popup
#define RULE_CHOICE_POPUP_HEIGHT 400
#define RULE_CHOICE_POPUP_WIDTH 847
#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_HEIGHT RULE_CHOICE_POPUP_HEIGHT - HEIGHT_MARGING
#define RULE_CHOICE_POPUP_VERTICAL_LAYOUT_WIDTH RULE_CHOICE_POPUP_WIDTH - WIDTH_MARGING

#define RULE_CHOICE_POPUP_TITLE "Configuration des règles à analyser"

// Tool parameter popup
#define EXTERNAL_TOOL_POPUP_HEIGHT 300
#define EXTERNAL_TOOL_POPUP_WIDTH 400
#define EXTERNAL_TOOL_POPUP_VERTICAL_LAYOUT_HEIGHT EXTERNAL_TOOL_POPUP_HEIGHT - HEIGHT_MARGING
#define EXTERNAL_TOOL_POPUP_VERTICAL_LAYOUT_WIDTH EXTERNAL_TOOL_POPUP_WIDTH - WIDTH_MARGING

#define EXTERNAL_TOOL_POPUP_TITLE "Paramétrage des outils externes"
#define EXCEL_PATH_LABEL "Veuillez renseigner le chemin vers Excel :"
#define CPP_CHECK_PATH_LABEL "Veuillez renseigner le chemin vers CPPCheck :"
#define CHECK_STYLE_PATH_LABEL "Veuillez renseigner le chemin vers CheckStyle :"

#define INPUT_EXCEL_PATH "Sélectionner le répertoire ou se trouve Excel"
#define INPUT_CPP_CHECK_PATH "Sélectionner le répertoire ou se trouve CPPCheck"
#define INPUT_CHECK_STYLE_PATH "Sélectionner le répertoire ou se trouve CheckSTYLE"

#define EXCEL_PATH_NOT_EXISTS "Le répertoire vers Excel n'existe pas !"
#define CPP_CHECK_PATH_NOT_EXISTS "Le répertoire vers CppCheck n'existe pas !"
#define CHECK_STYLE_PATH_NOT_EXISTS "Le répertoire vers CheckStyle n'existe pas !"

// Path to doc
#define CHECKLIST_PATH "/input/CheckList.xlsx"

// Default path
#define EXCEL_DEFAULT_PATH "\"C:/Program Files/Microsoft Office/OFFICE11/EXCEL.exe\""
#define EXCEL_FILTER "Excel application (excel.exe)"
#define LIBREOFFICE_CALC_DEFAULT_PATH "\"C:/Program Files/LibreOffice/program/scalc.exe\""
#define CPP_CHECK_DEFAULT_PATH "\"C:/Program Files/Cppcheck/cppcheckgui.exe\""
#define CPP_CHECK_FILTER "CppCheck application (cppCheck.exe)"
//TODO Change path
#define CHECK_STYLE_DEFAULT_PATH "\"C:/Program Files/Cppcheck/cppcheckgui.exe\""
#define CHECK_STYLE_FILTER "CheckStyle application (checkStyle.exe)"

#define EXPLORER_CMD "explorer.exe"

#endif // COMMONELEMENTS_H
