# Chip-8 Emulator in C++

This project covers the original Chip-8 specification of 35 opcodes.

## Outline of the project

```
chip8_emulator/
├── src/                 # Contains source files
├── docs/                # Documentation, implemented opcodes, and pipelines
├── TODOs/               # Project task tracking
│   └── TODO.md
├── ai_markdown_folder/  # Records/disclosures of AI editor usage
├── .gitignore
└── CMakeLists.txt
```

## How to build the project

To build the project, you will need to do the following:
1. Install glad from [here](https://glad.dav1d.de/)
2. Install glfw-3.5.1 from its [github releases page](https://github.com/glfw/glfw/releases)
3. On installation place them in a newly created `external` folder as follows

```
external/
├── glad/
└── glfw-3.5.2/
```

4. On doing so run the following command

```Bash
> cmake -S . -B build/

```

5. On completion, run the following command

```Bash
cmake --build build
```

6. To run the emulator

```Bash
.\build\Debug\<executable>
```

## Testing the project

So far, I have done the testing using testRoms which you can find [here](https://github.com/kripod/chip8-roms).
The emulator was able to pas the following testRoms (videos dropping soon):
1. IBM Logo
2. Fishie
3. Random Number Test
4. Keypad Test
5. Delay Timer Test
6. Clock Program
7. Jumping X and O
8. Life 

# AI Usage
I refrained from using AI for coding most of the project but thought I could create a custom renderer only for this project as using it would save me some time. So to create this renderer, AI was used in its inital stages but later on, I did not use AI for adding keyboard functions, etc. As far as understanding the emulator goes, I did use LLMs to understand how certain instructions and opcodes work and how to handle them efficiently.

# Final Remarks

Feel free to hack into the code, add native support for linux, macos or any other os. Feel free to reach out to me if you have any suggestions on what I could have done different in the project.

