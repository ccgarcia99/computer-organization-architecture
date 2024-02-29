/*
	LABORATORY EXERCISE 1 - The ALU 
	TEAM 2 - CPE3202 Group 1
	- Christian Clyde G. Decierdo(TEAM LEAD/HARDWARE LEAD)
	- Denzel Y. Dadang (SOFTWARE LEAD)
	- Melly Andrew D. Borja (RESEARCH LEAD)
	- Clyde G. Guerrero (DOCUMENTATION LEAD)
*/

#include <stdio.h>
#include <stdbool.h>

// Function Prototypes
int ALU(unsigned char op1, unsigned char op2, unsigned char ctrl_sig); //ALU function
unsigned char twosComp(unsigned data);	
unsigned char setFlags(unsigned int ACC);	
void printBin(int data, unsigned char data_width);	//print binary characters of data
void menu();	//display the menu of control signals

// Flags
unsigned char ZF = 0;
unsigned char CF = 0;
unsigned char SF = 0;
unsigned char OF = 0;

void main(void){
    unsigned char op1, op2, ctrl_sig;
    printf("Enter the first operand: ");
    scanf("%hhx", &op1);
    printf("Enter the second operand: ");
    scanf("%hhx", &op2);
    printf("Enter the control signal: ");
    menu();
    scanf("%hhx", &ctrl_sig);
    ALU(op1, op2, ctrl_sig);

}
void menu()
{
    printf("CONTROL SIGNALS: \n");
    printf("1) ADD\n2) SUB\n3) MUL\n4) AND\n5) OR\n6) NOT\n7) XOR\n8) SHIFT RIGHT\n9) SHIFT LEFT\n");

}

int ALU(unsigned char op1, unsigned char op2, unsigned char ctrl_sig){
	static int ACC;
	unsigned char temp_OP1 = 0x00, temp_OP2 = 0x00, temp_Pro = 0x00;
	unsigned char  MSB_A = 0x00, LSB_A = 0x00, LSB_Q = 0x00, bitNegOne = 0x00;
	int count = 0;
	
	ACC = 0x0000; ZF = 0, CF = 0, SF = 0, OF = 0;
	
	printf("*************************\n");
	printf("Fetching Operands...\n");
	printf("OP1 = ");
	printBin(op1, 8);
	printf("\nOP2 = ");
	printBin(op2, 8);
	
	if (ctrl_sig == 0x01 || ctrl_sig == 0x02){
		temp_OP1 = op1;
		
		if (ctrl_sig == 0x02){
			printf("\nOperation = SUB\n");
			temp_OP2 = twosComp(op2);
			printf("2's complement OP2\n");
		}else{
			temp_OP2 = op2;
			printf("\nOperation = ADD\n");
		}
		
		ACC = temp_OP1 + temp_OP2;	
	}else if (ctrl_sig == 0x03){
		temp_OP2 = op2; 
		printf("\nOperation = MUL\n");
		printf("*************************\n");
		printf("A\t\tQ\t\tQ_n1\tM\t\tn");
		
		for (count = 8; count > 0; count--){
			printf("\n");
			printBin(temp_Pro, 8);
			printf("\t");
			printBin(temp_OP2, 8);
			printf("\t");
			printBin(bitNegOne, 1);
			printf("\t");
			printBin(op1, 8);
			printf("\t");
			printf("%d\n", count);
			
			LSB_Q = temp_OP2 & 0x01;
			
			if (LSB_Q == 1 && bitNegOne == 0){
				temp_OP1 = twosComp(op1);
				temp_Pro = temp_Pro + temp_OP1; 	
			}else if (LSB_Q == 0 && bitNegOne == 1){
				temp_OP1 = op1;
				temp_Pro = temp_Pro + temp_OP1; 	
			}
			
			MSB_A = (temp_Pro >> 7) & 0x01;
			LSB_A = temp_Pro & 0x01;
			bitNegOne = LSB_Q;	
				
			temp_Pro = temp_Pro >> 1; 
			temp_Pro = temp_Pro | (MSB_A << 7);
			temp_OP2 = temp_OP2 >> 1;
			temp_OP2 = temp_OP2 | (LSB_A << 7);	
		}
		printf("\n");
		temp_OP1 = temp_Pro << 8 | temp_OP2;
		ACC = (unsigned int)temp_OP1;
	}else if (ctrl_sig == 0x04){
		printf("\nOPERATION = AND\n");
		ACC = op1 & op2;
	}else if (ctrl_sig == 0x05){
		printf("\nOPERATION = OR\n");
		ACC = op1 | op2;
	}else if (ctrl_sig == 0x06){
		printf("\nOPERATION = NOT\n");
		ACC = ~op1;
	}else if (ctrl_sig == 0x07){
		printf("\nOPERATION = XOR\n");
		ACC = op1 ^ op2;
	}else if (ctrl_sig == 0x08){
		printf("\nOPERATION = SHFTR\n");
		ACC = op1 >> op2;
	}else if (ctrl_sig == 0x09){
		printf("\nOPERATION = SHFTL\n");
		ACC = op1 << op2;
	}
	printf("ACC = ");
	printBin(ACC, 16);
	setFlags(temp_OP1);
	printf("\nZF = %d, CF = %d, SF = %d, OF = %d\n", ZF, CF, SF, OF);
}

unsigned char twosComp (unsigned data)
{
    return ~data + 1;
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

void printBin(int data, unsigned char data_width){
	int i, bit;
	
	for (i = (int)data_width - 1; i >= 0; i--){
		bit = data >> i;
		
		if (bit & 1){
			printf("1");
		}else{
			printf("0");
		}
	}
}
