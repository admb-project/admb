/* adpar32.h - expose 32 bit openCL functionality to ADMB */

#include <fvar.hpp>
#include <windows.h>

#ifndef ADMBPAR32_INCLUDE
#define ADMBPAR32_INCLUDE

int oclDeviceTest();
int cpuMatMult(int wa, int ha, int wb, int hb, bool printMatrices);
int oclMatMult(int wa, int ha, int wb, int hb, bool printMatrices);

//df3_two_matrix ocl_choleski_decomp(const df3_two_matrix& MM);

// very simple, high-precision timer for timing API calls
struct ProfTimer{
    void Start(void){
        QueryPerformanceCounter(&mTimeStart);
    };
    void Stop(void){
        QueryPerformanceCounter(&mTimeStop);
    };
    double GetDurationInSecs(void){
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        double duration = (double)(mTimeStop.QuadPart-mTimeStart.QuadPart)/(double)freq.QuadPart;
        return duration;
    }

    LARGE_INTEGER mTimeStart;
    LARGE_INTEGER mTimeStop;
};
#endif

#ifndef _MATRIXMUL_H_
#define _MATRIXMUL_H_

#define MAXMATRIXDIM 25000
#define PLATFORMINFOSIZE 1024

#endif


