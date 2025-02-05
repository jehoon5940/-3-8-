#include <memory.h>
#include "wave.h"
#include "hrtf.h"

#define CLIPPING(x) (x) < 0 ? 0 : (x) > 255 ? 255 : (x)

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

void Convolution8(unsigned char* mono, long data_size, unsigned char* stereo)
{

}

unsigned char* MemoryAllocationAndDataCopy(unsigned char* waveformdata, long char_size, int hrtf_length)
{
	unsigned char* tmp;
	long i;

	tmp = (unsigned char*)malloc(sizeof(char)*(char_size+2*hrtf_length));

	for(i=0;i<hrtf_length;i++) tmp[i] = 128;
	for(i=hrtf_length;i<char_size+hrtf_length;i++) tmp[i] = waveformdata[i-hrtf_length];
	for(i=char_size+hrtf_length;i<char_size+2*hrtf_length;i++) tmp[i] = 128;

	return((unsigned char*)(tmp+hrtf_length));
}


void main()
{
	char name[100] = "headset2.wav";
	char nameout[100];
	unsigned char* pcm_data = NULL;
	unsigned char* directed_pcm_data = NULL;
	int ELEV, AZIM;
	RiffHeader R;
	FormatChunk F;
	DataChunk D;

  	ELEV = 0;	AZIM = 40;
	InitializationHRTF(ETRI);
	GetHRTF(ELEV, AZIM);

	ReadWave(name, &R, &F, &D); 

	directed_pcm_data = (unsigned char*)malloc(sizeof(char)*D.chunkSize*2); 

	pcm_data = MemoryAllocationAndDataCopy(D.field.waveformData, D.chunkSize, HRTF_LENGTH);

	Convolution8(pcm_data, D.chunkSize, directed_pcm_data);

	sprintf(nameout, "E%02dA%02d.wav", ELEV, AZIM);
	WriteWave(nameout, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 2, directed_pcm_data,  D.chunkSize*2);

	free(directed_pcm_data);
	free(pcm_data-HRTF_LENGTH);
}
