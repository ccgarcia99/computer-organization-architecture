#include <stdio.h>
#include <stdbool.h>

unsigned char twosComplement(unsigned char data);
unsigned char binDivision(unsigned char dividend, unsigned char divisor);
unsigned char signedADD(unsigned char op1, unsigned char op2);

void printBin(unsigned char data, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (data >> i) & 0x01);
    }
}

void main(void)
{
    unsigned char DX = 0x00; // remainder
    unsigned char Q = 0x06; // quotient/dividend
    unsigned char M = 0x0c; // divisor
    unsigned char Q_0 = 0x0; // LSB of Q

    unsigned char MSB_Q = 0x0; // MSB of quotient
    unsigned char MSB_DX = 0x0; // MSB of DX

    int n = 4; // number of bits
    int j = 0; // cycles

    printf("\nDividend: ");
    printBin(Q, n);
    printf("\nDivisor: ");
    printBin(M, n);

    while(j!=4){
        printf("\nCycle %d\n", j+1);
        
        MSB_Q = Q >> (n-1); // get the MSB of the quotient
        printf("MSB_Q: ");
        printBin(MSB_Q,1);
        printf("\n");
        printf("A\t\tQ\t\tM\n");
        // SHIFT LEFT A, Q
        DX = DX << 1; // shift the remainder left by 1
        printBin(DX,4); printf("\t\t"); printBin(Q,4); printf("\t\t"); printBin(M,4); printf("\n"); // copy for line-by-line tracing
        DX = DX | MSB_Q; // place the MSB of the quotient to the LSB of the remainder
        Q = Q << 1; // shift Q by 1 to the left
        printBin(DX,4); printf("\t\t"); printBin(Q,4); printf("\t\t"); printBin(M,4); printf("\n"); // copy for line-by-line tracing

        //A <- A-M
        DX = DX + twosComplement(M);
        printBin(DX,4); printf("\t\t"); printBin(Q,4); printf("\t\t"); printBin(M,4); printf("\n"); // copy for line-by-line tracing

        MSB_DX = DX >> 3;
        printf("MSB of A: ");
        printBin(MSB_DX,1);
        printf("\n");
        // A < 0?
        if(MSB_DX == 0x1) // check if MSB is + or -
        {
            // if 1(negative), set LSB of Q to 0, and add M to DX(A) without 2's complement
            //Q_0 = 0x0;
            //Q = Q|Q_0;
            DX = DX + M; 
            printBin(DX,4); printf("\t\t"); printBin(Q,4); printf("\t\t"); printBin(M,4); printf("\n"); // copy for line-by-line tracing
        }else{
            // if 0(positive), set LSB of Q to 1 ONLY
            Q_0 = 0x1;
            Q = Q|Q_0;
            printBin(DX,4); printf("\t\t"); printBin(Q,4); printf("\t\t"); printBin(M,4); printf("\n"); // copy for line-by-line tracing
        }
        j++;
    }

}

unsigned char twosComplement(unsigned char data){return ~data + 1;}
unsigned char signedADD(unsigned char op1, unsigned char op2){
    unsigned char sum;
    if(op2 >> 3){
        twosComplement(op2);
        return sum = op1 + op2;
    }else{
        return sum = op1 + op2;
    }
}