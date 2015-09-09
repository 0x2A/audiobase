#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Audio/audioengine.h"
#include <QAudioDecoder>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public Q_SLOTS:

    void on_actionOpen_triggered();
    void on_actionExit_triggered();

    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    void decodingError(QAudioDecoder::Error error);
    void transferSamples();

private:

    //Loads window poperties like position and size from the config
    void LoadWindowProperties();

    //Saves window poperties like position and size to the config
    void SaveWindowProperties();

    Ui::MainWindow *ui;
    Audio::AudioEngine *m_AudioEngine;

    Audio::Channel* chnl_l;
    Audio::Channel* chnl_r;

    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    QAudioDecoder _audioDecoder;
};

#endif // MAINWINDOW_H
