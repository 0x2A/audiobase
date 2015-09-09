#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <thread>
#include <QFileDialog>
#include <QSettings>
#include "system/settings.h"

using namespace System;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    System::Settings::Load();

    LoadWindowProperties();

    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    m_AudioEngine = new Audio::AudioEngine(Audio::InterfaceTypes::Jack);
    if(m_AudioEngine->Initialize() != 0)
        QMessageBox::critical(this, "Audio Interface error", "Failed to init audio interface");

    chnl_l = m_AudioEngine->CreateChannel();
    chnl_l->SetBufferSize(m_AudioEngine->SampleRate() * 600); //we need to set the buffer the size of the audio file
                                                            //because QAudioDecoder is loading the whole file at once.
                                                            //we just set the buffer to 600 seconds (10 min)
    chnl_r = m_AudioEngine->CreateChannel();
    chnl_r->SetBufferSize(m_AudioEngine->SampleRate() * 600);

    m_AudioEngine->GetAudioInterface()->ConnectOutputPortToChannel(0, chnl_l);
    m_AudioEngine->GetAudioInterface()->ConnectOutputPortToChannel(1, chnl_r);

    connect(&_audioDecoder, SIGNAL(bufferReady()),
                this, SLOT(transferSamples()));

    connect(&_audioDecoder, SIGNAL(error(QAudioDecoder::Error)),
                this, SLOT(decodingError(QAudioDecoder::Error)));

    QAudioFormat targetAudioFormat;
    targetAudioFormat.setSampleRate(m_AudioEngine->SampleRate());
    targetAudioFormat.setSampleType(QAudioFormat::SignedInt);
    targetAudioFormat.setChannelCount(2);
    targetAudioFormat.setCodec("audio/x-raw");
    _audioDecoder.setAudioFormat(targetAudioFormat);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_AudioEngine;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveWindowProperties();

    Settings::Destroy();
}


void MainWindow::on_actionOpen_triggered()
{
    //TESTCODE: Testing audio engine functionality with QAudioDecoder
    QString fileName = QFileDialog::getOpenFileName(this, "Open mp3 file", QString(), "*.mp3");
    if(!fileName.isEmpty())
    {
           chnl_l->ClearBuffer();
           chnl_r->ClearBuffer();
           _audioDecoder.setSourceFilename(fileName);
           _audioDecoder.start();
    }
}

void MainWindow::on_actionExit_triggered()
{
    //TODO: Check if there is anything to be saved
    QApplication::quit();
}

//TESTCODE: Testing audio engine functionality with QAudioDecoder
void MainWindow::decodingError(QAudioDecoder::Error error)
{
    switch(error) {
        case QAudioDecoder::NoError:
            break;
        case QAudioDecoder::ResourceError:
            QMessageBox::warning(this, "Error", "A media resource couldn't be resolved.");
            break;
        case QAudioDecoder::FormatError:
            QMessageBox::warning(this, "Error", "The format of a media resource isn't supported.");
            break;
        case QAudioDecoder::AccessDeniedError:
            QMessageBox::warning(this, "Error", "There are not the appropriate permissions to play a media resource.");
            break;
        case QAudioDecoder::ServiceMissingError:
            QMessageBox::warning(this, "Error", "A valid playback service was not found, playback cannot proceed.");
            break;
        default:
            QMessageBox::warning(this, "Error", "Decoding failed with an unknown error.");
            break;
    }
}

//TESTCODE: Testing audio engine functionality with QAudioDecoder
void MainWindow::transferSamples()
{
    QAudioBuffer audioBuffer = _audioDecoder.read();
    if(audioBuffer.isValid()) {
        int frames = audioBuffer.frameCount();
        float left[frames];
        float right[frames];


        const QAudioBuffer::S16S *stereoBuffer = audioBuffer.constData<QAudioBuffer::S16S>();
        for (int i = 0; i < frames; i++) {
            left[i]     = (float)(stereoBuffer[i].left / 65536.0);
            right[i]    = (float)(stereoBuffer[i].right / 65536.0);
        }


        chnl_l->Write(left, frames);
        chnl_r->Write(right, frames);
    }
}

void MainWindow::LoadWindowProperties()
{
    restoreGeometry(Settings::GetValue(Settings::Section::UI, "MainWindowGeom").toByteArray());
}

void MainWindow::SaveWindowProperties()
{
    Settings::SetValue(Settings::Section::UI, "MainWindowGeom", saveGeometry());
}
