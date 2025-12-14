# ARM64 NEON SIMD Vector Addition

A benchmark comparing SIMD vs scalar float array addition on Apple Silicon.

## Building

```bash
make
```

Requires macOS with Apple Silicon (or ARM64) and Xcode command line tools.

## Running

```bash
./simd_test
```

Tests correctness with a 512-element array and benchmarks with 10 million floats.

## Implementation Details

The NEON kernel (`simd_add.s`) adds two float arrays using:
- `ld1` to load 4 floats at a time into vector registers
- `fadd` for parallel floating-point addition
- Scalar fallback for remaining elements (count not divisible by 4)

## License

MIT
