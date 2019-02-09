function [x1, Intercept, Rsquared] = LinearPot_DistanceRelation()
    %% CSV Import
    % Read data from the CSV file.
    CSV_Data = csvread('Linear Potentiometer.csv',1,0);

    % Place data in individual arrays.
    Arduino_Value = CSV_Data(:,1);
    Actual_Distance = CSV_Data(:,2);

    % Clear original CSV data array.
    clear CSV_Data

    %% Calculate Relation
    Reading_Relation = fitlm(Arduino_Value,Actual_Distance);
    x1 = Reading_Relation.Coefficients{2,1};
    Intercept = Reading_Relation.Coefficients{1,1};
    Rsquared = Reading_Relation.Rsquared.Ordinary;
end