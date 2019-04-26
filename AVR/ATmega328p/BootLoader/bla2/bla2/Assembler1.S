
/*
 * Assembler1.S
 *
 * Created: 3/17/2019 9:48:07 PM
 *  Author: mh-sh
 */ 
 
/*
 * Assembler1.s
 *
 * Created: 3/16/2019 2:47:22 PM
 *  Author: mh-sh
 */ 
;.include \"D:\Atmel\Studio\7.0\packs\atmel\ATmega_DFP\1.2.209\avrasm\inc\m328pdef.inc \"
;#define x 1 

#include "asmdefs.h"



 ;.org 0x3800
 .org 0x3f00

 .global JUMP0000
 JUMP0000:
 jmp 0000

 .global RAM_READ_BYTE
 RAM_READ_BYTE:
push xl
push xh

mov xl,r24
mov xh,r25
ld r24,x

pop xh
pop xl
ret

 .global RAM_WRITE_BYTE
RAM_WRITE_BYTE:
push xl
push xh

mov xl,r24
mov xh,r25
st x,r22

pop xh
pop xl
ret

//x to counter 
//y to ram
//z to flash
 .global BL_CPY_RAM_FLASH
BL_CPY_RAM_FLASH:
mov xl,r20
mov xh,r21
mov yl,r22
mov yh,r23
mov zl,r24
mov zh,r25
mov r19,r25
mov r18,r24

call Erase_buff_page

cpyloopr:

mov r24,yl
mov r25,yh
adiw yl,1
call RAM_READ_BYTE
mov r23,r24

mov r24,yl
mov r25,yh
adiw yl,1
call RAM_READ_BYTE
mov r22,r24

mov r24,Zl 
mov r25,ZH 
call Fill_buff_page

adiw zl,2
sbiw xl, 2 //adiw
brne cpyloopr //brpl brmi brne

mov r25,r19
mov r24,r18
call Write_buff_page
ret

//x to counter 
//y to eeprom
//z to flash
 .global BL_CPY_EE_FLASH
BL_CPY_EE_FLASH:
mov xl,r20
mov xh,r21
mov yl,r22
mov yh,r23
mov zl,r24
mov zh,r25
mov r19,r25
mov r18,r24

call Erase_buff_page

cpyloop:

mov r24,yl
mov r25,yh
adiw yl,1
call EE_READ_BYTE
mov r23,r24

mov r24,yl
mov r25,yh
adiw yl,1
call EE_READ_BYTE
mov r22,r24

mov r24,Zl 
mov r25,ZH 
call Fill_buff_page

adiw zl,2
sbiw xl, 2 //adiw
brne cpyloop //brpl brmi brne

mov r25,r19
mov r24,r18
call Write_buff_page
ret


 .global EE_READ_BYTE
EE_READ_BYTE:
SBIC EECR,EEPE       ;CHECK IF EEPROM BUSY
RJMP EE_READ_BYTE        ;ITS BUSY SO WE WAIT
OUT EEARL,r24 ;input       ;SET-UP THE ADDRESS
OUT EEARH,r25 ;input       ;SET-UP THE ADDRESS
SBI EECR,EERE        ;SET-UP TO READ
IN  r24,EEDR ;output          ;READ THE DATA REGISTER
RET                 ;RETURN

 .global ret_one
ret_one:
LDI R24,1
ret


.global Erase_buff_page
Erase_buff_page:
push zl
push zh

mov  Zl,r24 
mov ZH ,r25

ldi R20,  (1<<PGERS)|(1<<SPMEN)
OUT SPMCSR ,R20 
Spm
call Wait_spm

ldi r20, (1<<RWWSRE) | (1<<SELFPRGEN)
OUT SPMCSR ,R20 
Spm
call Wait_spm

pop zh
pop zl
ret

.global Fill_buff_page
Fill_buff_page:
push zl
push zh

mov R0,r23 ;movw
mov R1,r22

mov  Zl,r24 
mov ZH ,r25

ldi R20,  (1<<SPMEN)
OUT SPMCSR ,R20 
Spm
call Wait_spm

pop zh
pop zl
ret

.global Write_buff_page
Write_buff_page:
push zl
push zh

mov  Zl,r24 
mov ZH ,r25

ldi R20,  (1<<PGWRT)|(1<<SPMEN)
OUT SPMCSR ,R20 
spm
call Wait_spm

pop zh
pop zl
ret



 .global Write_page
Write_page:
; page erase
push zl
push zh

;LDI R16,1
mov R0,r23 ;movw
mov R1,r22

mov  Zl,r24 
mov ZH ,r25

ldi R20,  (1<<PGERS)|(1<<SPMEN)
OUT SPMCSR ,R20 
Spm
call Wait_spm

ldi r20, (1<<RWWSRE) | (1<<SELFPRGEN)//TODO wtf leh awl 2 bytes
OUT SPMCSR ,R20 
Spm
call Wait_spm

;ldi zl,2
;ldi zh,0
ldi R20,  (1<<SPMEN)
OUT SPMCSR ,R20 
Spm
call Wait_spm



ldi R20,  (1<<PGWRT)|(1<<SPMEN)
OUT SPMCSR ,R20 
spm
call Wait_spm

pop zh
pop zl
ret


; check for previous SPM complete
Wait_spm:
in r20, SPMCSR
sbrc r20, SELFPRGEN
rjmp Wait_spm
;ret

; check that no EEPROM write access is present
Wait_ee:
sbic EECR, EEPE
rjmp Wait_ee
; SPM timed sequenc
ret