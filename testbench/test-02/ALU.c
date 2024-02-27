#include <stdio.h>

/*
    FUNCTION PROTOTYPES
*/
unsigned char ADD(unsigned char operand1, unsigned char operand2);
unsigned char boothsAlgorithm(unsigned char operand1, unsigned char operand2);
unsigned char twosComp(unsigned char operand);
unsigned char setFlags(unsigned int ACC);
void printBin(int data, unsigned char data_width);
int ALU(unsigned char operand1, unsigned char operand2, unsigned char control_signals);
void newLine(){printf("\n");}

/*
    GLOBAL VARIABLES
*/
unsigned char ZF = 0;
unsigned char CF = 0;
unsigned char SF = 0;
unsigned char OF = 0;

int main()
{
    unsigned char operand1, operand2, control_signals;
    unsigned int ACC = 0x0000;

    printf("Fetching operands...");
    newLine();
    printf("Enter OP1: ");
    scanf("%hhx", &operand1);
    printf("Enter OP2: ");
    scanf("%hhx", &operand2);
    printf("Enter Control Signal: ");
    scanf("%hhx", &control_signals);
    printf("Operand 1: ");
    printBin(operand1, 8);
    newLine(); 
    printf("Operand 2: ");
    printBin(operand2, 8);
    newLine();
    ACC = ALU(operand1,operand2,control_signals);
    printf("Result: ");
    setFlags(ACC);
    newLine();
    printBin(ACC,8);
    newLine();
    printf("Flags:\n\tZF = %d\tCF = %d\tSF = %d\tOF = %d\n",ZF,CF,SF,OF);

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

unsigned char twosComp(unsigned char operand) {return ~operand+1;}

int ALU(unsigned char operand1, unsigned char operand2, unsigned char control_signals)
{
    int ACC = 0x0000;
    switch (control_signals)
    {
    case 0x01:
        printf("Operation: ADD\n");
        return ACC = operand1 + operand2;
    case 0x02:
        printf("Operation: SUB\n");
        printf("Twos complement of OP2: ");
        operand2 = twosComp(operand2);
        printBin(operand2,8);
        newLine();
        return ACC = operand1 + operand2;
    case 0x03:
        printf("Operation: MUL\n");
        return boothsAlgorithm(operand1,operand2);
    default:
        return 0x00;
    }
}
unsigned char setFlags (unsigned int ACC)
{
	if (ACC == 0x0000){
		ZF = 1;
	}else{
		ZF = 0;
	}if (ACC >= 0x1FF){
		CF = 1;
	}else{
		CF = 0;
	}if ((ACC & 0x80) == 0x80){
		SF = 1;
	}else{
		SF = 0;
	}if (ACC >= 0xFF){
		OF = 1;
	}else{
		OF = 0;
	}
}


unsigned char boothsAlgorithm(unsigned char operand1, unsigned char operand2)
{
    unsigned char ACC = 0x0000;
    unsigned char M = operand1;
    unsigned char Q = operand2;
    unsigned char Q_1 = 0;
    unsigned char count = 8;

    while (count > 0)
    {
        if ((Q & 0x01) == 0x01 && (Q_1 & 0x01) == 0x00)
        {
            ACC += M;
        }
        else if ((Q & 0x01) == 0x00 && (Q_1 & 0x01) == 0x01)
        {
            ACC += twosComp(M);
        }

        if ((ACC & 0x01) == 0x01)
        {
            Q_1 = Q;
            Q = (Q >> 1) | 0x80;
        }
        else
        {
            Q_1 = Q;
            Q = Q >> 1;
        }

        ACC = ACC >> 1;
        count--;
    }

    return ACC;
}
