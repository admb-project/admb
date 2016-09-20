% Script showing how to run hmc_da and nuts_da on a 2-d strongly correlated
% normal distribution. 
% 
% Because of the relatively high overhead associated with recursion in Matlab
% and the very low cost of evaluating gradients and likelihoods for the
% 2-d normal, NUTS adds an appreciable amount of overhead for this example.
% This overhead becomes negligible if evaluating gradients and
% likelihoods takes more than a few milliseconds.

% Copyright (c) 2011, Matthew D. Hoffman
% All rights reserved.
% 
% Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
% 
% Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
% Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

D = 2;

temp = mvnrnd(zeros(1, 2), [1, 1.98; 1.98, 4], 500);
plot(temp(:, 1), temp(:, 2), '.m');

fprintf('Running HMC with dual averaging and trajectory length 0.2...\n');
tic;
[samples epsilon] = hmc_da(@correlated_normal, 5000, 5000, randn(1, D), 0.2);
samples = samples(1:10:end, :);
fprintf('Done. Final epsilon = %f. Took %f seconds.\n', epsilon, toc);
hold on;
plot(samples(:, 1), samples(:, 2), 'y.');
hold off;
mu = mean(samples)
stddev = sqrt(mean(samples.^2))
correlations = corr(samples)

fprintf('Running HMC with dual averaging and trajectory length 2...\n');
tic;
[samples epsilon] = hmc_da(@correlated_normal, 500, 500, randn(1, D), 2);
fprintf('Done. Final epsilon = %f. Took %f seconds.\n', epsilon, toc);
hold on;
plot(samples(:, 1), samples(:, 2), 'b.');
hold off;
mu = mean(samples)
stddev = sqrt(mean(samples.^2))
correlations = corr(samples)

fprintf('Running NUTS with dual averaging...\n');
tic;
[samples epsilon] = nuts_da(@correlated_normal, 500, 500, randn(1, D));
fprintf('Done. Final epsilon = %f. Took %f seconds.\n', epsilon, toc);
hold on;
plot(samples(:, 1), samples(:, 2), 'k.');
hold off;
mu = mean(samples)
stddev = sqrt(mean(samples.^2))
correlations = corr(samples)
