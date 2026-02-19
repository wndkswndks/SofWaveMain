


#include "hifu_ctrl.h"
uint8_t testExpFlag;
ERROR_T m_err;


RF_T m_rf;
EEPROM_T m_eep =
{
//	.rfFrqBuff = {0, 11000, 11000, 11000, 11000, 11000, 11000, 11000},
//	.rfFrqBuff = {0, 11035, 11027, 10962, 10992, 11062, 11045, 11060},//td no 1
	.rfFrqBuff = {0, 11090, 11037, 11030, 11025, 11102, 10972, 11115},//td no 2

};

HAND_T m_hand1;

int AutoWattDefulteTable[78] =
{
255,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1
};
uint8_t AutoDaDefulteTable[78];


uint32_t watt[5] ={10,100,5,20,30};
void Test_Init()
{
//	AutoCal_Avg();
}

void Rf_TD_BLS001_Table_2511()
{
	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11035;
	m_eep.rfFrqBuff[2] = 11027;
	m_eep.rfFrqBuff[3] = 10962;
	m_eep.rfFrqBuff[4] = 10992;
	m_eep.rfFrqBuff[5] = 11062;
	m_eep.rfFrqBuff[6] = 11045;
	m_eep.rfFrqBuff[7] = 11060;

	//no1
	m_eep.rfWattBuff[0] = 0;	   //0
	m_eep.rfWattBuff[1] = 1;    //0.1w
	m_eep.rfWattBuff[2] = 16;   //0.2w
	m_eep.rfWattBuff[3] = 32;   //0.3w
	m_eep.rfWattBuff[4] = 46;   //0.4w
	m_eep.rfWattBuff[5] = 64;   //0.5w
	m_eep.rfWattBuff[6] = 78;   //0.6w
	m_eep.rfWattBuff[7] = 91;   //0.7w
	m_eep.rfWattBuff[8] = 103;  //0.8w
	m_eep.rfWattBuff[9] = 118;  //0.9w
	m_eep.rfWattBuff[10] = 129;  //1.0w
	m_eep.rfWattBuff[11] = 150;  //1.1w
	//no2
	m_eep.rfWattBuff[12] = 1;   //0.1w
	m_eep.rfWattBuff[13] = 19;  //0.2w
	m_eep.rfWattBuff[14] = 37;  //0.3w
	m_eep.rfWattBuff[15] = 54;  //0.4w
	m_eep.rfWattBuff[16] = 69;  //0.5w
	m_eep.rfWattBuff[17] = 80;  //0.6w
	m_eep.rfWattBuff[18] = 96;  //0.7w
	m_eep.rfWattBuff[19] = 110; 	//0.8w
	m_eep.rfWattBuff[20] = 123;  //0.9w
	m_eep.rfWattBuff[21] = 138;  //1.0w
	m_eep.rfWattBuff[22] = 150;  //1.1w
	//no3
	m_eep.rfWattBuff[23] = 1;   //0.1w
	m_eep.rfWattBuff[24] = 13;  //0.2w
	m_eep.rfWattBuff[25] = 31;  //0.3w
	m_eep.rfWattBuff[26] = 45;  //0.4w
	m_eep.rfWattBuff[27] = 60;  //0.5w
	m_eep.rfWattBuff[28] = 72;  //0.6w
	m_eep.rfWattBuff[29] = 86;  //0.7w
	m_eep.rfWattBuff[30] = 97;  //0.8w
	m_eep.rfWattBuff[31] = 114;  //0.9w
	m_eep.rfWattBuff[32] = 125;  //1.0w
	m_eep.rfWattBuff[33] = 140;  //1.1w
	////no4
	m_eep.rfWattBuff[34] = 1;   //0.1w
	m_eep.rfWattBuff[35] = 15;  //0.2w
	m_eep.rfWattBuff[36] = 32;  //0.3w
	m_eep.rfWattBuff[37] = 46;  //0.4w
	m_eep.rfWattBuff[38] = 61;  //0.5w
	m_eep.rfWattBuff[39] = 75;  //0.6w
	m_eep.rfWattBuff[40] = 86;  //0.7w
	m_eep.rfWattBuff[41] = 101;  //0.8w
	m_eep.rfWattBuff[42] = 113;  //0.9w
	m_eep.rfWattBuff[43] = 127;  //1.0w
	m_eep.rfWattBuff[44] = 142;  //1.1w
	//no5
	m_eep.rfWattBuff[45] = 1;   //0.1w
	m_eep.rfWattBuff[46] = 19;  //0.2w
	m_eep.rfWattBuff[47] = 38;  //0.3w
	m_eep.rfWattBuff[48] = 55;  //0.4w
	m_eep.rfWattBuff[49] = 68;  //0.5w
	m_eep.rfWattBuff[50] = 85;  //0.6w
	m_eep.rfWattBuff[51] = 97;  //0.7w
	m_eep.rfWattBuff[52] = 110;  //0.8w
	m_eep.rfWattBuff[53] = 122;  //0.9w
	m_eep.rfWattBuff[54] = 136;  //1.0w
	m_eep.rfWattBuff[55] = 150;  //1.1w
	//no6
	m_eep.rfWattBuff[56] = 1;   //0.1w
	m_eep.rfWattBuff[57] = 21;  //0.2w
	m_eep.rfWattBuff[58] = 35;  //0.3w
	m_eep.rfWattBuff[59] = 50;  //0.4w
	m_eep.rfWattBuff[60] = 64;  //0.5w
	m_eep.rfWattBuff[61] = 80;  //0.6w
	m_eep.rfWattBuff[62] = 91;  //0.7w
	m_eep.rfWattBuff[63] = 104;  //0.8w
	m_eep.rfWattBuff[64] = 117;  //0.9w
	m_eep.rfWattBuff[65] = 128;  //1.0w
	m_eep.rfWattBuff[66] = 150;  //1.1w



}

void Rf_TD_BLS002_Table_2511()
{
	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11090;
	m_eep.rfFrqBuff[2] = 11037;
	m_eep.rfFrqBuff[3] = 11030;
	m_eep.rfFrqBuff[4] = 11025;
	m_eep.rfFrqBuff[5] = 11102;
	m_eep.rfFrqBuff[6] = 10972;
	m_eep.rfFrqBuff[7] = 11115;

	//no1
	m_eep.rfWattBuff[0]		= 0;
	m_eep.rfWattBuff[1]		= 1;		//0.1
	m_eep.rfWattBuff[2]		= 17;		//0.2
	m_eep.rfWattBuff[3]		= 34;		//0.3
	m_eep.rfWattBuff[4]		= 51;		//0.4
	m_eep.rfWattBuff[5]		= 68;		//0.5
	m_eep.rfWattBuff[6]		= 80;		//0.6
	m_eep.rfWattBuff[7]		= 97;		//0.7
	m_eep.rfWattBuff[8]		= 110;		//0.8
	m_eep.rfWattBuff[9]		= 126;		//0.9
	m_eep.rfWattBuff[10]	= 143;		//1.0
	m_eep.rfWattBuff[11]	= 160;		//
	//no2
	m_eep.rfWattBuff[12]	= 1	;		//0.1
	m_eep.rfWattBuff[13]	= 17;		//0.2
	m_eep.rfWattBuff[14]	= 35;		//0.3
	m_eep.rfWattBuff[15]	= 50;		//0.4
	m_eep.rfWattBuff[16]	= 64;		//0.5
	m_eep.rfWattBuff[17]	= 79;		//0.6
	m_eep.rfWattBuff[18]	= 94;		//0.7
	m_eep.rfWattBuff[19]	= 107;		//0.8
	m_eep.rfWattBuff[20]	= 120;		//0.9
	m_eep.rfWattBuff[21]	= 135;		//1.0
	m_eep.rfWattBuff[22]	= 160;		//
	//no3
	m_eep.rfWattBuff[23]	= 1	;		//0.1
	m_eep.rfWattBuff[24]	= 18;		//0.2
	m_eep.rfWattBuff[25]	= 33;		//0.3
	m_eep.rfWattBuff[26]	= 50;		//0.4
	m_eep.rfWattBuff[27]	= 66;		//0.5
	m_eep.rfWattBuff[28]	= 82;		//0.6
	m_eep.rfWattBuff[29]	= 95;		//0.7
	m_eep.rfWattBuff[30]	= 110;		//0.8
	m_eep.rfWattBuff[31]	= 122;		//0.9
	m_eep.rfWattBuff[32]	= 139;		//1.0
	m_eep.rfWattBuff[33]	= 160;		//
	//no4
	m_eep.rfWattBuff[34]	= 1	;		//0.1
	m_eep.rfWattBuff[35]	= 19;		//0.2
	m_eep.rfWattBuff[36]	= 37;		//0.3
	m_eep.rfWattBuff[37]	= 53;		//0.4
	m_eep.rfWattBuff[38]	= 72;		//0.5
	m_eep.rfWattBuff[39]	= 86;		//0.6
	m_eep.rfWattBuff[40]	= 100;		//0.7
	m_eep.rfWattBuff[41]	= 115;		//0.8
	m_eep.rfWattBuff[42]	= 130;		//0.9
	m_eep.rfWattBuff[43]	= 145;		//1.0
	m_eep.rfWattBuff[44]	= 160;		//
	//no5
	m_eep.rfWattBuff[45]	= 1	;		//0.1
	m_eep.rfWattBuff[46]	= 25;		//0.2
	m_eep.rfWattBuff[47]	= 42;		//0.3
	m_eep.rfWattBuff[48]	= 61;		//0.4
	m_eep.rfWattBuff[49]	= 76;		//0.5
	m_eep.rfWattBuff[50]	= 88;		//0.6
	m_eep.rfWattBuff[51]	= 103;		//0.7
	m_eep.rfWattBuff[52]	= 115;		//0.8
	m_eep.rfWattBuff[53]	= 129;		//0.9
	m_eep.rfWattBuff[54]	= 146;		//1.0
	m_eep.rfWattBuff[55]	= 160;		//
	//no6
	m_eep.rfWattBuff[56]	= 1	;		//0.1
	m_eep.rfWattBuff[57]	= 18;		//0.2
	m_eep.rfWattBuff[58]	= 34;		//0.3
	m_eep.rfWattBuff[59]	= 48;		//0.4
	m_eep.rfWattBuff[60]	= 63;		//0.5
	m_eep.rfWattBuff[61]	= 78;		//0.6
	m_eep.rfWattBuff[62]	= 88;		//0.7
	m_eep.rfWattBuff[63]	= 104;		//0.8
	m_eep.rfWattBuff[64]	= 119;		//0.9
	m_eep.rfWattBuff[65]	= 133;		//1.0
	m_eep.rfWattBuff[66]	= 160;		//
	//no7
	m_eep.rfWattBuff[67]	= 1	;		//0.1
	m_eep.rfWattBuff[68]	= 25;		//0.2
	m_eep.rfWattBuff[69]	= 41;		//0.3
	m_eep.rfWattBuff[70]	= 60;		//0.4
	m_eep.rfWattBuff[71]	= 75;		//0.5
	m_eep.rfWattBuff[72]	= 90;		//0.6
	m_eep.rfWattBuff[73]	= 103;		//0.7
	m_eep.rfWattBuff[74]	= 116;		//0.8
	m_eep.rfWattBuff[75]	= 132;		//0.9
	m_eep.rfWattBuff[76]	= 145;		//1.0
	m_eep.rfWattBuff[77]	= 160;		//

}


