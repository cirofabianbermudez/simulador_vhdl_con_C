clear;
close all;
clc;

format longG;
% Generate VHDL code for fsm cordic
iter = 65-1;  % 5*13 = 65, le restamos 1
x = 0:1:iter;
n = 7;  %numero de bits

address = 0;
hab1 = repmat([0,1,0,0,0],1,13);
hab2 = repmat([0,0,1,0,0],1,13);
hab3 = repmat([0,0,0,1,0],1,13);

cont1 = 0;
for i = x
    % Para ultima iteracion
    if i == iter
         next = dec2bin(0,n);
    else
         next = dec2bin(i+1,n);
    end

    fprintf(' when "%s" => ADDRESS <= "%s"; SEL <= \''1\''; HAB <= \''%d\''; HAB2 <= \''%d\'';  HAB3 <= \''%d\''; -- %d \n\tQn <= "%s";\n',dec2bin(i,n),dec2bin(address,4),hab1(i+1),hab2(i+1),hab3(i+1),i,next);
    
    
    cont1 = cont1 + 1;
    if cont1 == 5
        cont1 = 0;
        address = address + 1;
    end
    
end
fprintf(' when %s    => ADDRESS <= "%s"; SEL <= \''0\''; HAB <= \''%d\''; HAB2 <= \''%d\''; HAB3 <= \''%d\''; -- %s \n\tQn <= "%s";\n','others',dec2bin(0,4),0,0,0,'others',dec2bin(0,n));

% NOTA: En las primeras 5 iteraciones, de 0-4 cambiar SEL <= '0'
% manualmente
