#ifndef GPS_UBLOX_h
#define GPS_UBLOX_h
//#define __cplusplus
#ifdef __cplusplus
extern "C" {
#endif

// Standard "C" code here

#ifdef __cplusplus

#include <inttypes.h>

#define UBX_MAX_SIZE 60

class GPS_UBLOX_Class
{
private:
	uint8_t ck_a;
	uint8_t ck_b;
	uint8_t UBX_step;
	uint8_t UBX_class;
	uint8_t UBX_id;
	uint8_t UBX_length_hi;
	uint8_t UBX_length_lo;
	uint8_t UBX_counter;
	uint8_t UBX_buffer[UBX_MAX_SIZE];
	uint8_t UBX_ck_a;
	uint8_t UBX_ck_b;
	long GPS_timer;
	long UBX_ecefVZ;
	void parse_ubx_gps();
	char* bytes_to_decimal(char Buffer[]);
	void ubx_checksum(unsigned char ubx_data);

	long join_4_bytes(unsigned char Buffer[]);
	long join_2_bytes(unsigned char Buffer[]);
	long one_byte(unsigned char Buffer[]);

public:

	GPS_UBLOX_Class();
	void Initi();
	void Read();
	int PosData;
	long Time;
	long Lattitude;
	long Longitude;
	long Altitude;
	long ch;
	long flags;
	long count;
	long wnR;
	long wnF;
	long towMsR;
	long towSubMsR;
	long towMsF;
	long towSubMsF;
	long accEst;
	long checksum;
	long Ground_Speed;
	long Speed_3d;
	long Ground_Course;
	int hour;
	int minute;
	int sow;
	int second;
	int millisecond;
	int microsecond;
	int nanosecond;
	int week_year;
	int days;
	int month;
	int weeks;
	int year;
	//void translate_tow(long ms, long week_number, long nanis);
	uint8_t NumSats;
	uint8_t Fix;
	uint8_t RTC;
	uint8_t NewData;
	uint8_t PrintErrors;
};
extern GPS_UBLOX_Class GPS;
#endif

#endif
