// simd_add.s - Add two float arrays using NEON SIMD
// void simd_add_floats(float *dst, const float *a, const float *b, size_t count)
// Arguments: x0 = dst, x1 = a, x2 = b, x3 = count

.global _simd_add_floats
.align 4

_simd_add_floats:
    // Handle case where count < 4 (can't use full SIMD)
    cmp     x3, #4
    b.lt    .Lscalar_loop

.Lsimd_loop:
    // Load 4 floats from array a into v0
    ld1     {v0.4s}, [x1], #16
    // Load 4 floats from array b into v1
    ld1     {v1.4s}, [x2], #16
    // Add them: v2 = v0 + v1
    fadd    v2.4s, v0.4s, v1.4s
    // Store result to dst
    st1     {v2.4s}, [x0], #16
    // Decrement count by 4
    sub     x3, x3, #4
    // Continue if we have 4+ elements remaining
    cmp     x3, #4
    b.ge    .Lsimd_loop

    // Handle remaining elements (0-3)
    cbz     x3, .Ldone

.Lscalar_loop:
    // Load single floats
    ldr     s0, [x1], #4
    ldr     s1, [x2], #4
    // Add them
    fadd    s2, s0, s1
    // Store result
    str     s2, [x0], #4
    // Decrement and loop
    subs    x3, x3, #1
    b.ne    .Lscalar_loop

.Ldone:
    ret
