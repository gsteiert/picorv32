
FemtoSoC - A simpler example SoC using PicoRV32
=============================================

![](overview.svg)

This is a simpler PicoRV32 example design that can run code directly from 
pre-loaded RAM. It can be used as a turn-key solution for simple control 
tasks in ASIC and FPGA designs.

An example implementation targeting the Lattice MachXO2 Breakout Board is
included.

The SRAM is located at 0x00000000. The SRAM is just a small scratchpad memory 
(default 1k words, i.e. 4 kB).

The reset vector is set to 0x00000000, the start of SRAM.

See the included demo firmware and linker script for how to build a firmware
image for this system.

| File                              | Description                                                     |
| --------------------------------- | --------------------------------------------------------------- |
| [femtosoc.v](femtosoc.v)          | Top-level FemtoSoC Verilog module                               |
| [start.s](start.s)                | Assembler source for firmware.hex/firmware.bin                  |
| [sections.lds](sections.lds)      | Linker script for firmware.hex/firmware.bin                     |

### Memory map:

| Address Range            | Description                             |
| ------------------------ | --------------------------------------- |
| 0x00000000 .. 0x00FFFFFF | Internal SRAM                           |
| 0x01000000 .. 0xFFFFFFFF | Memory mapped user peripherals          |

The example design (femto_top.v) has the 8 LEDs on the MachXO2 Breakout Board
mapped to the low byte of the 32 bit word at address 0x01000000.

