#ifndef _BSP_MQ5_H_
#define _BSP_MQ5_H_


#include <stdint.h>


typedef struct {
uint16_t raw_adc_avg;
float voltage;
float ppm;
} MQ5_Data_t;


void MQ5_Init(void);
MQ5_Data_t MQ5_GetData(void);


#endif // _MQ5_H_

