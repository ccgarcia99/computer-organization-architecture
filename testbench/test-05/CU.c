/*
CPE 3202 G1 - Computer Architecture and Organization
LE2: Control Unit Simulation
Date: 2024-23-03

TEAM 2:
    - Christian Clyde G. Decierdo
    - Clyde G. Guerrero
    - Denzel Y. Dadang
    - Melly Andrew D. Borja
*/
#include  <stdio.h>
#include <stdint.h>

#define DATA_MEMORY_SIZE 2048
#define IO_BUFFER_SIZE 32

uint8_t dataMemory[DATA_MEMORY_SIZE] = {0};
uint8_t ioBuffer[IO_BUFFER_SIZE] = {0};

int CU(void);
void initMemory();

int main(void)
{
    if(CU() == 1)
        printf("Program executed successfully.\n");
    else
        printf("Program execution failed.\n");
    return 0;
}

int CU(void)
{
    int returnCode = 0;
    // Declare local variables and initialize memory


    uint16_t PC = 0, IR = 0, MAR = 0, IOAR = 0;
    uint8_t MBR = 0, IOBR = 0;

    uint16_t inst_ctrl, operand;

    // Initialize memory
    initMemory();
    
    // Fetch and execute instructions
    do{
        // fetch cycle
        printf("PC:\t0x%03X\n", PC);
        printf("Fetching instruction...\n");

        IR = dataMemory[PC];
        IR <<= 8;
        PC++;

        IR |= dataMemory[PC];
        PC++;
        printf("IR:\t0x%04X\n", IR);

        // decode cycle
        inst_ctrl = IR >> 11;
        operand = IR & 0x7FF;
        printf("Opcode:\t0x%02X\n", inst_ctrl);

        switch (inst_ctrl)
        {
        case 0x0001: // WM: write memory from MBR
            printf("Instruction:\t WM\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Data:\t0x%02X\n", dataMemory[operand]);
            printf("Writing data to memory...\n");
            MAR = operand;
            dataMemory[MAR] = MBR;
            break;
        case 0x0002: // RM: read memory to MBR
            printf("Instruction:\t RM\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Reading data from memory...\n");
            MAR = operand;
            MBR = dataMemory[MAR];
            printf("MBR:\t0x%02X\n", MBR);
            break;
        case 0x0003: // BR: branch to address specified by operand
            printf("Instruction:\t WM\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Branching to address...\n");
            PC = operand;
            printf("PC:\t0x%03X\n", PC);
            break;
        case 0x0004: // RIO: read from IO to IOBR
            printf("Instruction:\t RIO\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Reading from IO...\n");
            IOAR = operand;
            IOBR = ioBuffer[IOAR];
            printf("IOBR:\t0x%02X\n", IOBR);
            break;
        case 0x0005: // WIO: write data to IO buffer from IOBR
            printf("Instruction:\t WIO\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Writing data to IO...\n");
            IOAR = operand;
            ioBuffer[IOAR] = IOBR;
            break;
        case 0x0006: // WB: write data to MBR
            printf("Instruction:\t WB\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Writing data to MBR...\n");
            MBR = operand;
            printf("MBR:\t0x%02X\n", MBR);
            break;
        case 0x0007: // WIB: write data to IOBR
            printf("Instruction:\t WIB\n");
            printf("Operand:\t0x%03X\n", operand);
            printf("Writing data to IOBR...\n");
            IOBR = operand;
            printf("IOBR:\t0x%02X\n", IOBR);
            break;
        case 0x001F: // EOP: end of program
            printf("Instruction:\t EOP\n");
            printf("End of program.\n");
            returnCode = 1;
            break;
        
        default:
            return returnCode;
        }
        getchar();

    }while(returnCode == 0);

    return returnCode; // return 1 if operation is successful
}

void initMemory(){
    dataMemory[0x000] = 0x30;
    dataMemory[0x001] = 0xFF;
    dataMemory[0x002] = 0x0C;
    dataMemory[0x003] = 0x00;
    dataMemory[0x004] = 0x14;
    dataMemory[0x005] = 0x00;
    dataMemory[0x006] = 0x19;
    dataMemory[0x007] = 0x2A;
    // ...

    dataMemory[0x12A] = 0x38;
    dataMemory[0x12B] = 0x05;
    dataMemory[0x12C] = 0x28;
    dataMemory[0x12D] = 0x0A;
    dataMemory[0x12E] = 0xF8;
    dataMemory[0x12F] = 0x00;
}
