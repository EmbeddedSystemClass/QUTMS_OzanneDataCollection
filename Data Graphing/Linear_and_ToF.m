%% CSV Import
% Read data from the CSV file.
CSV_Data = csvread('Linear and ToF Data.csv',1,0);

% Place data in individual arrays.
Cal_Linear = CSV_Data(:,1);
Cal_ToF = CSV_Data(:,2);
Run1_Linear = CSV_Data(:,3);
Run1_ToF = CSV_Data(:,4);
Run2_Linear = CSV_Data(:,5);
Run2_ToF = CSV_Data(:,6);

% Clear original CSV data array.
clear CSV_Data

%% Calculate other statistical data.
% Obtain linear potentiometer's relation variables.
[x1, Intercept, Rsquared] = LinearPot_DistanceRelation();

Cal_Linear_Median = median(Cal_Linear);
Cal_Linear_mm = x1 * Cal_Linear + Intercept;
Cal_Linear_mm_Diff = diff(Cal_Linear_mm);
Cal_Linear_mm_Median = median(Cal_Linear_mm);
Cal_Linear_mm_MedianDiff = median(Cal_Linear_mm_Diff);
Cal_ToF_Diff = diff(Cal_ToF);
Cal_ToF_Median = median(Cal_ToF);
Cal_ToF_MedianDiff = diff(Cal_ToF_Median);
Cal_ToF_MeanDiff = mean(Cal_ToF_Diff);

Run1_Linear_mm = x1 * Run1_Linear + Intercept;
Run1_Linear_mm_Diff = diff(Run1_Linear_mm);
Run1_Linear_mm_MaxDiff = max(Run1_Linear_mm_Diff);
Run1_ToF_Diff = diff(Run1_ToF);
Run1_ToF_MaxDiff = max(Run1_ToF_Diff);

Run2_Linear_mm = x1 * Run2_Linear + Intercept;
Run2_Linear_mm_Diff = diff(Run2_Linear_mm);
Run2_Linear_mm_MaxDiff = max(Run2_Linear_mm_Diff);
Run2_ToF_Diff = diff(Run2_ToF);
Run2_ToF_MaxDiff = max(Run2_ToF_Diff);

%% Graphs
% Calibration Linear Diff
figure
plot(Cal_Linear_mm_Diff);
title('Calibration Linear Diff (mm)')

% Calibration ToF Diff
figure
plot(Cal_ToF_Diff);
title('Calibration ToF Diff (mm)');

% Run 1 Linear Diff
figure
plot(Run1_Linear_mm_Diff);
title('Run 1 Linear Diff (mm)');

% Run 1 ToF Diff
figure
plot(Run1_ToF_Diff);
title('Run 1 ToF Diff (mm)');

% Run 2 Linear Diff
figure
plot(Run2_Linear_mm_Diff);
title('Run 2 Linear Diff (mm)');

% Run 2 ToF Diff
figure
plot(Run2_ToF_Diff);
title('Run 2 ToF Diff (mm)');