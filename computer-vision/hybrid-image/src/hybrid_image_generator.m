clc;
clear;

axe1=imread ('dog.tif');
lowf = fspecial('gaussian', 70, 8);

axe2=imread ('cat.tif');
low2 = fspecial('gaussian', 28, 400);

low1=imfilter(axe1,lowf);

high2=axe2-imfilter(axe2,low2);

hybrid=low1+high2;
imshow(hybrid);
