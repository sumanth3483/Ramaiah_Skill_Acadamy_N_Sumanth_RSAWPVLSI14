%  initial conditions
initial_velocity = 50; % in m/s
launch_angle = 45; % in degrees
g = 9.81; % gravitational acceleration in m/s^2

% Convert launch angle to radians
launch_angle_rad = deg2rad(launch_angle);

% Calculate initial velocity components
vx = initial_velocity * cos(launch_angle_rad);
vy = initial_velocity * sin(launch_angle_rad);

% Time of flight
t_flight = 2 * vy / g;

% Time vector
t = linspace(0, t_flight, 100);

% Trajectory equations
x = vx * t;
y = vy * t - 0.5 * g * t.^2;

% Plot trajectory
figure;
plot(x, y);
title('Projectile Trajectory');
xlabel('Range (m)');
ylabel('Height (m)');
grid on;

% Calculate and plot range and max height
range = vx * t_flight;
max_height = (vy^2) / (2 * g);

hold on;
plot([range, range], [0, max_height], 'r--');
plot([0, range], [max_height, max_height], 'g--');
legend('Trajectory', 'Range', 'Max Height');
hold off;

% Display range and max height
fprintf('Range: %.2f meters\n', range);
fprintf('Max Height: %.2f meters\n', max_height);