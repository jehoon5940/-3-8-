#include "wave.h"

int WriteWave2(char *filename, RiffHeader R, FormatChunk F, DataChunk D)
{
	FILE *fp;

	if((fp=fopen(filename, "wb")) == NULL){
		printf("\t File Open Failure!!!\n");
		return(0);
	}

	fwrite(&R, sizeof(R), 1, fp);

	F.chunkSize = 16;
	fwrite(&F, sizeof(F), 1, fp);

	fwrite(&(D.chunkID), sizeof(D.chunkID), 1, fp);
	fwrite(&(D.chunkSize), sizeof(D.chunkSize), 1, fp);
	fwrite(D.field.waveformData, sizeof(char), D.chunkSize, fp);

	fclose(fp);

	return(1);
}

int WriteWave(char *name, 
		      short BitsPerSample,   // 8bit과 16bit만 허용 
		      long SamplesPerSec,
		      short Channel,
	 		  unsigned char *waveform_data,
			  long waveform_data_size
)
{
	RiffHeader R;
	FormatChunk F;
	DataChunk D;

	R.chunkID = 0x46464952; // "RIFF"
	R.chunkSize = 16 + waveform_data_size + 20;
	R.field.wFormat = 0x45564157; // "WAVE"
	
	F.chunkID = 0x20746d66;  // "fmt "
	F.chunkSize = 16;
	F.field.wFormatTag = 1;
	F.field.wChannels = Channel; 
	F.field.dwAvgBytesPerSec = SamplesPerSec * Channel * (BitsPerSample/8);
	F.field.dwSamplesPerSec = SamplesPerSec;
	F.field.wBitsPerSample = BitsPerSample;
	F.field.wBlockAlign =  Channel*(BitsPerSample/8);
	
	D.chunkID = 0x61746164;   // "data"
	D.chunkSize = waveform_data_size;

	D.field.waveformData = waveform_data;

	WriteWave2(name, R, F, D);

	return(1);
}



