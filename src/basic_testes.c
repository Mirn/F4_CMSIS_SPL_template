/*
 * basic_testes.c
 *
 *  Created on: 12 сент. 2016 г.
 *      Author: Easy
 */

#include "stm32kiss.h"

void rand_test()
{
	printf("%08X\n", rand());
	printf("%08X\n", rand());
	srand(0x1223991);
	printf("srand\n");
	printf("%08X\n", rand());
	printf("%08X\n", rand());
	printf("\n");
}

void malloc_test()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
	void *ptr_a = NULL;
	printf("malloc(10)); \t%08X\n", (uint32_t*)malloc(10));
	printf("malloc(100));\t%08X\n", (uint32_t*)malloc(100));
	printf("malloc(1000))\t%08X\n", (uint32_t*)(ptr_a = malloc(1000)));
	printf("malloc(10000)\t%08X\n", (uint32_t*)malloc(10000));
	printf("malloc(1000))\t%08X\n", (uint32_t*)malloc(1000));
	printf("malloc(100));\t%08X\n", (uint32_t*)malloc(100));
	printf("malloc(10)); \t%08X\n", (uint32_t*)malloc(10));
	printf("\n");

	for (uint32_t cnt = 0; cnt < 10000; cnt++)
	{
		void *ptr = malloc(10000);
		memset(ptr, cnt, 10000);
		PrintChar((ptr) ? '+' : '-');
		free(ptr);
	}
	printf("\n");

	free(ptr_a);
	printf("malloc(100));\t%08X\n", (uint32_t*)malloc(100));
	printf("malloc(10)); \t%08X\n", (uint32_t*)malloc(10));
	printf("\n");
#pragma GCC diagnostic pop
}

void arm_sin_test()
{
	uint32_t time_arm = DWT_CYCCNT;
	float32_t sum_arm = 0.0;
	for (float32_t pos = 0.0; pos < PI*2; pos += PI/100.0f)
		sum_arm += arm_sin_f32(pos);
	time_arm = DWT_CYCCNT - time_arm;

	uint32_t time_gcc = DWT_CYCCNT;
	float32_t sum_gcc = 0.0;
	for (float32_t pos = 0.0; pos < PI*2; pos += PI/100.0f)
		sum_gcc += sinf(pos);
	time_gcc = DWT_CYCCNT - time_gcc;

	printf("library from\tARM\tGCC\n");
	printf("sinf results\t%+06.4f\t%+06.4f\n", sum_arm, sum_gcc);
	printf("sinf ticks  \t%lu\t%lu\n", time_arm, time_gcc);
	printf("\n");

	for (float32_t pos = 0.0; pos < PI*10; pos += PI/10.0f)
		printf("%+06.4f\t%+07.6f\t%+07.6f\n", pos, arm_sin_f32(pos), sinf(pos));
		//printf("%f\t%f\n", pos, arm_sin_f32(pos));
		//printf("%li\t%li\n", (int32_t)(pos*1000), (int32_t)(1000*arm_sin_f32(pos)));
	printf("\n");
}

#define Ntap 16

float32_t FIRCoef[Ntap] = {
    0.00491050126675623370,
    0.00820968581949351950,
    -0.03667132866703180800,
    -0.05322639448463983200,
    -0.03740416293129791200,
    -0.27222063419034065000,
    0.06272908936956618500,
    0.62056719594113607000,
    0.06272908936956618500,
    -0.27222063419034065000,
    -0.03740416293129791200,
    -0.05322639448463983200,
    -0.03667132866703180800,
    0.00820968581949351950,
    0.00491050126675623370,
    0.00592790129474772550
};

float fir(float NewSample)
{
    static float x[Ntap] = {0}; //input samples

    //shift the old samples
    for(int n=Ntap-1; n>0; n--)
       x[n] = x[n-1];

    //Calculate the new output
    x[0] = NewSample;
    float y=0;            //output sample
    for(int n=0; n<Ntap; n++)
        y += FIRCoef[n] * x[n];

    return y;
}

