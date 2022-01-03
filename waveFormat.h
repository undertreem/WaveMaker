

#include <stdio.h>
#include <stdlib.h>

//量子化ビット数定義
#define PCM16 (16)
#define PCM24 (24)

//符号付き整数の最大値定義
#define MAX_16BIT (32768.0)

//WORD型の定義
typedef unsigned short WORD; //2byte
typedef unsigned int DWORD; //4byte
typedef DWORD FOURCC; //?

//LPCM WAVEデータ構造体の定義
typedef struct waveformat_pcm{
    DWORD riffID;
    DWORD riffSize;
    DWORD typeID;
    DWORD fmtID;
    DWORD fmtSize;
    WORD formatTag;
    WORD numChannels;
    DWORD samplesPerSec;
    DWORD avgBytesPerSec;
    WORD dataFrameSize;
    WORD bitsPerSample;
    DWORD dataID;
    DWORD dataSize;
}WAVEFORMAT;

//チャンクID文字コードの定義
static char RIFF_ID[4] = {'R', 'I', 'F', 'F'};
static char WAVE_ID[4] = {'W', 'A', 'V', 'E'};
static char FMT_ID[4] = {'f', 'm', 't', ' '};
static char DATA_ID[4] = {'d', 'a', 't', 'a'};

