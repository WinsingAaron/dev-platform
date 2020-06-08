//
// Created by Jsiyong on 2020-06-07.
//
#include <QtGui>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QSplitter *splitter = new QSplitter;

    setCentralWidget(splitter);

    QWidget *editorContent = new QWidget;

    splitter->addWidget(editorContent);

    QVBoxLayout *layout = new QVBoxLayout;

    editorContent->setLayout(layout);

    editor = new QPlainTextEdit;

    layout->addWidget(editor);

    pb_commit = new QPushButton(tr("Commit"));

    connect(pb_commit, SIGNAL(clicked()), this, SLOT(runPythonCode()));

    layout->addWidget(pb_commit);

    scene = new QGraphicsScene(this);

    viewer = new QGraphicsView;

    viewer->setScene(scene);

    splitter->addWidget(viewer);

    splitter->setSizes(QList<int>() << 400 << 600);

}

MainWindow::~MainWindow() { ; }

void MainWindow::runPythonCode() {

    emit runSignal();
    emit runSignalInt(12);
    emit runPythonCode(editor->toPlainText());
    setWindowTitle(editor->toPlainText());

}
