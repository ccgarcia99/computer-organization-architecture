#include <stdio.h>
#include <stdbool.h>

unsigned char twosComplement(unsigned char data) {
    return (~data + 1) & 0xF; // Ensure the result is masked to 4 bits
}

void printBin(unsigned char data, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void) {
    unsigned char DX = 0x00; // Remainder, using only 4 bits
    unsigned char Q = 0x07; // Quotient/dividend, using only 4 bits
    unsigned char M = 0x03; // Divisor, using only 4 bits

    int n = 4; // Number of bits
    int j = 0; // Cycles

    printf("\nInitial Conditions:\n");
    printf("Dividend: ");
    printBin(Q, n);
    printf("  Divisor: ");
    printBin(M, n);
    printf("\n\n");

    printf("Cycle\tDX\tQ\tM\tOperation\n");
    printf("-----\t--\t-\t-\t---------\n");

    while(j < 4) {
        // Shift left (DX, Q)
        unsigned char MSB_Q = (Q & 0x8) >> 3; // Extract MSB of Q before shift
        DX = ((DX << 1) | MSB_Q) & 0xF; // Shift DX left, then add MSB of Q to LSB of DX
        Q = (Q << 1) & 0xF; // Shift Q left and ensure it remains 4-bit

        printf("%d\t", j+1);
        printBin(DX, n); printf("\t");
        printBin(Q, n); printf("\t");
        printBin(M, n); printf("\tShift Left\n");

        // Subtract M from DX
        DX = (DX + twosComplement(M)) & 0xF; // Ensure DX remains a 4-bit number after subtraction

        printf("\t");
        printBin(DX, n); printf("\t");
        printBin(Q, n); printf("\t");
        printBin(M, n); printf("\tSubtract M\n");

        // Check for negativity by examining MSB of DX
        unsigned char MSB_DX = (DX & 0x8) >> 3; // Extract MSB of DX

        if(MSB_DX == 1) {
            // If DX is negative, revert the subtraction
            DX = (DX + M) & 0xF; // Ensure DX remains a 4-bit number
            printf("\t");
            printBin(DX, n); printf("\t");
            printBin(Q, n); printf("\t");
            printBin(M, n); printf("\tRevert Subtract\n");
        } else {
            // If DX is positive, set LSB of Q to 1
            Q |= 0x1;
        }

        // Final state after cycle
        printf("\t");
        printBin(DX, n); printf("\t");
        printBin(Q, n); printf("\t");
        printBin(M, n); printf("\tFinal State\n");

        j++;
    }

    printf("\nFinal Result:\n");
    printf("Remainder: ");
    printBin(DX, n);
    printf("\nQuotient: ");
    printBin(Q, n);
    printf("\n");

    return 0;
}
