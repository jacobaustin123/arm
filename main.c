#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of our assembly function
extern void simd_add_floats(float *dst, const float *a, const float *b, size_t count);

// Simple scalar version for comparison
void scalar_add_floats(float *dst, const float *a, const float *b, size_t count) {
    for (size_t i = 0; i < count; i++) {
        dst[i] = a[i] + b[i];
    }
}

int main() {
    const size_t N = 512;  // Test with 16 floats
    
    float a[N], b[N], dst_simd[N], dst_scalar[N];
    
    // Initialize with some test values
    printf("Input arrays:\n");
    printf("  a: ");
    for (size_t i = 0; i < N; i++) {
        a[i] = (float)i * 1.5f;
        printf("%.1f ", a[i]);
    }
    printf("\n  b: ");
    for (size_t i = 0; i < N; i++) {
        b[i] = (float)i * 0.5f;
        printf("%.1f ", b[i]);
    }
    printf("\n\n");
    
    // Run SIMD version
    simd_add_floats(dst_simd, a, b, N);
    
    // Run scalar version for verification
    scalar_add_floats(dst_scalar, a, b, N);
    
    // Print results
    printf("Results:\n");
    printf("  SIMD:   ");
    for (size_t i = 0; i < N; i++) {
        printf("%.1f ", dst_simd[i]);
    }
    printf("\n  Scalar: ");
    for (size_t i = 0; i < N; i++) {
        printf("%.1f ", dst_scalar[i]);
    }
    printf("\n\n");
    
    // Verify correctness
    int match = 1;
    for (size_t i = 0; i < N; i++) {
        if (dst_simd[i] != dst_scalar[i]) {
            match = 0;
            printf("Mismatch at index %zu: SIMD=%.6f, Scalar=%.6f\n", 
                   i, dst_simd[i], dst_scalar[i]);
        }
    }
    
    if (match) {
        printf("✓ SIMD and scalar results match!\n");
    }
    
    // Quick benchmark with larger array
    const size_t BENCH_SIZE = 10000000;
    float *big_a = malloc(BENCH_SIZE * sizeof(float));
    float *big_b = malloc(BENCH_SIZE * sizeof(float));
    float *big_dst = malloc(BENCH_SIZE * sizeof(float));
    
    for (size_t i = 0; i < BENCH_SIZE; i++) {
        big_a[i] = (float)i;
        big_b[i] = (float)i * 2.0f;
    }
    
    clock_t start, end;
    
    // Benchmark SIMD
    start = clock();
    for (int iter = 0; iter < 10; iter++) {
        simd_add_floats(big_dst, big_a, big_b, BENCH_SIZE);
    }
    end = clock();
    double simd_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Benchmark scalar
    start = clock();
    for (int iter = 0; iter < 10; iter++) {
        scalar_add_floats(big_dst, big_a, big_b, BENCH_SIZE);
    }
    end = clock();
    double scalar_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\nBenchmark (10M floats × 10 iterations):\n");
    printf("  Scalar: %.3f seconds\n", scalar_time);
    printf("  SIMD:   %.3f seconds\n", simd_time);
    printf("  Speedup: %.2fx\n", scalar_time / simd_time);
    
    free(big_a);
    free(big_b);
    free(big_dst);
    
    return 0;
}
