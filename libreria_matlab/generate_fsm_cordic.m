clear;
close all;
clc;

format longG;
% Generate VHDL code for fsm cordic
iter = 38;
x = 0:1:iter;


%fprintf("library ieee;\nuse ieee.std_logic_1164.all;\nentity lut_cordic is\n\n	generic(\n		n : integer := 16		 -- tamaño de palabra\n	);\n	port(\n		address :	in	std_logic_vector(3 downto 0);\n		angulo 	:	out	std_logic_vector(n-1 downto 0)\n	);\n	end lut_cordic;\n\n\narchitecture arch of lut_cordic is\nbegin\n	  \n		with address select angulo <= \n");
j = 0;
k = 0;
contJ = 1;
contK = 1;
for i = x
        if i == iter
             next = dec2bin(0,6);
        else
             next = dec2bin(i+1,6);
        end
       
        fprintf(' when "%s" => ADDRESS <= "%s"; SEL <= \''1\''; HAB <= \''%d\''; -- %d \n\tQn <= "%s";\n',dec2bin(i,6),dec2bin(j,4),k,i,next);
    
    if contJ == 3
        j = j + 1;
        contJ = 0;
    end
    contJ = contJ + 1;
    
    if contK == 1
         k = 1;   
    elseif contK == 2
         k = 0;
    elseif contK == 3
         k = 0;
         contK = 0;
    end
    contK = contK + 1;
end
fprintf(' when %s   => ADDRESS <= "%s"; SEL <= \''0\''; HAB <= \''%d\''; -- %s \n\tQn <= "%s";\n','others',dec2bin(0,4),0,'others',dec2bin(0,6));

