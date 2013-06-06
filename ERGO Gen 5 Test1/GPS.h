/*
 * GPS.h
 *
 *  Created on: Jun 5, 2013
 *      Author: Simon
 */

#ifndef GPS_H_
#define GPS_H_

#include "inttypes.h"


#define UBX_MAX_SIZE 60
		int i;
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
	int getdataz(void);
	void sendUBX(int *MSG, int len);
	int getUBX_ACK(int *MSG);
	char* URLEncode(const char* msg);
	char *itoa(int num, char *str, int radix);
	unsigned long millis();
	void Initi(void);
	void Read(void);

#endif /* GPS_H_ */
