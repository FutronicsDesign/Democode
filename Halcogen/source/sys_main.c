/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */
#include "sys_common.h"
#include "system.h"
#include <math.h>
#include <stdbool.h>
#include "sci.h"
#include "spi.h"
#include "rti.h"
#include "uartstdio.h"
#include "sdc-hercules.h"
/* USER CODE BEGIN (1) */
#include <string.h>
#include <stdio.h>
#include "ff.h"
/* USER CODE END */
#include "diskio.h"

#if _USE_LFN
static char lfn[_MAX_LFN + 1];
#endif


#if _USE_LFN
fno.lfname = lfn;
fno.lfsize = sizeof(lfn);
#endif
/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/
//void showdata4(struct cell c,float vPack,float iPack,float zAvg,float TempPack, float PCap);
//void showdata4(struct cell c[],float vPack,float iPack,float zAvg,float TempPack, float PCap);
//*Number of cells connected in Series & Parallel and Temp. Sensors

long fileNum = 10000;  // maximum 99999
char name[13];
FATFS Fatfs;
FRESULT res;
FILINFO fno;
FIL fsrc;


int main(void)
{

UINT bw;
FRESULT fr;

char filename[16]; // enough space for characters and terminating NUL


      sciInit(); // To Initalize LIN/SCI2 routines to receive commands and transmit data
      //  spiInit(); // Use it  in Fatfs port

      UARTprintf("Futronics Limited");

       rtiInit();
      /* Enable RTI Compare 3 interrupt notification */
      rtiEnableNotification(rtiNOTIFICATION_COMPARE3);
      /* Enable IRQ - Clear I flag in CPS register */


      _enable_IRQ();
      /* Start RTI Counter Block 1 */
      rtiStartCounter(rtiCOUNTER_BLOCK1);

   //   _cacheDisable_();

   //   mmcSelectSpi(spiPORT1, spiREG1);  // SD card is on the SPI1
        mmcSelectSpi(spiPORT2, spiREG2);  // SD card is on the SPI2
   //   SD_Test();

   //   f_mount(&Fatfs, "", 3);     /* Give a work area to the default drive */


   //   sprintf(fr, "xyz_%d.txt", GetNextIndex("") );

 //     fr = f_open(&fil,"xyz_%d.txt", FA_WRITE | FA_CREATE_ALWAYS);  /* Create a file */

      incFileNum(); // set it to dat10000.txt
      if((res == FR_OK) || (res == FR_EXIST))
      incFileNum();
   //   Serial.println("new file name: " + String(name));
      save(name);

     // while(1);

}


void incFileNum() { // generate next file name:

    int i; // string filename ;
        for (i = 0; i < fileNum; ++i) {
            int ret  = snprintf(name, 13, "sachin_%d.txt", i);
            // sprintf(buf,"sachin_%d.txt", i);
            if (ret < 0 || ret >= 13) {
                fprintf(stderr, "snprintf: error at iteration %d: return value was %d\n", i, ret);
                exit(1);
            }

}

}

void save(char *name)

{
    int nStatus;
        //
        // Mount the file system, using logical disk 0.
         res = f_mount(&Fatfs, "", FS_FAT32);
       // iFResult = f_mount(0, &g_sFatFs);
        if(res != FR_OK)
        {
     //       UARTprintf("f_mount error: %s\n", StringFromFResult(iFResult));
            return(1);
        }



          /* Open  the file for append */
          res = f_open(&fsrc,name, FA_WRITE | FA_CREATE_ALWAYS);  /* Create a file */
          res = open_append(&fsrc, name);


          if (res != FR_OK) {
              /* Error. Cannot create the file */
              while(1);
          }

          // if file empty, write header
          if (! f_size(&fsrc)) {

              res = f_printf(&fsrc,name);


            if (res <0) {
                /* Error. Cannot write header */
                while(1);
            }
          }

        while(1){
        }
          if (res < FR_OK) {
              /* Error. Cannot log data */
              while(1);
          }

          /* Close the file */
          res = f_close(&fsrc);
          if (res != FR_OK)
          {
            /* Error. Cannot close the file */
            while(1);
          }



}

//void loop() {
  // save new integer every loop and then wait 1s
//    fr = f_open(&fil, "xyz.txt", FA_WRITE | FA_CREATE_ALWAYS);
//    if (fr) {
    // save a different number each loop
//        f_printf(String(millis())+","+String(int_iter));
//    testfile.close();
//    Serial.println("Saving "+String(int_iter));
//  } else {
//    Serial.println("error opening file");
//  }
//  int_iter+=1;
//  delay(1000);
//}

/* USER CODE BEGIN (4) */
/* USER CODE END */
