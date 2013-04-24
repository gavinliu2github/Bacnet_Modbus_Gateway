
#ifndef	_SCHEDULE_H_

#define	_SCHEDULE_H_


#define MAX_ID					254
#define MAX_WR      			20
#define MAX_AR					16

#define WR_DESCRIPTION_SIZE		31
#define AR_DESCRIPTION_SIZE		29
#define ID_SIZE					3
#define AR_TIME_SIZE			46
#define WR_TIME_SIZE			72
#define SCH_TIME_SIZE			1

#define SCAN_DB_SIZE			5 	



#define	MAX_INTERVALS_PER_DAY	4


/* the following defintion is for schedule */

#define SCHEDUAL_MODBUS_ADDRESS 200

typedef enum
{
	MODBUS_TIMER_ADDRESS		= SCHEDUAL_MODBUS_ADDRESS, // 200
	
	MODBUS_WR_DESCRIP_FIRST		= MODBUS_TIMER_ADDRESS + 8,
	MODBUS_WR_DESCRIP_LAST		= MODBUS_WR_DESCRIP_FIRST + WR_DESCRIPTION_SIZE * MAX_WR ,
	
	MODBUS_AR_DESCRIP_FIRST		= MODBUS_WR_DESCRIP_LAST ,
	MODBUS_AR_DESCRIP_LAST		= MODBUS_AR_DESCRIP_FIRST +  AR_DESCRIPTION_SIZE * MAX_AR ,
	
	MODBUS_ID_FIRST				= MODBUS_AR_DESCRIP_LAST ,
	MODBUS_ID_LAST				= MODBUS_ID_FIRST + ID_SIZE * MAX_ID ,
	
	MODBUS_AR_TIME_FIRST		= MODBUS_ID_LAST ,
	MODBUS_AR_TIME_LAST			= MODBUS_AR_TIME_FIRST + AR_TIME_SIZE * MAX_AR ,
	
	MODBUS_WR_ONTIME_FIRST		= MODBUS_AR_TIME_LAST ,
	MODBUS_WR_ONTIME_LAST		= MODBUS_WR_ONTIME_FIRST + WR_TIME_SIZE * MAX_WR ,
	
	MODBUS_WR_OFFTIME_FIRST		= MODBUS_WR_ONTIME_LAST ,
	MODBUS_WR_OFFTIME_LAST		= MODBUS_WR_OFFTIME_FIRST + WR_TIME_SIZE * MAX_WR,

	MODBUS_SCAN_DB_CTR			= MODBUS_WR_OFFTIME_LAST, // 5670
	MODBUS_SCAN_DB_START		= MODBUS_SCAN_DB_CTR + 1, // +1
	MODBUS_SCAN_DB_LAST			= MODBUS_SCAN_DB_START + SCAN_DB_SIZE * MAX_ID,	// + 5 * 254 = 1270



	MODBUS_TOTAL_PARAMETERS

};

typedef struct //_tagSch_Time
{
	unsigned char centry;
	unsigned char year;
	unsigned char month;
	unsigned char week;
	unsigned char date;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}Sch_Time;


typedef struct //_tagSTR_WR
{
	union
	{
		unsigned char all[WR_DESCRIPTION_SIZE];
		struct
		{
			unsigned char full_table[20];
			unsigned char lable[8];
			unsigned char holiday1;
			unsigned char holiday2;
			unsigned char flag;	
		/*  flag formate:
			7 		6		5		4		3 		2 		1		0
		  a/m 	value		-		-		-		-		-		-
		*/
		}Desc;
	}UN;
	unsigned char OnTime[WR_TIME_SIZE]; 
	unsigned char OffTime[WR_TIME_SIZE];
}STR_WR; /* weekly routions description */

#define	WR_STRUCT_LENGTH	(WR_DESCRIPTION_SIZE + WR_TIME_SIZE + WR_TIME_SIZE)



typedef struct
{
	union
	{
		unsigned char all[AR_DESCRIPTION_SIZE];
		struct
		{
			unsigned char full_table[20];
			unsigned char lable[8];
			unsigned char flag;
		/*  flag formate:
			7 		6		5		4		3 		2 		1		0
		  a/m 	value		-		-		-		-		-		-
		*/
		}Desc;
	}UN;
	unsigned char Time[AR_TIME_SIZE];
}STR_AR; /* annual roution */

#define	AR_STRUCT_LENGTH	(AR_DESCRIPTION_SIZE + AR_TIME_SIZE)

typedef	union
{
	unsigned char all[ID_SIZE];
	struct
	{
	unsigned char schedule1;
	unsigned char schedule2;
	unsigned char flag;  
	/*  flag formate:
		7 		6		5		4		3 		2 		1		0
	  a/m 	output	state1	state2		-		-		-		-
	*/
	}Str;
}UN_ID; /*config roution */


typedef struct
{
	unsigned char table;
	unsigned char line;
	unsigned char dat[72];
}STR_FLASH;

#define WR_BLOCK_SIZE				1024
#define AR_BLOCK_SIZE				1024
#define ID_BLOCK_SIZE				1536
#define AR_TIME_BLOCK_SIZE			1024
#define INITIALIZE_BLOCK_SIZE		512
 
#define TIME_START_ADDRESS			0X14
#define WR_START_ADDRESS			0X15
#define WR_ON_TIME_START_ADDRESS	0X16
#define WR_OFF_TIME_START_ADDRESS	0X17
#define AR_START_ADDRESS			0X18
#define AR_TIME_START_ADDRESS		0X19
#define ID_START_ADDRESS			0X1a
#define NO_DEFINE_ADDRESS			0xB4DC


extern unsigned char xdata ar_state_index[2];
extern unsigned char xdata wr_state_index[3];
extern unsigned char xdata holiday1_state_index[3];
extern unsigned char xdata holiday2_state_index[3];

extern unsigned char xdata output_state_index[32];
extern unsigned char xdata schedual1_state_index[32];
extern unsigned char xdata schedual2_state_index[32];
extern bit calibrated_time;

extern STR_FLASH flash;
extern unsigned char bdata REFRESH_STATUS;
extern unsigned char xdata daylight_enable;
extern unsigned char xdata daylight_flag;
extern bit BIT_FLAG; // 0 -- run schedule 


extern STR_WR WR_Roution[MAX_WR];
extern STR_AR AR_Roution[MAX_AR];
extern UN_ID ID_Config[MAX_ID];

extern unsigned char far schedule_flag;
extern unsigned char far schedule_id;

void SetBit(unsigned char bit_number, unsigned char *byte);
void ClearBit(unsigned char bit_number, unsigned char *byte);
bit GetBit(unsigned char bit_number, unsigned char *value);
void CheckAnnualRoutines(void);
void CheckWeeklyRoutines(void);
void SendSchedualData(unsigned char id_index, bit output);
void CheckIdRoutines(void);
void CaculateTime(void);

#endif