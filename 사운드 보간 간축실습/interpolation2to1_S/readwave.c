#include "wave.h"

void LongToString(long H_chunkID, char *chunkID)
{
	long MASK = 0x000000FF;

	chunkID[0] = (char)(H_chunkID & MASK);
	chunkID[1] = (char)((H_chunkID >>  8) & MASK);
	chunkID[2] = (char)((H_chunkID >> 16) & MASK);
	chunkID[3] = (char)((H_chunkID >> 24) & MASK);
	chunkID[4] = '\0';
}


int ReadWave(char *filename, RiffHeader *R, FormatChunk *F, DataChunk *D) //wav2dat
{
  FILE *fp;
  HEADER H;
  char chunkID[5];

  if( (fp=fopen(filename,"rb")) == NULL) {
	  printf("\t Reading File Not Found!!!\n");
	  return(0);
  }

  // WAVE header file information 

  while(0 != fread(&H, sizeof(HEADER), 1, fp)){

	LongToString(H.chunkID, chunkID);
 
	if(strcmp(chunkID, "RIFF")==0){
	  R->chunkID = H.chunkID;
	  R->chunkSize = H.chunkSize;
	  fread(&(R->field.wFormat), sizeof(R->field.wFormat), 1, fp);

	  LongToString(R->field.wFormat, chunkID);

	  if(strcmp(chunkID, "WAVE")!=0){
		  printf("\n\t[] Not supported format !!"); 
		  return(0);
	  }
	}
	else if(strcmp(chunkID, "fmt ")==0){
		F->chunkID = H.chunkID;
		F->chunkSize = H.chunkSize;
		fread(&(F->field), sizeof(F->field), 1, fp);
		if(!(F->field.wBitsPerSample == 8) && !(F->field.wBitsPerSample == 16)){
			printf("\n BitsPerSample = %d is not supported !!", F->field.wBitsPerSample);
			return(-1);
		}

		if(H.chunkSize>sizeof(F->field))
			fseek(fp, (long)(H.chunkSize-sizeof(F->field)), SEEK_CUR);
	}
	else if(strcmp(chunkID, "data")==0){
		D->chunkID = H.chunkID;
		D->chunkSize = H.chunkSize;
		D->field.waveformData = (unsigned char *)malloc(sizeof(char)*H.chunkSize);
		if(D->field.waveformData==NULL) return(-1);
		// available only in case of less than 8 bit precision 
		// in case of exceeding 8 bit precision, 
		// waveformData must be converted to a suitable format
		fread(D->field.waveformData, 1, H.chunkSize, fp); 
	}
	else{ // RIFF, fmt , data 외의 chunk는 제외시킴  
		fseek(fp, (long)H.chunkSize, SEEK_CUR);
	}
  }
 
  fclose(fp);

  return(1);
}

unsigned char* WaveToPCM(char* name, long* data_size)
{
	RiffHeader R;
	FormatChunk F;
	DataChunk D;

	ReadWave(name, &R, &F, &D); 

	*data_size = D.chunkSize;
	if(F.field.wBitsPerSample != 8){
		printf("\n BitsPerSample of input wave file MUST be 8 bits !!!");
	}

	return(D.field.waveformData);

}