void Rf_TD_BLS001_Table_2601()
{
	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11035;
	m_eep.rfFrqBuff[2] = 11027;
	m_eep.rfFrqBuff[3] = 10962;
	m_eep.rfFrqBuff[4] = 10992;
	m_eep.rfFrqBuff[5] = 11062;
	m_eep.rfFrqBuff[6] = 11045;
	m_eep.rfFrqBuff[7] = 11060;

	//no.1
	m_eep.rfWattBuff[0]  = 0   ;
	m_eep.rfWattBuff[1]  = 1   ;//0.1w
	m_eep.rfWattBuff[2]  = 9   ;//0.2w
	m_eep.rfWattBuff[3]  = 24  ;//0.3w
	m_eep.rfWattBuff[4]  = 39  ;//0.4w
	m_eep.rfWattBuff[5]  = 50  ;//0.5w
	m_eep.rfWattBuff[6]  = 63  ;//0.6w
	m_eep.rfWattBuff[7]  = 78  ;//0.7w
	m_eep.rfWattBuff[8]  = 89  ;//0.8w
	m_eep.rfWattBuff[9]  = 101 ;//0.9w
	m_eep.rfWattBuff[10] = 115 ;//1.0w
	m_eep.rfWattBuff[11] = 160 ;//1.1w

	//no.2
	m_eep.rfWattBuff[12] = 2   ;//0.1w
	m_eep.rfWattBuff[13] = 18  ;//0.2w
	m_eep.rfWattBuff[14] = 34  ;//0.3w
	m_eep.rfWattBuff[15] = 46  ;//0.4w
	m_eep.rfWattBuff[16] = 60  ;//0.5w
	m_eep.rfWattBuff[17] = 72  ;//0.6w
	m_eep.rfWattBuff[18] = 86  ;//0.7w
	m_eep.rfWattBuff[19] = 98  ;//0.8w
	m_eep.rfWattBuff[20] = 108 ;//0.9w
	m_eep.rfWattBuff[21] = 122 ;//1.0w
	m_eep.rfWattBuff[22] = 160 ;//1.1w

	//no.3
	m_eep.rfWattBuff[23] = 1   ;//0.1w
	m_eep.rfWattBuff[24] = 14  ;//0.2w
	m_eep.rfWattBuff[25] = 28  ;//0.3w
	m_eep.rfWattBuff[26] = 42  ;//0.4w
	m_eep.rfWattBuff[27] = 52  ;//0.5w
	m_eep.rfWattBuff[28] = 64  ;//0.6w
	m_eep.rfWattBuff[29] = 76  ;//0.7w
	m_eep.rfWattBuff[30] = 87  ;//0.8w
	m_eep.rfWattBuff[31] = 101 ;//0.9w
	m_eep.rfWattBuff[32] = 110 ;//1.0w
	m_eep.rfWattBuff[33] = 160 ;//1.1w

	//no.4
	m_eep.rfWattBuff[34] = 1   ;//0.1w
	m_eep.rfWattBuff[35] = 16  ;//0.2w
	m_eep.rfWattBuff[36] = 32  ;//0.3w
	m_eep.rfWattBuff[37] = 46  ;//0.4w
	m_eep.rfWattBuff[38] = 58  ;//0.5w
	m_eep.rfWattBuff[39] = 72  ;//0.6w
	m_eep.rfWattBuff[40] = 82  ;//0.7w
	m_eep.rfWattBuff[41] = 95  ;//0.8w
	m_eep.rfWattBuff[42] = 106 ;//0.9w
	m_eep.rfWattBuff[43] = 117 ;//1.0w
	m_eep.rfWattBuff[44] = 160 ;//1.1w

	//no.5
	m_eep.rfWattBuff[45] = 2   ;//0.1w
	m_eep.rfWattBuff[46] = 22  ;//0.2w
	m_eep.rfWattBuff[47] = 40  ;//0.3w
	m_eep.rfWattBuff[48] = 52  ;//0.4w
	m_eep.rfWattBuff[49] = 64  ;//0.5w
	m_eep.rfWattBuff[50] = 80  ;//0.6w
	m_eep.rfWattBuff[51] = 92  ;//0.7w
	m_eep.rfWattBuff[52] = 102 ;//0.8w
	m_eep.rfWattBuff[53] = 115 ;//0.9w
	m_eep.rfWattBuff[54] = 126 ;//1.0w
	m_eep.rfWattBuff[55] = 160 ;//1.1w

	//no.6
	m_eep.rfWattBuff[56] = 1   ;//0.1w
	m_eep.rfWattBuff[57] = 18  ;//0.2w
	m_eep.rfWattBuff[58] = 36  ;//0.3w
	m_eep.rfWattBuff[59] = 46  ;//0.4w
	m_eep.rfWattBuff[60] = 60  ;//0.5w
	m_eep.rfWattBuff[61] = 71  ;//0.6w
	m_eep.rfWattBuff[62] = 84  ;//0.7w
	m_eep.rfWattBuff[63] = 93  ;//0.8w
	m_eep.rfWattBuff[64] = 108 ;//0.9w
	m_eep.rfWattBuff[65] = 119 ;//1.0w
	m_eep.rfWattBuff[66] = 160 ;//1.1w

	//no.7
	m_eep.rfWattBuff[67] = 2   ;//0.1w
	m_eep.rfWattBuff[68] = 20  ;//0.2w
	m_eep.rfWattBuff[69] = 36  ;//0.3w
	m_eep.rfWattBuff[70] = 50  ;//0.4w
	m_eep.rfWattBuff[71] = 64  ;//0.5w
	m_eep.rfWattBuff[72] = 76  ;//0.6w
	m_eep.rfWattBuff[73] = 88  ;//0.7w
	m_eep.rfWattBuff[74] = 98  ;//0.8w
	m_eep.rfWattBuff[75] = 112 ;//0.9w
	m_eep.rfWattBuff[76] = 122 ;//1.0w
	m_eep.rfWattBuff[77] = 160 ;//1.1w
}
void Rf_TD_BLS002_Table_2602()//260211
{

	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11200;
	m_eep.rfFrqBuff[2] = 11132;
	m_eep.rfFrqBuff[3] = 11142;
	m_eep.rfFrqBuff[4] = 11145;
	m_eep.rfFrqBuff[5] = 11187;
	m_eep.rfFrqBuff[6] = 11085;
	m_eep.rfFrqBuff[7] = 11252;


	//no.1
	m_eep.rfWattBuff[0] =  0 ;
	m_eep.rfWattBuff[1] =  4  ;   //0.1w
	m_eep.rfWattBuff[2] =  30 ;   //0.2w
	m_eep.rfWattBuff[3] =  50 ;   //0.3w
	m_eep.rfWattBuff[4] =  68 ;   //0.4w
	m_eep.rfWattBuff[5] =  90 ;   //0.5w
	m_eep.rfWattBuff[6] =  108;   //0.6w
	m_eep.rfWattBuff[7] =  124;   //0.7w
	m_eep.rfWattBuff[8] =  146;   //0.8w
	m_eep.rfWattBuff[9] =  164;   //0.9w
	m_eep.rfWattBuff[10] =	184;  //1.0w
	m_eep.rfWattBuff[11] =	200;  //1.1w
	//==================
	//no.2
	m_eep.rfWattBuff[12] =	2  ;  //0.1w
	m_eep.rfWattBuff[13] =	24 ;  //0.2w
	m_eep.rfWattBuff[14] =	42 ;  //0.3w
	m_eep.rfWattBuff[15] =	60 ;  //0.4w
	m_eep.rfWattBuff[16] =	74 ;  //0.5w
	m_eep.rfWattBuff[17] =	90 ;  //0.6w
	m_eep.rfWattBuff[18] =	104;  //0.7w
	m_eep.rfWattBuff[19] =	120;  //0.8w
	m_eep.rfWattBuff[20] =	136;  //0.9w
	m_eep.rfWattBuff[21] =	152;  //1.0w
	m_eep.rfWattBuff[22] =	200;  //1.1w
	//==================
	//no.3
	m_eep.rfWattBuff[23] =	2  ;  //0.1w
	m_eep.rfWattBuff[24] =	22 ;  //0.2w
	m_eep.rfWattBuff[25] =	42 ;  //0.3w
	m_eep.rfWattBuff[26] =	60 ;  //0.4w
	m_eep.rfWattBuff[27] =	76 ;  //0.5w
	m_eep.rfWattBuff[28] =	90 ;  //0.6w
	m_eep.rfWattBuff[29] =	108;  //0.7w
	m_eep.rfWattBuff[30] =	122;  //0.8w
	m_eep.rfWattBuff[31] =	136;  //0.9w
	m_eep.rfWattBuff[32] =	154;  //1.0w
	m_eep.rfWattBuff[33] =	200;  //1.1w
	//==================
	//no.4
	m_eep.rfWattBuff[34] =	2  ;  //0.1w
	m_eep.rfWattBuff[35] =	28 ;  //0.2w
	m_eep.rfWattBuff[36] =	50 ;  //0.3w
	m_eep.rfWattBuff[37] =	68 ;  //0.4w
	m_eep.rfWattBuff[38] =	88 ;  //0.5w
	m_eep.rfWattBuff[39] =	104;  //0.6w
	m_eep.rfWattBuff[40] =	122;  //0.7w
	m_eep.rfWattBuff[41] =	140;  //0.8w
	m_eep.rfWattBuff[42] =	154;  //0.9w
	m_eep.rfWattBuff[43] =	172;  //1.0w
	m_eep.rfWattBuff[44] =	200;  //1.1w
	//==================
	//no.5
	m_eep.rfWattBuff[45] =	2  ;  //0.1w
	m_eep.rfWattBuff[46] =	28 ;  //0.2w
	m_eep.rfWattBuff[47] =	50 ;  //0.3w
	m_eep.rfWattBuff[48] =	66 ;  //0.4w
	m_eep.rfWattBuff[49] =	84 ;  //0.5w
	m_eep.rfWattBuff[50] =	98 ;  //0.6w
	m_eep.rfWattBuff[51] =	112;  //0.7w
	m_eep.rfWattBuff[52] =	128;  //0.8w
	m_eep.rfWattBuff[53] =	142;  //0.9w
	m_eep.rfWattBuff[54] =	160;  //1.0w
	m_eep.rfWattBuff[55] =	200;  //1.1w
	//==================
	//no.6
	m_eep.rfWattBuff[56] =	2  ;  //0.1w
	m_eep.rfWattBuff[57] =	22 ;  //0.2w
	m_eep.rfWattBuff[58] =	40 ;  //0.3w
	m_eep.rfWattBuff[59] =	56 ;  //0.4w
	m_eep.rfWattBuff[60] =	72 ;  //0.5w
	m_eep.rfWattBuff[61] =	86 ;  //0.6w
	m_eep.rfWattBuff[62] =	102;  //0.7w
	m_eep.rfWattBuff[63] =	116;  //0.8w
	m_eep.rfWattBuff[64] =	130;  //0.9w
	m_eep.rfWattBuff[65] =	142;  //1.0w
	m_eep.rfWattBuff[66] =	200;  //1.1w
	//==================
	//no.7
	m_eep.rfWattBuff[67] =	6  ;  //0.1w
	m_eep.rfWattBuff[68] =	30 ;  //0.2w
	m_eep.rfWattBuff[69] =	52 ;  //0.3w
	m_eep.rfWattBuff[70] =	70 ;  //0.4w
	m_eep.rfWattBuff[71] =	86 ;  //0.5w
	m_eep.rfWattBuff[72] =	104;  //0.6w
	m_eep.rfWattBuff[73] =	118;  //0.7w
	m_eep.rfWattBuff[74] =	134;  //0.8w
	m_eep.rfWattBuff[75] =	150;  //0.9w
	m_eep.rfWattBuff[76] =	164;  //1.0w
	m_eep.rfWattBuff[77] =	200;  //1.1w

}

