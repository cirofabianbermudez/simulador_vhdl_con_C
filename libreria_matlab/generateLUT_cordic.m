clear;
close all;
clc;

format longG;
% Generate VHDL code for LUT cordic
iter = 15;
x = 0:1:iter;
angulo = atand(2.^(-x));
angulobin = cell(size(angulo));

fprintf("library ieee;\nuse ieee.std_logic_1164.all;\nentity lut_cordic is\n\n	generic(\n		n : integer := 16		 -- tamaño de palabra\n	);\n	port(\n		address :	in	std_logic_vector(3 downto 0);\n		angulo 	:	out	std_logic_vector(n-1 downto 0)\n	);\n	end lut_cordic;\n\n\narchitecture arch of lut_cordic is\nbegin\n	  \n		with address select angulo <= \n");

for i = x
    str = sprintf('%d', dectobin(angulo(i+1),7,8,'trunc') );
    angulobin(i+1) = {str};
    r = bintodec( strtobin(angulobin{i+1}),7,8 );
    fprintf(' "%s" when "%s",\t-- %2.8f \t%2.8f \n',str,dec2bin(i,4),angulo(i+1), r);
end

fprintf(' "0000000000000000" when others;\n end arch;\n');

