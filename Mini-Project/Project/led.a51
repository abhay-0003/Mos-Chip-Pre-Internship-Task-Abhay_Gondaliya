ORG 0000H
SJMP MAIN          ; Jump to main program

;--------------------------
; INT0 Interrupt Vector
;--------------------------
ORG 0003H
AJMP INT0_ISR

;==========================
;       VARIABLES
;==========================
FLAG BIT 20H       ; Flag stored in BIT-ADDRESSABLE RAM

;==========================
;       MAIN PROGRAM
;==========================
MAIN:
    MOV P2, #00H        ; LEDs off

    MOV IE, #81H        ; EA=1, EX0=1
    MOV TCON, #01H      ; IT0=1 ? edge triggered

    CLR FLAG            ; Initially flag = 0 (normal mode)

MAIN_LOOP:
    MOV A, P1
	MOV P2, A
	JB FLAG, TOGGLE   ; If FLAG = 1 ? toggle mode
	SJMP MAIN_LOOP
TOGGLE:
	CPL A
	MOV P2, A
	JNB FLAG, MAIN_LOOP
	MOV A, P1
	SJMP TOGGLE
    
;==========================
;     INTERRUPT SERVICE
;==========================
INT0_ISR:

    CPL FLAG             ; Toggle mode flag (0?1, 1?0)
                         ; No debounce here, can add if needed

    RETI



END
