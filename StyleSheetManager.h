#ifndef STYLESHEETMANAGER_H
#define STYLESHEETMANAGER_H

#include <QString>
#include <QHeaderView>






class StyleSheetManager {
public:

    static QString mainWindow() {
        return   "QMainWindow {"
                 "    border: none;"
                 "    border: 3px solid navy;"
                 "    border-radius: 20px;"
                 "}";}


    static QString treeWidget() {
        return  "QTreeWidget {"
                "    background-color: #e0e0e0;"
                "    border: 1px solid #cccccc;"
                "    border-radius: 8px;"
                "    font-family: 'Segoe UI', sans-serif;"
                "    font-size: 14px;"
                "    color: #333333;"
                "    outline: none;"
                "    padding: 10px;"
                "    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);"
                "}"
                "QTreeWidget::item {"
                "    background-color: #ffffff;"
                "    border: 1px solid #333333;"
                "    border-radius: 6px;"
                "    padding: 4px;"
                "    margin-bottom: 6px;"
                "    transition: background-color 0.3s ease, transform 0.2s ease;"
                "}"
                "QTreeWidget::item:selected {"
                "    background-color: #004C99;"
                "    color: white;"
                "    transform: scale(1.01);"
                "}"
                "QTreeWidget::item:hover {"
                "    background-color: #FFCC00;"
                "    cursor: pointer;"
                "    transform: scale(1.02);"
                "}"
                "QTreeWidget::item:disabled {"
                "    background-color: #f9f9f9;"
                "    color: #bbb;"
                "}"

                ;}
    static QString header() {
        return   "QHeaderView::section {"
                 "    background-color: #004C99;"
                 "    color: #FFCC00;"
                 "    padding: 6px;"
                 "    font-family: 'Segoe UI', sans-serif;"
                 "    font-size: 16px;"
                 "    font-weight: bold;"
                 "    border: 1px solid #cccccc;"
                 "    border-radius: 4px;"
                 "    text-align: center;"
                 "    margin-bottom: 6px;"
                 "}"
                 "QHeaderView::section:hover {"
                 "    background-color: #FFCC00;"
                 "    color: black;"
                 "    cursor: pointer;"
                 "}"
                 "QHeaderView {"
                 "    background-color: transparent;"
                 "    border: none;"
                 "}";}


    static QString buttonStyle() {
          return "QPushButton {"
            "    background-color: #004C99;"
            "    color: #FFCC00;"
            "    border: 2px solid #004C99;"
            "    border-radius: 5px;"
            "    padding: 5px 10px;"
            "    font-size: 14px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #ADD8E6;"
            "    color: #FFEB3B;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #003366;"
            "    border-color: #002244;"
            "}"
            "QPushButton:disabled {"
            "    background-color: #e0e0e0;"
            "    color: #a0a0a0;"
            "}";}

   static QString ProgressBarStyle(){
          return  "QProgressBar {"
            "border: 2px solid #004C99;"
            "border-radius: 5px;"
            "background-color: #f3f3f3;"
            "text-align: center;"
            "}"
            "QProgressBar::chunk {"
            "background-color: #FFCC00;"
            "min-width: 20px;"
            "max-width: 50px;"
            "border-radius: 5px;"
            "}"
            "QProgressBar:disabled {"
            "background-color: #ddd;"
            "border-color: #aaa;"
                  "}" ;}


   static QString LabelStyle(){
          return "QLabel {"
            "    font-family: 'Segoe UI', sans-serif;"
            "    font-size: 16px;"
            "    color: #333333;"
            "    background-color: #f9f9f9;"
            "    padding: 10px;"
            "    border-radius: 8px;"
            "    border: 2px solid #FFCC00;"
            "}"
            "QLabel:hover {"
            "    background-color: #e9e9e9;"
            "    color: #004C99;"
            "}"
            "QLabel:disabled {"
            "    color: #aaa;"
            "    background-color: #ddd;"
                 "}";}

