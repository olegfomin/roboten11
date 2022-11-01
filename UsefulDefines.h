
#define BIT1 1
#define BIT2 2
#define BIT3 4
#define BIT4 8
#define BIT5 16
#define BIT6 32
#define BIT7 64
#define BIT8 128
#define BIT9 256
#define BIT10 512
#define BIT11 1024
#define BIT12 2048
#define BIT13 4096
#define BIT14 8192
#define BIT15 16384
#define BIT16 32768
#define BIT17 65536
#define BIT18 131072
#define BIT19 262144
#define BIT20 524288
#define BIT21 1048576
#define BIT22 2097152
#define BIT23 4194304
#define BIT24 8388608
#define BIT25 16777216
#define BIT26 33554432
#define BIT27 67108864
#define BIT28 134217728
#define BIT29 268435456
#define BIT30 536870912
#define BIT31 1073741824
#define BIT32 2147483648

#define RB1 4294967295-1
#define RB2 4294967295-2
#define RB3 4294967295-4
#define RB4 4294967295-8
#define RB5 4294967295-16
#define RB6 4294967295-32
#define RB7 4294967295-64
#define RB8 4294967295-128
#define RB9 4294967295-256
#define RB10 4294967295-512
#define RB11 4294967295-1024
#define RB12 4294967295-2028
#define RB13 4294967295-4096
#define RB14 4294967295-8192
#define RB15 4294967295-16384
#define RB16 4294967295-32768
#define RB17 4294967295-65536
#define RB18 4294967295-131072
#define RB19 4294967295-262144
#define RB20 4294967295-524288
#define RB21 4294967295-1048576
#define RB22 4294967295-2097152
#define RB23 4294967295-4194304
#define RB24 4294967295-8388608
#define RB25 4294967295-16777216
#define RB26 4294967295-33554432
#define RB27 4294967295-67108864
#define RB28 4294967295-134217728
#define RB29 4294967295-268435456
#define RB30 4294967295-536870912
#define RB31 4294967295-1073741824
#define RB32 4294967295-2147483648

#define bitSetters {BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7,BIT8,BIT9,BIT10,BIT11,BIT12,BIT13,BIT14,BIT15,BIT16,BIT17,BIT18,BIT19,BIT20,BIT21,BIT22,BIT23,BIT24,BIT25,BIT26,BIT27,BIT28,BIT29,BIT30,BIT31,BIT32};
#define bitResetters {RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, RB10, RB11, RB12, RB13, RB14, RB15, RB16, RB17, RB18, RB19, RB20, RB21, RB22, RB23, RB24, RB25, RB26, RB27, RB28, RB29, RB30, RB31, RB32};


/*************/
/*   ------  */
/*   |    |  */
/*   |    |  */
/*   |    |  */
/*   |    |  */ 
/*   @-----  */
#define LEFT_REAR_LED 52

/*   ------  */
/*   |    |  */
/*   |    |  */
/*   |    |  */
/*   |    |  */ 
/*   -----@  */
#define RIGHT_REAR_LED 49

/*   -----@  */
/*   |    |  */
/*   |    |  */
/*   |    |  */
/*   |    |  */ 
/*   ------  */
#define RIGHT_FRONT_LED 51

/*   @-----  */
/*   |    |  */
/*   |    |  */
/*   |    |  */
/*   |    |  */ 
/*   ------  */
#define LEFT_FRONT_LED 50
/* int* log2(int mask) {
    int numbers[32] = {0,0,0,0,0,0,
                       0,0,0,0,0,0,
                       0,0,0,0,0,0,
                       0,0,0,0,0,0,
                       0,0,0,0,0,0,
                       0, 0};
    int i = 0;
    while (mask > 0) {
        if (mask % 2) numbers[i]=1;
        else numbers[i]=0;
        mask = mask/2;
        i++;
    }

    return numbers;

} */
