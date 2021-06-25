clear;
close all;
clc;

iter = 20;

% Vectores del algoritmo
xi = zeros(1,iter+1);
yi = zeros(1,iter+1);
zi = zeros(1,iter+1);
ki = zeros(1,iter+1);

% Variables de entrada
xi(1) = 1;
yi(1) = 0;
zi(1) = -150;


ki(1) = 1/ sqrt(1 + 2^(-2*0));
fprintf("Datos de entrada\n");
fprintf("0\t%f\t%f\t%f\t%f\n",xi(1),yi(1),zi(1),ki(1) );
fprintf("i\txi\t\t\tyi\t\t\tzi\t\t\tki\n");
for i = 1:1:iter+1
    ki(i+1) = 1/ sqrt(1 + 2^(-2*(i)));
    xi(i+1) = ki(i)*(xi(i) - yi(i) * d_fun( zi(i) ) * 2^-(i-1));
    yi(i+1) = ki(i)*(yi(i) + xi(i) * d_fun( zi(i) ) * 2^-(i-1));
    zi(i+1) = zi(i) -  d_fun( zi(i) ) * atand(2^-(i-1));
    fprintf("%d\t%f\t%f\t%f\t%f\n",i,xi(i+1),yi(i+1),zi(i+1),ki(i+1));
end
% comprobar ki
kn =  prod(ki);
xn = xi(iter+1);
yn = yi(iter+1);
fprintf("Ki = %f\n", kn);
fprintf("xn = %f\tyn = %f\n", xn,yn);

% Dibujar un circulo
t = 0:0.01:2*pi;
R = 1;    %sqrt(2)
x = sin(t)*R;
y = cos(t)*R;
plot(x,y);
axis equal;
hold on;


plot([0 xi(1)],[0 yi(1)],'-o' );
hold on;
plot([0 xn],[0 yn],'-o' );
grid on;
grid minor;
zoom = 2;
axis([-zoom zoom -zoom zoom]);


function R = d_fun(x)
    if x >= 0
        R = 1;
    else
        R = -1;
    end
end