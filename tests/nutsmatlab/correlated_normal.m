function [logp grad] = correlated_normal(theta)
% function [logp grad] = correlated_normal(theta)
% 
% Example of a target distribution that could be sampled from using NUTS.
% (Although of course you could sample from it more efficiently using
% mvnrnd.) Doesn't include the normalizing constant.

% Precision matrix with covariance [1, 1.98; 1.98, 4].
A = [50.251256, -24.874372; -24.874372, 12.562814];
% A = inv([1, 1.98; 1.98, 4]);

grad = -theta * A;
logp = 0.5 * grad * theta';
