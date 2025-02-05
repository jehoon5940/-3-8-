#include "wave.h"

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);


#define PI 3.14159265358979323846

unsigned char Harmonics(int type, double f, double t)
{

}


void main()
{
	//도, 레, 미, 파, 솔, 라, 시, 도의 주파수
	static double freq[]={
		264.0, 297.0, 330.0, 352.0, 396.0, 440.0, 495.0, 528.0
	};
	char name[100];
  	long SamplesPerSec = 11025; // 11kHz sampling
	short BitsPerSample = 8; // 8bits
	short Channels = 1; // mono
  	double SamplesPeriod = 1/SamplesPerSec;
  	double PlayTime=1;
	long waveformDataSize;
	unsigned char *waveformData;
  	double t, f;
	long index, length;
	int i, num, type;

	num = 8; // 8개의 음정 
		
	length = (long)(PlayTime*SamplesPerSec*Channels*(BitsPerSample/8));
	waveformDataSize = length * num;
	waveformData = (unsigned char *)malloc(sizeof(char)*waveformDataSize);

	type = 2;
	for(i=0;i<num;i++){
		f = freq[i];  // 음정 
		for(index=0, t=0.0;index<length;index++, t+=1.0/SamplesPerSec)			
			waveformData[length*i+index] = Harmonics(type, f, t);
	}

	sprintf(name, "harmonics%02d.wav", type);
	WriteWave(name, BitsPerSample, SamplesPerSec, Channels, waveformData, waveformDataSize);

	free(waveformData);
}
