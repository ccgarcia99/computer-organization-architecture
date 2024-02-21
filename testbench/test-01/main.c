#include <stdio.h>
// Prototype of ALU function
int ALU(unsigned char operand1 , unsigned char operand2 , unsigned char control_signals);

/*
    0x01 -> ADD
    0x02 -> SUB
    0x03 -> MUL
    0x04 -> AND
    0x05 -> OR
    0x06 -> NOT
    0x07 -> XOR
    0x08 -> SHL(logical shift left)
    0x09 -> SHR(logical shift right)
*/

void main()
{

    printf("Result = %d\n", ALU(0x05,0x02,0x02));
}

int ALU(unsigned char operand1 , unsigned char operand2 , unsigned char control_signals)
{
    switch(control_signals)
    {
        case 0x01:
            return operand1 + operand2;
        case 0x02:
            return operand1 - operand2;
        case 0x03:
            return operand1 * operand2;
        case 0x04:
            return operand1 & operand2;
        case 0x05:
            return operand1 | operand2;
        case 0x06:
            return ~operand1;
        case 0x07:
            return operand1 ^ operand2;
        case 0x08:
            return operand1 << operand2;
        case 0x09:
            return operand1 >> operand2;
        default:
            return 0;
    }
}
