
% Dans ce démo
% - Calcul du volume de coût
% - Agrégation (diff sols)
% - Estimation de disparité (winner-takes-all)

G = imread('im2.bmp');
D = imread('im6.bmp');
GT=imread('disp2.bmp');
mindisp = 0; 
maxdisp = 64;

figure; imshow(G); title('Image gauche');
figure; imshow(D); title('Image droite');
figure; imshow(GT); title('La verité terrain');
figure;
imshowpair(G, D,'montage');
figure; imshow(stereoAnaglyph(rgb2gray(G),rgb2gray(D)));
%% Calcul du coût
[CoutG, CoutD] = calculate_cost(G, D, mindisp, maxdisp);
figure; disp = 5 ; imshow(CoutG(:,:,disp), []); title('Le coût pour une disparité donné');


%% winner-takes-all
[DispG] = winner_takes_all(CoutG);
DispG = DispG + mindisp;
figure, imshow(DispG, [mindisp maxdisp]); 
title(['Disparité gauche estimée sans agrégation des coûts : ']);


%% Agrégation sur block
R = 5; % Rayon
CoutGa = aggregate_cost_block(CoutG, R);
[DispGa] = winner_takes_all(CoutGa);
DispGa = DispGa + mindisp;
figure, imshow(DispGa, [mindisp maxdisp]);
title(['Disparité gauche estimée avec agrégation – block centré de rayon R : ' ]);


%% Agrégation gaussienne 
R=5; %Rayon
S=2; %Sigma
CoutGb = aggregate_cost_gauss(CoutG, R, S);
[DispGb] = winner_takes_all(CoutGb);
DispGb = DispGb + mindisp;
figure, imshow(DispGb, [mindisp maxdisp]); 
title(['Disparité estimée avec agrégation gaussienne aggregation']);

