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
		extern int i;
		extern int PosData;
		extern long Time;
		extern long Lattitude;
		extern long Longitude;
		extern long Altitude;
		extern long ch;
		extern long flags;
		extern long count;
		extern long wnR;
		extern long wnF;
		extern long towMsR;
		extern long towSubMsR;
		extern long towMsF;
		extern long towSubMsF;
		extern long accEst;
		extern long checksum;
		extern long Ground_Speed;
		extern long Speed_3d;
		extern long Ground_Course;
		extern int hour;
		extern int minute;
		extern int sow;
		extern int second;
		extern int millisecond;
		extern int microsecond;
		extern int nanosecond;
		extern int week_year;
		extern int days;
		extern int month;
		extern int weeks;
		extern int year;
		extern uint8_t NumSats;
		extern uint8_t Fix;
		extern uint8_t RTC;
		extern uint8_t NewData;
		extern uint8_t PrintErrors;
		extern uint8_t ck_a;
		extern uint8_t ck_b;
		extern uint8_t UBX_step;
		extern uint8_t UBX_class;
		extern uint8_t UBX_id;
		extern uint8_t UBX_length_hi;
		extern uint8_t UBX_length_lo;
		extern uint8_t UBX_counter;
		extern uint8_t UBX_buffer[60];
		extern uint8_t UBX_ck_a;
		extern uint8_t UBX_ck_b;
		extern long GPS_timer;
		extern long UBX_ecefVZ;
		int getdataz(void);
		void sendUBX(int *MSG, int len);
		int getUBX_ACK(int *MSG);
		char* URLEncode(const char* msg);
		char *itoa(int num, char *str, int radix);
		unsigned long millis();
		void Initi(void);
		void Read(void);

#endif /* GPS_H_ */
