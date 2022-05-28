#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    int M = 4000;
    int N = 4000;
    int K = 4000;
    std::cout << "M N K size " << M << " " << N << " " << K << std::endl;
    float *A = new float[M * K];
    float *B = new float[K * N];
    float *C = new float[M * N];
    float *C_check = new float[M * N];
    for (int i = 0; i < M * K; i++)
        A[i] = i;
    for (int i = 0; i < K * N; i++)
        B[i] = i;
    for (int i = 0; i < M * N; i++)
        C[i] = 0;
    for (int i = 0; i < M * N; i++)
        C_check[i] = 0;
    clock_t timein, timeout;
    clock_t time_single, time_thread;
    timein = clock();
    for (int m = 0; m < M; m++)
        for (int k = 0; k < K; k++)
            for (int n = 0; n < N; n++)
                C_check[m * N + n] += A[m * K + k] * B[k * N + n];
    timeout = clock();
    time_single = timeout - timein;
    std::cout << "gemm single " << time_single << std::endl;

    clock_t timein_omp = clock();

#pragma omp parallel for
    for (int m = 0; m < M; m++)
        for (int k = 0; k < K; k++)
            for (int n = 0; n < N; n++)
                C[m * N + n] += A[m * K + k] * B[k * N + n];
    clock_t timeout_omp = clock();

    time_thread = timeout_omp - timein_omp;
    std::cout <<"gemm omp "<< time_thread << std::endl;
    // check result
    bool error = false;
    for (int i = 0; i < M * N; i++)
        if (fabs(C[i] - C_check[i]) > 1e-5)
        {
            std::cout << "error at " << i << " " << C[i] << " " << C_check[i] << std::endl;
            error = true;
            break;
        }
    if (error)
        std::cout << "gemm failed " << std::endl;
    else
        std::cout << "gemm done sucessfully " << std::endl;
    return 0;
}
