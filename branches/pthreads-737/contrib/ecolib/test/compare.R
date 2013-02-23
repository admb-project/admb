r_results=scan("results_from_R.txt")
ADMB_results=scan("results_from_ADMB.txt", nmax=length(r_results))

r_results[which.max(abs((r_results- ADMB_results)/r_results))]
ADMB_results[which.max(abs((r_results- ADMB_results)/r_results))]

