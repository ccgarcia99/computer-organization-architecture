#include <stdio.h>

/*
    FUNCTION PROTOTYPES
*/
unsigned char addOp(unsigned char operand1, unsigned char operand2);
unsigned char boothsAlgorithm(unsigned char operand1, unsigned char operand2);
unsigned char twosComp(unsigned char operand);
unsigned char setFlags(unsigned int ACC);
void printBin(int data, unsigned char data_width);
int ALU(unsigned char operand1, unsigned char operand2, unsigned char control_signals);
void newLine(){printf("\n");}

int main()
{
    unsigned char operand1, operand2, control_signals;
    unsigned int ACC;

    printf("Fetching operands...");
    newLine();
    printf("Enter OP1: ");
    scanf("%hhx", &operand1);
    printf("Enter OP2: ");
    scanf("%hhx", &operand2);
    printf("Enter Control Signals: ");
    scanf("%hhx", &control_signals);
    printf("Operand 1: ");
    printBin(operand1, 8);
    newLine(); 
    printf("Operand 2: ");
    printBin(operand2, 8);
    newLine();
    printf("Control Signals: ");
    printBin(control_signals, 8);

    return 0;
}

void printBin(int data, unsigned char data_width)
{
    int i;
    for(i = data_width - 1; i >= 0; i--)
    {
        printf("%d", (data >> i) & 1);
    }
}
