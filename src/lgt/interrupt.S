#include <avr/io.h>

.macro lgt_vector num
    .global __vector_\num
    .weak   __vector_\num
    jmp     __vector_\num
.endm

.section .vectors
.global __vectors_lgt
__vectors_lgt:
    lgt_vector 26  /* - */
    lgt_vector 27  /* 0x6C: PCINT3 */
    lgt_vector 28  /* 0x70: PCINT4 */
    lgt_vector 29  /* 0x74: TC3 */