void Rf_TD_BLS002_Table_2601()//260125
{

	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11090;
	m_eep.rfFrqBuff[2] = 11037;
	m_eep.rfFrqBuff[3] = 11030;
	m_eep.rfFrqBuff[4] = 11025;
	m_eep.rfFrqBuff[5] = 11102;
	m_eep.rfFrqBuff[6] = 10972;
	m_eep.rfFrqBuff[7] = 11115;


	//no.1
	m_eep.rfWattBuff[0] = 0 ;
	m_eep.rfWattBuff[1] = 1 ; //0.1w
	m_eep.rfWattBuff[2] = 13 ; //0.2w
	m_eep.rfWattBuff[3] = 29 ; //0.3w
	m_eep.rfWattBuff[4] = 43 ; //0.4w
	m_eep.rfWattBuff[5] = 59 ; //0.5w
	m_eep.rfWattBuff[6] = 73 ; //0.6w
	m_eep.rfWattBuff[7] = 89 ; //0.7w
	m_eep.rfWattBuff[8] = 102 ; //0.8w
	m_eep.rfWattBuff[9] = 113 ; //0.9w
	m_eep.rfWattBuff[10] = 127 ; //1.0w
	m_eep.rfWattBuff[11] = 160 ; //1.1w

	//no.2
	m_eep.rfWattBuff[12] = 1 ; //0.1w
	m_eep.rfWattBuff[13] = 16 ; //0.2w
	m_eep.rfWattBuff[14] = 34 ; //0.3w
	m_eep.rfWattBuff[15] = 48 ; //0.4w
	m_eep.rfWattBuff[16] = 60 ; //0.5w
	m_eep.rfWattBuff[17] = 75 ; //0.6w
	m_eep.rfWattBuff[18] = 86 ; //0.7w
	m_eep.rfWattBuff[19] = 100 ; //0.8w
	m_eep.rfWattBuff[20] = 114 ; //0.9w
	m_eep.rfWattBuff[21] = 126 ; //1.0w
	m_eep.rfWattBuff[22] = 160 ; //1.1w

	//no.3
	m_eep.rfWattBuff[23] = 1 ; //0.1w
	m_eep.rfWattBuff[24] = 16 ; //0.2w
	m_eep.rfWattBuff[25] = 30 ; //0.3w
	m_eep.rfWattBuff[26] = 46 ; //0.4w
	m_eep.rfWattBuff[27] = 58 ; //0.5w
	m_eep.rfWattBuff[28] = 73 ; //0.6w
	m_eep.rfWattBuff[29] = 84 ; //0.7w
	m_eep.rfWattBuff[30] = 98 ; //0.8w
	m_eep.rfWattBuff[31] = 110 ; //0.9w
	m_eep.rfWattBuff[32] = 124 ; //1.0w
	m_eep.rfWattBuff[33] = 160 ; //1.1w

	//no.4
	m_eep.rfWattBuff[34] = 1 ; //0.1w
	m_eep.rfWattBuff[35] = 20 ; //0.2w
	m_eep.rfWattBuff[36] = 38 ; //0.3w
	m_eep.rfWattBuff[37] = 50 ; //0.4w
	m_eep.rfWattBuff[38] = 66 ; //0.5w
	m_eep.rfWattBuff[39] = 80 ; //0.6w
	m_eep.rfWattBuff[40] = 94 ; //0.7w
	m_eep.rfWattBuff[41] = 106 ; //0.8w
	m_eep.rfWattBuff[42] = 124 ; //0.9w
	m_eep.rfWattBuff[43] = 136 ; //1.0w
	m_eep.rfWattBuff[44] = 160 ; //1.1w

	//no.5
	m_eep.rfWattBuff[45] = 1 ; //0.1w
	m_eep.rfWattBuff[46] = 22 ; //0.2w
	m_eep.rfWattBuff[47] = 40 ; //0.3w
	m_eep.rfWattBuff[48] = 58 ; //0.4w
	m_eep.rfWattBuff[49] = 72 ; //0.5w
	m_eep.rfWattBuff[50] = 82 ; //0.6w
	m_eep.rfWattBuff[51] = 94 ; //0.7w
	m_eep.rfWattBuff[52] = 108 ; //0.8w
	m_eep.rfWattBuff[53] = 120 ; //0.9w
	m_eep.rfWattBuff[54] = 134 ; //1.0w
	m_eep.rfWattBuff[55] = 160 ; //1.1w

	//no.6
	m_eep.rfWattBuff[56] = 1 ; //0.1w
	m_eep.rfWattBuff[57] = 16 ; //0.2w
	m_eep.rfWattBuff[58] = 30 ; //0.3w
	m_eep.rfWattBuff[59] = 46 ; //0.4w
	m_eep.rfWattBuff[60] = 56 ; //0.5w
	m_eep.rfWattBuff[61] = 70 ; //0.6w
	m_eep.rfWattBuff[62] = 82 ; //0.7w
	m_eep.rfWattBuff[63] = 94 ; //0.8w
	m_eep.rfWattBuff[64] = 107 ; //0.9w
	m_eep.rfWattBuff[65] = 120 ; //1.0w
	m_eep.rfWattBuff[66] = 160 ; //1.1w

	//no.7
	m_eep.rfWattBuff[67] = 1 ; //0.1w
	m_eep.rfWattBuff[68] = 22; //0.2w
	m_eep.rfWattBuff[69] = 38 ; //0.3w
	m_eep.rfWattBuff[70] = 54 ; //0.4w
	m_eep.rfWattBuff[71] = 66 ; //0.5w
	m_eep.rfWattBuff[72] = 80 ; //0.6w
	m_eep.rfWattBuff[73] = 94 ; //0.7w
	m_eep.rfWattBuff[74] = 108 ; //0.8w
	m_eep.rfWattBuff[75] = 120 ; //0.9w
	m_eep.rfWattBuff[76] = 134 ; //1.0w
	m_eep.rfWattBuff[77] = 160 ; //1.1w
}

void Rf_TD_BHB001_Table_260212()//260212
{
	//BHB001
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11395;
	m_eep.rfFrqBuff[1] = 11402;
	m_eep.rfFrqBuff[2] = 11400;
	m_eep.rfFrqBuff[4] = 11392;
	m_eep.rfFrqBuff[5] = 11407;
	m_eep.rfFrqBuff[6] = 11402;
	m_eep.rfFrqBuff[7] = 11412;

	m_eep.rfWattBuff[10] = 160 ; //1.0w
	m_eep.rfWattBuff[21] = 156 ; //1.0w
	m_eep.rfWattBuff[32] = 88 ; //1.0w
	m_eep.rfWattBuff[43] = 158 ; //1.0w
	m_eep.rfWattBuff[54] = 162 ; //1.0w
	m_eep.rfWattBuff[65] = 164 ; //1.0w
	m_eep.rfWattBuff[76] = 156 ; //1.0w

}
void Rf_TD_BHB002_Table_260212()//260212
{
	//BHB002
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11380;
	m_eep.rfFrqBuff[2] = 11350;
	m_eep.rfFrqBuff[3] = 11305;
	m_eep.rfFrqBuff[4] = 11345;
	m_eep.rfFrqBuff[5] = 11335;
	m_eep.rfFrqBuff[6] = 11352;
	m_eep.rfFrqBuff[7] = 11332;

	m_eep.rfWattBuff[10] = 162 ; //1.0w
	m_eep.rfWattBuff[21] = 144 ; //1.0w
	m_eep.rfWattBuff[32] = 144 ; //1.0w
	m_eep.rfWattBuff[43] = 156 ; //1.0w
	m_eep.rfWattBuff[54] = 154 ; //1.0w
	m_eep.rfWattBuff[65] = 152 ; //1.0w
	m_eep.rfWattBuff[76] = 146 ; //1.0w


}
void Rf_TD_BHB003_Table_260212()//260212
{
	//BHB003
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11447;
	m_eep.rfFrqBuff[2] = 11285;
	m_eep.rfFrqBuff[3] = 11420;
	m_eep.rfFrqBuff[4] = 11375;
	m_eep.rfFrqBuff[5] = 11360;
	m_eep.rfFrqBuff[6] = 11385;
	m_eep.rfFrqBuff[7] = 11427;

	m_eep.rfWattBuff[10] = 174 ; //1.0w
	m_eep.rfWattBuff[21] = 140 ; //1.0w
	m_eep.rfWattBuff[32] = 170 ; //1.0w
	m_eep.rfWattBuff[43] = 166 ; //1.0w
	m_eep.rfWattBuff[54] = 152 ; //1.0w
	m_eep.rfWattBuff[65] = 162 ; //1.0w
	m_eep.rfWattBuff[76] = 160 ; //1.0w

}
void Rf_TD_BHB004_Table_260212()//260212
{
	//BHB004
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11342;
	m_eep.rfFrqBuff[2] = 11367;
	m_eep.rfFrqBuff[3] = 11302;
	m_eep.rfFrqBuff[4] = 11345;
	m_eep.rfFrqBuff[5] = 11372;
	m_eep.rfFrqBuff[6] = 11352;
	m_eep.rfFrqBuff[7] = 11380;

	m_eep.rfWattBuff[10] = 150 ; //1.0w
	m_eep.rfWattBuff[21] = 152 ; //1.0w
	m_eep.rfWattBuff[32] = 154 ; //1.0w
	m_eep.rfWattBuff[43] = 160 ; //1.0w
	m_eep.rfWattBuff[54] = 162 ; //1.0w
	m_eep.rfWattBuff[65] = 158 ; //1.0w
	m_eep.rfWattBuff[76] = 156 ; //1.0w

}

void Rf_TD_BHB005_Table_260212()//260212
{
	//BHB005
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11402;
	m_eep.rfFrqBuff[2] = 11430;
	m_eep.rfFrqBuff[3] = 11407;
	m_eep.rfFrqBuff[4] = 11367;
	m_eep.rfFrqBuff[5] = 11285;
	m_eep.rfFrqBuff[6] = 11322;
	m_eep.rfFrqBuff[7] = 11307;

	m_eep.rfWattBuff[10] = 190 ; //1.0w
	m_eep.rfWattBuff[21] = 186 ; //1.0w
	m_eep.rfWattBuff[32] = 180 ; //1.0w
	m_eep.rfWattBuff[43] = 200; //1.0w
	m_eep.rfWattBuff[54] = 176 ; //1.0w
	m_eep.rfWattBuff[65] = 168 ; //1.0w
	m_eep.rfWattBuff[76] = 158 ; //1.0w

}


