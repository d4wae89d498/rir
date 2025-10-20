# Reflective IR

Experimental compiler pipelines.

## Goals

1) The IR should remain as simple as possible using a single type that is a native CPU word (inspired from B langauge).

2) Demo frontend should do - lexing/parsing/first IR building - in a single pass and allow modification of the entire compiler pipeline.

## Implementation details

Libraries are written in C99, while the CLI and tests are written in C23.
The code uses only libc and [STC](https://github.com/stclib/STC), without POSIX or any other target-specific features. This implementation choice ensures that run-time extensions can easily interact with compiler internals using the well-known C ABI.

## Roadmap

- [ ] FE
    - [x] parsing tool
    - [ ] a textual syntax spec
    - [ ] build ir
    - [ ] meta construct

- [ ] IR
    - [x] finish node spec
    - [x] IR Builder tool
    - [ ] visitors 
        - [ ] delete visitor
        - [ ] ability to detect if visitor implement all nodes or ERROR

- [ ] BE
    - [ ] passes
        - [ ] generic pass 'class' with dependencies etc
        - [ ] phi nodes / stack alloc insertions
        - [ ] constant propagation
        - [ ] dead code elimination
    - [ ] abstract machine decl / regalloc interface
    - [ ] targets 
        - [ ] quick interpreter that uses LIBFFI for C interop
        - [x] Print visitor
        - [ ] Graph visitor (emit a CFG)
        - [ ] C

- [x] CLI
    - [x] a man page
    - [x] impl
    - [x] dynamic cli help 
    - [ ] dynamic man page generation  

## Dev env

Windows: `vscode + wsl extension`
Mac/linux: `codium`

```bash
apt install fswatch pipx
pipx install compiledb
```

*fswatch and compiledb is needed to make the vscode task that maintains `compile_commands.json` working.*
  
## See also

- [GNU lightning](https://www.gnu.org/software/lightning/)
- [Dmitry Stogov's ir framework](https://github.com/dstogov/ir.git) 
- [MIR](https://github.com/vnmakarov/mir.git)
- [LLVM & MLIR](https://mlir.llvm.org/) 
- [QBE](https://c9x.me/compile/)
