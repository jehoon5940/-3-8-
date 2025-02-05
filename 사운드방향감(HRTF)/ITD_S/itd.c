#include <memory.h>
#include "wave.h"

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

void LeftDelay(unsigned char* input, long size, unsigned char* output)
{

}

void RightDelay(unsigned char* input, long size, unsigned char* output)
{

}

void main()
{
	char name[100] = "headset2.wav";
	char nameoutL[100] = "leftdelayed.wav";
	char nameoutR[100] = "rightdelayed.wav";
	unsigned char* data = NULL;

	RiffHeader R;
	FormatChunk F;
	DataChunk D;

	ReadWave(name, &R, &F, &D); 

	data = (unsigned char*)malloc(sizeof(char)*D.chunkSize*2); 

	LeftDelay(D.field.waveformData, D.chunkSize, data);
	WriteWave(nameoutL, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 2, data,  D.chunkSize*2);

	RightDelay(D.field.waveformData, D.chunkSize, data);
	WriteWave(nameoutR, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 2, data,  D.chunkSize*2);

	free(data);
}
