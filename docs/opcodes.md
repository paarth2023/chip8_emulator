# Opcodes Implemented

1. 0x0E00 - Clear Screen
2. 0x1nnn - jump to memory address `nnn`
3. 0x6xkk - set `Vx` register to `kk`
4. 0x7xkk - add `kk` to register `Vx`
5. 0xAnnn - set `I` register to `nnn`
   
### Special Instruction DXYN

This instruction is important in the sense that it controls the drawing to the screen, hence it will be explained separately with more illustration.