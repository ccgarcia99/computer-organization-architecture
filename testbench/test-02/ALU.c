#include <stdio.h>

/*
    FUNCTION PROTOTYPES
*/
unsigned char ADD(unsigned char operand1, unsigned char operand2);
unsigned char twosComp(unsigned char operand);
unsigned char setFlags(unsigned int ACC);
<<<<<<< HEAD
int boothsAlgorithm(unsigned char operand1, unsigned char operand2);
=======
unsigned int boothsAlgorithm(unsigned char operand1, unsigned char operand2);
>>>>>>> 2703fc4340296fe10fceb220c74fcad18bcb2919
int ALU(unsigned char operand1, unsigned char operand2, unsigned char control_signals);
void printBin(int data, unsigned char data_width);
void newLine(){printf("\n");}
void menu();

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
    menu();
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

void menu()
{
    printf("CONTROL SIGNALS: \n");
    printf("1) ADD\n2) SUB\n3) MUL\n4) AND\n5) OR\n6) NOT\n7) XOR\n8) SHIFT RIGHT\n9) SHIFT LEFT\n");

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
        boothsAlgorithm(operand1,operand2);
        return 0;
    case 0x04:
        printf("Operation: AND\n");
        return ACC = operand1 & operand2;
    case 0x05:
        printf("Operation: OR\n");
        return ACC = operand1 | operand2;
    case 0x06:
        printf("Operation: NOT\n");
        return ACC =! operand1;
    case 0x07:
        printf("Operation: XOR\n");
        return ACC = operand1 ^ operand2;
    case 0x08:
        printf("Operation: SHIFT RIGHT\n");
        return ACC = operand1 >> operand2;
    case 0x09:
        printf("Operation: SHIFT LEFT\n");
        return ACC = operand1 << operand2;
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

<<<<<<< HEAD
int boothsAlgorithm(unsigned char operand1, unsigned char operand2)
{
    return 0; 
=======
unsigned int boothsAlgorithm(unsigned char operand1, unsigned char operand2)
{
    unsigned char temp_OP1 = 0x00, temp_OP2 = 0x00, temp_Prod = 0x00;
    unsigned char MSB_A = 0x00, LSB_A = 0x00, LSB_Q = 0x00, bitNegOne = 0x00;
    
    temp_OP2 = operand2;
    printf("\nOperation = MUL\n");
    printf("\n**********************\n");
    printf("A\t\tQ\t\tQ_n1\tM\t\tn");
    for (int count = 8; count > 0; count--){
        printf("\n");
        printBin(temp_Prod, 8);
        printf("\t");
        printBin(temp_OP2, 8);
        printf("\t");
        printBin(bitNegOne, 1);
        printf("\t");
        printBin(operand1, 8);
        printf("\t");
        printf("%d\n", count);
        
        LSB_Q = temp_OP2 & 0x01;
        
        if (LSB_Q == 1 && bitNegOne == 0){
            temp_OP1 = twosComp(operand1);
            temp_Prod = temp_Prod + temp_OP1; // A = A - M
        }
        else if (LSB_Q == 0 && bitNegOne == 1){
            temp_OP1 = operand1;
            temp_Prod = temp_Prod + temp_OP1; // A = A + M
        }
            
        MSB_A = (temp_Prod >> 7) & 0x01;
        LSB_A = temp_Prod & 0x01;
        bitNegOne = LSB_Q;
    
        temp_Prod = temp_Prod >> 1; // SHFTR
        temp_Prod = temp_Prod | (MSB_A << 7);
        temp_OP2 = temp_OP2 >> 1;
        temp_OP2 = temp_OP2 | (LSB_A << 7);
    
    }
    return temp_Prod;
>>>>>>> 2703fc4340296fe10fceb220c74fcad18bcb2919
}