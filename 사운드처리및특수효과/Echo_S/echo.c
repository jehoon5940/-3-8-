#include <memory.h>
#include "wave.h"

#define CLIPPING(x) (x) < 0 ? 0 : (x) > 255 ? 255 : (x)

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

void main()
{
	char name[100] = "demo.wav";
	char nameout[100] = "echo.wav";

	long i;

	RiffHeader R;
	FormatChunk F;
	DataChunk D;
	unsigned char *data;
	double gamma;
	int delay;

	ReadWave(name, &R, &F, &D); 

	gamma = 0.5;
	delay = 2000;
	data = D.field.waveformData;

	for(i=0;i<D.chunkSize;i++){
		if(i<delay) continue;
		else	data[i] = CLIPPING((data[i]-128)+gamma*(data[i-delay]-128)+128.5);
	}

	WriteWave(nameout, F.field.wBitsPerSample, F.field.dwSamplesPerSec, F.field.wChannels, data,  D.chunkSize);

}
