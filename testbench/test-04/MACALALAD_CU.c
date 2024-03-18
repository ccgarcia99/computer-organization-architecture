#include <stdio.h>
unsigned char memory[0x800];
unsigned char ioBuffer[0x20];	


int CU(){
	unsigned int PC = 0x0000, IR, MAR, IOAR;
	unsigned char MBR = 0x0000, IOBR = 0x0000;
	unsigned int inst_ctrl = 0x0000, operand = 0x0000;
	int return_code = 0;
	
	do{
		printf("***************************************\n");
		printf("PC			: 0x%03X\n", PC);
		printf("Fetching instruction...\n");
		IR = memory[PC];
		IR <<= 8;
		PC++;

		IR = IR | memory[PC];
		PC++;
		printf("IR			: 0x%04X\n", IR);
		
		inst_ctrl = IR >> 11;
		operand = IR & 0x07FF;
		printf("Opcode			: 0x%02X\n", inst_ctrl);
		

		switch(inst_ctrl){
			case 0x0001:	// WM: Write to Memory from MBR
				printf("Instruction		: WM\n");
				printf("Operand			: 0x%03X\n", operand);
				printf("Writing data from MBR to memory address specified in operand...\n");
				MAR = operand;
				memory[MAR] = MBR;
				break;
			case 0x0002:	// RM: Read from Memory to MBR
				printf("Instruction		: RM\n");
				printf("Operand			: 0x%03X\n", operand);
				printf("Reading data from memory address specified in operand to write in MBR...\n");
				MAR = operand;
				MBR = memory[MAR];
				printf("MBR			: 0x%02X\n", MBR);
				break;
			case 0x0003:	// BR: Branch to address specified in operand
				printf("Instruction		: WM\n");
				printf("Operand			: 0x%03X\n", operand);
				printf("Branching (Jumping) to memory address specified in operand...\n");
				PC = operand;
				printf("Branched to 0x%03X for next cycle.\n", PC);
				break;
			case 0x0004:	// RIO: Read from IO buffer to IOBR
				printf("Instruction		: RIO\n");
				printf("Operand			: 0x%03X\n", operand);
				printf("Reading data from IO buffer address specified in operand to write in IOBR...\n");
				IOAR = operand;
				IOBR = ioBuffer[IOAR];
				printf("IOBR			: 0x%02X\n", IOBR);
				break;
			case 0x0005:	// WIO: Write to IO buffer from IOBR
				printf("Instruction		: WIO\n");
				printf("Operand			: 0x%03X\n", operand);
				printf("Writing data from IOBR to IO buffer address specified in operand...\n");
				IOAR = operand;
				ioBuffer[IOAR] = IOBR;
				break;
			case 0x0006:	// WB: Write data to Memory Buffer Register
				operand &= 0x00FF;
				printf("Instruction		: WB\n");
				printf("Operand			: 0x%02X\n", operand);
				printf("Directly loading operand data into MBR...\n");
				MBR = operand;
				printf("MBR			: 0x%02X\n", MBR);
				break;
			case 0x0007:	// WIB: Write data to IO Buffer Register
				operand &= 0x00FF;	
				printf("Instruction		: WIB\n");
				printf("Operand			: 0x%02X\n", operand);
				printf("Directly loading operand data into IOBR...\n");
				IOBR = operand;
				printf("IOBR			: 0x%02X\n", IOBR);
				break;
			case 0x001F:	// EOP: End of program
				printf("Instruction		: EOP\n");	
				printf("End of program.\n");
				return_code = 1;
				break;
			default:
				return return_code;
		}
		getch();
	}while(return_code != 1);
	return return_code;	// successful op returns 1
}

void initMemory(){
	// Initialize instruction memory
	memory[0x000] = 0x14;	// RM 0x403
	memory[0x001] = 0x03;	// binary: 00010 100 0000 0011
	memory[0x002] = 0x0C;	// WM 0x400
	memory[0x003] = 0x00;	// binary: 00001 100 0000 0000
	memory[0x004] = 0x0C;	// WM 0x401
	memory[0x005] = 0x01;	// binary: 00001 100 0000 0001
	memory[0x006] = 0x14;	// RM 0x400
	memory[0x007] = 0x00;	// binary: 00010 100 0000 0000
	memory[0x008] = 0x30;	// WB 0x1E
	memory[0x009] = 0x1E;	// binary: 00110 000 0001 1110
	memory[0x00A] = 0x0C;	// WM 0x402
	memory[0x00B] = 0x02;	// binary: 00001 100 0000 0010
	memory[0x00C] = 0x14;	// RM 0x402
	memory[0x00D] = 0x02;	// binary: 00010 100 0000 0010
	memory[0x00E] = 0x1A;	// BR 0x20E
	memory[0x00F] = 0x0E;	// binary: 00011 010 0000 1110
	memory[0x010] = 0xF8;	// EOP
	memory[0x011] = 0x00;	// binary: 11111 000 0000 0000
	memory[0x20E] = 0x38;	// WIB 0x48
	memory[0x20F] = 0x48;	// binary: 00111 000 0100 1000
	memory[0x210] = 0x28;	// WIO 0x000
	memory[0x211] = 0x00;	// binary: 00101 000 0000 0000
	memory[0x212] = 0x38;	// WIB 0x11
	memory[0x213] = 0x11;	// binary: 00111 000 0001 0001
	memory[0x212] = 0x20;	// RIO 0x000
	memory[0x213] = 0x00;	// binary: 00100 000 0000 0000
	memory[0x214] = 0x18;	// BR 0x010
	memory[0x215] = 0x10;	// binary: 00011 000 0001 0000
	
	// Initialize data memory
	memory[0x400] = 0x00;
	memory[0x401] = 0x20;
	memory[0x402] = 0x00;
	memory[0x403] = 0x07;
	memory[0x404] = 0x00;
	memory[0x405] = 0x00;
	memory[0x406] = 0x00;
	memory[0x407] = 0x00;

}

int main(){
	initMemory();
	
	if(CU()) printf("Program run successfully!");
	else printf("Error during run.");
	return 0;
}

