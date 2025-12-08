#ifndef DEBUG_H
#define DEBUG_H

/*  			include start  			*/
#include "common.h"

/*  			include end  			*/

/*  			define start  			*/

#define OTHER_CPYBUFF_LEN	5
#define CLEAR_SCR           "\033[2J"
#define CLEAR_X0Y0          "\033[0;0H"
#define CMD_ESC		27
#define CMD_ENTER	13
#define CMD_SPACE	32


#define DEBUG_STEP_SIZE		20


#define DEBUG_IBUFF1_SIZE	20
#define DEBUG_IBUFF2_SIZE	20
#define DEBUG_IBUFF3_SIZE	20

#define DEBUG_CBUFF1_SIZE	20
#define DEBUG_CBUFF2_SIZE	20
#define DEBUG_CBUFF3_SIZE	20

#define DEBUG_ICPY1_SIZE		20
#define DEBUG_ICPY2_SIZE		20
#define DEBUG_ICPY3_SIZE		20
#define DEBUG_ICPY_D_SIZE		20

#define DEBUG_CCPY1_SIZE		20
#define DEBUG_CCPY2_SIZE		20
#define DEBUG_CCPY3_SIZE		20
#define DEBUG_CPY_D_SIZE		10
#define DEBUG_CPY_D_MAIN_SIZE	10
#define DEBUG_CNT_SIZE			10
#define DEBUG_DATAVIEW_SIZE		10




#define DEBUG_CPY_S_MAIN_SIZE	 5
#define DEBUG_CPY_S_SIZE		 5


#define DEBUG_TRACE_SIZE	     5
#define DEBUG_AGING_SIZE	 	10


/*  			define end  			*/



/*  			enum start  			*/

/*  			enum end  				*/



/*  			stuct start  			*/
typedef struct
{
	int d1,d2,d3,d4;
	int diBuff1[10];
	int diBuff2[10];
	int diBuff3[10];
	uint8_t dcBuff1[10];
	uint8_t dcBuff2[10];
	uint8_t dcBuff3[10];

	int step[DEBUG_STEP_SIZE];
	char trace[DEBUG_TRACE_SIZE];
	char traceCnt;
	int mcpyS[DEBUG_CPY_S_MAIN_SIZE][DEBUG_CPY_S_SIZE];//
	char mcpySCnt;
	uint8_t button1,button2,button3;
	uint8_t gpioRead[10];

	int timeStart1,timeStart2,timeStart3;
	int timeTerm1,timeTerm2,timeTerm3;
	int cnt[DEBUG_CNT_SIZE];
	char txDflag;
	int dataView[DEBUG_DATAVIEW_SIZE];
	int timePre1, timePre2,timePre3;
	int timeRatio1,timeRatio2,timeRatio3;
	int agingBuff[DEBUG_AGING_SIZE]; // 미리 정의 해놔야함
	int agingCnt;
	int diff1,diff2,diff3;// 모두 0xffff로 초기화 해놔야함

	int ibuff1[DEBUG_IBUFF1_SIZE];
	int icnt1;
	int ibuff2[DEBUG_IBUFF2_SIZE];
	int icnt2;
	int ibuff3[DEBUG_IBUFF3_SIZE];
	int icnt3;

	char cbuff1[DEBUG_CBUFF1_SIZE];
	int ccnt1;
	char cbuff2[DEBUG_CBUFF2_SIZE];
	int ccnt2;
	char cbuff3[DEBUG_CBUFF3_SIZE];
	int ccnt3;

	int Icpy1[DEBUG_ICPY1_SIZE];
	int Icpy2[DEBUG_ICPY2_SIZE];
	int Icpy3[DEBUG_ICPY3_SIZE];

	char ccpy1[DEBUG_CCPY1_SIZE];
	char ccpy2[DEBUG_CCPY2_SIZE];
	char ccpy3[DEBUG_CCPY3_SIZE];


	char mcpyC[DEBUG_CPY_D_MAIN_SIZE][DEBUG_CPY_D_SIZE];
	int cpyCnt;
	uint8_t txCallback;

} DEBUG_T;

/*  			stuct end  				*/



/*  			function start  		*/
uint32_t DeGetTime();
void ddInit();
void ddFunc1(char*);
void ddFunc2();
void ddFunc3();


void ddClearIntBuff(int* buff, int*cnt, int size);
void ddClearCharBuff(char* buff, int*cnt, int size);
void ddStep(char data);
void ddCnt(char data);
void ddIBuff1(int data);
void ddIBuff2(int data);
void ddIBuff3(int data);
void ddCBuff1(char data);
void ddCBuff2(char data);
void ddCBuff3(char data);
void ddICpy1(int* cpyBff, int len);
void ddICpy2(int* cpyBff, int len);
void ddICpy3(int* cpyBff, int len);
void ddMCpyc(char* cpyBff, int len);
void ddCCpy1(char* cpyBff, int len);
void ddCCpy2(char* cpyBff, int len);
void ddCCpy3(char* cpyBff, int len);
void ddGpio(GPIO_TypeDef *gpio,uint16_t pin, uint8_t ch);
void ddTimeStart1();
int ddTimeEnd1();
void ddTimeStart2();
int ddTimeEnd2();
void ddTimeStart3();
int ddTimeEnd3();
int ddTimeRatio1();
int ddTimeRatio2();
int ddTimeRatio3();
int ddButton1();
int ddButton2();
int ddButton3();
int ddAgingBuff();
void ddStepDe(char step, char limt, int data0, int data1, int data2, int data3, int data4 );
void ddCmd_Tx();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t ddCMD_RX_Parssing(uint8_t data);
void ddbugConfig();
void uart_send_string(const char *str) ;
void send_debug_info_uart(const char *function, int line) ;
void wndks_function() ;
int ddDiff1(int data);
int ddDiff2(int data);
int ddDiff3(int data);


/*  			function end  			*/


/*  			extern start  		*/
extern DEBUG_T dd;


/*  			extern end  			*/

#endif
//dubug.h
