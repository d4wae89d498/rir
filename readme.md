# Reflective IR

Experimental compiler pipelines written in C99 using [STC](https://github.com/stclib/STC). 

## Goals

1) The IR should remain as simple as possible using a single type that is a native CPU word (inspired from B langauge).

2) Demo frontend should do - lexing/parsing/first IR building - in a single pass and allow modification of the backend pipeline.

## Roadmap

- [ ] FE
    - [x] parsing tool
    - [ ] a textual syntax spec
    - [ ] build ir
    - [ ] meta construct

- [ ] IR
    - [x] finish node spec
    - [x] IR Builder tool
    - [ ] visitors (todo: move em into BE targets)
        - [ ] Print visitor
        - [ ] Graph visitor (emit a CFG)

- [ ] BE
    - [ ] passes
        - [ ] phi nodes / stack alloc insertions
        - [ ] ...
    - [ ] abstract machine decl / regalloc interface
    - [ ] targets 
        - [ ] quick interpreter that uses LIBFFI for C interop

- [x] CLI
    - [x] a man page
    - [x] impl

## See also

- [GNU lightning](https://www.gnu.org/software/lightning/)
- [Dmitry Stogov's ir framework](https://github.com/dstogov/ir.git) 
- [MIR](https://github.com/vnmakarov/mir.git)
- [LLVM & MLIR](https://mlir.llvm.org/) 
- [QBE](https://c9x.me/compile/)
