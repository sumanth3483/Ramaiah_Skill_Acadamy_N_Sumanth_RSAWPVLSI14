% Number of random numbers
n = 100;

% Generate random numbers
random_numbers = rand(1, n);

% Plot the random numbers
figure;
plot(random_numbers);
title('Random Numbers Line Graph');
xlabel('Index');
ylabel('Random Number');
grid on;
