/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Src/waveplayer.c 
  * @author  MCD Application Team
  * @brief   This file provides the Audio Out (playback) interface API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "waveplayer.h"

/* Private define ------------------------------------------------------------*/
#define TOUCH_NEXT_XMIN         325
#define TOUCH_NEXT_XMAX         365
#define TOUCH_NEXT_YMIN         212
#define TOUCH_NEXT_YMAX         252

#define TOUCH_PREVIOUS_XMIN     250
#define TOUCH_PREVIOUS_XMAX     290
#define TOUCH_PREVIOUS_YMIN     212
#define TOUCH_PREVIOUS_YMAX     252

#define TOUCH_STOP_XMIN         170
#define TOUCH_STOP_XMAX         210
#define TOUCH_STOP_YMIN         212
#define TOUCH_STOP_YMAX         252

#define TOUCH_PAUSE_XMIN        100
#define TOUCH_PAUSE_XMAX        124
#define TOUCH_PAUSE_YMIN        212
#define TOUCH_PAUSE_YMAX        252

#define TOUCH_VOL_MINUS_XMIN    20
#define TOUCH_VOL_MINUS_XMAX    70
#define TOUCH_VOL_MINUS_YMIN    212
#define TOUCH_VOL_MINUS_YMAX    252

#define TOUCH_VOL_PLUS_XMIN     402
#define TOUCH_VOL_PLUS_XMAX     452
#define TOUCH_VOL_PLUS_YMIN     212
#define TOUCH_VOL_PLUS_YMAX     252

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static AUDIO_OUT_BufferTypeDef  BufferCtl;
static int16_t FilePos = 0;
static __IO uint32_t uwVolume = 20;
static Point NextPoints[] = {{TOUCH_NEXT_XMIN, TOUCH_NEXT_YMIN},
                             {TOUCH_NEXT_XMAX, (TOUCH_NEXT_YMIN+TOUCH_NEXT_YMAX)/2},
                             {TOUCH_NEXT_XMIN, TOUCH_NEXT_YMAX}};
static Point PreviousPoints[] = {{TOUCH_PREVIOUS_XMIN, (TOUCH_PREVIOUS_YMIN+TOUCH_PREVIOUS_YMAX)/2},
                                 {TOUCH_PREVIOUS_XMAX, TOUCH_PREVIOUS_YMIN},
                                 {TOUCH_PREVIOUS_XMAX, TOUCH_PREVIOUS_YMAX}};

WAVE_FormatTypeDef WaveFormat;
FIL WavFile;
uint8_t check_STOP = 1;

extern FILELIST_FileTypeDef FileList;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
extern uint8_t check_FIRST;
extern uint8_t state_INPUT;
extern uint8_t clk_IN;
/* Private function prototypes -----------------------------------------------*/
static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info);
static uint8_t PlayerInit(uint32_t AudioFreq);
static void AUDIO_PlaybackDisplayButtons(void);
static void AUDIO_AcquireTouchButtons(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes Audio Interface.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Init(void)
{
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, uwVolume, I2S_AUDIOFREQ_48K) == 0)
  {
    return AUDIO_ERROR_NONE;
  }
  else
  {
    return AUDIO_ERROR_IO;
  }
}

/**
  * @brief  Starts Audio streaming.    
  * @param  idx: File index
  * @retval Audio error
  */ 
