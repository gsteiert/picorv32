module femtosoc_top(
	inout wire sda, scl,
	output wire [7:0] led
);

parameter integer MEM_WORDS = 1024;

wire clk;

wire iomem_valid;
reg iomem_ready = 0;
wire [3:0] iomem_wstrb;
wire [31:0] iomem_addr;
wire [31:0] iomem_wdata;
reg [31:0] iomem_rdata = 32'h0A5;

reg [5:0] reset_cnt = 0;
wire resetn = &reset_cnt;

always @(posedge clk) begin
	reset_cnt <= reset_cnt + !resetn;
end

assign led = ~iomem_rdata[7:0];

always @(posedge clk) begin
	if (iomem_valid) begin
		iomem_ready <= 1'b1;
		if (iomem_wstrb[3]) iomem_rdata[31:24] <= iomem_wdata[31:24];
		if (iomem_wstrb[2]) iomem_rdata[23:16] <= iomem_wdata[23:16];
		if (iomem_wstrb[1]) iomem_rdata[15:8] <= iomem_wdata[15:8];
		if (iomem_wstrb[0]) iomem_rdata[7:0] <= iomem_wdata[7:0];
	end else begin
		iomem_ready <= 1'b0;
	end
end



// Internal Oscillator
// defparam OSCH_inst.NOM_FREQ = "2.08";// This is the default frequency
defparam OSCH_inst.NOM_FREQ = "24.18";
OSCH OSCH_inst( .STDBY(1'b0), // 0=Enabled, 1=Disabled
.OSC(clk),
.SEDSTDBY()); // this signal is not required if not using SED


	femtosoc #(
		.MEM_WORDS(MEM_WORDS)
	) soc (
		.clk          (clk         ),
		.resetn       (resetn      ),

		.iomem_valid  (iomem_valid ),
		.iomem_ready  (iomem_ready ),
		.iomem_wstrb  (iomem_wstrb ),
		.iomem_addr   (iomem_addr  ),
		.iomem_wdata  (iomem_wdata ),
		.iomem_rdata  (iomem_rdata )
	);

efb efb0 (.wb_clk_i( clk ), .i2c1_scl( scl ), .i2c1_sda( sda ), .i2c1_irqo( ));

endmodule
