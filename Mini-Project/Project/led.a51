ORG 0000H          ; Program start address
LJMP MAIN          ; Jump to main program

;---------------------------------------------------
; Interrupt Vector Table
;---------------------------------------------------
ORG 0003H          ; External Interrupt 0 vector address
LJMP EX0_ISR       ; Jump to Interrupt Service Routine

;---------------------------------------------------
; Main Program
;---------------------------------------------------
ORG 0030H
MAIN:
	//MOV P1, #66H      ; Port 1 as input (Switches, active low)
	MOV P2, #00H       ; Port 2 as output (LEDs initially OFF)

	MOV IE, #81H       ; Enable EA (bit7) and EX0 (bit0)
	MOV TCON, #01H     ; IT0=1 (edge triggered), IE0=0

MAIN_LOOP:
	MOV A, P1          ; Read switches
	MOV P2, A          ; Display switch pattern on LEDs
	SJMP MAIN_LOOP     ; Repeat forever

;---------------------------------------------------
; External Interrupt 0 ISR
;---------------------------------------------------
EX0_ISR:
	MOV A, P2      ; Load Port 2 into Accumulator
	CPL A          ; Complement accumulator
	MOV P2, A      ; Write back to LEDs
	RETI           ; Return from interrupt

END