void Rf_TD_BLS002_Table_Auto_frQ()// ÁÖÆÄ¼ö ¹Ù²ã°¡¸é¼­ °¡Àå Ãâ·ÂÀÌ ³ôÀº ÁÖÆÄ¼ö
{

/*

1¿ÍÆ®¿¡ ÇØ´çÇÏ´Â°ª

ACal 0 102 -> 100 99 101 101 100 avg : 100
ACal 1 104 -> 100 101 100 100 99 avg : 100
ACal 2 112 -> 101 102 101 101 101 avg : 101
ACal 3 110 -> 100 101 100 100 100 avg : 100
ACal 4 104 -> 101 101 102 101 101 avg : 101
ACal 5 104 -> 102 104 100 100 101 avg : 101
ACal 6 104 -> 98 96 96 97 121 avg : 102

¿ì¼± 1.0w¸¸ Ã£À½ ³ª¸ÓÁö´Â ¸ô¶ó


*/


	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 10940;
	m_eep.rfFrqBuff[2] = 10930;
	m_eep.rfFrqBuff[3] = 10930;
	m_eep.rfFrqBuff[4] = 10860;
	m_eep.rfFrqBuff[5] = 10950;
	m_eep.rfFrqBuff[6] = 10910;
	m_eep.rfFrqBuff[7] = 10990;

	//no.1
	m_eep.rfWattBuff[0] = 0 ;
	m_eep.rfWattBuff[1] = 1 ; //0.1w
	m_eep.rfWattBuff[2] = 13 ; //0.2w
	m_eep.rfWattBuff[3] = 29 ; //0.3w
	m_eep.rfWattBuff[4] = 43 ; //0.4w
	m_eep.rfWattBuff[5] = 59 ; //0.5w
	m_eep.rfWattBuff[6] = 73 ; //0.6w
	m_eep.rfWattBuff[7] = 89 ; //0.7w
	m_eep.rfWattBuff[8] = 102 ; //0.8w
	m_eep.rfWattBuff[9] = 113 ; //0.9w
	m_eep.rfWattBuff[10] = 102 ; //1.0w
	m_eep.rfWattBuff[11] = 160 ; //1.1w

	//no.2
	m_eep.rfWattBuff[12] = 1 ; //0.1w
	m_eep.rfWattBuff[13] = 16 ; //0.2w
	m_eep.rfWattBuff[14] = 34 ; //0.3w
	m_eep.rfWattBuff[15] = 48 ; //0.4w
	m_eep.rfWattBuff[16] = 60 ; //0.5w
	m_eep.rfWattBuff[17] = 75 ; //0.6w
	m_eep.rfWattBuff[18] = 86 ; //0.7w
	m_eep.rfWattBuff[19] = 100 ; //0.8w
	m_eep.rfWattBuff[20] = 114 ; //0.9w
	m_eep.rfWattBuff[21] = 104 ; //1.0w
	m_eep.rfWattBuff[22] = 160 ; //1.1w

	//no.3
	m_eep.rfWattBuff[23] = 1 ; //0.1w
	m_eep.rfWattBuff[24] = 16 ; //0.2w
	m_eep.rfWattBuff[25] = 30 ; //0.3w
	m_eep.rfWattBuff[26] = 46 ; //0.4w
	m_eep.rfWattBuff[27] = 58 ; //0.5w
	m_eep.rfWattBuff[28] = 73 ; //0.6w
	m_eep.rfWattBuff[29] = 84 ; //0.7w
	m_eep.rfWattBuff[30] = 98 ; //0.8w
	m_eep.rfWattBuff[31] = 110 ; //0.9w
	m_eep.rfWattBuff[32] = 112 ; //1.0w
	m_eep.rfWattBuff[33] = 160 ; //1.1w

	//no.4
	m_eep.rfWattBuff[34] = 1 ; //0.1w
	m_eep.rfWattBuff[35] = 20 ; //0.2w
	m_eep.rfWattBuff[36] = 38 ; //0.3w
	m_eep.rfWattBuff[37] = 50 ; //0.4w
	m_eep.rfWattBuff[38] = 66 ; //0.5w
	m_eep.rfWattBuff[39] = 80 ; //0.6w
	m_eep.rfWattBuff[40] = 94 ; //0.7w
	m_eep.rfWattBuff[41] = 106 ; //0.8w
	m_eep.rfWattBuff[42] = 124 ; //0.9w
	m_eep.rfWattBuff[43] = 110 ; //1.0w
	m_eep.rfWattBuff[44] = 160 ; //1.1w

	//no.5
	m_eep.rfWattBuff[45] = 1 ; //0.1w
	m_eep.rfWattBuff[46] = 22 ; //0.2w
	m_eep.rfWattBuff[47] = 40 ; //0.3w
	m_eep.rfWattBuff[48] = 58 ; //0.4w
	m_eep.rfWattBuff[49] = 72 ; //0.5w
	m_eep.rfWattBuff[50] = 82 ; //0.6w
	m_eep.rfWattBuff[51] = 94 ; //0.7w
	m_eep.rfWattBuff[52] = 108 ; //0.8w
	m_eep.rfWattBuff[53] = 120 ; //0.9w
	m_eep.rfWattBuff[54] = 104 ; //1.0w
	m_eep.rfWattBuff[55] = 160 ; //1.1w

	//no.6
	m_eep.rfWattBuff[56] = 1 ; //0.1w
	m_eep.rfWattBuff[57] = 16 ; //0.2w
	m_eep.rfWattBuff[58] = 30 ; //0.3w
	m_eep.rfWattBuff[59] = 46 ; //0.4w
	m_eep.rfWattBuff[60] = 56 ; //0.5w
	m_eep.rfWattBuff[61] = 70 ; //0.6w
	m_eep.rfWattBuff[62] = 82 ; //0.7w
	m_eep.rfWattBuff[63] = 94 ; //0.8w
	m_eep.rfWattBuff[64] = 107 ; //0.9w
	m_eep.rfWattBuff[65] = 104 ; //1.0w
	m_eep.rfWattBuff[66] = 160 ; //1.1w

	//no.7
	m_eep.rfWattBuff[67] = 1 ; //0.1w
	m_eep.rfWattBuff[68] = 22; //0.2w
	m_eep.rfWattBuff[69] = 38 ; //0.3w
	m_eep.rfWattBuff[70] = 54 ; //0.4w
	m_eep.rfWattBuff[71] = 66 ; //0.5w
	m_eep.rfWattBuff[72] = 80 ; //0.6w
	m_eep.rfWattBuff[73] = 94 ; //0.7w
	m_eep.rfWattBuff[74] = 108 ; //0.8w
	m_eep.rfWattBuff[75] = 120 ; //0.9w
	m_eep.rfWattBuff[76] = 104 ; //1.0w
	m_eep.rfWattBuff[77] = 160 ; //1.1w
}

void Rf_Init()
{
	m_rf.pluseOn = 0;
	m_rf.pluseLevel = 0;
	m_rf.pluseTimeStamp = HAL_GetTick();
	m_eep.remainingShotNum = 10000;
	HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
	HAL_Delay(1500);
	RF_Pwr_ON();


	Rf_TD_BHB005_Table_260212();



	m_rf.pulseMaxBuff[IDX_MAIN_P1_WATT]			= 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P1_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P1_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P4_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P4_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_POSTCO0L_TIME]   = 30;

	m_rf.pulseMinBuff[IDX_MAIN_P1_WATT]			= 1;
	m_rf.pulseMinBuff[IDX_MAIN_P1_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P1_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P2_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P2_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P2_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P3_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P3_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P3_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P4_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P4_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_POSTCO0L_TIME]   = 0;



}
void Hand_Init()//
{
	m_eep.catridgeDetectPre = CATRIGE_DETECT;
	m_eep.catridgeDetect = CATRIGE_DETECT;
	m_eep.cartAllow = 1;// temp
	m_hand1.tempDutyEn = 1;
}
void LCD_Init()
{
	HAL_Delay(500);

	m_rf.energy = 50;
	m_rf.pulseDuration = 50;
	m_rf.postCooling = 5;
	m_rf.interval = 1;


	Tx_LCD_Msg(CMD_ENERGY, m_rf.energy);
	Tx_LCD_Msg(CMD_PULSE_DURATION, m_rf.pulseDuration);
	Tx_LCD_Msg(CMD_POST_COOLING, m_rf.postCooling);
	Tx_LCD_Msg(CMD_INTERVAL, m_rf.interval);

	m_rf.currentShot = 0;
	m_rf.totaEnergy = 0;
	Tx_LCD_Msg(CMD_TOTAL_JOULE, m_rf.totaEnergy);
	Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);
	Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
	m_rf.testPulseOption = 2;
	Tx_LCD_Msg(CMD_TEST_PULSE, m_rf.testPulseOption);

	Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_STNBY);

}
void LCD_Max_Init()
{
	HAL_Delay(500);



	PulseData_Sand(IDX_MAIN_P1_WATT, 1);
	PulseData_Sand(IDX_MAIN_P1_DURATION_TIME, 10);
	PulseData_Sand(IDX_MAIN_P1_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P2_WATT, 1);
	PulseData_Sand(IDX_MAIN_P2_DURATION_TIME, 10);
	PulseData_Sand(IDX_MAIN_P2_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P3_WATT, 1);
	PulseData_Sand(IDX_MAIN_P3_DURATION_TIME, 10);
	PulseData_Sand(IDX_MAIN_P3_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P4_WATT, 1);
	PulseData_Sand(IDX_MAIN_P4_DURATION_TIME, 10);
	PulseData_Sand(IDX_MAIN_POSTCO0L_TIME, 10);

	PulseEn_Sand(1, PULSE_ENABLE);
	PulseEn_Sand(2, PULSE_ENABLE);
	PulseEn_Sand(3, PULSE_ENABLE);
	PulseEn_Sand(4, PULSE_ENABLE);
	CurrentEnergy_Cal();

	m_rf.currentShot = 0;
	m_rf.totaEnergy = 0;
	Tx_LCD_Msg(CMD_TOTAL_JOULE, m_rf.totaEnergy);
	Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);
	Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);

	Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_STNBY);

}


void Err_Init()
{
	for(int i =0 ;i < 16;i++)
	{
		m_err.errStandBuff[i] = 5;
	}
}
void PulseData_Sand(uint8_t num, uint16_t data)
{
	uint16_t pulseData;
	if(num>12)return;

	m_rf.pulseBuff[num] = data;
	pulseData = num*100 + data;
	Tx_LCD_Msg(CMD_PLUSE_VALUE, pulseData);

}
void PulseEn_Sand(uint8_t num, uint16_t enDis)
{
	uint16_t pulseData;
	if(num>4)return;

	pulseData = num*10 + enDis;
	m_rf.pulseEndisBuff[num] = enDis;
	Tx_LCD_Msg(CMD_PLUSE_EN, pulseData);

}


#if 0

uint8_t Check_Common(uint8_t status, uint8_t idx, uint8_t level, uint8_t cmd)
{
	uint16_t errData;

	if(status)
	{
		if(m_err.errBuff[idx]==1)
		{
			errData = level*LEVEL_UNIT + ERR_DISABLE +cmd;
			m_err.errDataBuff[idx] = errData;

		}
		m_err.errBuff[idx] = 0;
	}
	else
	{
		if(m_err.errBuff[idx] == 0)
		{
			errData = level*LEVEL_UNIT + ERR_ENABLE +cmd;
			m_err.errDataBuff[idx] = errData;
		}
		m_err.errBuff[idx] = 1;
	}
	return m_err.errBuff[idx];

}
#else

void Set_Err_StatusBitFlag(uint8_t cmd, uint8_t status)
{
	if(status)
	{
		if(cmd<=15) m_err.errStatus[0] |= 1<<cmd;
		else if(cmd<=31) m_err.errStatus[1] |= 1<<cmd;
		else if(cmd<=47) m_err.errStatus[2] |= 1<<cmd;
		else m_err.errStatus[3] |= 1<<cmd;
	}
	else
	{
		if(cmd<=15) m_err.errStatus[0] &= ~(1<<cmd);
		else if(cmd<=31) m_err.errStatus[1] &= ~(1<<cmd);
		else if(cmd<=47) m_err.errStatus[2] &= ~(1<<cmd);
		else m_err.errStatus[3] |= ~(1<<cmd);
	}


	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_1, m_err.errStatus[0]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_2, m_err.errStatus[1]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_3, m_err.errStatus[2]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_4, m_err.errStatus[3]);

}

void Get_Err_StatusBitFlag()
{
	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[0]>>i)&0x01) m_err.errDataBuff[i] = i;
		else m_err.errDataBuff[i] = 0;

	}
	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[1]>>i)&0x01) m_err.errDataBuff[i+16] = i;
		else m_err.errDataBuff[i+16] = 0;
	}
	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[2]>>i)&0x01) m_err.errDataBuff[i+32] = i;
		else m_err.errDataBuff[i+32] = 0;
	}
	for(int i =0 ;i <= 1;i++)
	{
		if((m_err.errStatus[3]>>i)&0x01) m_err.errDataBuff[i+48] = i;
		else m_err.errDataBuff[i+48] = 0;
	}
}

uint8_t Check_Common(uint8_t status, uint8_t cmd)
{

	if(status)//Nomal
	{
		if(m_err.errDataBuff[cmd])
		{
			m_err.errTxDoneBuff[cmd] = 0;
			m_err.errDataBuff[cmd] = 0;
//			Set_Err_StatusBitFlag(cmd, 0);
		}
		m_err.errNowBuff[cmd] = 0;
		m_err.errCntBuff[cmd] = 0;
	}
	else//errs
	{
		if(!m_err.errDataBuff[cmd])
		{
			m_err.errCntBuff[cmd]++;
			if(m_err.errStandBuff[cmd] < m_err.errCntBuff[cmd])
			{
				m_err.errCntBuff[cmd] = 0;
				m_err.errDataBuff[cmd] = cmd;
//				Set_Err_StatusBitFlag(cmd, 1);
				if(m_eepMain.errCntBuff[cmd]<999)m_eepMain.errCntBuff[cmd]++;
				Eeprom_Word_Write(IDX_EEP_ERROR+cmd*2, m_eepMain.errCntBuff[cmd]);
			}
		}
		m_err.errNowBuff[cmd] = cmd;
	}
	return m_err.errDataBuff[cmd];

}

