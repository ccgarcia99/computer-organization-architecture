#include <stdio.h>
#include <stdint.h>

#define DATA_MEMORY_SIZE 2048 // 2^11
#define IO_BUFFER_SIZE 32     // 2^5
#define PROGRAM_START 0x000
#define DATA_START 0x400
#define IO_START 0x000

void initMemory(uint8_t dataMemory[], uint8_t ioBuffer[]) {
    // Instructions and data as per Table 2
    dataMemory[0x000] = 0x30; dataMemory[0x001] = 0xFF; // WB
    dataMemory[0x002] = 0x0C; dataMemory[0x003] = 0x00; // WM
    dataMemory[0x004] = 0x14; dataMemory[0x005] = 0x00; // RM
    dataMemory[0x006] = 0x19; dataMemory[0x007] = 0x2A; // BR
    // Populate further as per the exercise's instructions
    // Initialize IO Buffer if needed
}

int CU(void) {
    // Declare local variables (PC, IR, MAR, MBR, I/O AR, I/O BR)
    uint16_t PC = 0, IR = 0, MAR = 0, IOAR = 0;
    uint8_t MBR = 0, IOBR = 0;
    uint8_t dataMemory[DATA_MEMORY_SIZE] = {0};
    uint8_t ioBuffer[IO_BUFFER_SIZE] = {0};

    // Initialize memory
    initMemory(dataMemory, ioBuffer);

    // Fetch and execute loop
    while(1) {
        // Fetch instruction
        printf("PC: 0x%03X\n", PC);
        printf("Fetching Instruction...\n");
        IR = dataMemory[PC]; // Get upper byte from memory pointed to by PC
        printf("Fetched upper byte: 0x%02X\n", IR);
        IR = IR << 8;             // Move the byte to the upper half of the 16-bit IR
        PC++;                 // Increment PC to point to the next byte (lower byte of the instruction)
        
        // Fetching lower byte
        IR = IR | dataMemory[PC]; // Merge lower byte with the upper byte in IR
        printf("Fetched lower byte: 0x%02X\n", dataMemory[PC]);
        PC++;                  // Increment PC to point to the next instruction's upper byte
        printf("IR: 0x%04X\n", IR);

        // Decode instruction
        uint8_t inst_code = IR >> 11;
        uint16_t operand = IR & 0x07FF;
        
        printf("Instruction Code: 0x%X\n", inst_code);
        printf("Operand: 0x%03X\n", operand);

        // Execute instruction
        switch(inst_code) {
            case 0x01: // WM
                printf("Instruction: WM\n");
                MAR = operand;
                dataMemory[MAR] = MBR;
                printf("Writing to Memory at MAR: 0x%03X, Data: 0x%02X\n", MAR, MBR);
                break;
            case 0x02: // RM
                printf("Instruction: RM\n");
                MAR = operand;
                MBR = dataMemory[MAR];
                printf("Reading from Memory at MAR: 0x%03X, Data: 0x%02X\n", MAR, MBR);
                break;
            case 0x03: // BR
                printf("Instruction: BR\n");
                PC = operand;
                printf("Branching to Address: 0x%03X\n", PC);
                break;
            case 0x04: // RIO
                printf("Instruction: RIO\n");
                IOAR = operand;
                MBR = ioBuffer[IOAR];
                printf("Reading from IO Buffer at IOAR: 0x%X, Data: 0x%02X\n", IOAR, MBR);
                break;
            case 0x05: // WIO
                printf("Instruction: WIO\n");
                IOAR = operand;
                ioBuffer[IOAR] = IOBR;
                printf("Writing to IO Buffer at IOAR: 0x%X, Data: 0x%02X\n", IOAR, IOBR);
                break;
            case 0x06: // WB
                printf("Instruction: WB\n");
                MBR = operand; // Assuming direct data write to MBR
                printf("Writing Data to MBR: 0x%02X\n", MBR);
                break;
            case 0x07: // WIB
                printf("Instruction: WIB\n");
                IOBR = operand; // Assuming direct data write to IOBR
                printf("Writing Data to IOBR: 0x%02X\n", IOBR);
                break;
            case 0x1F: // EOP
                printf("Instruction: EOP\n");
                return 1; // Successful completion
            default:
                printf("Unknown Instruction Code: 0x%X\n", inst_code);
                return 0;
        }
    }
}

int main(void) {
    if(CU() == 1) {
        printf("Program run successfully!\n");
    } else {
        printf("Error encountered, program terminated!\n");
    }
    return 0;
}


