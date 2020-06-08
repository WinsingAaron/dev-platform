//
// Created by Jsiyong on 2020-06-07.
//

#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include "macros.h"

class QPushButton;

class QGraphicsView;

class QGraphicsScene;

class QPlainTextEdit;


class BINDINGS_API MainWindow
        : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0L);

    virtual~ MainWindow();

//signals:
Q_SIGNALS:

    void runSignal();

    void runSignalInt(int);

    void runPythonCode(QString);

//private slots:
public slots://Q_SLOTS:
    void runPythonCode();

public:
    QGraphicsView *viewer;
    QGraphicsScene *scene;
    QPlainTextEdit *editor;
    QPushButton *pb_commit;
};

#endif //TEST_PYTHON_BINGS_MAINWINDOW_H
