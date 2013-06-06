/*
 * GPS.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: Simon
 */
#include "GPS.h"
#include <stdlib.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/listbox.h"
#include "grlib/pushbutton.h"
#include "utils/cmdline.h"
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "utils/swupdate.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"
#include "drivers/formike240x320x16_ili9320.h"
#include "drivers/touch.h"
#include "utils/uartstdio.h"
#include "inttypes.h"

int getdataz(void) {
return UARTgetc();
}
// Send a byte array of UBX protocol to the GPS
void sendUBX(int *MSG, int len) {
	i=0;
  while (i<len) {
	  i++;
	  UARTprintf("%h", MSG[i]);
   // Serial.print(MSG[i], HEX);
  }
  UARTprintf("\n");
}
// Calculate expected UBX ACK packet and parse UBX response from GPS
int getUBX_ACK(int *MSG) {
  int b;
  int millis = 0;
  int ackByteID = 0;
  int ackPacket[10];
  //unsigned long startTime = millis();
  //Serial.print(" * Reading ACK response: ");

  // Construct the expected ACK packet
  ackPacket[0] = 0xB5;	// header
  ackPacket[1] = 0x62;	// header
  ackPacket[2] = 0x05;	// class
  ackPacket[3] = 0x01;	// id
  ackPacket[4] = 0x02;	// length
  ackPacket[5] = 0x00;
  ackPacket[6] = MSG[2];	// ACK class
  ackPacket[7] = MSG[3];	// ACK id
  ackPacket[8] = 0;		// CK_A
  ackPacket[9] = 0;		// CK_B

  // Calculate the checksums
  i=2;
  while ( i<8){
	  i++;
    ackPacket[8] = ackPacket[8] + ackPacket[i];
    ackPacket[9] = ackPacket[9] + ackPacket[8];
  }

  while (1) {
millis++;
    // Test for success
    if (ackByteID > 9) {
      // All packets in order!
    	UARTprintf(" (SUCCESS!)");
      return true;
    }

    // Timeout if no valid response in 3 seconds
    if (millis > 3000) {
    	UARTprintf(" (FAILED!)");
      return false;
    }
    // Make sure data is available to read
    if (getdataz()/getdataz() > 0) {
      b = getdataz();
      // Check that bytes arrive in sequence as per expected ACK packet
      if (b == ackPacket[ackByteID]) {
        ackByteID++;
        UARTprintf("%h", b);
      }
      else {
        ackByteID = 0;	// Reset and look again, invalid order
      }

    }
  }
}

