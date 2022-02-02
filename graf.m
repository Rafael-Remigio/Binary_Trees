clear;
close all;
clc;

A_1 = load("0_creation.txt");
A_2 = load("0_Search.txt");
A_3 = load("1_creation.txt");
A_4 = load("1_Search.txt");
A_5 = load("2_creation.txt");
A_6 = load("2_Search.txt");
 
 


 %se coluda 2==1  %coluna
n_V1_1 = A_1(:, 1);
f_V1_1 = A_1(:, 2); 

n_V1_2 = A_2(:, 1);
f_V1_2 = A_2(:, 2); 

n_V1_3 = A_3(:, 1);
f_V1_3 = A_3(:, 2);

n_V1_4 = A_4(:, 1);
f_V1_4 = A_4(:, 2);

n_V1_5 = A_5(:, 1);
f_V1_5 = A_5(:, 2); 

n_V1_6 = A_6(:, 1);
f_V1_6 = A_6(:, 2); 

    


 
figure(1);    
plot(n_V1_1, f_V1_1, n_V1_3, f_V1_3, n_V1_5, f_V1_5); 
title("Criação da Árvore")
legend("Names","Zip Code","Phone Numbers" )
xlabel("Número de Pessoas")
ylabel("Tempo (s)")
grid on  

figure(2);   
plot(n_V1_2, f_V1_2, n_V1_4, f_V1_4, n_V1_6, f_V1_6);
title("Procura")
legend("Names","Zip Code","Phone Numbers" )
xlabel("Número de Pessoas")
ylabel("Tempo (s)")
grid on  
  

%%  
clear;
close all;
clc;

A = load("file");

      %se coluda 2==1  %coluna
    deapth_0 = A(A(:,2)==0, 3);
  figure(1)
    plot(deapth_0);

    %deapth_1 = A(A(:,2)==1, 3);
    %deapth_2 = A(A(:,2)==2, 3); 
    %deapth_3 = A(A(:,2)==3, 3); 
     
grid on

 
    
  
 

 

