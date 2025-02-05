#include <memory.h>
#include "wave.h"

#define CLIPPING(x) (x) < 0 ? 0 : (x) > 255 ? 255 : (x)
#define PI 3.14159265358979323846

int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D);
int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
);

unsigned char* MemoryAllocationAndDataCopy(unsigned char* waveformdata, long char_size, int boundary_length)
{
	unsigned char* tmp;
	long i;

	tmp = (unsigned char*)malloc(sizeof(char)*(char_size+2*boundary_length));

	for(i=0;i<boundary_length;i++) tmp[i] = 128;
	for(i=boundary_length;i<char_size+boundary_length;i++) tmp[i] = waveformdata[i-boundary_length];
	for(i=char_size+boundary_length;i<char_size+2*boundary_length;i++) tmp[i] = 128;

	return((unsigned char*)(tmp+boundary_length));

}

// filter size는 홀수만 허용
// sin(w_c*n)/(pi*n)
void LPF(double f_c, int filterSize, double *filter)
{

}

void HPF(double f_c, int filterSize, double *filter)
{

}

void BPF(double f_1, double f_2, int filterSize, double *filter)
{

}

void Filtering(unsigned char* in, int size, double *filter, int filterSize, unsigned char* out)
{

}


void main()
{
	RiffHeader R;
	FormatChunk F;
	DataChunk D;
	char name[100] = "demo.wav";
	char nameout1[100] = "LPF.wav";
	char nameout2[100] = "HPF.wav";
	char nameout3[100] = "BPF.wav";
	unsigned char *pcm_data, *data_out;
	double filter[21];
	int filterSize = 21;
	double f_c, f_1, f_2;

	ReadWave(name, &R, &F, &D); 

	pcm_data = MemoryAllocationAndDataCopy(D.field.waveformData, D.chunkSize, (filterSize-1)/2);
	data_out = (unsigned char *)malloc(sizeof(char)*D.chunkSize);

	f_c = 1.0/16.0;
	LPF(f_c, filterSize, filter);
	Filtering(pcm_data, D.chunkSize, filter, filterSize, data_out);

	WriteWave(nameout1, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 
		F.field.wChannels, data_out, D.chunkSize);

	f_c = 3.0/16.0;
	HPF(f_c, filterSize, filter);
	Filtering(pcm_data, D.chunkSize, filter, filterSize, data_out);

	WriteWave(nameout2, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 
		F.field.wChannels, data_out, D.chunkSize);

	f_1 = 1.0/16.0; f_2 = 3.0/16.0;
	BPF(f_1, f_2, filterSize, filter);
	Filtering(pcm_data, D.chunkSize, filter, filterSize, data_out);

	WriteWave(nameout3, F.field.wBitsPerSample, F.field.dwSamplesPerSec, 
		F.field.wChannels, data_out, D.chunkSize);

	free(pcm_data-((filterSize-1)/2));
	free(data_out);
}