AUDIO_ErrorTypeDef AUDIO_PLAYER_Start(uint8_t idx)
{
  uint32_t bytesread;
  f_close(&WavFile);
  if(AUDIO_GetWavObjectNumber() > idx)
  { 
    GetFileInfo(idx, &WaveFormat);
    
    /*Adjust the Audio frequency */
    PlayerInit(WaveFormat.SampleRate); 
    
    BufferCtl.state = BUFFER_OFFSET_NONE;
    
    /* Get Data from USB Flash Disk */
    f_lseek(&WavFile, 0);
    
    /* Fill whole buffer at first time */
    if(f_read(&WavFile, 
              &BufferCtl.buff[0], 
              AUDIO_OUT_BUFFER_SIZE, 
              (void *)&bytesread) == FR_OK)
    {
    if(check_FIRST == 1 || check_STOP == 1){
    	check_FIRST = 0;
    	check_STOP = 0;
    	AudioState = AUDIO_STATE_PAUSE;
    }
    else
    	AudioState = AUDIO_STATE_PLAY;
      AUDIO_PlaybackDisplayButtons();
      BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PLAY ]", LEFT_MODE);
      { 
        if(bytesread != 0)
        {
          BSP_AUDIO_OUT_Play((uint16_t*)&BufferCtl.buff[0], AUDIO_OUT_BUFFER_SIZE);
          BufferCtl.fptr = bytesread;
          return AUDIO_ERROR_NONE;
        }
      }
    }
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process. 
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Process(void)
{
  uint32_t bytesread, elapsed_time;
  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  static uint32_t prev_elapsed_time = 0xFFFFFFFF;
  uint8_t str[16];
  
  switch(AudioState)
  {
  case AUDIO_STATE_PLAY:
    if(BufferCtl.fptr >= WaveFormat.FileSize)
    {
      BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
      AudioState = AUDIO_STATE_NEXT;
    }
    
    if(BufferCtl.state == BUFFER_OFFSET_HALF)
    {
      if(f_read(&WavFile, 
                &BufferCtl.buff[0], 
                AUDIO_OUT_BUFFER_SIZE/2, 
                (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
      BufferCtl.state = BUFFER_OFFSET_NONE;
      BufferCtl.fptr += bytesread; 
    }
    
    if(BufferCtl.state == BUFFER_OFFSET_FULL)
    {
      if(f_read(&WavFile, 
                &BufferCtl.buff[AUDIO_OUT_BUFFER_SIZE /2], 
                AUDIO_OUT_BUFFER_SIZE/2, 
                (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
 
      BufferCtl.state = BUFFER_OFFSET_NONE;
      BufferCtl.fptr += bytesread; 
    }
    
    /* Display elapsed time */
    elapsed_time = BufferCtl.fptr / WaveFormat.ByteRate; 
    if(prev_elapsed_time != elapsed_time)
    {
      prev_elapsed_time = elapsed_time;
      sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));
      BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
      BSP_LCD_DisplayStringAt(263, LINE(8), str, LEFT_MODE);
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
    }

    /* Update audio state machine according to touch acquisition */
    AUDIO_AcquireTouchButtons();
    break;
    
  case AUDIO_STATE_STOP:
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(TOUCH_STOP_XMIN, TOUCH_STOP_YMIN , /* Stop rectangle */
                     TOUCH_STOP_XMAX - TOUCH_STOP_XMIN,
                     TOUCH_STOP_YMAX - TOUCH_STOP_YMIN);
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    check_STOP = 1;
    AUDIO_PLAYER_Start(FilePos);
        if(uwVolume == 0)
        {
          BSP_AUDIO_OUT_SetVolume(uwVolume);
        }
    break;
    
  case AUDIO_STATE_NEXT:
    if(++FilePos >= AUDIO_GetWavObjectNumber())
    {
      FilePos = 0; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_PLAYER_Start(FilePos);
    if(uwVolume == 0)
    {
      BSP_AUDIO_OUT_SetVolume(uwVolume);
    }
    break;    
    
  case AUDIO_STATE_PREVIOUS:
    if(--FilePos < 0)
    {
      FilePos = AUDIO_GetWavObjectNumber() - 1; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_PLAYER_Start(FilePos);
    if(uwVolume == 0)
    {
      BSP_AUDIO_OUT_SetVolume(uwVolume);
    }
    break;   
    
  case AUDIO_STATE_PAUSE:
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
    BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PAUSE]", LEFT_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);    /* Display red pause rectangles */
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_AUDIO_OUT_Pause();
    AudioState = AUDIO_STATE_WAIT;
    break;
    
  case AUDIO_STATE_RESUME:
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
    BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PLAY ]", LEFT_MODE);
                                            /* Display blue cyan pause rectangles */
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_AUDIO_OUT_Resume();
    if(uwVolume == 0)
    {
      BSP_AUDIO_OUT_SetVolume(uwVolume);
    }
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_UP: 
    if( uwVolume <= 90)
    {
      uwVolume += 10;
      AudioState = AUDIO_STATE_PLAY;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    sprintf((char *)str,  "Volume : %lu ", uwVolume);
    BSP_LCD_DisplayStringAtLine(9, str);
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_DOWN:    
    if( uwVolume >= 10)
    {
      uwVolume -= 10;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    sprintf((char *)str,  "Volume : %lu ", uwVolume);
    BSP_LCD_DisplayStringAtLine(9, str);
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_WAIT:
  case AUDIO_STATE_IDLE:
  case AUDIO_STATE_INIT:    
  default:
    /* Update audio state machine according to touch acquisition */
    AUDIO_AcquireTouchButtons();
    break;
  }
  return audio_error;
}

/**
  * @brief  Stops Audio streaming.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Stop(void)
{
  AudioState = AUDIO_STATE_STOP;
  FilePos = 0;
  
  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
  f_close(&WavFile);
  return AUDIO_ERROR_NONE;
}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{ 
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.state = BUFFER_OFFSET_HALF;
  }
}
/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Gets the file info.
  * @param  file_idx: File index
  * @param  info: Pointer to WAV file info
  * @retval Audio error
  */
static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info)
{
  uint32_t bytesread;
  uint32_t duration;
  uint8_t str[FILEMGR_FILE_NAME_SIZE + 20];  
  
  if(f_open(&WavFile, (char *)FileList.file[file_idx].name, FA_OPEN_EXISTING | FA_READ) == FR_OK) 
  {
    /* Fill the buffer to Send */
    if(f_read(&WavFile, info, sizeof(WaveFormat), (void *)&bytesread) == FR_OK)
    {
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
      sprintf((char *)str, "%s\r",(char *)FileList.file[file_idx].name);
      BSP_LCD_ClearStringLine(4);
      BSP_LCD_DisplayStringAtLine(4, str);
//      HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str),1000);
      HAL_UART_Transmit(&huart6, (uint8_t*) str, strlen(str),1000);

      BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
      sprintf((char *)str,  "Sample rate : %d Hz", (int)(info->SampleRate));
      BSP_LCD_ClearStringLine(6);
      BSP_LCD_DisplayStringAtLine(6, str);
      
      sprintf((char *)str,  "Channels number : %d", info->NbrChannels);
      BSP_LCD_ClearStringLine(7);      
      BSP_LCD_DisplayStringAtLine(7, str);
      
      duration = info->FileSize / info->ByteRate; 
      sprintf((char *)str, "File Size : %d KB [%02d:%02d]", (int)(info->FileSize/1024), (int)(duration/60), (int)(duration%60));
      BSP_LCD_ClearStringLine(8);
      BSP_LCD_DisplayStringAtLine(8, str);
      BSP_LCD_DisplayStringAt(263, LINE(8), (uint8_t *)"[00:00]", LEFT_MODE);
 
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
      sprintf((char *)str,  "Volume : %lu", uwVolume);
      BSP_LCD_ClearStringLine(9);      
      BSP_LCD_DisplayStringAtLine(9, str);
      return AUDIO_ERROR_NONE;
    }
    f_close(&WavFile);
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Initializes the Wave player.
  * @param  AudioFreq: Audio sampling frequency
  * @retval None
  */
static uint8_t PlayerInit(uint32_t AudioFreq)
{ 
  /* Initialize the Audio codec and all related peripherals (I2S, I2C, IOExpander, IOs...) */  
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, uwVolume, AudioFreq) != 0)
  {
    return 1;
  }
  else
  {
    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
    return 0;
  } 
}

/**
  * @brief  Display interface touch screen buttons
  * @param  None
  * @retval None
  */
static void AUDIO_PlaybackDisplayButtons(void)
{
  BSP_LCD_SetFont(&LCD_LOG_HEADER_FONT);
  BSP_LCD_ClearStringLine(13);            /* Clear dedicated zone */
  BSP_LCD_ClearStringLine(14);
  BSP_LCD_ClearStringLine(15);

  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
  BSP_LCD_FillPolygon(PreviousPoints, 3);   /* Previous track icon */
  BSP_LCD_FillRect(TOUCH_PREVIOUS_XMIN, TOUCH_PREVIOUS_YMIN , 10, TOUCH_PREVIOUS_YMAX - TOUCH_PREVIOUS_YMIN);
  BSP_LCD_FillPolygon(NextPoints, 3);       /* Next track icon */
  BSP_LCD_FillRect(TOUCH_NEXT_XMAX-9, TOUCH_NEXT_YMIN , 10, TOUCH_NEXT_YMAX - TOUCH_NEXT_YMIN);
  BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);    /* Pause rectangles */
  BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
  BSP_LCD_FillRect(TOUCH_STOP_XMIN, TOUCH_STOP_YMIN , /* Stop rectangle */
                   TOUCH_STOP_XMAX - TOUCH_STOP_XMIN,
                   TOUCH_STOP_YMAX - TOUCH_STOP_YMIN);
  BSP_LCD_DrawRect(TOUCH_VOL_MINUS_XMIN, TOUCH_VOL_MINUS_YMIN , /* VOl- rectangle */
                   TOUCH_VOL_MINUS_XMAX - TOUCH_VOL_MINUS_XMIN,
                   TOUCH_VOL_MINUS_YMAX - TOUCH_VOL_MINUS_YMIN);
  BSP_LCD_DisplayStringAt(24, LINE(14), (uint8_t *)"VOl-", LEFT_MODE);
  BSP_LCD_DrawRect(TOUCH_VOL_PLUS_XMIN, TOUCH_VOL_PLUS_YMIN , /* VOl+ rectangle */
                   TOUCH_VOL_PLUS_XMAX - TOUCH_VOL_PLUS_XMIN,
                   TOUCH_VOL_PLUS_YMAX - TOUCH_VOL_PLUS_YMIN);
  BSP_LCD_DisplayStringAt(24, LINE(14), (uint8_t *)"VOl+", RIGHT_MODE);
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_SetFont(&LCD_LOG_TEXT_FONT);
  BSP_LCD_ClearStringLine(15);
  BSP_LCD_DisplayStringAtLine(15, (uint8_t *)"Use stop button to exit");
  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
}

/**
  * @brief  Test touch screen state and modify audio state machine according to that
  * @param  None
  * @retval None
  */
static void AUDIO_AcquireTouchButtons(void)
{
  if(clk_IN == GPIO_PIN_SET)
  {
	  while(clk_IN){
		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET){
			clk_IN = GPIO_PIN_RESET;
		 }
	  }

	  if (state_INPUT == 2)
	  {
	    if (AudioState == AUDIO_STATE_PLAY)
	     {
	       AudioState = AUDIO_STATE_PAUSE;
	     }
	    else
	     {
	       AudioState = AUDIO_STATE_RESUME;
	     }
	  }
	  else if (state_INPUT == 3)
	  {
	    AudioState = AUDIO_STATE_STOP;
	  }
	  else if (state_INPUT == 4)
	  {
	    AudioState = AUDIO_STATE_PREVIOUS;
	  }
	  else if (state_INPUT == 5)
	  {
	    AudioState = AUDIO_STATE_NEXT;
	  }
	  else if(state_INPUT == 6)
	  {
		AudioState = AUDIO_STATE_VOLUME_DOWN;
	  }
	  else if(state_INPUT == 7)
	  {
		AudioState = AUDIO_STATE_VOLUME_UP;
	  }


  }

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
