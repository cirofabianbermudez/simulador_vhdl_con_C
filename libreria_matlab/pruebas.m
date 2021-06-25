clear;
close all;
clc;

format longG
reg = dectobin(0.607252935008881,7,8,'trunc');
regStr = sprintf('%d',  reg)
regReal = bintodec(reg,7,8)


