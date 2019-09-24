.section .text
.global main

/* set stack pointer */
lui sp, %hi(32768)
addi sp, sp, %lo(32768) 

/* call main */
jal ra, main

/* break */
ebreak