   static QString LabelStyle2(){
          return "QLabel {"
            "    font-family: 'Segoe UI', sans-serif;"
            "    font-size: 16px;"
            "    color: #333333;"
            "    background-color: #f9f9f9;"
            "    border-radius: 8px;"
            "    border: 2px solid #FFCC00;"
            "    min-width: 180px;"
            "    max-width: 300px;"
            "    max-height: 400px;"
            "    word-wrap: break-word;"
            "    text-align: center;"
            "    qproperty-alignment: AlignCenter;"
            "}"
            "QLabel:hover {"
            "    background-color: #e9e9e9;"
            "    color: #004C99;"
            "}"
            "QLabel:disabled {"
            "    color: #aaa;"
            "    background-color: #ddd;"
                 "}";}


   static QString dialogStyleSheet(){
          return "QDialog {"
            "    background-color: #f9f9f9;"
            "    border-radius: 10px;"
            "    font-family: 'Segoe UI', sans-serif;"
            "    font-size: 14px;"
            "    color: #333333;"
            "    border: 2px solid #004C99;"
            "    padding: 10px;"
            "    min-width: 300px;"
            "}"
            "QComboBox {"
            "    font-size: 14px;"
            "    color: #333333;"
            "    border: 1px solid #004C99;"
            "    padding: 5px;"
            "    background-color: #ffffff;"
            "}"
            "QDialogButtonBox {"
            "    font-size: 14px;"
            "}"
            "QDialogButtonBox QPushButton {"
            "    background-color: #004C99;"
            "    color: #FFEB3B;"
            "    border: 1px solid #004C99;"
            "    border-radius: 5px;"
            "    padding: 5px 15px;"
            "    font-size: 14px;"
            "    margin: 5px;"
            "}"
            "QDialogButtonBox QPushButton:hover {"
            "    background-color: #003366;"
            "}"
            "QDialogButtonBox QPushButton:pressed {"
            "    background-color: #003366;"
                 "}";}

   static QString lineEditStyle(){
          return  "QLineEdit {"
            "    border: 2px solid #004C99;"
            "    border-radius: 5px;"
            "    padding: 5px;"
            "    font-size: 12px;"
            "    color: #004C99;"
            "    background-color: #f3f3f3;"
            "}"
            "QLineEdit:disabled {"
            "    background-color: #e0e0e0;"
            "    color: #a0a0a0;"
            "}";}

   static QString listWidgetStyle(){
         return   "QListWidget {"
            "    background-color: #e0e0e0;"
            "    color: #004C99;"
            "    border: 2px solid #004C99;"
            "    border-radius: 8px;"
            "    padding: 5px;"
            "}"
            "QListWidget::item {"
            "    border: 1px solid #004C99;"
            "    border-radius: 4px;"
            "    margin: 2px;"
            "    padding: 5px;"
            "    background-color: #f3f3f3;"
            "    color: #004C99;"
            "}"
            "QListWidget::item:selected {"
            "    background-color: #004C99;"
            "    color: #FFEB3B;"
            "}";}



   static QString modeComboBoxStyle(){
      return "QComboBox {"
             "    background-color: #e0e0e0;"
             "    border: 1px solid #cccccc;"
             "    border-radius: 8px;"
             "    font-family: 'Segoe UI', sans-serif;"
             "    font-size: 14px;"
             "    color: #333333;"
             "    padding: 5px 10px;"
             "    min-width: 120px;"
             "}"
             "QComboBox::drop-down {"
             "    border: none;"
             "    background: #004C99;"
             "    width: 20px;"
             "    border-radius: 8px;"
             "}"
             "QComboBox::down-arrow {"
             "    image: url(:/icons/down-arrow.png);"
             "    width: 14px;"
             "    height: 14px;"
             "}"
             "QComboBox QAbstractItemView {"
             "    background-color: #ffffff;"
             "    border-radius: 8px;"
             "    padding: 5px;"
             "    selection-background-color: #004C99;"
             "    selection-color: white;"
             "}"
             "QComboBox QAbstractItemView::item:hover {"
             "    background-color: #FFCC00;"
             "}"
             "QComboBox::disabled {"
             "    background-color: #f9f9f9;"
             "    color: #bbb;"
             "}";}


    };


#endif // STYLESHEETMANAGER_H
