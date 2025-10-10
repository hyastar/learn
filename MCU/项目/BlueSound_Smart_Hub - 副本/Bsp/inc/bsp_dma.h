#ifndef __BSP_DMA_H
#define __BSP_DMA_H

#include "stm32f10x.h"

/* DMA CCR 位定义 (寄存器级) */
#define DMA_CCR_EN        (1U << 0)
#define DMA_CCR_TCIE      (1U << 1)
#define DMA_CCR_HTIE      (1U << 2)
#define DMA_CCR_TEIE      (1U << 3)
#define DMA_CCR_DIR       (1U << 4)
#define DMA_CCR_CIRC      (1U << 5)
#define DMA_CCR_PINC      (1U << 6)
#define DMA_CCR_MINC      (1U << 7)
#define DMA_CCR_PSIZE_0   (1U << 8)
#define DMA_CCR_PSIZE_1   (1U << 9)
#define DMA_CCR_MSIZE_0   (1U << 10)
#define DMA_CCR_MSIZE_1   (1U << 11)
#define DMA_CCR_PL_0      (1U << 12)
#define DMA_CCR_PL_1      (1U << 13)
#define DMA_CCR_MEM2MEM   (1U << 14)

/* DMA ISR / IFCR 标志 (channel1) */
//#define DMA_ISR_GIF1      (1U << 0)
//#define DMA_ISR_TCIF1     (1U << 1)
//#define DMA_ISR_HTIF1     (1U << 2)
//#define DMA_ISR_TEIF1     (1U << 3)

//#define DMA_IFCR_CGIF1    (1U << 0)
//#define DMA_IFCR_CTCIF1   (1U << 1)
//#define DMA_IFCR_CHTIF1   (1U << 2)
//#define DMA_IFCR_CTEIF1   (1U << 3)

void DMA_Init_Common(void);

#endif


