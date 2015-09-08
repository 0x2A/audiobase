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


public Q_SLOTS:

    void on_actionOpen_triggered();

    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    void decodingError(QAudioDecoder::Error error);
    void transferSamples();

private:
    Ui::MainWindow *ui;
    Audio::AudioEngine *m_AudioEngine;

    Audio::Channel* chnl_l;
    Audio::Channel* chnl_r;

    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    QAudioDecoder _audioDecoder;
};

#endif // MAINWINDOW_H
