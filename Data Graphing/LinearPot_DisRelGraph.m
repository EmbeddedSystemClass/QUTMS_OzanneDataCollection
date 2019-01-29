% Obtain linear potentiometer's relation variables.
[x1, Intercept, Rsquared] = LinearPot_DistanceRelation();

% Plot Graph
plot(Reading_Relation);
ylim([0 90]);
title('Linear Potentiometer Reading Value to Distance Relation');
xlabel('Arduino Value');
ylabel('Actual Distance');

% Place equations on graph.
String_Equation = "y = " + string(x1) + " + " + string(Intercept) + "x";
String_Rsquared = "R^2 = " + string(Rsquared);
text(250,80,String_Equation);
text(250,74,String_Rsquared);