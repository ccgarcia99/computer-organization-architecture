#include <stdio.h>

// Function to display an unsigned char in binary
void printBin(unsigned char value) {
    for (int i = 7; i >= 0; i--) {
        printf("%c", (value & (1 << i)) ? '1' : '0');
    }
    printf("\n"); // Added newline for better readability
}

// Function to calculate the two's complement of an unsigned char
unsigned char twosComp(unsigned char value) {
    return (~value) + 1;
}

// The Booth's Algorithm implementation for 8-bit unsigned chars
void boothsAlgorithm(unsigned char M, unsigned char Q) {
    unsigned char A = 0, Q_N1 = 0;
    int n;

    printf("Cycle\tOperation\t\tA\t\tQ\t\tQ-1\n");
    printf("Initial\t\t\t\t");
    printBin(A);
    printf("\t");
    printBin(Q);
    printf("\t%d\n", Q_N1);

    for (n = 0; n < 8; n++) {
        printf("Step %d\t", n + 1);
        unsigned char LSB_Q = Q & 1;
        if (LSB_Q == 1 && Q_N1 == 0) { // 10: Subtract M, use two's complement for subtraction
            A += twosComp(M);
            printf("Subtract M\t");
        } else if (LSB_Q == 0 && Q_N1 == 1) { // 01: Add M
            A += M;
            printf("Add M\t\t");
        } else {
            printf("No op\t\t");
        }

        // Right shift AQ and Q_N1 as a single unit
        unsigned char old_A = A; // Save old A for determining shift-in bit
        Q_N1 = Q & 1;
        Q = (Q >> 1) | (A << 7);
        A = (A >> 1) | (old_A & 0x80); // Keep the sign bit of A

        printBin(A);
        printf("\t");
        printBin(Q);
        printf("\t%d\n", Q_N1);
    }

    // Display the final result in A and Q
    printf("Result in A and Q: ");
    printBin(A);
    printBin(Q); // Removed unnecessary space for consistency
}

int main() {
    unsigned char M = 0x07; // Multiplicand
    unsigned char Q = 0x02; // Multiplier

    printf("Booth's Algorithm: Multiplying\n");
    boothsAlgorithm(M, Q);

    return 0;
}