#endif

uint8_t Check_CartrigeCommon(uint8_t status, uint8_t cmd)
{
	uint16_t errData;

	if(status)
	{
		errData = ERR_DISABLE +cmd;
		m_err.errDataBuff[cmd] = errData;
	}

	return 0;

}

uint8_t Check_Max_Min(int data, int max, int min, uint8_t cmd)
{
	uint8_t status = (min <= data && data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;
}

uint8_t Check_Max(int data, int max, uint8_t cmd)
{

	uint8_t status = (data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;

}

uint8_t Check_Min(int data, int min, uint8_t cmd)
{
	uint8_t status = (min <= data);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status,cmd);

	return returnValue;

}


uint8_t Check_Status(int data, int nomalData, uint8_t cmd)
{
	uint8_t status = (data == nomalData);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;

}


uint8_t Check_Day(uint16_t YY, uint16_t MM, uint16_t DD, uint8_t cmd)
{
	uint8_t yyOk = (YY_MIN <= YY && YY <=YY_MAX);
	uint8_t mmOk = (MM_MIN <= MM && MM <=MM_MAX);
	uint8_t ddOk = (DD_MIN <= DD && DD <=DD_MAX);
	uint8_t status = (yyOk && mmOk && ddOk);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;
}

uint8_t Check_Time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t cmd)
{
	uint8_t hourOk = (HOUR_MIN <= hour && hour <=HOUR_MAX);
	uint8_t minOk = (MIN_MIN <= min && min <=MIN_MAX);
	uint8_t secOk = (SEC_MIN <= sec && sec <=SEC_MAX);
	uint8_t status = (hourOk && minOk && secOk);
	uint8_t returnValue = 0;

	returnValue = Check_Common(status, cmd);

	return returnValue;


}
void Error_Buff_Clear()
{
	memset(m_err.errDataBuff, 0, sizeof(m_err.errDataBuff));
}


void Error_Buff_Main_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_MAIN_EVENT_START ;i < IDX_MAIN_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
			HAL_Delay(1500);
		}
	}
	if(errCnt==0)
	{
		Tx_LCD_Msg(CMD_OK, OK_MAIN);
	}
}

void Error_Buff_HP_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_HP_EVENT_START ;i < IDX_HP_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			if(!m_err.errTxDoneBuff[i])
			{
				Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
				m_err.errTxDoneBuff[i] = 1;
				HAL_Delay(1500);
			}
		}
	}
	if(errCnt==0)
	{
		Tx_LCD_Msg(CMD_OK, OK_HP);
	}
}

void Error_Buff_Rf_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_RF_EVENT_START ;i < IDX_RF_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
			HAL_Delay(1500);
		}
	}
	if(errCnt==0)
	{
		Tx_LCD_Msg(CMD_OK, OK_RF);
	}
}

/*
m_err.errDataBuff[IDX_TEMP_OUT]
m_err.errDataBuff[IDX_TEMP_LIMIT_UNDER]
m_err.errDataBuff[IDX_TEMP_LOW]
m_err.errDataBuff[IDX_FLOW_LIMIT_UNDER]
m_err.errDataBuff[IDX_FLOW_ZERO_IDX]
m_err.errDataBuff[IDX_LEVEL_LOW]
m_err.errDataBuff[IDX_AUTO_CAL_COMU_ERR]
m_err.errDataBuff[IDX_BATTRY_LIMIT_OVER]
m_err.errDataBuff[IDX_BATTRY_LIMIT_UNDER]
m_err.errDataBuff[IDX_BATTRY_LIMIT_LOW]
m_err.errDataBuff[IDX_RTC_ERR]
m_err.errDataBuff[IDX_PRE_COOL_ERR]
m_err.errDataBuff[IDX_HAND_COMU_ERR]
m_err.errDataBuff[IDX_CATRIGE_ID_ERR]
m_err.errDataBuff[IDX_CATRIGE_MANU_ERR]
m_err.errDataBuff[IDX_CATRIGE_MANU_OVER_ERR]
m_err.errDataBuff[IDX_CATRIGE_ISUE_ERR]
m_err.errDataBuff[IDX_CATRIGE_ISUE_OVER_ERR]
m_err.errDataBuff[IDX_CATRIGE_WATT_ERR]
m_err.errDataBuff[IDX_CATRIGE_FRQ_ERR]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_ERR]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_LOW]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_ZERO]
m_err.errDataBuff[IDX_CATRIGE_DETECT]
m_err.errDataBuff[IDX_CATRIGE_UN_DETEC]
m_err.errDataBuff[IDX_HAND_TIMEOUT]
m_err.errDataBuff[IDX_RF_COMU_ERR]
m_err.errDataBuff[IDX_RF_STATUS_ERR]
m_err.errDataBuff[IDX_RF_EVENT_END]
m_err.errDataBuff[IDX_LCD_COMU_ERR]
m_err.errDataBuff[IDX_LCD_TIMEOUT]
m_err.errDataBuff[IDX_IS_CURRNTSHOT_RESET]
m_err.errDataBuff[IDX_IS_TOTALJULE_RESET]
m_err.errDataBuff[IDX_CATRIGE_NEW]
*/


void Error_Check_Main()
{
#if 0
	Check_Max_Min(m_hand1.temprature, TEMP_OUT_MAX, TEMP_OUT_MIN,IDX_TEMP_OUT);
	Check_Min(m_hand1.temprature, TEMP_MIN, IDX_TEMP_LIMIT_UNDER);
	Check_Min(m_hand1.temprature, TEMP_LOW_VALUE, IDX_TEMP_LOW);

	Check_Status(m_io.level1Status, 0, IDX_LEVEL_LOW);
#if 0//die
	Check_Min(m_io.flowSensorFrq, FLOW_LOW_MIN, IDX_FLOW_ZERO_IDX);
	Check_Max_Min(m_io.flowSensorFrq, FLOW_LOW_MAX, FLOW_LOW_MIN, IDX_FLOW_LIMIT_UNDER);
#endif

	Check_Max(m_io.battery*10, BATTRY_LIMIT_MAX, IDX_BATTRY_LIMIT_OVER);
	Check_Min(m_io.battery*10, BATTRY_LIMIT_MIN, IDX_BATTRY_LIMIT_UNDER);
	Check_Min(m_io.battery*10, BATTRY_NOMAL_MIN, IDX_BATTRY_LIMIT_LOW);

	Check_Status(m_err.autoCalStatus, 0, IDX_AUTO_CAL_COMU_ERR);
	Check_Time(m_io.hour, m_io.min, m_io.sec, IDX_RTC_ERR);


#endif

	if(m_err.txEn)Error_Buff_Main_Tx();





}

void Error_Check_HP()
{
	uint8_t errStatus;
#if 0

	m_err.handTimeout++;
	Check_Max(m_err.handTimeout, COMU_MAX_CNT, IDX_HAND_COMU_ERR);



	Check_Day(m_eep.manufacYY, m_eep.manufacMM, m_eep.manufacDD, IDX_CATRIGE_MANU_ERR);
	Check_Day(m_eep.issuedYY, m_eep.issuedMM, m_eep.issuedDD, IDX_CATRIGE_ISUE_ERR);

	for(int i = 1; i <= 7; i++)
	{
		errStatus = Check_Max_Min(m_eep.rfFrqBuff[i], CATRIDGE_FRQ_MAX, CATRIDGE_FRQ_MIN, IDX_CATRIGE_FRQ_ERR);
		if(errStatus) break;
	}
	for(int i = 1; i <= 77; i++)
	{
		errStatus = Check_Max_Min(m_eep.rfWattBuff[i], CATRIDGE_WATT_MAX, CATRIDGE_WATT_MIN, IDX_CATRIGE_WATT_ERR);
		if(errStatus) break;
	}
	Check_Max(m_eep.remainingShotNum, CATRIDGE_REMAIN_MAX, IDX_CATRIGE_RESHOT_ERR);
	if(!m_rf.remainingShotNegative)
	{
		Check_Min(m_eep.remainingShotNum, CATRIDGE_REMAIN_LOW_3, IDX_CATRIGE_RESHOT_LOW);
	}
	else
	{
		Check_Max(m_rf.remainingShotNegative, m_eepMain.remainingShotRandom, IDX_CATRIGE_RESHOT_ZERO);
	}


	Check_Max(m_eep.catridgeId, CATRIDGE_ID_MAX, IDX_CATRIGE_ID_ERR);

	Check_Status(m_err.preCoolStatus, 0, IDX_PRE_COOL_ERR);

	m_eep.manufacDay = m_eep.manufacYY*10000 + m_eep.manufacMM*100 + m_eep.manufacDD;
	m_eep.issuedDay = m_eep.issuedYY*10000 + m_eep.issuedMM*100 + m_eep.issuedDD;
	Check_Max(m_io.day, m_eep.manufacDay + DAY_MAX, IDX_CATRIGE_MANU_OVER_ERR);
	Check_Max(m_io.day, m_eep.issuedDay + DAY_MAX, IDX_CATRIGE_ISUE_OVER_ERR);


#endif

	if(m_err.txEn)Error_Buff_HP_Tx();

}

void Error_Check_RF()
{
#if 0
	m_err.rfTimeout++;
	Tx_RF_GenStatus_Check();
	Check_Max(m_err.rfTimeout, COMU_MAX_CNT, IDX_RF_COMU_ERR);//E02

	Check_Status(m_err.rfStatus, 0, IDX_RF_STATUS_ERR);//E14
#endif

	if(m_err.txEn)Error_Buff_Rf_Tx();

}

void Error_Check_Config()
{
	static uint32_t timeStamp;

	if(m_rf.pluseOn) return;
	if(HAL_GetTick()-timeStamp >= 2000)
	{
		Error_Check_Main();
		Error_Check_HP();
		Error_Check_RF();

		timeStamp = HAL_GetTick();
	}




}


void Hand1_Poling_Ctrl(int add, int data1, int data2, int data3, int data4)
{

	if(add != CMD_HP1_ADD)return;

	m_hand1.mode = data1;
	m_hand1.pwmDuty = data2;
	m_hand1.temprature = data3;
	m_hand1.ioStatus = data4;

}

void RF_Watt_All_Calculate()
{
	int idx;
	float wattF;
	wattF = ((float)m_rf.energy /(float)m_rf.pulseDuration);

	m_rf.watt = (uint8_t)(wattF * 10.0);
	if(m_rf.watt > MAX_WATT_IDX) m_rf.watt = MAX_WATT_IDX;

	idx = m_rf.watt;
	for(int i =0 ;i < 7; i++)
	{
		m_rf.rfwattBuff[i] = m_eep.rfWattBuff[idx+(i*11)];
	}
}


void RF_Frq_All_Calculate()
{

	for(int i =0 ;i < 7;i++)
	{
		m_rf.rfFrqBuff[i] = m_eep.rfFrqBuff[i+1];
	}
}

void Tx_RF_GenStatus_Check()
{

	uint8_t len = 0;
	uint8_t dataLen = 0;

	len = RF_NUM_FIX + 1;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_STATUS_CHECK;

	m_rf.txBuff[RF_INDEX_DATA] = 0x00;
	dataLen = 3;


	for(int i =0 ;i <= RF_INDEX_DATA ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+1] ^= m_rf.txBuff[i];
	}

	m_rf.txBuff[RF_INDEX_DATA+2] = ETX;
	Debug_Tx_GenStatus_Check_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}

void Tx_RF_FeedBack_Check()
{

	uint8_t len = 0;
	uint8_t dataLen = 0;

	len = RF_NUM_FIX + 1;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_RF_VOLTAGE_REQ;

	m_rf.txBuff[RF_INDEX_DATA] = 0x00;
	dataLen = 3;


	for(int i =0 ;i <= RF_INDEX_DATA ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+1] ^= m_rf.txBuff[i];
	}

	m_rf.txBuff[RF_INDEX_DATA+2] = ETX;
	Debug_Tx_FeedBack_Check_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}



