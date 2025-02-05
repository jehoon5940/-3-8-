
// ����� HRTF DB ��ó 
#define ETRI 1
#define MIT  2

#define TOTAL_HRTF_DATA_LENGTH 370688
#define HRTF_LENGTH 128

extern int HRTF_MAP[14][361];					//HRTF ����Ÿ ���� ���� �迭
extern short HRTF_DAT[TOTAL_HRTF_DATA_LENGTH];	//��ü HRTF ����Ÿ�� ���� �޸� ����
extern float HRTF_L[HRTF_LENGTH];				//���� HRTF
extern float HRTF_R[HRTF_LENGTH];				//������ HRTF

void InitializationHRTF(int db_name);
void GetHRTF(int ELEV, int AZIM);