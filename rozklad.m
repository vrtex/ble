function [ output ] = rozklad( input, eps )
output = input;
check = 1;
while check == 1
    for y = 2:size(input, 1) - 1
        for x = 2:size(input, 2) -1
            output(y, x) = (output(y - 1, x) + output(y, x - 1) + input(y + 1, x) + input(y, x + 1)) / 4;
        end
    end
    if abs(input - output) < eps
        check = 0;
    end
    input = output;
end
output = flip(input, 1);
contourf(output)
end