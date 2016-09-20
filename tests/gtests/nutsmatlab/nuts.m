function samples = nuts(epsilon, f, M, theta0)
% function samples = nuts(epsilon, f, M, theta0)
% 
% Implements the No-U-Turn Sampler (NUTS), specifically, algorithm 3
% from the NUTS paper (Hoffman & Gelman, 2011). 
% 
% This algorithm requires that you specify a step size parameter epsilon---try
% nuts_da() if you want to avoid tuning epsilon.
% 
% epsilon is a step size parameter.
% f(theta) should be a function that returns the log probability its
% gradient evaluated at theta. I.e., you should be able to call 
% [logp grad] = f(theta).
% M is the number of samples to generate.
% theta0 is a 1-by-D vector with the desired initial setting of the parameters.
% 
% The returned variable "samples" is an M-by-D matrix of samples generated
% by NUTS. samples(1, :) = theta0.

% Copyright (c) 2011-2012, Matthew D. Hoffman
% All rights reserved.
% 
% Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
% 
% Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
% Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

assert(size(theta0, 1) == 1);

D = length(theta0);
samples = zeros(M, D);

[logp grad] = f(theta0);
samples(1, :) = theta0;

for m = 2:M,
    % Resample momenta.
    r0 = randn(1, D);
    % Joint log-probability of theta and momenta r.
    joint = logp - 0.5 * (r0 * r0');
    % Resample u ~ uniform([0, exp(joint)]).
    % Equivalent to (log(u) - joint) ~ exponential(1).
    logu = joint - exprnd(1);
    % Initialize tree.
    thetaminus = samples(m-1, :);
    thetaplus = samples(m-1, :);
    rminus = r0;
    rplus = r0;
    gradminus = grad;
    gradplus = grad;
    % Initial height j = 0.
    j = 0;
    % If all else fails, the next sample is the previous sample.
    samples(m, :) = samples(m-1, :);
    % Initially the only valid point is the initial point.
    n = 1;

    % Main loop---keep going until the criterion s == 0.
    s = 1;
    while (s == 1)
        % Choose a direction. -1=backwards, 1=forwards.
        v = 2*(rand() < 0.5)-1;
        % Double the size of the tree.
        if (v == -1)
            [thetaminus, rminus, gradminus, ~, ~, ~, thetaprime, gradprime, logpprime, nprime, sprime] = ...
                build_tree(thetaminus, rminus, gradminus, logu, v, j, epsilon, f);
        else
            [~, ~, ~, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime] = ...
                build_tree(thetaplus, rplus, gradplus, logu, v, j, epsilon, f);
        end
        % Use Metropolis-Hastings to decide whether or not to move to a
        % point from the half-tree we just generated.
        if ((sprime == 1) && (rand() < nprime/n))
            samples(m, :) = thetaprime;
            logp = logpprime;
            grad = gradprime;
        end
        % Update number of valid points we've seen.
        n = n + nprime;
        % Decide if it's time to stop.
        s = sprime && stop_criterion(thetaminus, thetaplus, rminus, rplus);
        % Increment depth.
        j = j + 1;
    end
end

function [thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, epsilon, f)
rprime = r + 0.5 * epsilon * grad;
thetaprime = theta + epsilon * rprime;
[logpprime, gradprime] = f(thetaprime);
rprime = rprime + 0.5 * epsilon * gradprime;

function criterion = stop_criterion(thetaminus, thetaplus, rminus, rplus)
thetavec = thetaplus - thetaminus;
criterion = (thetavec * rminus' >= 0) && (thetavec * rplus' >= 0);

% The main recursion.
function [thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime] = ...
                build_tree(theta, r, grad, logu, v, j, epsilon, f)
if (j == 0)
    % Base case: Take a single leapfrog step in the direction v.
    [thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, v*epsilon, f);
    joint = logpprime - 0.5 * (rprime * rprime');
    % Is the new point in the slice?
    nprime = logu < joint;
    % Is the simulation wildly inaccurate?
    sprime = logu - 1000 < joint;
    % Set the return values---minus=plus for all things here, since the
    % "tree" is of depth 0.
    thetaminus = thetaprime;
    thetaplus = thetaprime;
    rminus = rprime;
    rplus = rprime;
    gradminus = gradprime;
    gradplus = gradprime;
else
    % Recursion: Implicitly build the height j-1 left and right subtrees.
    [thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime] = ...
                build_tree(theta, r, grad, logu, v, j-1, epsilon, f);
    % No need to keep going if the stopping criteria were met in the first
    % subtree.
    if (sprime == 1)
        if (v == -1)
            [thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2] = ...
                build_tree(thetaminus, rminus, gradminus, logu, v, j-1, epsilon, f);
        else
            [~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2] = ...
                build_tree(thetaplus, rplus, gradplus, logu, v, j-1, epsilon, f);
        end
        % Choose which subtree to propagate a sample up from.
        if (rand() < nprime2 / (nprime + nprime2))
            thetaprime = thetaprime2;
            gradprime = gradprime2;
            logpprime = logpprime2;
        end
        % Update the number of valid points.
        nprime = nprime + nprime2;
        % Update the stopping criterion.
        sprime = sprime && sprime2 && stop_criterion(thetaminus, thetaplus, rminus, rplus);
    end
end











