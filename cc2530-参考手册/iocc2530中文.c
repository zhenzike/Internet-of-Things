/**************************************************************************************************
ioCC2530.h -
Header file with definitions for the Texas Instruments CC2530 low-power System-on-Chip:
an 8051-based MCU with 2.4 GHz IEEE 802.15.4 RF transceiver, and up to 256 kB FLASH.
This file supports the IAR Embedded Workbench for 8051.
*/
#ifndef IOCC2530_H
#define IOCC2530_H
/*------------------------------------------------------------------------------------------------
Compiler Abstraction
*/
#ifdef IAR_SYSTEMS_ICC
#pragma language = extended
#define SFR(name, addr) __sfr __no_init volatile unsigned char name @addr;
#define SFRBIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)
__sfr __no_init volatile union
{
    unsigned char name;
    struct
    {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    };
} @addr;
#define SBIT(name, addr) // 未被 IAR C 编译器使用 *//
#define XREG(addr) ((unsigned char volatile __xdata *)0)[addr]
#define PXREG(addr) ((unsigned char volatile __xdata)addr)
#define VECT(num, addr) addr
#elif defined IAR_SYSTEMS_ASM
#define SFR(name, addr) name DEFINE addr
SFRBITMACRO MACRO t, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0 t DEFINE addr bit7 DEFINE addr .7 bit6 DEFINE addr .6 bit5 DEFINE addr .5 bit4 DEFINE addr .4;
;
NB : 请勿修改此宏的缩进
         bit3 DEFINE addr .3 bit2 DEFINE addr .2 bit1 DEFINE addr .1 bit0 DEFINE addr .0 ENDM
#define SFRBIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)
             SFRBITMACRO<name>,
     <addr>,
     <bit7>,
     <bit6>,
     <bit5>,
     <bit4>,
     <bit3>,
     <bit2>,
     <bit1>,
     <bit0>
#define SBIT(name, addr) name DEFINE addr
#define XREG(addr) addr
#define PXREG(addr) addr
#define VECT(num, addr) addr
// IAR 汇编器使用一些预定义的寄存器。以下内容用于防止名称冲突。 //
#define SP SPx
#define ACC ACCx
#define B Bx
#define PSW PSWx
#define CY CYx
#define AC ACx
#define F0 F0x
#define RS1 RS1x
#define RS0 RS0x
#define OV OVx
#define P Px
#else

#endif
/* ------------------------------------------------------------------------------------------------
中断向量
*/
#define RFERR_VECTOR VECT(0, 0x03)  // RF 发送 FIFO 下溢和接收 FIFO 溢出 //
#define ADC_VECTOR VECT(1, 0x0B)    // ADC 转换结束 //
#define URX0_VECTOR VECT(2, 0x13)   // USART0 接收完成 //
#define URX1_VECTOR VECT(3, 0x1B)   // USART1 接收完成 //
#define ENC_VECTOR VECT(4, 0x23)    // AES 加密//解密完成 //
#define ST_VECTOR VECT(5, 0x2B)     // 睡眠定时器比较 //
#define P2INT_VECTOR VECT(6, 0x33)  // 端口 2 输入 //
#define UTX0_VECTOR VECT(7, 0x3B)   // USART0 发送完成 //
#define DMA_VECTOR VECT(8, 0x43)    // DMA 传输完成 //
#define T1_VECTOR VECT(9, 0x4B)     // 定时器 1（16 位）捕获//比较//溢出 //
#define T2_VECTOR VECT(10, 0x53)    // 定时器 2（MAC 定时器） //
#define T3_VECTOR VECT(11, 0x5B)    // 定时器 3（8 位）捕获//比较//溢出 //
#define T4_VECTOR VECT(12, 0x63)    // 定时器 4（8 位）捕获//比较//溢出 //
#define P0INT_VECTOR VECT(13, 0x6B) // 端口 0 输入 //
#define UTX1_VECTOR VECT(14, 0x73)  // USART1 发送完成 //
#define P1INT_VECTOR VECT(15, 0x7B) // 端口 1 输入 //
#define RF_VECTOR VECT(16, 0x83)    // RF 一般中断 //
#define WDT_VECTOR VECT(17, 0x8B)   // 看门狗在定时器模式下溢出 //
/*------------------------------------------------------------------------------------------------
SFRs
*/
/*
地址以 0 或 8 结尾的 SFRs 是位可访问的。
它们使用 SFRBIT() 宏定义，该宏设置了每个位的名称。
*/
// Port 0 //

