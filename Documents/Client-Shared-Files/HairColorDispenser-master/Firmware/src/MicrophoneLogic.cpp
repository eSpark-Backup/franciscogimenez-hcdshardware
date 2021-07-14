#include "MicrophoneLogic.hpp"
#include "Arduino.h"
#include <FS.h>
#include "Libraries/Wav.h"
#include "Libraries/I2S.h"
#include <SD.h>

#define I2S_MODE I2S_MODE_ADC_BUILT_IN

// const int record_time = 10;  // second
// const char filename[] = "/sound.wav";

// const int headerSize = 44;
// const int waveDataSize = record_time * 88000;
// const int numCommunicationData = 8000;
// const int numPartWavData = numCommunicationData/4;
// byte header[headerSize];
// char communicationData[numCommunicationData];
// char partWavData[numPartWavData];
// File file;

MicrophoneLogic::MicrophoneLogic()
{

}

MicrophoneLogic::~MicrophoneLogic()
{

}

void MicrophoneLogic::RecordFromMicrophone(int duration)
{
    // CreateWavHeader(header, waveDataSize);

    // file = SD.open(filename, FILE_WRITE);
    // if (!file) return;
    // file.write(header, headerSize);
    // I2S_Init(I2S_MODE, I2S_BITS_PER_SAMPLE_32BIT);
    // for (int j = 0; j < waveDataSize/numPartWavData; ++j)
    // {
    //     I2S_Read(communicationData, numCommunicationData);
    //     for (int i = 0; i < numCommunicationData/8; ++i)
    //     {
    //         partWavData[2*i] = communicationData[8*i + 2];
    //         partWavData[2*i + 1] = communicationData[8*i + 3];
    //     }
    //     file.write((const byte*)partWavData, numPartWavData);
    // }
    // file.close();

}
