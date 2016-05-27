
module crc_comb (data, enable, curr_crc, next_crc);

input [3:0] data;
input enable;
input [31:0] curr_crc;

output [31:0] next_crc;

assign next_crc[0]  = enable & (data[0] ^ curr_crc[28]);
assign next_crc[1]  = enable & (data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29]);
assign next_crc[2]  = enable & (data[2] ^ data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29] ^ curr_crc[30]);
assign next_crc[3]  = enable & (data[3] ^ data[2] ^ data[1] ^ curr_crc[29] ^ curr_crc[30] ^ curr_crc[31]);
assign next_crc[4]  = (enable & (data[3] ^ data[2] ^ data[0] ^ curr_crc[28] ^ curr_crc[30] ^ curr_crc[31])) ^ curr_crc[0];
assign next_crc[5]  = (enable & (data[3] ^ data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29] ^ curr_crc[31])) ^ curr_crc[1];
assign next_crc[6]  = (enable & (data[2] ^ data[1] ^ curr_crc[29] ^ curr_crc[30])) ^ curr_crc[ 2];
assign next_crc[7]  = (enable & (data[3] ^ data[2] ^ data[0] ^ curr_crc[28] ^ curr_crc[30] ^ curr_crc[31])) ^ curr_crc[3];
assign next_crc[8]  = (enable & (data[3] ^ data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29] ^ curr_crc[31])) ^ curr_crc[4];
assign next_crc[9]  = (enable & (data[2] ^ data[1] ^ curr_crc[29] ^ curr_crc[30])) ^ curr_crc[5];
assign next_crc[10] = (enable & (data[3] ^ data[2] ^ data[0] ^ curr_crc[28] ^ curr_crc[30] ^ curr_crc[31])) ^ curr_crc[6];
assign next_crc[11] = (enable & (data[3] ^ data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29] ^ curr_crc[31])) ^ curr_crc[7];
assign next_crc[12] = (enable & (data[2] ^ data[1] ^ data[0] ^ curr_crc[28] ^ curr_crc[29] ^ curr_crc[30])) ^ curr_crc[8];
assign next_crc[13] = (enable & (data[3] ^ data[2] ^ data[1] ^ curr_crc[29] ^ curr_crc[30] ^ curr_crc[31])) ^ curr_crc[9];
assign next_crc[14] = (enable & (data[3] ^ data[2] ^ curr_crc[30] ^ curr_crc[31])) ^ curr_crc[10];
assign next_crc[15] = (enable & (data[3] ^ curr_crc[31])) ^ curr_crc[11];
assign next_crc[16] = (enable & (data[0] ^ curr_crc[28])) ^ curr_crc[12];
assign next_crc[17] = (enable & (data[1] ^ curr_crc[29])) ^ curr_crc[13];
assign next_crc[18] = (enable & (data[2] ^ curr_crc[30])) ^ curr_crc[14];
assign next_crc[19] = (enable & (data[3] ^ curr_crc[31])) ^ curr_crc[15];
assign next_crc[20] = curr_crc[16];
assign next_crc[21] = curr_crc[17];
assign next_crc[22] = (enable & (data[0] ^ curr_crc[28])) ^ curr_crc[18];
assign next_crc[23] = (enable & (data[1] ^ data[0] ^ curr_crc[29] ^ curr_crc[28])) ^ curr_crc[19];
assign next_crc[24] = (enable & (data[2] ^ data[1] ^ curr_crc[30] ^ curr_crc[29])) ^ curr_crc[20];
assign next_crc[25] = (enable & (data[3] ^ data[2] ^ curr_crc[31] ^ curr_crc[30])) ^ curr_crc[21];
assign next_crc[26] = (enable & (data[3] ^ data[0] ^ curr_crc[31] ^ curr_crc[28])) ^ curr_crc[22];
assign next_crc[27] = (enable & (data[1] ^ curr_crc[29])) ^ curr_crc[23];
assign next_crc[28] = (enable & (data[2] ^ curr_crc[30])) ^ curr_crc[24];
assign next_crc[29] = (enable & (data[3] ^ curr_crc[31])) ^ curr_crc[25];
assign next_crc[30] = curr_crc[26];
assign next_crc[31] = curr_crc[27];

endmodule