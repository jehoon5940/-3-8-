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


void Subsampling2to1(unsigned char *input, long size, unsigned char *output)
{

}

void DecimationWith1stOrderFilter(unsigned char *input, long size, unsigned char *output)
{

}

void DecimationWith2ndOrderFilter(unsigned char *input, long size, unsigned char *output)
{

}


void main()
{
	RiffHeader R;
	FormatChunk F;
	DataChunk D;
	char name_in[100] = "demo.wav";
	char name_out0[100] = "deci0.wav";
	char name_out1[100] = "deci1.wav";
	char name_out2[100] = "deci2.wav";
	unsigned char *data_out;

	ReadWave(name_in, &R, &F, &D);

	if(F.field.wBitsPerSample!=8 || F.field.wChannels!=1) return;

	data_out = (unsigned char *)malloc(sizeof(char)*(D.chunkSize/2+1));

	Subsampling2to1(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out0, F.field.wBitsPerSample, F.field.dwSamplesPerSec/2, F.field.wChannels, data_out, D.chunkSize/2);

	DecimationWith1stOrderFilter(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out1, F.field.wBitsPerSample, F.field.dwSamplesPerSec/2, F.field.wChannels, data_out, D.chunkSize/2);

	DecimationWith2ndOrderFilter(D.field.waveformData, D.chunkSize, data_out);
	WriteWave(name_out2, F.field.wBitsPerSample, F.field.dwSamplesPerSec/2, F.field.wChannels, data_out, D.chunkSize/2);

	free(data_out);
}
