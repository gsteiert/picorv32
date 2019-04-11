/*
 *  FemtoSoC - A simple example SoC using PicoRV32
 *
 *  Copyright (C) 2017  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

`ifndef PICORV32_REGS
`ifdef PICORV32_V
//`error "femtosoc.v must be read before picorv32.v!"
`endif

`define PICORV32_REGS femtosoc_regs
`endif

`ifndef FEMTOSOC_MEM
`define FEMTOSOC_MEM femtosoc_mem
`endif

// this macro can be used to check if the verilog files in your
// design are read in the correct order.
`define FEMTOSOC_V

module femtosoc (
	input clk,
	input resetn,

	output        iomem_valid,
	input         iomem_ready,
	output [ 3:0] iomem_wstrb,
	output [31:0] iomem_addr,
	output [31:0] iomem_wdata,
	input  [31:0] iomem_rdata

);
	parameter [0:0] BARREL_SHIFTER = 0;
    parameter [0:0] TWO_STAGE_SHIFT = 0;
	parameter [0:0] CATCH_MISALIGN = 0;
	parameter [0:0] CATCH_ILLINSN = 0;
	parameter [0:0] ENABLE_MULDIV = 0;
	parameter [0:0] ENABLE_COMPRESSED = 0;
	parameter [0:0] ENABLE_COUNTERS = 0;
	parameter [0:0] ENABLE_COUNTERS64 = 0;
	parameter [0:0] ENABLE_IRQ_QREGS = 0;
	parameter [0:0] ENABLE_IRQ_TIMER = 0;
	parameter [0:0] ENABLE_REGS_16_31 = 1;
	parameter [0:0] ENABLE_REGS_DUALPORT = 0;

	parameter integer MEM_WORDS = 1024;  // 32bit words
	parameter [31:0] CODE_START = 32'h 0000_0000;  // must be on word boundary
	parameter [31:0] STACKADDR = (4 * MEM_WORDS);  // end of memory
	parameter [31:0] PROGADDR_RESET = CODE_START;  // start of code
	parameter [31:0] PROGADDR_IRQ = 32'h 0000_0000;

	wire mem_valid;
	wire mem_instr;
	wire mem_ready;
	wire [31:0] mem_addr;
	wire [31:0] mem_wdata;
	wire [3:0] mem_wstrb;
	wire [31:0] mem_rdata;

	reg ram_ready;
	wire [31:0] ram_rdata;

	assign iomem_valid = mem_valid && (mem_addr[31:24] > 8'h 00);
	assign iomem_wstrb = mem_wstrb;
	assign iomem_addr = mem_addr;
	assign iomem_wdata = mem_wdata;

	assign mem_ready = (iomem_valid && iomem_ready) || ram_ready;

    assign mem_rdata = (iomem_valid && iomem_ready) ? iomem_rdata : 
                        ram_ready ? ram_rdata : 32'h 0000_0000;

	picorv32 #(
		.STACKADDR(STACKADDR),
		.PROGADDR_RESET(PROGADDR_RESET),
		.PROGADDR_IRQ(PROGADDR_IRQ),
		.BARREL_SHIFTER(BARREL_SHIFTER),
        .TWO_STAGE_SHIFT(TWO_STAGE_SHIFT),
		.COMPRESSED_ISA(ENABLE_COMPRESSED),
		.CATCH_MISALIGN(CATCH_MISALIGN),
		.CATCH_ILLINSN(CATCH_ILLINSN),
		.ENABLE_COUNTERS(ENABLE_COUNTERS),
		.ENABLE_COUNTERS64(ENABLE_COUNTERS64),
		.ENABLE_REGS_16_31(ENABLE_REGS_16_31),
		.ENABLE_REGS_DUALPORT(ENABLE_REGS_DUALPORT),
		.ENABLE_MUL(ENABLE_MULDIV),
		.ENABLE_DIV(ENABLE_MULDIV),
		.ENABLE_IRQ(0),
		.ENABLE_IRQ_QREGS(ENABLE_IRQ_QREGS)
	) cpu (
		.clk         (clk        ),
		.resetn      (resetn     ),
		.mem_valid   (mem_valid  ),
		.mem_instr   (mem_instr  ),
		.mem_ready   (mem_ready  ),
		.mem_addr    (mem_addr   ),
		.mem_wdata   (mem_wdata  ),
		.mem_wstrb   (mem_wstrb  ),
		.mem_rdata   (mem_rdata  ),
		.irq         (32'h0      )
	);

	always @(posedge clk)
		ram_ready <= mem_valid && !mem_ready && mem_addr < 4*MEM_WORDS;

	`FEMTOSOC_MEM #(
		.WORDS(MEM_WORDS)
	) memory (
		.clk(clk),
		.wen((mem_valid && !mem_ready && mem_addr < 4*MEM_WORDS) ? mem_wstrb : 4'b0),
		.addr(mem_addr[23:2]),
		.wdata(mem_wdata),
		.rdata(ram_rdata)
	);
endmodule

// Implementation note:
// Replace the following two modules with wrappers for your SRAM cells.

module dp_regs #(
	parameter [0:0] ENABLE_REGS_16_31 = 1, 
	parameter [0:0] ENABLE_IRQ_QREGS = 1
) (
	input clk, wen,
	input [(3 + ENABLE_REGS_16_31 + ENABLE_IRQ_QREGS):0] waddr,
	input [(3 + ENABLE_REGS_16_31 + ENABLE_IRQ_QREGS):0] raddr,
	input [31:0] wdata,
	output [31:0] rdata
);
	reg [31:0] regs [0:((2**(4 + ENABLE_REGS_16_31 + ENABLE_IRQ_QREGS))-1)];

	// initial begin
	// 	$readmemh ("reg_init.memh", regs);
	// end

	always @(posedge clk)
		if (wen) regs[waddr] <= wdata;

//`define SYNC_REG_MEM 1
`ifdef SYNC_REG_MEM
	reg [31:0] rdata_r;		
	always @(negedge clk) 
		rdata_r = regs[raddr];
	assign rdata = rdata_r;
`else
	assign rdata = regs[raddr[(ENABLE_REGS_16_31 ? 4 : 3):0]];
`endif

endmodule

module femtosoc_regs #(
	parameter [0:0] ENABLE_REGS_16_31 = 1,
	parameter [0:0] ENABLE_REGS_DUALPORT = 0
) (
	input clk, wen,
	input [5:0] waddr,
	input [5:0] raddr1,
	input [5:0] raddr2,
	input [31:0] wdata,
	output [31:0] rdata1,
	output [31:0] rdata2
);

localparam integer regindex_bits = (ENABLE_REGS_16_31 ? 4 : 3);


dp_regs #(
	.ENABLE_REGS_16_31(ENABLE_REGS_16_31) 
) regs1 (
	.clk(clk), 
	.wen(wen), 
	.waddr(waddr[regindex_bits:0]), 
	.raddr(raddr1[regindex_bits:0]), 
	.wdata(wdata), 
	.rdata(rdata1)
);

generate
	if (ENABLE_REGS_DUALPORT) 
		dp_regs #(
			.ENABLE_REGS_16_31(ENABLE_REGS_16_31) 
		) regs2 (
			.clk(clk), 
			.wen(wen), 
			.waddr(waddr[regindex_bits:0]), 
			.raddr(raddr2[regindex_bits:0]), 
			.wdata(wdata), 
			.rdata(rdata2)
		);
endgenerate

endmodule

module femtosoc_mem #(
	parameter integer WORDS = 1024
) (
	input clk,
	input [3:0] wen,
	input [21:0] addr,
	input [31:0] wdata,
	output reg [31:0] rdata
);
	reg [31:0] mem [0:WORDS-1];

	initial begin
		$readmemh ("../../firmware/femto_fw.mem", mem);
	end

	always @(posedge clk) begin
		rdata <= mem[addr];
		if (wen[0]) mem[addr][ 7: 0] <= wdata[ 7: 0];
		if (wen[1]) mem[addr][15: 8] <= wdata[15: 8];
		if (wen[2]) mem[addr][23:16] <= wdata[23:16];
		if (wen[3]) mem[addr][31:24] <= wdata[31:24];
	end
endmodule

