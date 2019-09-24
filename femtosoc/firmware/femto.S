.section .text
.global main

/* set stack pointer */
lui sp, %hi(16384)
addi sp, sp, %lo(16384) 

/* call main */
jal ra, main

/* break */
ebreak
