%%
angulos = 15;
deltaAng = 2*pi/angulos;
radios = 15;
radioi = 10;
radioe = 100;
deltaRad = (radioe-radioi)/(radios-1);
puntos = angulos*radios;
caloriso = 500;


% Armado de la A
A = zeros(puntos,puntos);
for i=1:angulos
    A(i,i) = 1;
    A(puntos+1-i,puntos+1-i) = 1;
end

for j=1:angulos
    for i = 2:radios-1
        auxj1 = j-1;
        if auxj1==0
            auxj1=angulos;
        end
        radAct = radioi + deltaRad*(i-1);
        A(idx(i,j,angulos),idx(i,j,angulos)) = -2/(deltaRad^2)+1/(deltaRad*radAct)-2/(deltaAng^2*radAct^2);
        A(idx(i,j,angulos),idx(i,mod(j,angulos)+1,angulos)) = 1/(radAct^2*deltaAng^2);
        A(idx(i,j,angulos),idx(i,auxj1,angulos)) = 1/(radAct^2*deltaAng^2);
        A(idx(i,j,angulos),idx(i-1,j,angulos)) = 1/(deltaRad^2)-1/(deltaRad*radAct);
        A(idx(i,j,angulos),idx(i+1,j,angulos)) = 1/(deltaRad^2);
    end
end

%%


% Armo el tiempo
tiempos = linspace(0,6*pi, 200);



for tie = 2:size(tiempos,2)-1
    %armado de b 
    b = zeros(puntos,1);
    b(1:angulos) = 1500;
    
    %Adentro y afuera todo junto
    %{
    b(puntos+1-angulos:puntos) = 300+100*cos(tiempos(tie));
    %}
    
    % Soplete dando vueltas
    %{
    b(puntos+1-angulos:puntos) = 300+100*cos(tiempos(tie)+linspace(0,2*pi,angulos));
    %}
    
    % Girando    
    
    aux = linspace(0,2*pi,angulos);
    for ang = 1:angulos
        if rem(ang,8)<=4
            b(puntos+ang-angulos) = 300+200*cos(tiempos(tie)+aux(ang));
        else
            b(puntos+ang-angulos) = 300-200*cos(tiempos(tie)+aux(ang));
        end
    end
    %}
    
    
    % Adentro y afuera alternado
    %{
    for ang = 1:angulos
        if rem(ang,8)<=4
            b(puntos+ang-angulos) = 300+200*cos(tiempos(tie));
        else
            b(puntos+ang-angulos) = 300-200*cos(tiempos(tie));
        end
    end
    %}
    
    %Random
    %{
    b(puntos+1-angulos:puntos) = 500*rand(angulos,1);
    %}
    
    

       
    
    
    % Rellenar la resolucion del sistema mediante Jacobi    
    tic
    x = jacobi(A,b,(1:size(A,2))');
    toc
    %}
    
    % Rellenar la resolucion del sistema mediante Gauss-Seidel
    tic
    x = gausssei(A,b,(1:size(A,2))');
    toc
    %}
    






   



    %Esta seccion plotea el calor dentro de todo el horno
    xdib = zeros(puntos,1);
    ydib = zeros(puntos,1);

    pis = linspace(0,2*pi,angulos+1);
    pis = pis(1:angulos);

    for i=1:radios
        radAct = radioi + deltaRad*(i-1); 
        for j=1:angulos
           xdib(idx(i,j,angulos)) = cos(pis(j))*radAct;
           ydib(idx(i,j,angulos)) = sin(pis(j))*radAct;
        end
    end

    xdib = reshape(xdib,angulos,radios);
    xdib(angulos+1,:) = xdib(1,:);
    ydib = reshape(ydib,angulos,radios);
    ydib(angulos+1,:) = ydib(1,:);
    x = reshape(x,angulos,radios);
    x(angulos+1,:) = x(1,:);
    h = pcolor(xdib,ydib,x);
    set(h, 'EdgeColor', 'none');
 

    %Esta seccion plotea solo la isoterma
    radioiso=zeros(1,angulos+1);
    for i = 1:angulos
       for j = 1:radios-1
          if x(i,j)>=caloriso && x(i,j+1)<caloriso
            pendiente = (x(i,j+1)-x(i,j))/(deltaRad);
            ordenada = x(i,j)-pendiente*(radioi+(j-1)*deltaRad);
            radioiso(i) = (caloriso-ordenada)/pendiente;
          end
       end
    end
    radioiso(angulos+1) = radioiso(1);


    theta=linspace(0,2*pi,angulos+1);
    interno=linspace(radioi,radioi,angulos+1);
    externo=linspace(radioe,radioe,angulos+1);
    polar(theta,externo), hold on;
    polar(theta,radioiso);
    polar(theta,interno);
    hold off;
    pause(0.1);
end