

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include "waveFormat.h"

//ヘッダ設定関数
void waveSetHeader(WAVEFORMAT *header, int fs, int channels, int nBits, int dataBytes)
{
    header->riffID = *(FOURCC*)RIFF_ID;
    header->riffSize = dataBytes + sizeof(WAVEFORMAT) - 8;
    header->typeID = *(FOURCC*)WAVE_ID;
    header->fmtID = *(FOURCC*)FMT_ID;
    header->fmtSize = 16;
    header->formatTag = 1;
    header->numChannels = (WORD)channels;
    header->samplesPerSec = fs;
    header->avgBytesPerSec = (DWORD)(fs*channels*nBits/8);
    header->dataFrameSize = (WORD)(channels*nBits/8);
    header->bitsPerSample = (WORD)nBits;
    header->dataID = *(FOURCC *)DATA_ID;
    header->dataSize = dataBytes;
    return;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("./実行プログラム 長さ 周波数\n");
        exit(1);
    }
    //変数定義
    char *filePath = "tone.wav";
    FILE *fpout;
    short ssample;
    int numSamples;
    int fs = 44100;
    int numBits = PCM16;
    int dataBytes = 0;
    float duration = atof(argv[1]);
    float frequency = atof(argv[2]);
    double fsample;
    double pi = 4 * atan(1.);
    double start = 1.0;
    double end = 1.0e-4;
    
    double current;
    double factor;
    double anglelncrement;
    WAVEFORMAT *header;
    
    
    //再生音パラメータ算出
    numSamples = (int)(duration * fs);
    dataBytes = numSamples * sizeof(short);
    anglelncrement = 2. * pi * frequency/fs;
    factor = pow(end/start, 1.0/numSamples);
    
    //ヘッダ書き込み
    header = (WAVEFORMAT *)malloc(sizeof(WAVEFORMAT));
    waveSetHeader(header, fs, 1, numBits, dataBytes);
    fpout = fopen(filePath, "wb");
    fwrite(header, 1, sizeof(WAVEFORMAT), fpout);
    
    //音データ書き込み
    current = start;
    for(int i = 0; i < numSamples; i++){
        fsample = current * sin(anglelncrement*i);
        current *= factor;
        ssample = (short)(SHRT_MAX * fsample);
        fwrite(&ssample, sizeof(short), 1, fpout);
    }
    printf("%g 秒　%g HzのSine波を　%s に書きこみ\n", duration, frequency, filePath);
    
    //開放
    free(header);
    fclose(fpout);
    
    return 0;
}


