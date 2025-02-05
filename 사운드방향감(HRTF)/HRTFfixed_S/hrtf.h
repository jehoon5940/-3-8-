
// 사용할 HRTF DB 출처 
#define ETRI 1
#define MIT  2

#define TOTAL_HRTF_DATA_LENGTH 370688
#define HRTF_LENGTH 128

extern int HRTF_MAP[14][361];					//HRTF 데이타 맵을 담을 배열
extern short HRTF_DAT[TOTAL_HRTF_DATA_LENGTH];	//전체 HRTF 데이타를 담을 메모리 공간
extern float HRTF_L[HRTF_LENGTH];				//왼쪽 HRTF
extern float HRTF_R[HRTF_LENGTH];				//오른쪽 HRTF

void InitializationHRTF(int db_name);
void GetHRTF(int ELEV, int AZIM);