char* URLEncode(const char* msg)
{
   const char *hex = "0123456789abcdef";
   char* encodedMsg = "";

   while (*msg!='\0'){
       if( ('a' <= *msg && *msg <= 'z')
               || ('A' <= *msg && *msg <= 'Z')
               || ('0' <= *msg && *msg <= '9') ) {
           encodedMsg += *msg;
       } else {
           encodedMsg += '%';
           encodedMsg += hex[*msg >> 4];
           encodedMsg += hex[*msg & 15];
       }
       msg++;
   }
   return encodedMsg;
}



	char *itoa(int num, char *str, int radix) {
	    char sign = 0;
	    char temp[17];  //an int can only be 16 bits long
	                    //at radix 2 (binary) the string
	                    //is at most 16 + 1 null long.
	    int temp_loc = 0;
	    int digit;
	    int str_loc = 0;

	    //save sign for radix 10 conversion
	    if (radix == 10 && num < 0) {
	        sign = 1;
	        num = -num;
	    }

	    //construct a backward string of the number.
	    do {
	        digit = (unsigned int)num % radix;
	        if (digit < 10)
	            temp[temp_loc++] = digit + '0';
	        else
	            temp[temp_loc++] = digit - 10 + 'A';
	        num /= radix;
        } while ((unsigned int)num > 0);

	    //now add the sign for radix 10
	    if (radix == 10 && sign) {
	        temp[temp_loc] = '-';
	    } else {
          temp_loc--;
	    }


	    //now reverse the string.
		while ( temp_loc >=0 ) {// while there are still chars
	        str[str_loc++] = temp[temp_loc--];
	    }
	    str[str_loc] = 0; // add null termination.

	    return str;
	}

	unsigned long millis()
	{

		return 0;
	}
	void Initi(void)
	{

			PosData = 0;
			ck_a=0;
			ck_b=0;
			UBX_step=0;
			NewData=0;
			Fix=0;
			PrintErrors=0;
		GPS_timer=millis();   //Restarting timer...
		// Initialize serial port
	//		Serial.begin(38400);
		//UARTStdioInitExpClk(1, 38400);
	}

	/****************************************************************
	 *
	 ****************************************************************/
	 // Join 4 bytes into a long
	long join_4_bytes(unsigned char Buffer[])
	{
	  union long_union {
		int32_t dword;
		uint8_t  byte[4];
	} longUnion;

	  longUnion.byte[0] = *Buffer;
	  longUnion.byte[1] = *(Buffer+1);
	  longUnion.byte[2] = *(Buffer+2);
	  longUnion.byte[3] = *(Buffer+3);
	  return(longUnion.dword);
	}

	long join_2_bytes(unsigned char Buffer[])
	{
	  union long_union {
		int32_t dword;
		uint8_t  byte[2];
	} longUnion;

	  longUnion.byte[0] = *Buffer;
	  longUnion.byte[1] = *(Buffer+1);
	  return(longUnion.dword);
	}

	long one_byte(unsigned char Buffer[])
	{
	  union long_union {
		int32_t dword;
		uint8_t  byte[1];
	} longUnion;

	  longUnion.byte[0] = *Buffer;
	  return(longUnion.dword);
	}

	char* bytes_to_decimal(char Buffer[])
	{

	int number = 0;
	return(itoa(number, Buffer, 10));
	}
	/****************************************************************
	 *
	 ****************************************************************/
	// Ublox checksum algorithm
	void ubx_checksum(uint8_t ubx_data)
	{
	  ck_a+=ubx_data;
	  ck_b+=ck_a;
	}

	/****************************************************************
	 *
	 ****************************************************************/
	// Private Methods //////////////////////////////////////////////////////////////
	void parse_ubx_gps(void)
	{
	  int j;
	  switch(UBX_class){
	  case 0x01:

	    switch(UBX_id)//Checking the UBX ID
	    {
	    case 0x02: //ID NAV-POSLLH
	      j=0;
	      Time = join_4_bytes(&UBX_buffer[j]); // ms Time of week
	      j+=4;
	      Longitude = join_4_bytes(&UBX_buffer[j]); // lon*10000000
	      j+=4;
	      Lattitude = join_4_bytes(&UBX_buffer[j]); // lat*10000000
	      j+=4;
	      Altitude = join_4_bytes(&UBX_buffer[j]);  // elipsoid heigth mm
	      j+=4;
	      //Altitude = (float)join_4_bytes(&UBX_buffer[j]);  // MSL heigth mm
	      NewData=1;
	      break;
	    case 0x03://ID NAV-STATUS
	      //if(UBX_buffer[4] >= 0x03)
		  if((UBX_buffer[4] >= 0x03)&&(UBX_buffer[5]&0x01))
	        Fix=1; //valid position
	      else
	        Fix=0; //invalid position
	      break;

	    case 0x06://ID NAV-SOL
	      if((UBX_buffer[10] >= 0x03)&&(UBX_buffer[11]&0x01))
	        Fix=1; //valid position
	      else
	        Fix=0; //invalid position
	      UBX_ecefVZ=join_4_bytes(&UBX_buffer[36]);  //Vertical Speed in cm/s
	      NumSats=UBX_buffer[47];                    //Number of sats...
	      break;

	    case 0x12:// ID NAV-VELNED
	      j=16;
	      Speed_3d = join_4_bytes(&UBX_buffer[j]); // cm/s
	      j+=4;
	      Ground_Speed = join_4_bytes(&UBX_buffer[j]); // Ground speed 2D cm/s
	      j+=4;
	      Ground_Course = join_4_bytes(&UBX_buffer[j]); // Heading 2D deg*100000
	      Ground_Course /= 1000;	// Rescale heading to deg * 100
	      j+=4;
	      break;
	      }
		//  UBX_class = 0x0D;
		PosData = 1;
	    break;
		//Serial.println(UBX_class);
		case 0x0D:
		//UBX_id = 0x03;
		    switch(UBX_id)//Checking the UBX ID
	    {
		    case 0x03: //ID TIM-TM2
		ch = one_byte(&UBX_buffer[0]);
		flags = one_byte(&UBX_buffer[1]);
		count = join_2_bytes(&UBX_buffer[2]);
		wnR = join_2_bytes(&UBX_buffer[4]);
		wnF = join_2_bytes(&UBX_buffer[6]);
		towMsR = join_4_bytes(&UBX_buffer[8]);
		towSubMsR = join_4_bytes(&UBX_buffer[12]);
		towMsF = join_4_bytes(&UBX_buffer[16]);
		towSubMsF = join_4_bytes(&UBX_buffer[20]);
		accEst = join_4_bytes(&UBX_buffer[24]);
		checksum = join_2_bytes(&UBX_buffer[28]);
	      break;
		}
		NewData=1;
	break;
	}
	}
	void Read(void)
	{
	  static unsigned long GPS_timer=0;
	  uint8_t data;
	  int numc;
		numc = ((getdataz())/(getdataz()));

	  if (numc > 0)
		  //i = 0;
	    for (i=0;i<numc;i++)  // Process bytes received
	      {
	    	getdataz();
			data = getdataz();
	      switch(UBX_step)
	      {
	      case 0:
	        if(data==0xB5)
	          UBX_step++;
	        break;
	      case 1:
	        if(data==0x62)
	          UBX_step++;
	        else
	          UBX_step=0;
	        break;
	      case 2:
	        UBX_class=data;
	        ubx_checksum(UBX_class);
	        UBX_step++;
	        break;
	      case 3:
	        UBX_id=data;
	        ubx_checksum(UBX_id);
	        UBX_step++;
	        break;
	      case 4:
	        UBX_length_hi=data;
	        ubx_checksum(UBX_length_hi);
	        UBX_step++;

			if (UBX_length_hi>=UBX_MAX_SIZE)
	        {
			  if (PrintErrors)
				  UARTprintf("ERR:GPS_BAD_PAYLOAD_LENGTH!!");
	          UBX_step=0;
	          ck_a=0;
	          ck_b=0;
	        }
	        break;
	      case 5:
	        UBX_length_lo=data;
	        ubx_checksum(UBX_length_lo);
	        UBX_step++;
			UBX_counter=0;
	        break;
	      case 6:
		if (UBX_counter < UBX_length_hi)
	        {
	          UBX_buffer[UBX_counter] = data;
	          ubx_checksum(data);
	          UBX_counter++;
	          if (UBX_counter==UBX_length_hi)
	            UBX_step++;
	        }
	        break;
	      case 7:
	        UBX_ck_a=data;
		//	Serial.println(UBX_ck_a);
	        UBX_step++;
	        break;
	      case 8:
	        UBX_ck_b=data;
	    //   Serial.println(UBX_ck_b);

	        if((ck_a==UBX_ck_a)&&(ck_b==UBX_ck_b))
		  		parse_ubx_gps();
	        else
			  {
			  if (PrintErrors)
				  UARTprintf("ERR:GPS_CHK!!");
			  }
	        UBX_step=0;
	        ck_a=0;
	        ck_b=0;
	        GPS_timer=millis();
	        break;
		  }
	    }
	  if ((millis() - GPS_timer)>2000)
	    {
		Fix = 0;
		if (PrintErrors)
			UARTprintf("ERR:GPS_TIMEOUT!!");
	    }
	}