void Tx_RF_FRQ_Module(uint8_t ch, uint16_t frequency)
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 3;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_FREQ_SET;

	m_rf.txBuff[RF_INDEX_DATA] = ch+1;
	m_rf.txBuff[RF_INDEX_DATA+1] = (frequency>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+2] = (frequency)&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+2 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+3] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+4] = ETX;
	Debug_Tx_RF_Frq_Printf(ch+1, frequency);
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_Watt_Module(uint8_t ch, uint16_t watt)
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 3;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_OUTPUT_SET;

	m_rf.txBuff[RF_INDEX_DATA] = ch+1;
	m_rf.txBuff[RF_INDEX_DATA+1] = (watt>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+2] = (watt)&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+2 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+3] ^= m_rf.txBuff[i];
	}

	m_rf.txBuff[RF_INDEX_DATA+4] = ETX;
	Debug_Tx_RF_Watt_Printf(ch+1, watt);
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_FRQ_ALL_Module( )
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_FREQ_SET;

	RF_Frq_All_Calculate();


	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfFrqBuff[RF_FRQ_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfFrqBuff[RF_FRQ_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfFrqBuff[RF_FRQ_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfFrqBuff[RF_FRQ_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfFrqBuff[RF_FRQ_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfFrqBuff[RF_FRQ_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfFrqBuff[RF_FRQ_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfFrqBuff[RF_FRQ_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfFrqBuff[RF_FRQ_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfFrqBuff[RF_FRQ_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfFrqBuff[RF_FRQ_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfFrqBuff[RF_FRQ_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfFrqBuff[RF_FRQ_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfFrqBuff[RF_FRQ_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfFrqBuff[RF_FRQ_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfFrqBuff[RF_FRQ_CH6])&0xff;

	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Frq_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_Watt_ALL_Module_org( )
{

	uint8_t len = 0;
	ddTimeStart1(); //wndksdebug
	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;

	RF_Watt_All_Calculate();
	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfwattBuff[RF_WATT_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfwattBuff[RF_WATT_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfwattBuff[RF_WATT_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfwattBuff[RF_WATT_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfwattBuff[RF_WATT_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfwattBuff[RF_WATT_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfwattBuff[RF_WATT_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfwattBuff[RF_WATT_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfwattBuff[RF_WATT_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfwattBuff[RF_WATT_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfwattBuff[RF_WATT_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfwattBuff[RF_WATT_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);
	ddTimeEnd1(); //wndksdebug

}




void Tx_RF_Watt_ALL_Module(uint16_t watt)
{

	uint8_t len = 0;



	ddTimeStart1(); //wndksdebug
	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;



	m_rf.watt = watt;
	if(m_rf.watt > MAX_WATT_IDX) m_rf.watt = MAX_WATT_IDX;
	int idx = m_rf.watt;
	for(int i =0 ;i < 7; i++)
	{
		m_rf.rfwattBuff[i] = m_eep.rfWattBuff[idx+(i*11)];
	}

	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfwattBuff[RF_WATT_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfwattBuff[RF_WATT_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfwattBuff[RF_WATT_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfwattBuff[RF_WATT_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfwattBuff[RF_WATT_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfwattBuff[RF_WATT_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfwattBuff[RF_WATT_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfwattBuff[RF_WATT_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfwattBuff[RF_WATT_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfwattBuff[RF_WATT_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfwattBuff[RF_WATT_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfwattBuff[RF_WATT_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);


}



void TX_RF_Max_Ontime_Set()
{
	uint8_t len;

	len = RF_NUM_FIX + 2;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_MAX_ON_TIME_SET;

	m_rf.txBuff[RF_INDEX_DATA] = (MAX_ONTIME>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (MAX_ONTIME)&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+1 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+2] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+3] = ETX;
	Debug_Tx_RF_MaxOntime_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);
}


void Tx_RF_Watt_Zero_ALL_Module( )
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;

	RF_Watt_All_Calculate();
	m_rf.txBuff[RF_INDEX_DATA+0] = 0;
	m_rf.txBuff[RF_INDEX_DATA+1] = 0;

	m_rf.txBuff[RF_INDEX_DATA+2] = 0;
	m_rf.txBuff[RF_INDEX_DATA+3] = 0;

	m_rf.txBuff[RF_INDEX_DATA+4] = 0;
	m_rf.txBuff[RF_INDEX_DATA+5] = 0;

	m_rf.txBuff[RF_INDEX_DATA+6] = 0;
	m_rf.txBuff[RF_INDEX_DATA+7] = 0;

	m_rf.txBuff[RF_INDEX_DATA+8] = 0;
	m_rf.txBuff[RF_INDEX_DATA+9] = 0;

	m_rf.txBuff[RF_INDEX_DATA+10] = 0;
	m_rf.txBuff[RF_INDEX_DATA+11] = 0;

	m_rf.txBuff[RF_INDEX_DATA+12] = 0;
	m_rf.txBuff[RF_INDEX_DATA+13] = 0;

	m_rf.txBuff[RF_INDEX_DATA+14] = 0;
	m_rf.txBuff[RF_INDEX_DATA+15] = 0;

	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Zero_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}


void Rx_RF_Get(uint8_t getData)
{
	m_rf.rxBuff[m_rf.rxCnt] = getData;
	m_rf.rxCnt++;
	m_rf.rxCnt %= 30;

	m_rf.lastTimeStamp = HAL_GetTick();
}
void RF_Max_Pwm_On()
{
	uint16_t pulse1Watt = m_rf.pulseBuff[IDX_MAIN_P1_WATT];
	Tx_RF_Watt_ALL_Module(pulse1Watt);
	m_rf.pluseOn = 1;
	Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_H1_LEVEL);
	m_rf.pluseTimeStamp = HAL_GetTick();

	m_rf.pulseEndisChkBuff[1] = 0;
	m_rf.pulseEndisChkBuff[2] = 0;
	m_rf.pulseEndisChkBuff[3] = 0;
	m_rf.pulseEndisChkBuff[4] = 0;
	Pulse_Trig_TimeSave();
	Get_PluseWatt(pulse1Watt);
	m_rf.pluseLevel = PWM_H1_LEVEL;
}

void RF_Pwm_On()
{
	m_rf.pluseOn = 1;
	m_rf.pluseTimeStamp = HAL_GetTick();
	Pulse_Trig_TimeSave();
	m_rf.pluseLevel = PWM_H_LEVEL;

}

void RF_eg_Exp_On(uint32_t expTime)
{
	m_rf.egExpOn = 1;
	m_rf.pluseEgTimeStamp = HAL_GetTick();
	m_rf.pluseEnginerHigh = expTime;
	HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
}


void Pulse_Trig_TimeSave()
{
	m_rf.trigTemeStamp[m_rf.trigCnt++] = HAL_GetTick();
	m_rf.trigCnt %= 30;
}
void Get_PluseWatt(uint16_t watt)
{
	m_rf.getWattBuff[m_rf.getWattCnt++] = watt;
	m_rf.getWattCnt %= 10;
}

void Exp_Total_Log()
{
	int timeGap;

	printf(">>================================ \r\n");

	printf("%d W ",m_rf.watt);
	if(m_rf.trigCnt>=2)
	{
		for(int i =0 ;i < m_rf.trigCnt-1;i++)
		{
			timeGap = m_rf.trigTemeStamp[i+1] -m_rf.trigTemeStamp[i];

			printf("%d sec ",timeGap);


		}
	}
	memset(m_rf.trigTemeStamp, 0, sizeof(m_rf.trigTemeStamp));
	m_rf.trigCnt = 0;

#if 0
	for(int i =0 ;i < m_rf.getWattCnt;i++)
	{
		printf("[%d] Watt %u \r\n",i, m_rf.getWattBuff[i]);
	}
	memset(m_rf.getWattBuff, 0, sizeof(m_rf.getWattBuff));
	m_rf.getWattCnt = 0;
#endif

	printf("%d TotEng ",m_rf.totaEnergy);
	printf("\r\n");

	Tx_RF_FeedBack_Check();
	printf(">>================================ \r\n");

}
void PulseEnDisCheck()
{
	uint16_t pulse2Watt = m_rf.pulseBuff[IDX_MAIN_P2_WATT];
	uint16_t pulse3Watt = m_rf.pulseBuff[IDX_MAIN_P3_WATT];
	uint16_t pulse4Watt = m_rf.pulseBuff[IDX_MAIN_P4_WATT];

	if(m_rf.pulseEndisBuff[2] && !m_rf.pulseEndisChkBuff[2] )
	{
		m_rf.pulseEndisChkBuff[2] = 1;
		Tx_RF_Watt_ALL_Module(pulse2Watt);
//		Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_H2_LEVEL);
		Pulse_Trig_TimeSave();
		Get_PluseWatt(pulse2Watt);
		m_rf.pluseLevel = PWM_H2_LEVEL;
	}
	else if(m_rf.pulseEndisBuff[3] && !m_rf.pulseEndisChkBuff[3] )
	{
		m_rf.pulseEndisChkBuff[3] = 1;
		Tx_RF_Watt_ALL_Module(pulse3Watt);
//		Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_H3_LEVEL);
		Pulse_Trig_TimeSave();
		Get_PluseWatt(pulse3Watt);
		m_rf.pluseLevel = PWM_H3_LEVEL;
	}
	else if(m_rf.pulseEndisBuff[4] && !m_rf.pulseEndisChkBuff[4] )
	{
		m_rf.pulseEndisChkBuff[4] = 1;
		Tx_RF_Watt_ALL_Module(pulse4Watt);
//		Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_H4_LEVEL);
		Pulse_Trig_TimeSave();
		Get_PluseWatt(pulse4Watt);
		m_rf.pluseLevel = PWM_H4_LEVEL;
	}
	else
	{
//		Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_COOL_LEVEL);
		Pulse_Trig_TimeSave();
		m_rf.pluseLevel = PWM_COOL_LEVEL;
	}


}


void RF_Pwm_Conter_Individual()
{

	uint32_t pulse1Htime = m_rf.pulseBuff[IDX_MAIN_P1_DURATION_TIME] * TIME_100MS;
	uint32_t pulse1Ltime = m_rf.pulseBuff[IDX_MAIN_P1_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse2Htime = m_rf.pulseBuff[IDX_MAIN_P2_DURATION_TIME]* TIME_100MS;
	uint32_t pulse2Ltime = m_rf.pulseBuff[IDX_MAIN_P2_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse3Htime = m_rf.pulseBuff[IDX_MAIN_P3_DURATION_TIME]* TIME_100MS;
	uint32_t pulse3Ltime = m_rf.pulseBuff[IDX_MAIN_P3_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse4Htime = m_rf.pulseBuff[IDX_MAIN_P4_DURATION_TIME]* TIME_100MS;
	uint32_t pulseCooltime = m_rf.pulseBuff[IDX_MAIN_POSTCO0L_TIME]* TIME_100MS;


	if(pulse1Ltime>109)pulse1Ltime -= 109;
	if(pulse2Ltime>109)pulse2Ltime -= 109;
	if(pulse3Ltime>109)pulse3Ltime -= 109;


	if(m_rf.pluseOn)
	{
		switch (m_rf.pluseLevel)
		{
			case PWM_H1_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse1Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
//					Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_L1_LEVEL);
					Pulse_Trig_TimeSave();
					m_rf.pluseLevel = PWM_L1_LEVEL;
				}
			break;

			case PWM_L1_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp>pulse1Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();

				}
			break;

			case PWM_H2_LEVEL:

				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse2Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
//					Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_L2_LEVEL);
					Pulse_Trig_TimeSave();
					m_rf.pluseLevel = PWM_L2_LEVEL;
				}
			break;

			case PWM_L2_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse2Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();
				}
			break;

			case PWM_H3_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse3Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
//					Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_L3_LEVEL);
					Pulse_Trig_TimeSave();
					m_rf.pluseLevel = PWM_L3_LEVEL;
				}
			break;

			case PWM_L3_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse3Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();
				}
			break;

			case PWM_H4_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse4Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
//					Tx_Hand1_Msg(CMD_PULSE_TRIGER, PWM_COOL_LEVEL);
					Pulse_Trig_TimeSave();
					m_rf.pluseLevel = PWM_COOL_LEVEL;
				}
			break;

			case PWM_COOL_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulseCooltime)
				{
					m_rf.expEndFlag = 1;
					m_rf.pluseOn = 0;
					Pulse_Trig_TimeSave();
					Exp_Total_Log();
					m_rf.pluseLevel = PWM_H1_LEVEL;
				}
			break;

		}
	}
}


void RF_Pwm_Conter_Common(uint8_t pulseNum)
{
	static uint8_t pulseCnt;
	if(m_rf.pluseOn)
	{
		switch (m_rf.pluseLevel)
		{
			case PWM_H_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp >= ((float)m_rf.pulseDuration/pulseNum *TIME_100MS))
				{
					Pulse_Trig_TimeSave();
					m_rf.pluseTimeStamp = HAL_GetTick();
					pulseCnt++;
					if(pulseCnt == pulseNum)
					{
						m_rf.pluseLevel = PWM_POST_LEVEL;
						pulseCnt = 0;
					}
					else
					{
						m_rf.pluseLevel = PWM_L_LEVEL;
					}

				}
			break;

			case PWM_L_LEVEL:
				if(m_rf.interval != 0)HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp >= m_rf.interval*TIME_1000MS)
				{
					Pulse_Trig_TimeSave();
					m_rf.pluseTimeStamp = HAL_GetTick();

					m_rf.pluseLevel = PWM_H_LEVEL;
				}
			break;

			case PWM_POST_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp >= m_rf.postCooling*TIME_100MS)
				{
					Pulse_Trig_TimeSave();

					m_rf.pluseLevel = PWM_H1_LEVEL;
					m_rf.expEndFlag = 1;

					m_rf.pluseOn = 0;
				}
			break;

		}
	}
}


void RF_Eg_Exp_Conter()
{
	if(m_rf.egExpOn)
	{
		if(HAL_GetTick()- m_rf.pluseEgTimeStamp > m_rf.pluseEnginerHigh)
		{
			HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
			m_rf.egExpOn = 0;
			m_rf.expEndFlag = 1;
		}
	}
}




void LCD_Status_Tret()
{
	if(m_rf.pluseOn) return;
	if(m_rf.treatStatus == STATUS_PRECOOLING)
	{
		if(m_hand1.temprature <70)
		{
			m_rf.readyFlag = READY_ON;

			Tx_RF_FRQ_ALL_Module();
			Tx_RF_Watt_ALL_Module_org();
			TX_RF_Max_Ontime_Set();

			Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_TRET);
			m_rf.treatStatus = STATUS_TRET;

			m_rf.preCooltime = 0;
			m_err.preCoolStatus = 1;

#if 0
		HAL_Delay(500);
		testExpFlag =1;
#endif
		}

		if(HAL_GetTick()- m_rf.preCooltime> PRECOOL_TIMEOUT && m_rf.preCooltime)
		{
			m_rf.readyFlag = READY_ON;

			Tx_RF_FRQ_ALL_Module();
			Tx_RF_Watt_ALL_Module_org();
			TX_RF_Max_Ontime_Set();

			Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_TRET);
			m_rf.treatStatus = STATUS_TRET;

			m_rf.preCooltime = 0;
			m_err.preCoolStatus = 2;
		}

	}


}

void CARTRIGE_REQ_DATA(uint8_t idx)
{
	switch (idx)
	{
		case CART_IDX_CART_ID:
			Tx_LCD_Msg(CMD_CART_ID, m_eep.catridgeId);
		break;
		case CART_IDX_MANUFAC_YY:
			Tx_LCD_Msg(CMD_MANUFAC_YY, m_eep.manufacYY);
		break;
		case CART_IDX_MANUFAC_MM:
			Tx_LCD_Msg(CMD_MANUFAC_MM, m_eep.manufacMM);
		break;
		case CART_IDX_MANUFAC_DD:
			Tx_LCD_Msg(CMD_MANUFAC_DD, m_eep.manufacDD);
		break;
		case CART_IDX_ISSUED_YY:
			Tx_LCD_Msg(CMD_ISSUED_YY, m_eep.issuedYY);
		break;
		case CART_IDX_ISSUED_MM:
			Tx_LCD_Msg(CMD_ISSUED_MM, m_eep.issuedMM);
		break;
		case CART_IDX_ISSUED_DD:
			Tx_LCD_Msg(CMD_ISSUED_DD, m_eep.issuedDD);
		break;
		case CART_IDX_TRANDU1_FRQ:
			Tx_LCD_Msg(CMD_TRANDU1_FRQ, m_eep.rfFrqBuff[1]);
		break;
		case CART_IDX_TRANDU2_FRQ:
			Tx_LCD_Msg(CMD_TRANDU2_FRQ, m_eep.rfFrqBuff[2]);
		break;
		case CART_IDX_TRANDU3_FRQ:
			Tx_LCD_Msg(CMD_TRANDU3_FRQ, m_eep.rfFrqBuff[3]);
		break;
		case CART_IDX_TRANDU4_FRQ:
			Tx_LCD_Msg(CMD_TRANDU4_FRQ, m_eep.rfFrqBuff[4]);
		break;
		case CART_IDX_TRANDU5_FRQ:
			Tx_LCD_Msg(CMD_TRANDU5_FRQ, m_eep.rfFrqBuff[5]);
		break;
		case CART_IDX_TRANDU6_FRQ:
			Tx_LCD_Msg(CMD_TRANDU6_FRQ, m_eep.rfFrqBuff[6]);
		break;
		case CART_IDX_TRANDU7_FRQ:
			Tx_LCD_Msg(CMD_TRANDU7_FRQ, m_eep.rfFrqBuff[7]);
		break;
		case CART_IDX_REMIND_SHOT:
			Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
		break;

		case CART_IDX_STATUS:

		break;
		case CART_IDX_RTC:

		break;


	}
}
int compare_32(const void *a, const void *b)    // ¿À¸§Â÷¼ø ºñ±³ ÇÔ¼ö (uint32_t ±âÁØ)
{
    int num1 = *(int *)a;
    int num2 = *(int *)b;

    if (num1 < num2)    // a°¡ bº¸´Ù ÀÛÀ» ¶§´Â
        return -1;      // -1 ¹ÝÈ¯

    if (num1 > num2)    // a°¡ bº¸´Ù Å¬ ¶§´Â
        return 1;       // 1 ¹ÝÈ¯

    return 0;    // a¿Í b°¡ °°À» ¶§´Â 0 ¹ÝÈ¯
}


int wattDa = 140;
int trandu = 0;
int tranduOut = 6;


int qsortBuff[5] = {0,};
int AutoCal_Avg()// ¿À¸§Â÷¼øÀ¸·Î Á¤¸®
{
	int sum =0, avgInt;
	float avg = 0;
	qsort(qsortBuff, sizeof(qsortBuff) / sizeof(int), sizeof(int), compare_32);// u32
	sum += qsortBuff[0];
	sum += qsortBuff[1];
	sum += qsortBuff[2];
	sum += qsortBuff[3];
	sum += qsortBuff[4];

	avg = (float)(sum)/5;
	avg +=0.5;
	avgInt = avg;
	printf("avg : %d \r\n",avgInt);
	memset(qsortBuff, 0, sizeof(qsortBuff));

	return avg;

}

int qsort10Buff[10] = {0,};
int AutoCal_10_Avg()// ¿À¸§Â÷¼øÀ¸·Î Á¤¸®
{
	int sum =0;
	float avg = 0;
	qsort(qsort10Buff, sizeof(qsort10Buff) / sizeof(int), sizeof(int), compare_32);// u32

	for(int i =2 ;i < 8;i++)
	{
		sum += qsort10Buff[i];
	}

	avg = (float)(sum)/6;
	printf(">>avg : %d %.2f \r\n", trandu, avg);
	memset(qsort10Buff, 0, sizeof(qsort10Buff));

	return avg;

}




void AutoCal_Config()
{
	uint8_t wattBuff[10] = {10, 20, 30, 40, 50, 60 , 70, 80 , 90, 100};
	int avg = 0;
	uint16_t add;

	if(m_rf.autoCalFlag==0)return;

	memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
	m_rf.FeedBackCnt = 0;

	if(wattDa<200)
	{
		wattDa += 2 ;
	}
	else
	{
		Debug_Printf("AutoCal Da Over Err",1);
		trandu = 0;
		wattDa = 0;
		m_rf.autoCalFlag = 0;
		m_rf.autoCalWattLevel = 0;
	}

	Tx_RF_Watt_Module(trandu, wattDa);

	for(int i =0 ;i < 1;i++)
	{
		AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
		HAL_Delay(500);

		RF_eg_Exp_On(2000);
		HAL_Delay(1500);

		AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
		HAL_Delay(4000); // ÈÞ½Ä

	}

	printf("ACal %d %d -> ",trandu, wattDa);


	qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
	printf("%d \r\n",qsortBuff[0]);

//	qsortBuff[1] = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
//	printf("%d ",qsortBuff[1]);

//	qsortBuff[2] = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
//	printf("%d ",qsortBuff[2]);

//	qsortBuff[3] = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
//	printf("%d ",qsortBuff[3]);

//	qsortBuff[4] = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
//	printf("%d ",qsortBuff[4]);

//	avg = AutoCal_Avg();
	avg = qsortBuff[0];
	if(avg>wattBuff[m_rf.autoCalWattLevel])
	{
		add = (CMD_TRANDU_WATT_BASE + trandu*11 +m_rf.autoCalWattLevel+1);
		Tx_LCD_Msg(add, wattDa);

		m_rf.autoCalWattLevel++;
		if(m_rf.autoCalWattLevel == 10)
		{
			m_rf.autoCalWattLevel = 0;
			Tx_RF_Watt_Zero_ALL_Module();
			if(trandu<6)
			{
				trandu++;
				wattDa = 0;
			}
			else
			{
				trandu = 0;
				wattDa = 0;
				m_rf.autoCalFlag = 0;
				Tx_LCD_Msg(CMD_AUTO_CAL_START, 0);
			}
		}
	}

}
void AutoCal_Config_test()
{
  uint8_t wattBuff[10] = {10, 20, 30, 40, 50, 60 , 70, 80 , 90, 100};
  int avg = 0;
  uint16_t add;

  if(m_rf.autoCalFlag==0)return;

  memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
  m_rf.FeedBackCnt = 0;
#if 0
  wattDa++;
  if(wattDa>=120)
  {
	  trandu++;
	  wattDa = 100;
  }
#endif

  Tx_RF_Watt_Module(trandu, wattDa);

  for(int i =0 ;i < 5;i++)
  {
    AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
    HAL_Delay(500);

    RF_eg_Exp_On(2000);
    HAL_Delay(1000);

    AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
    HAL_Delay(4000); // ÈÞ½Ä

  }

  printf("ACal %d %d -> \r\n",trandu, wattDa);

  if(m_rf.FeedBackCnt<5)// 10°³Áß¿¡ 5°³ ¹Ì¸¸ÀÏ¶§ Åë½ÅºÒ·®
  {
    m_err.autoCalStatus = 1;
    Debug_Printf("AutoCal Commu Err",1);
  }
  else
  {
    m_err.autoCalStatus = 0;
  }

  qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
  printf(">>> %d\r\n",qsortBuff[0]);

  qsortBuff[1] = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
  printf(">>> %d\r\n",qsortBuff[1]);

  qsortBuff[2] = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
  printf(">>> %d\r\n",qsortBuff[2]);

  qsortBuff[3] = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
  printf(">>> %d\r\n",qsortBuff[3]);

  qsortBuff[4] = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
  printf(">>> %d\r\n",qsortBuff[4]);

  avg = AutoCal_Avg();

  m_rf.autoCalFlag = 0;

}
void AutoCal_Config_test2()
{
  int wattLongBuff[60] ={0,};
  int wattDaBuff[7] = {127, 126, 124, 136, 134, 120, 134};
  int avg = 0;
  uint16_t add;
  static uint16_t calCnt;

  if(m_rf.autoCalFlag==0)return;

  memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
  m_rf.FeedBackCnt = 0;
#if 0
  wattDa++;
  if(wattDa>=120)
  {
	  trandu++;
	  wattDa = 100;
  }
#endif

  Tx_RF_Watt_Module(trandu, wattDa);

  AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
  HAL_Delay(500);

  for(int i =0 ;i < 10;i++)
  {
    AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
	HAL_Delay(100);

  }
  RF_eg_Exp_On(4000);
  for(int i =0 ;i < 40;i++)
  {
    AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
	HAL_Delay(100);
  }

  for(int i =0 ;i < 10;i++)
  {
    AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
	HAL_Delay(100);

  }
  HAL_Delay(4000); // ÈÞ½Ä

  printf("ACal %d %d -> \r\n",trandu, wattDa);



	for(int i =1 ;i < 60;i++)
	{
		wattLongBuff[i] = m_rf.FeedBackWBuff[i] +(-1*m_rf.FeedBackWBuff[0]);

		printf(">>%d %d\r\n", trandu, wattLongBuff[i]);
		if(25<=i && i<35)
		{
			qsort10Buff[i-25]= wattLongBuff[i];
		}
	}
	avg = AutoCal_10_Avg();

	calCnt++;
	if(calCnt == 10)
	{
		m_rf.autoCalFlag = 0;
		calCnt = 0;

		Tx_RF_Watt_Zero_ALL_Module();
#if 0
	trandu++;
	wattDa = wattDaBuff[trandu];
	if(trandu==7)
	{
		m_rf.autoCalFlag = 0;
	}
#endif
	}

}



void AutoCal_Config_test3()
{
	uint8_t wattBuff[10] = {10, 20, 30, 40, 50, 60 , 70, 80 , 90, 100};
	int avg = 0;
	uint16_t add;

	if(m_rf.autoCalFlag==0)return;

	memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
	m_rf.FeedBackCnt = 0;

	if(wattDa<200)
	{
		wattDa += 2 ;
	}



	Tx_RF_Watt_Module(trandu, wattDa);

	for(int i =0 ;i < 1;i++)
	{
		AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
		HAL_Delay(500);

		RF_eg_Exp_On(2000);
		HAL_Delay(1500);

		AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
		HAL_Delay(4000); // ÈÞ½Ä

	}

	printf("ACal %d %d -> ",trandu, wattDa);


	qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
	printf("%d\r\n",qsortBuff[0]);

//	qsortBuff[1] = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
//	printf("%d ",qsortBuff[1]);

//	qsortBuff[2] = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
//	printf("%d ",qsortBuff[2]);

//	qsortBuff[3] = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
//	printf("%d ",qsortBuff[3]);

//	qsortBuff[4] = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
//	printf("%d ",qsortBuff[4]);

//	avg = AutoCal_Avg();

	avg = qsortBuff[0];

	if(avg >=100)
	{
		Tx_RF_Watt_Zero_ALL_Module();
		if(trandu<tranduOut)
		{
			printf("NEXT !!\r\n");
			trandu++;
			wattDa = 140;
		}
		else
		{
			printf("OUT TD !!\r\n");
			m_rf.autoCalFlag = 0;
		}

	}


}

int frqQ = 10500;
void AutoCal_Config_test_Frq()
{
  int avg = 0;
  uint16_t add;

  if(m_rf.autoCalFlag==0)return;

  memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
  m_rf.FeedBackCnt = 0;

  frqQ += 10;
  Tx_RF_FRQ_Module(trandu, frqQ);
  Tx_RF_Watt_Module(trandu, wattDa);

  printf("ACal %d %d -> \r\n",trandu, frqQ);

  for(int i =0 ;i < 1;i++)
  {
    AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
    HAL_Delay(500);

    RF_eg_Exp_On(2000);
    HAL_Delay(1500);

    AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
    HAL_Delay(4000); // ÈÞ½Ä

  }


  qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
  printf(">>> %d\r\n",qsortBuff[0]);

//  qsortBuff[1] = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
//  printf(">>> %d\r\n",qsortBuff[1]);

//  qsortBuff[2] = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
//  printf(">>> %d\r\n",qsortBuff[2]);

//  qsortBuff[3] = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
//  printf(">>> %d\r\n",qsortBuff[3]);

//  qsortBuff[4] = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
//  printf(">>> %d\r\n",qsortBuff[4]);

//  avg = AutoCal_Avg();
  if(frqQ > 13000)
  {
  	Tx_RF_Watt_Zero_ALL_Module();
  	frqQ = 10800;
  	trandu++;
//	Tx_RF_FRQ_Module(trandu, frqQ);

  	if(trandu>6)
  	{
  		trandu = 0;
		m_rf.autoCalFlag = 0;
  	}
  }

}

void RF_Borad_FeedBack_Test()
{
	static uint8_t step = STEP0;
	static uint32_t timeStamp;

	if(m_rf.feedBackTest==0)return;


	switch (step)
	{
		case STEP0:

			Tx_RF_Watt_Zero_ALL_Module();
			Tx_RF_Watt_Module(1, wattDa);
			RF_eg_Exp_On(1000);
			printf("wattDa = %d \r\n",wattDa);
			timeStamp = HAL_GetTick();
			step = STEP1;
		break;

		case STEP1:

			if(HAL_GetTick()-timeStamp >= 2000)
			{
				Tx_RF_FeedBack_Check();

				if(wattDa<200)
				{
					wattDa += 10;
				}
				else
				{
					Debug_Printf("End",1);
					wattDa = 10;
					m_rf.feedBackTest--;
					if(!m_rf.feedBackTest)
					{
						Debug_Printf("Final End",1);
					}
				}
				step = STEP0;
			}
		break;

		case STEP2:

		break;

	}




}

void RF_Rx_Parssing(uint8_t rxID)
{
	uint32_t timeStamp;



	if(rxID == RF_RX_CALLBACK)
	{
		m_rf.lastTimeStamp = 0;
		timeStamp = HAL_GetTick();
		while (HAL_GetTick() -timeStamp< 100 )
		{
			if(m_rf.lastTimeStamp)
			{
				if(HAL_GetTick() - m_rf.lastTimeStamp>50)break;
			}
		}
	}


	if(m_rf.lastTimeStamp == 0) return;

	if(HAL_GetTick() - m_rf.lastTimeStamp>50)
	{
		m_rf.lastTimeStamp = 0;

		memcpy(m_rf.rxBuffPassing, m_rf.rxBuff, 30);
		memset(m_rf.rxBuff, 0, 30);

		Debug_Rx_RF_Printf(m_rf.rxBuffPassing, m_rf.rxCnt);

		m_rf.rxCnt = 0;
		m_rf.rxCallBackCmd = m_rf.rxBuffPassing[RF_INDEX_CMD];
		switch (m_rf.rxCallBackCmd)
		{
			case GEN_STATUS_CHECK_R:
				m_err.rfTimeout = 0;
				m_err.rfComuErr = 0;
				m_err.rfStatus= m_rf.rxBuffPassing[RF_INDEX_DATA]<<8 |m_rf.rxBuffPassing[RF_INDEX_DATA+1];// ¾ÆÁ÷ ¾ÈÇÔ
				m_rf.liveChkCnt++;
			break;

			case GEN_GET_VERSION_R:
			break;

			case GEN_FREQ_SET_R:
				Debug_Printf("[RX_RF] GEN_FREQ_SET_R",1);
			break;

			case GEN_OUTPUT_SET_R://
				Debug_Printf("[RX_RF] GEN_OUTPUT_SET_R",1);
			break;

			case GEN_MAX_ON_TIME_SET_R:
				Debug_Printf("[RX_RF] GEN_MAX_ON_TIME_SET_R",1);
			break;

			case GEN_RF_VOLTAGE_REQ_R:
				Debug_Printf("[RX_RF] GEN_RF_VOLTAGE_REQ_R",1);
			break;

			case ALL_CH_FREQ_SET_R:
				Debug_Printf("[RX_RF] ALL_CH_FREQ_SET_R",1);
			break;

			case ALL_CH_OUTPUT_SET_R:
				Debug_Printf("[RX_RF] ALL_CH_OUTPUT_SET_R",1);
			break;
		}

		ddTimeEnd1(); //wndksdebug
	}


}


int testTriger=1;
void Rf_Test()
{

}


void CurrentEnergy_Cal()
{
	uint16_t pulse1Htime =m_rf.pulseBuff[IDX_MAIN_P1_DURATION_TIME];
	uint16_t pulse2Htime = m_rf.pulseBuff[IDX_MAIN_P2_DURATION_TIME];
	uint16_t pulse3Htime = m_rf.pulseBuff[IDX_MAIN_P3_DURATION_TIME];
	uint16_t pulse4Htime = m_rf.pulseBuff[IDX_MAIN_P4_DURATION_TIME];
	uint16_t pulse1Watt  = m_rf.pulseBuff[IDX_MAIN_P1_WATT];
	uint16_t pulse2Watt  = m_rf.pulseBuff[IDX_MAIN_P2_WATT];
	uint16_t pulse3Watt  = m_rf.pulseBuff[IDX_MAIN_P3_WATT];
	uint16_t pulse4Watt  = m_rf.pulseBuff[IDX_MAIN_P4_WATT];
	uint16_t energy = 0;

	if(m_rf.pulseEndisBuff[1]) energy += (pulse1Htime * pulse1Watt);
	if(m_rf.pulseEndisBuff[2]) energy += (pulse2Htime * pulse2Watt);
	if(m_rf.pulseEndisBuff[3]) energy += (pulse3Htime * pulse3Watt);
	if(m_rf.pulseEndisBuff[4]) energy += (pulse4Htime * pulse4Watt);


	m_rf.currentEnergy = energy;

	Tx_LCD_Msg(CMD_CURRENT_JOULE, m_rf.currentEnergy);

}



void Exp_Nomal_Config()
{
	uint16_t totalEenerge;

	static uint8_t step = STEP0;
	if(m_rf.readyFlag != READY_ON) return;

	switch (step)
	{
		case STEP0:
			if(testExpFlag || IS_HP1_SHOT_PUSH())
			{
				HAL_Delay(200);
				testExpFlag = 0;
				Tx_LCD_Msg(CMD_LCD_EXP, LCD_EXP_START);
				Tx_Hand1_Msg(CMD_LCD_EXP, LCD_EXP_START);
				HAL_Delay(200);
				RF_Pwm_On();

				step = STEP1;
			}
		break;

		case STEP1:
#if 0
			RF_Pwm_Conter_Individual();
#else
			RF_Pwm_Conter_Common(m_rf.testPulseOption);
#endif
			if(m_rf.expEndFlag) step = STEP2;
		break;

		case STEP2:
			if(m_rf.expEndFlag)
			{
				m_rf.expEndFlag = 0;

				m_rf.totaEnergy = m_rf.totaEnergy + m_rf.energy;
				totalEenerge = m_rf.totaEnergy;
				Tx_LCD_Msg(CMD_TOTAL_JOULE, totalEenerge);

				m_rf.currentShot++;
				Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);
				if(m_eep.remainingShotNum > 0)
				{
					m_eep.remainingShotNum--;
				}
				else
				{
					m_rf.remainingShotNegative++;
				}

				Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
				Tx_LCD_Msg(CMD_LCD_EXP, LCD_EXP_END);
				Tx_Hand1_Msg(CMD_LCD_EXP, LCD_EXP_END);
				Tx_Hand1_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);

				Exp_Total_Log();
				step = STEP0;
			}
		break;

	}

}


void Exp_Config()
{
	Exp_Nomal_Config();
}
void Rf_Config()
{

#if 1
	LCD_Status_Tret();
	Exp_Config();
	AutoCal_Config_test3();
	RF_Borad_FeedBack_Test();

#else

	Rf_Test();
#endif


}


