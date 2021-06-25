clear; close all; clc;
angulo = 20;
% Caso 1
a1 = cosd(angulo);
b1 = 0.9296875;
e1_r = a1 - b1;
e1 = abs(a1 - b1)*100/a1;

% Caso 1
a2 = sind(angulo);
b2 = 0.35546875;
e2_r = a2 - b2;
e2 = abs(a2 - b2)*100/a2;