void fir2(float *NewSample, float *result, UNUSED uint32_t cnt)
{
    static float x[Ntap] = {0}; //input samples
//    float y;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
//    for(int n=Ntap-1; n>0; n--) x[n] = x[n-1]; x[0] = *NewSample; y = 0; for(int n=0; n<Ntap; n++) y += FIRCoef[n] * x[n]; *result = y; result++; NewSample++;
    float y;

    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;
    x[15]=x[14];x[14]=x[13];x[13]=x[12];x[12]=x[11];x[11]=x[10];x[10]=x[9];x[9]=x[8];x[8]=x[7];x[7]=x[6];x[6]=x[5];x[5]=x[4];x[4]=x[3];x[3]=x[2];x[2]=x[1];x[1]=x[0]; x[0] = *NewSample; y=0; y+=FIRCoef[0]*x[0];y+=FIRCoef[1]*x[1];y+=FIRCoef[2]*x[2];y+=FIRCoef[3]*x[3];y+=FIRCoef[4]*x[4];y+=FIRCoef[5]*x[5];y+=FIRCoef[6]*x[6];y+=FIRCoef[7]*x[7];y+=FIRCoef[8]*x[8];y+=FIRCoef[9]*x[9];y+=FIRCoef[10]*x[10];y+=FIRCoef[11]*x[11];y+=FIRCoef[12]*x[12];y+=FIRCoef[13]*x[13];y+=FIRCoef[14]*x[14];y+=FIRCoef[15]*x[15]; *result = y; result++; NewSample++;



//    while (cnt--)
//    {
//        //shift the old samples
//        //for(int n=Ntap-1; n>0; n--)
//        //   x[n] = x[n-1];
//    	x[15] = x[14];
//    	x[14] = x[13];
//    	x[13] = x[12];
//    	x[12] = x[11];
//    	x[11] = x[10];
//    	x[10] = x[ 9];
//    	x[ 9] = x[ 8];
//    	x[ 8] = x[ 7];
//    	x[ 7] = x[ 6];
//    	x[ 6] = x[ 5];
//    	x[ 5] = x[ 4];
//    	x[ 4] = x[ 3];
//    	x[ 3] = x[ 2];
//    	x[ 2] = x[ 1];
//    	x[ 1] = x[ 0];
//
//        //Calculate the new output
//        x[0] = *NewSample;
//        float y=0;            //output sample
//        //for(int n=0; n<Ntap; n++)
//        //    y += FIRCoef[n] * x[n];
//        y += FIRCoef[ 0] * x[ 0];
//        y += FIRCoef[ 1] * x[ 1];
//        y += FIRCoef[ 2] * x[ 2];
//        y += FIRCoef[ 3] * x[ 3];
//        y += FIRCoef[ 4] * x[ 4];
//        y += FIRCoef[ 5] * x[ 5];
//        y += FIRCoef[ 6] * x[ 6];
//        y += FIRCoef[ 7] * x[ 7];
//        y += FIRCoef[ 8] * x[ 8];
//        y += FIRCoef[ 9] * x[ 9];
//        y += FIRCoef[10] * x[10];
//        y += FIRCoef[11] * x[11];
//        y += FIRCoef[12] * x[12];
//        y += FIRCoef[13] * x[13];
//        y += FIRCoef[14] * x[14];
//        y += FIRCoef[15] * x[15];
//        *result = y;
//
//        result++;
//        NewSample++;
//    }
}

void arm_fir_test()
{
#define CNT 4096
	static float32_t data_in[CNT];
	static float32_t data_out_a[CNT];
	static float32_t data_out_b[CNT];
	static float32_t data_out_c[CNT];

	for (uint32_t pos = 0; pos < LENGTH(data_in); pos++)
		data_in[pos] = (
				arm_sin_f32(pos / 17.0) +
				arm_sin_f32(pos / 7.0) +
				arm_sin_f32(pos / 3.0) +
				arm_sin_f32(pos / 64.0)
				) / 4.0;

	uint32_t time_a = DWT_CYCCNT;
	for (uint32_t pos = 0; pos < LENGTH(data_in); pos++)
		data_out_a[pos] = fir(data_in[pos]);
	time_a = DWT_CYCCNT - time_a;

	uint32_t time_b = DWT_CYCCNT;
	for (uint32_t pos = 0; pos < LENGTH(data_in); pos += 16)
		fir2(&(data_in[pos]), &(data_out_b[pos]), 16);
	time_b = DWT_CYCCNT - time_b;

	arm_fir_instance_f32 f = {0};
	float32_t state[256] = {0};
	arm_fir_init_f32(&f, Ntap, FIRCoef, state, 16);

	uint32_t time_c = DWT_CYCCNT;
	for (uint32_t pos = 0; pos < LENGTH(data_in); pos += 16)
		arm_fir_f32(&f, &(data_in[pos]), &(data_out_c[pos]), 16);
	time_c = DWT_CYCCNT - time_c;

	for (uint32_t pos = 0; pos < LENGTH(data_in); pos++)
		printf("%+06.4f\t%+06.4f\t%+06.4f\t%+06.4f\n", data_in[pos], data_out_a[pos], data_out_b[pos], data_out_c[pos]);
	printf("\n");
	printf("time_a\t%lu\t%lu\n", time_a, time_a / CNT);
	printf("time_b\t%lu\t%lu\n", time_b, time_b / CNT);
	printf("time_c\t%lu\t%lu\n", time_c, time_c / CNT);
	printf("\n");

#define SAMPLES					(CNT*2) 			/* 256 real party and 256 imaginary parts */
#define FFT_SIZE				(SAMPLES / 2)		/* FFT size is always the same size as we have samples, so 256 in our case */
	arm_cfft_radix4_instance_f32 S;

	static float32_t Input[SAMPLES];
	static float32_t Output[FFT_SIZE];

	for (uint32_t pos = 0; pos < LENGTH(data_in); pos++)
	{
		data_in[pos] *= (0.5f - 0.5f * cosf(2.0f*PI * pos / (FFT_SIZE-1)));
		Input[pos * 2 + 0] = data_in[pos];
		Input[pos * 2 + 1] = 0;
	}

	/* Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1 */
	arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

	uint32_t time_fft = DWT_CYCCNT;
	/* Process the data through the CFFT/CIFFT module */
	arm_cfft_radix4_f32(&S, Input);
	time_fft = DWT_CYCCNT - time_fft;

	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(Input, Output, FFT_SIZE);

	for (uint32_t pos = 0; pos < LENGTH(Output); pos++)
		printf("%f\t%f\n", data_in[pos], Output[pos]);
	printf("\n");

	printf("FFT time: %lu\tticks\n", time_fft);
	printf("FFT time: %lu\tuS\n", (uint32_t)(((uint64_t)time_fft * 1000000LL) / SystemCoreClock));
	printf("\n");
}

