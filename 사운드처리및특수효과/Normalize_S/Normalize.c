#include "wave.h"

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

#define CLIPPING(x) (x) < 0 ? 0 : (x) > 255 ? 255 : (x)
#define PI 3.14159265358979323846

// 8bit 데이터의 최대 진폭을 찾음 
unsigned char GetMax8(unsigned char* data, long size)
{
	long i;
	unsigned char max;

	max = abs(data[0]-128);

	for(i=1;i<size;i++)
		if(abs(data[i]-128)>max) max = abs(data[i]-128);

	return(max);
}

void main()
{
	char name_in[100] = "headset2.wav";
	char name_out[100] = "normalize.wav";

	long i;
	unsigned char *data, maxvalue;
	double scale;

	RiffHeader R;
	FormatChunk F;
	DataChunk D;


	ReadWave(name_in, &R, &F, &D);

	data = D.field.waveformData;

	maxvalue = GetMax8(D.field.waveformData, D.chunkSize);
	scale = (double)128/maxvalue;

	for(i=0;i<D.chunkSize;i++)
		data[i] = CLIPPING((data[i]-128)*scale + 128.5);
	WriteWave(name_out, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 
		F.field.wChannels, D.field.waveformData, D.chunkSize);
}
