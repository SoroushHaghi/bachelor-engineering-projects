clc;
clear;
clear all;
close all;

filePath = 'E:\\file.wav';

chunkSize = 44100;

[data, fs] = audioread(filePath);

if size(data, 2) ~= 2
    error('The audio must be in stereo format.');
end

numChunks = floor(size(data, 1) / chunkSize);

for i = 1:numChunks
    startIndex = (i - 1) * chunkSize + 1;
    endIndex = i * chunkSize;
    chunkData = data(startIndex:endIndex, :);

    leftChannel = chunkData(:, 1);
    rightChannel = chunkData(:, 2);

    leftEnergy = sqrt(mean(leftChannel .^ 2));
    rightEnergy = sqrt(mean(rightChannel .^ 2));

    if leftEnergy > rightEnergy
        direction = 'Left';
    else
        direction = 'Right';
    end

    disp(['In the current 1-second interval: ' direction]);
    pause(1);
end
