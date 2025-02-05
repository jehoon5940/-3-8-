#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define ID long

typedef struct {
	ID chunkID;
	long chunkSize;
} HEADER;

typedef struct {
	long wFormat;
} subRiffHeader;

typedef struct {
	ID chunkID;
	long chunkSize;
	subRiffHeader field;
} RiffHeader;

typedef struct {
	short wFormatTag; // PCM = 1 , Values other than 1 indicate some form of compression 
	unsigned short wChannels; // the number of audio channels(Mono = 1, Stereo = 2, etc)
	unsigned long dwSamplesPerSec; // sampling rate, or sample frame per sec
	unsigned long dwAvgBytesPerSec; //the number of bytes(stereo의 경우, 2*dwSamplesPerSec)
	unsigned short wBlockAlign; //the size of a sample frame, in terms of bytes: wBlockAlign = wChannels * (wBitsPerSample / 8)
	unsigned short wBitsPerSample; //the bit resolution of a sample point 
/* Note: there may be additional fields here, depending upon wFormatTag. */ 
} subFormatChunk;

typedef struct { 
	ID chunkID; //ASCII코드로 “fmt " (0x666d7420 big-endian form). 
	long chunkSize; //16 for PCM the size of the rest of the chunk which follows this number 
	subFormatChunk field;
} FormatChunk; 

typedef struct {
	unsigned char *waveformData;
} subDataChunk;

typedef struct { 
	ID chunkID; //ASCII코드로 “data" (0x64617461 big-endian form). 
	long chunkSize; //the number of remaining bytes in the chunk after the chunkSize field
	subDataChunk field; 
} DataChunk; 
