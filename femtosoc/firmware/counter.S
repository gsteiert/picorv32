.equ GPIO_BASE,  0x04000000
.equ DLY_CNT,    0x00080000

.section .text

start:
    li    a3, 0x01
    li    a2, GPIO_BASE
forever:
    sw    a3, (a2)
    li    a1, DLY_CNT 
1:  addi  a1, a1, -1
    bnez  a1, 1b
    addi  a3, a3, 1
    j     forever
