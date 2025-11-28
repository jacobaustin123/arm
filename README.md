# ARM64 NEON Experiments

Experiments with ARM64 NEON SIMD instructions on Apple Silicon.

## Projects

### [simd/](simd/)
Vector addition benchmark comparing hand-written NEON assembly to scalar C code.

### [matmul/](matmul/)
Matrix multiplication benchmark comparing scalar, hand-written NEON, and Apple Accelerate implementations.

## Requirements

- macOS with Apple Silicon (M1/M2/M3)
- Xcode command line tools

## Building

Each project has its own Makefile:

```bash
cd simd && make
cd matmul && make
```

## License

MIT
