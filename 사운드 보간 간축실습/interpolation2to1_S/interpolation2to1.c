#include "wave.h"

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

// 0과 255내로 값을 제한함 
#define CLIPPING(x) (x) < 0 ? 0 : (x) > 255 ? 255 : (x)

void InterpolationZeroOrder(unsigned char *input, long size, unsigned char *output)
{

}

void Interpolation1stOrder(unsigned char *input, long size, unsigned char *output)
{

}

void Interpolation2ndOrder(unsigned char *input, long size, unsigned char *output)
{

}


void main()
{
	RiffHeader R;
	FormatChunk F;
	DataChunk D;
	char name_in[100] = "demo.wav";
	char name_out0[100] = "inter0.wav";
	char name_out1[100] = "inter1.wav";
	char name_out2[100] = "inter2.wav";
	unsigned char *data_out;

	ReadWave(name_in, &R, &F, &D);

	if(F.field.wBitsPerSample!=8 || F.field.wChannels!=1) return;

	data_out = (unsigned char *)malloc(sizeof(char)*D.chunkSize*2);
	InterpolationZeroOrder(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out0, F.field.wBitsPerSample, 2*F.field.dwSamplesPerSec, F.field.wChannels, data_out, D.chunkSize*2);

	Interpolation1stOrder(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out1, F.field.wBitsPerSample, 2*F.field.dwSamplesPerSec, F.field.wChannels, data_out, D.chunkSize*2);

	Interpolation2ndOrder(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out2, F.field.wBitsPerSample, 2*F.field.dwSamplesPerSec, F.field.wChannels, data_out, D.chunkSize*2);

	free(data_out);

}