SFRBIT(P0, 0x80, P0_7, P0_6, P0_5, P0_4, P0_3, P0_2, P0_1, P0_0)
SFR(SP, 0x81)    // 堆栈指针 //
SFR(DPL0, 0x82)  // 数据指针 0 低字节 //
SFR(DPH0, 0x83)  // 数据指针 0 高字节 //
SFR(DPL1, 0x84)  // 数据指针 1 低字节 //
SFR(DPH1, 0x85)  // 数据指针 1 高字节 //
SFR(U0CSR, 0x86) // USART 0 控制和状态 //
SFR(PCON, 0x87)  // 电源模式控制 //
// Interrupt Flags 0  中断标志 //
SFRBIT(TCON, 0x88, URX1IF, _TCON6, ADCIF, _TCON4, URX0IF, IT1, RFERRIF, IT0)
SFR(P0IFG, 0x89)  // 端口 0 中断状态标志 //
SFR(P1IFG, 0x8A)  // 端口 1 中断状态标志 //
SFR(P2IFG, 0x8B)  // 端口 2 中断状态标志 //
SFR(PICTL, 0x8C)  // 端口中断控制 //
SFR(P1IEN, 0x8D)  // 端口 1 中断屏蔽 //
SFR(_SFR8E, 0x8E) // 未使用 //
SFR(P0INP, 0x8F)  // 端口 0 输入模式 //
// Port 1 *//
SFRBIT(P1, 0x90, P1_7, P1_6, P1_5, P1_4, P1_3, P1_2, P1_1, P1_0)
SFR(RFIRQF1, 0x91) //* RF 中断标志高位 //
SFR(DPS, 0x92)     // 数据指针选择 //
SFR(MPAGE, 0x93)   // 内存页选择 //
SFR(T2CTRL, 0x94)  // 定时器 2 控制寄存器 //
SFR(ST0, 0x95)     // 睡眠定时器 0 //
SFR(ST1, 0x96)     // 睡眠定时器 1 //
SFR(ST2, 0x97)     // 睡眠定时器 2 //
// Interrupt Flags 2 //
SFRBIT(S0CON, 0x98, _S0CON7, _S0CON6, _S0CON5, _S0CON4, _S0CON3, _S0CON2, ENCIF_1, ENCIF_0)
SFR(_SFR99, 0x99)    // 保留 //
SFR(IEN2, 0x9A)      // 中断使能 2 //
SFR(S1CON, 0x9B)     // 中断标志 3 //
SFR(T2CSPCFG, 0x9C)  // 定时器 2 CSP 接口配置（旧名称） //
SFR(T2EVTCFG, 0x9C)  // 定时器 2 事件输出配置 //
SFR(SLEEPSTA, 0x9D)  // 睡眠状态 //
SFR(CLKCONSTA, 0x9E) // 时钟控制状态 //
SFR(FMAP, 0x9F)      // 闪存页映射 //
// Port 2 //
SFRBIT(P2, 0xA0, _P2_7, _P2_6, _P2_5, P2_4, P2_3, P2_2, P2_1, P2_0)
SFR(T2IRQF, 0xA1)  // 定时器 2 中断标志 //
SFR(T2M0, 0xA2)    // 定时器 2 复用寄存器 0 //
SFR(T2M1, 0xA3)    // 定时器 2 复用寄存器 1 //
SFR(T2MOVF0, 0xA4) // 定时器 2 复用溢出寄存器 0 //
SFR(T2MOVF1, 0xA5) // 定时器 2 复用溢出寄存器 1 //
SFR(T2MOVF2, 0xA6) // 定时器 2 复用溢出寄存器 2 //
SFR(T2IRQM, 0xA7)  // 定时器 2 中断屏蔽 //
// Interrupt Enable 0  中断启用 //
SFRBIT(IEN0, 0xA8, EA, _IEN06, STIE, ENCIE, URX1IE, URX0IE, ADCIE, RFERRIE)
SFR(IP0, 0xA9)     // 中断优先级 0 //
SFR(_SFRAA, 0xAA)  // 未使用 //
SFR(P0IEN, 0xAB)   // 端口 0 中断屏蔽 //
SFR(P2IEN, 0xAC)   // 端口 2 中断屏蔽 //
SFR(STLOAD, 0xAD)  // 睡眠定时器加载状态 //
SFR(PMUX, 0xAE)    // 电源下降信号复用 //
SFR(T1STAT, 0xAF)  // 定时器 1 状态 //
SFR(_SFRB0, 0xB0)  // 未使用 //
SFR(ENCDI, 0xB1)   // 加密//解密输入数据 //
SFR(ENCDO, 0xB2)   // 加密//解密输出数据 //
SFR(ENCCS, 0xB3)   // 加密//解密控制和状态 //
SFR(ADCCON1, 0xB4) // ADC 控制 1 //
SFR(ADCCON2, 0xB5) // ADC 控制 2 //
SFR(ADCCON3, 0xB6) // ADC 控制 3 //
SFR(_SFRB7, 0xB7)  // 保留 //
// Interrupt Enable 1 //
SFRBIT(IEN1, 0xB8, _IEN17, _IEN16, P0IE, T4IE, T3IE, T2IE, T1IE, DMAIE)
SFR(IP1, 0xB9)      // 中断优先级 1 //
SFR(ADCL, 0xBA)     // ADC 数据低字节 //
SFR(ADCH, 0xBB)     // ADC 数据高字节 //
SFR(RNDL, 0xBC)     // 随机数生成器低字节 //
SFR(RNDH, 0xBD)     // 随机数生成器高字节 //
SFR(SLEEPCMD, 0xBE) // 睡眠模式控制命令 //
SFR(RFERRF, 0xBF)   // RF 错误中断标志 //
// Interrupt Flags 4    中断标志//
SFRBIT(IRCON, 0xC0, STIF, _IRCON6, P0IF, T4IF, T3IF, T2IF, T1IF, DMAIF)
SFR(U0DBUF, 0xC1)    // USART 0 接收//发送数据缓冲区 //
SFR(U0BAUD, 0xC2)    // USART 0 波特率控制 //
SFR(T2MSEL, 0xC3)    // 定时器 2 复用选择 //
SFR(U0UCR, 0xC4)     // USART 0 UART 控制 //
SFR(U0GCR, 0xC5)     // USART 0 通用控制 //
SFR(CLKCONCMD, 0xC6) // 时钟控制命令 //
SFR(MEMCTR, 0xC7)    // 内存系统控制 //
SFR(_SFRC8, 0xC8)    // 未使用 //
SFR(WDCTL, 0xC9)     // 看门狗定时器控制 //
SFR(T3CNT, 0xCA)     // 定时器 3 计数器 //
SFR(T3CTL, 0xCB)     // 定时器 3 控制 //
SFR(T3CCTL0, 0xCC)   // 定时器 3 通道 0 捕获//比较控制 //
SFR(T3CC0, 0xCD)     // 定时器 3 通道 0 捕获//比较值 //
SFR(T3CCTL1, 0xCE)   // 定时器 3 通道 1 捕获//比较控制 //
SFR(T3CC1, 0xCF)     // 定时器 3 通道 1 捕获//比较值 //
// Program Status Word *//
SFRBIT(PSW, 0xD0, CY, AC, F0, RS1, RS0, OV, F1, P)
SFR(DMAIRQ, 0xD1)   //* DMA 中断标志 //
SFR(DMA1CFGL, 0xD2) // DMA 通道 1 - 4 配置地址低字节 //
SFR(DMA1CFGH, 0xD3) // DMA 通道 1 - 4 配置地址高字节 //
SFR(DMA0CFGL, 0xD4) // DMA 通道 0 配置地址低字节 //
SFR(DMA0CFGH, 0xD5) // DMA 通道 0 配置地址高字节 //
SFR(DMAARM, 0xD6)   // DMA 通道启动 //
SFR(DMAREQ, 0xD7)   // DMA 通道开始请求和状态 //
// Timers 1//3//4 Interrupt Mask//Flag //
SFRBIT(TIMIF, 0xD8, _TIMIF7, T1OVFIM, T4CH1IF, T4CH0IF, T4OVFIF, T3CH1IF, T3CH0IF, T3OVFIF)
SFR(RFD, 0xD9)     // RF 数据 //
SFR(T1CC0L, 0xDA)  // 定时器 1 通道 0 捕获//比较值低字节 //
SFR(T1CC0H, 0xDB)  // 定时器 1 通道 0 捕获//比较值高字节 //
SFR(T1CC1L, 0xDC)  // 定时器 1 通道 1 捕获//比较值低字节 //
SFR(T1CC1H, 0xDD)  // 定时器 1 通道 1 捕获//比较值高字节 //
SFR(T1CC2L, 0xDE)  // 定时器 1 通道 2 捕获//比较值低字节 //
SFR(T1CC2H, 0xDF)  // 定时器 1 通道 2 捕获//比较值高字节 //
SFR(ACC, 0xE0)     // 累加器 //
SFR(RFST, 0xE1)    // RF 命令触发 //
SFR(T1CNTL, 0xE2)  // 定时器 1 计数器低字节 //
SFR(T1CNTH, 0xE3)  // 定时器 1 计数器高字节 //
SFR(T1CTL, 0xE4)   // 定时器 1 控制和状态 //
SFR(T1CCTL0, 0xE5) // 定时器 1 通道 0 捕获//比较控制 //
SFR(T1CCTL1, 0xE6) // 定时器 1 通道 1 捕获//比较控制 //
SFR(T1CCTL2, 0xE7) // 定时器 1 通道 2 捕获//比较控制 //
// Interrupt Flags 5 //
SFRBIT(IRCON2, 0xE8, _IRCON27, _IRCON26, _IRCON25, WDTIF, P1IF, UTX1IF, UTX0IF, P2IF)
SFR(RFIRQF0, 0xE9) // RF 中断标志低位 //
SFR(T4CNT, 0xEA)   // 定时器 4 计数器 //
SFR(T4CTL, 0xEB)   // 定时器 4 控制 //
SFR(T4CCTL0, 0xEC) // 定时器 4 通道 0 捕获//比较控制 //
SFR(T4CC0, 0xED)   // 定时器 4 通道 0 捕获//比较值 //
SFR(T4CCTL1, 0xEE) // 定时器 4 通道 1 捕获//比较控制 //
SFR(T4CC1, 0xEF)   // 定时器 4 通道 1 捕获//比较值 //
SFR(B, 0xF0)       // B 寄存器 //
SFR(PERCFG, 0xF1)  // 外设 I//O 控制 //
SFR(ADCCFG, 0xF2)  // ADC 输入配置（旧名称） //
SFR(APCFG, 0xF2)   // 模拟外设 I//O 配置 //
SFR(P0SEL, 0xF3)   // 端口 0 功能选择 //
SFR(P1SEL, 0xF4)   // 端口 1 功能选择 //
SFR(P2SEL, 0xF5)   // 端口 2 功能选择 //
SFR(P1INP, 0xF6)   // 端口 1 输入模式 //
SFR(P2INP, 0xF7)   // 端口 2 输入模式 //
// USART 1 Control and Status //
SFRBIT(U1CSR, 0xF8, U1MODE, U1RE, U1SLAVE, U1FE, U1ERR, U1RX_BYTE, U1TX_BYTE, U1ACTIVE)
SFR(U1DBUF, 0xF9) // USART 1 接收//发送数据缓冲区 //
SFR(U1BAUD, 0xFA) // USART 1 波特率控制 //
SFR(U1UCR, 0xFB)  // USART 1 UART 控制 //
SFR(U1GCR, 0xFC)  // USART 1 通用控制 //
SFR(P0DIR, 0xFD)  // 端口 0 方向 //
SFR(P1DIR, 0xFE)  // 端口 1 方向 //
SFR(P2DIR, 0xFF)  // 端口 2 方向 //
/* ------------------------------------------------------------------------------------------------
Xdata Radio Registers
*/
// 射频核心RAM //
#define RFCORE_RAM PXREG(0x6000)
#define RFCORE_RAM_SZ 384
// FIFO直接存取 //
#define RXFIFO PXREG(0x6000)
#define RXFIFO_SZ 128
#define TXFIFO PXREG(0x6080)
#define TXFIFO_SZ 128
// 帧过滤和源匹配存储器 //
#define FRMF_SRCM_RAM PXREG(0x6100)
#define FRMF_SRCM_RAM_SZ 128
// 源地址表 //
#define SRC_ADDR_TABLE PXREG(0x6100)
#define SRC_ADDR_TABLE_SZ 96
// 源地址匹配控制 //
#define SRCRESMASK0 XREG(0x6160)
#define SRCRESMASK1 XREG(0x6161)
#define SRCRESMASK2 XREG(0x6162)
#define SRCRESINDEX XREG(0x6163)
#define SRCEXTPENDEN0 XREG(0x6164)
#define SRCEXTPENDEN1 XREG(0x6165)
#define SRCEXTPENDEN2 XREG(0x6166)
#define SRCSHORTPENDEN0 XREG(0x6167)
#define SRCSHORTPENDEN1 XREG(0x6168)
#define SRCSHORTPENDEN2 XREG(0x6169)
// 本地地址信息 *//
#define EXT_ADDR0 XREG(0x616A)
#define EXT_ADDR
#define EXT_ADDR1 XREG(0x616B)
#define EXT_ADDR2 XREG(0x616C)
#define EXT_ADDR3 XREG(0x616D)
#define EXT_ADDR4 XREG(0x616E)
#define EXT_ADDR5 XREG(0x616F)
#define EXT_ADDR6 XREG(0x6170)
#define EXT_ADDR7 XREG(0x6171)
#define PAN_ID0 XREG(0x6172)
#define PAN_ID1 XREG(0x6173)
#define SHORT_ADDR0 XREG(0x6174)
#define SHORT_ADDR1 XREG(0x6175)
//* RX控制的地址信息 //
#define FRMFILT0 XREG(0x6180)
#define FRMFILT1 XREG(0x6181)
#define SRCMATCH XREG(0x6182)
#define SRCSHORTEN0 XREG(0x6183)
#define SRCSHORTEN1 XREG(0x6184)
#define SRCSHORTEN2 XREG(0x6185)
#define SRCEXTEN0 XREG(0x6186)
#define SRCEXTEN1 XREG(0x6187)
#define SRCEXTEN2 XREG(0x6188)
// 无线电控制 //
#define FRMCTRL0 XREG(0x6189)
#define FRMCTRL1 XREG(0x618A)
#define RXENABLE XREG(0x618B)
#define RXMASKSET XREG(0x618C)
#define RXMASKCLR XREG(0x618D)
#define FREQTUNE XREG(0x618E)
#define FREQCTRL XREG(0x618F)
#define TXPOWER XREG(0x6190)
#define TXCTRL XREG(0x6191)
#define FSMSTAT0 XREG(0x6192)
#define FSMSTAT1 XREG(0x6193)
#define FIFOPCTRL XREG(0x6194)
#define FSMCTRL XREG(0x6195)
#define CCACTRL0 XREG(0x6196)
#define CCACTRL1 XREG(0x6197)
#define RSSI XREG(0x6198)
#define RSSISTAT XREG(0x6199)
#define RXFIRST XREG(0x619A)
#define RXFIFOCNT XREG(0x619B)
#define TXFIFOCNT XREG(0x619C)
#define RXFIRST_PTR XREG(0x619D)
#define RXLAST_PTR XREG(0x619E)
#define RXP1_PTR XREG(0x619F)
#define _XREG61A0 XREG(0x61A0)
#define TXFIRST_PTR XREG(0x61A1)
#define TXLAST_PTR XREG(0x61A2)
// 中断控制器寄存器 //
#define RFIRQM0 XREG(0x61A3)
#define RFIRQM1 XREG(0x61A4)
#define RFERRM XREG(0x61A5)
// 随机数生成器 //
#define RFRND XREG(0x61A7)
// 模拟和数字无线电测试和调谐 //
#define MDMCTRL0 XREG(0x61A8)
#define MDMCTRL1 XREG(0x61A9)
#define FREQEST XREG(0x61AA)
#define RXCTRL XREG(0x61AB)
#define FSCTRL XREG(0x61AC)
#define FSCAL0 XREG(0x61AD)
#define FSCAL1 XREG(0x61AE)
#define FSCAL2 XREG(0x61AF)
#define FSCAL3 XREG(0x61B0)
#define AGCCTRL0 XREG(0x61B1)
#define AGCCTRL1 XREG(0x61B2)
#define AGCCTRL2 XREG(0x61B3)
#define AGCCTRL3 XREG(0x61B4)
#define ADCTEST0 XREG(0x61B5)
#define ADCTEST1 XREG(0x61B6)
#define ADCTEST2 XREG(0x61B7)
#define MDMTEST0 XREG(0x61B8)
#define MDMTEST1 XREG(0x61B9)
#define DACTEST0 XREG(0x61BA)
#define DACTEST1 XREG(0x61BB)
#define DACTEST2 XREG(0x61BC)
#define ATEST XREG(0x61BD)
#define PTEST0 XREG(0x61BE)
#define PTEST1 XREG(0x61BF)
#define TXFILTCFG XREG(0x61FA)
// CSP控制和观察登记簿 *//
#define CSPPROG0 XREG(0x61C0)
#define CSPPROG1 XREG(0x61C1)
#define CSPPROG2 XREG(0x61C2)
#define CSPPROG3 XREG(0x61C3)
#define CSPPROG4 XREG(0x61C4)
#define CSPPROG5 XREG(0x61C5)
#define CSPPROG6 XREG(0x61C6)
#define CSPPROG7 XREG(0x61C7)
#define CSPPROG8 XREG(0x61C8)
#define CSPPROG9 XREG(0x61C9)
#define CSPPROG10 XREG(0x61CA)
#define CSPPROG11 XREG(0x61CB)
#define CSPPROG12 XREG(0x61CC)
#define CSPPROG13 XREG(0x61CD)
#define CSPPROG14 XREG(0x61CE)
#define CSPPROG15 XREG(0x61CF)
#define CSPPROG16 XREG(0x61D0)
#define CSPPROG17 XREG(0x61D1)
#define CSPPROG18 XREG(0x61D2)
#define CSPPROG19 XREG(0x61D3)
#define CSPPROG20 XREG(0x61D4)
#define CSPPROG21 XREG(0x61D5)
#define CSPPROG22 XREG(0x61D6)
#define CSPPROG23 XREG(0x61D7)
#define _XREG61D8 XREG(0x61D8)
#define _XREG61D9 XREG(0x61D9)
#define _XREG61DA XREG(0x61DA)
#define _XREG61DB XREG(0x61DB)
#define _XREG61DC XREG(0x61DC)
#define _XREG61DD XREG(0x61DD)
#define _XREG61DE XREG(0x61DE)
#define _XREG61DF XREG(0x61DF)
#define CSPCTRL XREG(0x61E0)
#define CSPSTAT XREG(0x61E1)
#define CSPX XREG(0x61E2)
#define CSPY XREG(0x61E3)
#define CSPZ XREG(0x61E4)
#define CSPT XREG(0x61E5)
#define _XREG61E6 XREG(0x61E6)
#define _XREG61E7 XREG(0x61E7)
#define _XREG61E8 XREG(0x61E8)
#define _XREG61E9 XREG(0x61E9)
#define _XREG61EA XREG(0x61EA)
//* 可观测性控制 //
#define RFC_OBS_CTRL0 XREG(0x61EB)
#define RFC_OBS_CTRL1 XREG(0x61EC)
#define RFC_OBS_CTRL2 XREG(0x61ED)
#define OBSSEL0 XREG(0x6243)
#define OBSSEL1 XREG(0x6244)
#define OBSSEL2 XREG(0x6245)
#define OBSSEL3 XREG(0x6246)
#define OBSSEL4 XREG(0x6247)
#define OBSSEL5 XREG(0x6248)
#define TR0 XREG(0x624B)
// 芯片识别 //
#define CHVER XREG(0x6249)
#define CHIPID XREG(0x624A)
// 调试接口DMA写入闪存 //
#define DBGDATA XREG(0x6260)
// 闪存控制器 //
#define FCTL XREG(0x6270)
#define FADDRL XREG(0x6271)
#define FADDRH XREG(0x6272)
#define FWDATA XREG(0x6273)
#define _XREG6274 XREG(0x6274)
#define _XREG6275 XREG(0x6275)
// 芯片信息 //
#define CHIPINFO0 XREG(0x6276)
#define CHIPINFO1 XREG(0x6277)
// IR生成控制 //
#define IRCTL XREG(0x6281)
// 时钟丢失检测器 //
#define CLD XREG(0x6290)
// 定时器1通道（仅映射为XREG） //
#define T1CCTL3 XREG(0x62A3)
#define T1CCTL4 XREG(0x62A4)
#define T1CC3L XREG(0x62AC)
#define T1CC3H XREG(0x62AD)
#define T1CC4L XREG(0x62AE)
#define T1CC4H XREG(0x62AF)
// 定义包括SFR中表示的通道（SFR的附加XREG映射） //
#define XX_T1CCTL0 XREG(0x62A0)
#define XX_T1CCTL1 XREG(0x62A1)
#define XX_T1CCTL2 XREG(0x62A2)
#define XX_T1CCTL3 XREG(0x62A3)
#define XX_T1CCTL4 XREG(0x62A4)
#define XX_T1CC0L XREG(0x62A6)
#define XX_T1CC0H XREG(0x62A7)
#define XX_T1CC1L XREG(0x62A8)
#define XX_T1CC1H XREG(0x62A9)
#define XX_T1CC2L XREG(0x62AA)
#define XX_T1CC2H XREG(0x62AB)
#define XX_T1CC3L XREG(0x62AC)
#define XX_T1CC3H XREG(0x62AD)
#define XX_T1CC4L XREG(0x62AE)
#define XX_T1CC4H XREG(0x62AF)
// 数组访问指针 //
#define P_T1CCTL PXREG(0x62A0)
#define P_T1CC PXREG(0x62A6)
// 睡眠定时器捕获控制 //
#define STCC XREG(0x62B0)
#define STCS XREG(0x62B1)
#define STCV0 XREG(0x62B2)
#define STCV1 XREG(0x62B3)
#define STCV2 XREG(0x62B4)
// Op.Amp。控制 //
#define OPAMPMC XREG(0x61A6)
#define OPAMPC XREG(0x62C0)
#define OPAMPS XREG(0x62C1)
// 模拟比较器控制 //
#define CMPCTL XREG(0x62D0)
/* ------------------------------------------------------------------------------------------------
Xdata Mapped SFRs
*/
/*
大多数 SFR 也可以通过 XDATA 地址空间访问。 这种访问类型的寄存器定义如下。 寄存器名称与 SFR 名称相同，但带有前缀 X_ 以表示 XDATA 寄存器。
一些 SFR 无法通过 XDATA 空间访问。 为了清晰起见，包括了这些寄存器的条目。 它们的前缀为 _NA 以表示“不可用”。
有关寄存器的描述，请参考此文件中其他地方的实际 SFR 声明。
*/
#define X_P0 XREG(0x7080) // 端口 0。注意！从 XREG 进行只读访问。 //
#define _NA_SP XREG(0x7081)
#define _NA_DPL0 XREG(0x7082)
#define _NA_DPH0 XREG(0x7083)
#define _NA_DPL1 XREG(0x7084)
#define _NA_DPH1 XREG(0x7085)
#define X_U0CSR XREG(0x7086) // USART 0 控制和状态 //
#define _NA_PCON XREG(0x7087)
#define _NA_TCON XREG(0x7088)
#define X_P0IFG XREG(0x7089) // 端口 0 中断状态标志 //
#define X_P1IFG XREG(0x708A) // 端口 1 中断状态标志 //
#define X_P2IFG XREG(0x708B) // 端口 2 中断状态标志 //
#define X_PICTL XREG(0x708C) // 端口中断控制 //
#define X_P1IEN XREG(0x708D) // 端口 1 中断屏蔽 //
#define _NA_SFR8E XREG(0x708E)
#define X_P0INP XREG(0x708F)   // 端口 0 输入模式 //
#define X_P1 XREG(0x7090)      // 端口 1。注意！从 XREG 进行只读访问。 //
#define X_RFIRQF1 XREG(0x7091) // RF 中断标志高位 //
#define _NA_DPS XREG(0x7092)
#define X_MPAGE XREG(0x7093)  // 内存页选择 //
#define X_T2CTRL XREG(0x7094) // 定时器 2 控制寄存器 //
#define X_ST0 XREG(0x7095)    // 睡眠定时器 0 //
#define X_ST1 XREG(0x7096)    // 睡眠定时器 1 //
#define X_ST2 XREG(0x7097)    // 睡眠定时器 2 //
#define _NA_S0CON XREG(0x7098)
#define _NA_SFR99 XREG(0x7099)
#define _NA_IEN2 XREG(0x709A)
#define _NA_S1CON XREG(0x709B)
#define X_T2CSPCFG XREG(0x709C)  // 定时器 2 CSP 接口配置（旧名称） //
#define X_T2EVTCFG XREG(0x709C)  // 定时器 2 事件输出配置 //
#define X_SLEEPSTA XREG(0x709D)  // 睡眠状态 //
#define X_CLKCONSTA XREG(0x709E) // 时钟控制状态 //
#define X_FMAP XREG(0x709F)      // 闪存页映射 //
#define X_P2 XREG(0x70A0)        // 端口 2。注意！从 XREG 进行只读访问。 //
#define X_T2IRQF XREG(0x70A1)    // 定时器 2 中断标志 //
#define X_T2M0 XREG(0x70A2)      // 定时器 2 复用寄存器 0 //
#define X_T2M1 XREG(0x70A3)      // 定时器 2 复用寄存器 1 //
#define X_T2MOVF0 XREG(0x70A4)   // 定时器 2 复用溢出寄存器 0 //
#define X_T2MOVF1 XREG(0x70A5)   // 定时器 2 复用溢出寄存器 1 //
#define X_T2MOVF2 XREG(0x70A6)   // 定时器 2 复用溢出寄存器 2 //
#define X_T2IRQM XREG(0x70A7)    // 定时器 2 中断屏蔽 //
#define _NA_IEN0 XREG(0x70A8)
#define _NA_IP0 XREG(0x70A9)
#define _NA_SFRAA XREG(0x70AA)
#define X_P0IEN XREG(0x70AB)  // //
#define X_P2IEN XREG(0x70AC)  // //
#define X_STLOAD XREG(0x70AD) // 睡眠定时器加载状态 //
#define X_PMUX XREG(0x70AE)   // //
#define X_T1STAT XREG(0x70AF) // //
#define _NA_SFRB0 XREG(0x70B0)
#define X_ENCDI XREG(0x70B1)   // 加密输入数据 //
#define X_ENCDO XREG(0x70B2)   // 加密输出数据 //
#define X_ENCCS XREG(0x70B3)   // 加密控制和状态 //
#define X_ADCCON1 XREG(0x70B4) // ADC 控制 1 //
#define X_ADCCON2 XREG(0x70B5) // ADC 控制 2 //
#define X_ADCCON3 XREG(0x70B6) // ADC 控制 3 //
#define _NA_SFRB7 XREG(0x70B7)
#define _NA_IEN1 XREG(0x70B8)
#define _NA_IP1 XREG(0x70B9)
#define X_ADCL XREG(0x70BA)     // ADC 数据低字节 //
#define X_ADCH XREG(0x70BB)     // ADC 数据高字节 //
#define X_RNDL XREG(0x70BC)     // 随机寄存器低字节 //
#define X_RNDH XREG(0x70BD)     // 随机寄存器高字节 //
#define X_SLEEPCMD XREG(0x70BE) // 睡眠模式命令 //
#define X_RFERRF XREG(0x70BF)   // RF 错误中断标志 //
#define _NA_IRCON XREG(0x70C0)
#define X_U0DBUF XREG(0x70C1)    // USART 0 接收//发送数据缓冲区 //
#define X_U0BAUD XREG(0x70C2)    // USART 0 波特率控制 //
#define X_T2MSEL XREG(0x70C3)    // 定时器 2 复用选择 //
#define X_U0UCR XREG(0x70C4)     // USART 0 UART 控制 //
#define X_U0GCR XREG(0x70C5)     // USART 0 通用控制 //
#define X_CLKCONCMD XREG(0x70C6) // 时钟控制命令 //
#define X_MEMCTR XREG(0x70C7)    // 内存仲裁控制 //
#define _NA_SFRC8 XREG(0x70C8)
#define X_WDCTL XREG(0x70C9)   // 看门狗定时器控制 //
#define X_T3CNT XREG(0x70CA)   // 定时器 3 计数器 //
#define X_T3CTL XREG(0x70CB)   // 定时器 3 控制 //
#define X_T3CCTL0 XREG(0x70CC) // 定时器 3 通道 0 捕获//比较控制 //
#define X_T3CC0 XREG(0x70CD)   // 定时器 3 通道 0 捕获//比较值 //
#define X_T3CCTL1 XREG(0x70CE) // 定时器 3 通道 1 捕获//比较控制 //
#define X_T3CC1 XREG(0x70CF)   // 定时器 3 通道 1 捕获//比较值 //
#define _NA_PSW XREG(0x70D0)
#define X_DMAIRQ XREG(0x70D1)   // DMA 中断标志 //
#define X_DMA1CFGL XREG(0x70D2) // DMA 通道 1 - 4 配置地址低字节 //
#define X_DMA1CFGH XREG(0x70D3) // DMA 通道 1 - 4 配置地址高字节 //
#define X_DMA0CFGL XREG(0x70D4) // DMA 通道 0 配置地址低字节 //
#define X_DMA0CFGH XREG(0x70D5) // DMA 通道 0 配置地址高字节 //
#define X_DMAARM XREG(0x70D6)   // DMA 通道启动 //
#define X_DMAREQ XREG(0x70D7)   // DMA 通道开始请求和状态 //
#define X_TIMIF XREG(0x70D8)    // 定时器 1//3//4 中断屏蔽//标志 //
#define X_RFD XREG(0x70D9)      // RF 数据 //
#define X_T1CC0L XREG(0x70DA)   // 定时器 1 通道 0 捕获//比较值低字节 //
#define X_T1CC0H XREG(0x70DB)   // 定时器 1 通道 0 捕获//比较值高字节 //
#define X_T1CC1L XREG(0x70DC)   // 定时器 1 通道 1 捕获//比较值低字节 //
#define X_T1CC1H XREG(0x70DD)   // 定时器 1 通道 1 捕获//比较值高字节 //
#define X_T1CC2L XREG(0x70DE)   // 定时器 1 通道 2 捕获//比较值低字节 //
#define X_T1CC2H XREG(0x70DF)   // 定时器 1 通道 2 捕获//比较值高字节 //
#define _NA_ACC XREG(0x70E0)
#define X_RFST XREG(0x70E1)    // RF 触发 *//
#define X_T1CNTL XREG(0x70E2)  //* 定时器 1 计数器低字节 //
#define X_T1CNTH XREG(0x70E3)  // 定时器 1 计数器高字节 //
#define X_T1CTL XREG(0x70E4)   // 定时器 1 控制和状态 //
#define X_T1CCTL0 XREG(0x70E5) // 定时器 1 通道 0 捕获//比较控制 //
#define X_T1CCTL1 XREG(0x70E6) // 定时器 1 通道 1 捕获//比较控制 //
#define X_T1CCTL2 XREG(0x70E7) // 定时器 1 通道 2 捕获//比较控制 //
#define _NA_IRCON2 XREG(0x70E8)
#define X_RFIRQF0 XREG(0x70E9) // RF 中断标志低位 //
#define X_T4CNT XREG(0x70EA)   // 定时器 4 计数器 //
#define X_T4CTL XREG(0x70EB)   // 定时器 4 控制 //
#define X_T4CCTL0 XREG(0x70EC) // 定时器 4 通道 0 捕获//比较控制 //
#define X_T4CC0 XREG(0x70ED)   // 定时器 4 通道 0 捕获//比较值 //
#define X_T4CCTL1 XREG(0x70EE) // 定时器 4 通道 1 捕获//比较控制 //
#define X_T4CC1 XREG(0x70EF)   // 定时器 4 通道 1 捕获//比较值 //
#define _NA_B XREG(0x70F0)
#define X_PERCFG XREG(0x70F1) // 外设控制 //
#define X_ADCCFG XREG(0x70F2) // ADC 输入配置（旧名称） //
#define X_APCFG XREG(0x70F2)  // 模拟外设 I//O 配置 //
#define X_P0SEL XREG(0x70F3)  // 端口 0 功能选择 //
#define X_P1SEL XREG(0x70F4)  // 端口 1 功能选择 //
#define X_P2SEL XREG(0x70F5)  // 端口 2 功能选择 //
#define X_P1INP XREG(0x70F6)  // 端口 1 输入模式 //
#define X_P2INP XREG(0x70F7)  // 端口 2 输入模式 //
#define X_U1CSR XREG(0x70F8)  // USART 1 控制和状态 //
#define X_U1DBUF XREG(0x70F9) // USART 1 接收//发送数据缓冲区 //
#define X_U1BAUD XREG(0x70FA) // USART 1 波特率控制 //
#define X_U1UCR XREG(0x70FB)  // USART 1 UART 控制 //
#define X_U1GCR XREG(0x70FC)  // USART 1 通用控制 //
#define X_P0DIR XREG(0x70FD)  // 端口 0 方向 //
#define X_P1DIR XREG(0x70FE)  // 端口 1 方向 //
#define X_P2DIR XREG(0x70FF)  // 端口 2 方向 //
/*------------------------------------------------------------------------------------------------
Flash
*/
#define P_INFOPAGE PXREG(0x7800) // 指向闪存信息页的起始指针 //
#define P_XBANK PXREG(0x8000)    // 指向可选闪存银行（XBANK）的起始指针 //
// ------------------------------------------------------------------------------------------------
//
#ifdef IAR_SYSTEMS_ICC
#pragma language = default
#endif

#endif