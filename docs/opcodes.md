# Opcodes Implemented

1. 0x0E00 - Clear Screen
2. 0x1nnn - jump to memory address `nnn`
3. 0x6xkk - set `Vx` register to `kk`
4. 0x7xkk - add `kk` to register `Vx`
5. 0xAnnn - set `I` register to `nnn`
6. 0xDxyn - draw pixels on the screen at position x, y which are n height tall (illustration will be added soon).
7. 0x3xkk - skip the next instruciton if Vx == kk
8. 0x4xkk - skip the next instruction if Vx != kk
9. 0x5xy0 - skip the next instruction if Vx == Vy
10. 0x8xyN - where N could be:
    1. 0 - set Vx = Vy
    2. 1 - set Vx = Vx | Vy
    3. 2 - Vx = Vx & Vy
    4. 3 - Vx = Vx ^ Vy
    5. 4 - Vx = Vx + Vy, Vf = carry
    6. 5 - Vx = Vx - Vy, Vf = borrow
    7. 6 - Vx = Vx >> 1, Vf = least significant bit.
    8. 7 - Vx = Vy - Vx, Vf = borrow
    9. E - Vx = Vx << 1, Vf = most significant bit
11. 0x9xy0 - skip the next instrucition if Vx != Vy
12. 0xBnnn - jump to V0 + nnnn memory address.