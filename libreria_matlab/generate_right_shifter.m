clear;
close all;
clc;
% Generate VHDL code for fsm cordic
format longG;
iter = 12; x = 0:1:iter; str = ''; n = 5; %n es el numero de bits
for i = x
    if i == 0
      fprintf(' D when "%s", \n',dec2bin(i,n));  
    else
        fprintf(' "%s" & D(n-1 downto %2d) when "%s", \n',str,i,dec2bin(i,n));
    end
    str = strcat(str,'0');
end
fprintf("\n");

str = '';
for i = x
    if i == 0
      fprintf(' D when "%s", \n',dec2bin(i+16,n));  
    else
        fprintf(' "%s" & D(n-1 downto %2d) when "%s", \n',str,i,dec2bin(i+16,n));
    end
    str = strcat(str,'1');
end

fprintf(' \t\t\t\t  D when others; \n');
