NAME=pella_t

all:
	$(MAKE) clean
	$(MAKE) $(NAME)
	$(MAKE) run

pella_t:
	../../admb pella_t

run:
	echo -1.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_none.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_none.par

	echo 1.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_1.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_1.par

	echo 10.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_10.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_10.par

	echo 100.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_100.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_100.par

	echo 1000.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_1000.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_1000.par

	echo 10000.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_10000.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_10000.par

	echo 100000.0 > penalty.dat
	./$(NAME)
	mv $(NAME).par $(NAME)_penalty_100000.par
	./$(NAME) -mcmc 1000 -mcsave 100 && ./$(NAME) -mceval
	mv $(NAME).par $(NAME)_mcmc_penalty_100000.par

plot:
	$(MAKE) plot_variances

plot_variances:
	python plot_variances.py ../../examples/admb/pella_t/pella_t.par pella_t_mcmc_penalty_1.par pella_t_mcmc_penalty_10.par pella_t_mcmc_penalty_100.par pella_t_mcmc_penalty_1000.par pella_t_mcmc_penalty_10000.par pella_t_mcmc_penalty_100000.par pella_t_mcmc_penalty_none.par pella_t_penalty_1.par pella_t_penalty_10.par pella_t_penalty_100.par pella_t_penalty_1000.par pella_t_penalty_10000.par pella_t_penalty_100000.par pella_t_penalty_none.par

clean:
	@rm -vf penalty.dat
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf $(NAME)
	@rm -vf $(NAME).b01
	@rm -vf $(NAME).b02
	@rm -vf $(NAME).b03
	@rm -vf $(NAME).bar
	@rm -vf $(NAME).cor
	@rm -vf $(NAME).cpp
	@rm -vf $(NAME).ecm
	@rm -vf $(NAME).eva
	@rm -vf $(NAME).hst
	@rm -vf $(NAME).htp
	@rm -vf $(NAME).log
	@rm -vf $(NAME).mc2
	@rm -vf $(NAME).mcm
	@rm -vf $(NAME).obj
	@rm -vf $(NAME).p01
	@rm -vf $(NAME).p02
	@rm -vf $(NAME).p03
	@rm -vf $(NAME).par
	@rm -vf $(NAME)_penalty_none.par
	@rm -vf $(NAME)_penalty_1.par
	@rm -vf $(NAME)_penalty_10.par
	@rm -vf $(NAME)_penalty_100.par
	@rm -vf $(NAME)_penalty_1000.par
	@rm -vf $(NAME)_penalty_10000.par
	@rm -vf $(NAME)_penalty_100000.par
	@rm -vf $(NAME)_mcmc_penalty_none.par
	@rm -vf $(NAME)_mcmc_penalty_1.par
	@rm -vf $(NAME)_mcmc_penalty_10.par
	@rm -vf $(NAME)_mcmc_penalty_100.par
	@rm -vf $(NAME)_mcmc_penalty_1000.par
	@rm -vf $(NAME)_mcmc_penalty_10000.par
	@rm -vf $(NAME)_mcmc_penalty_100000.par
	@rm -vf $(NAME).std
	@rm -vf $(NAME).psv
	@rm -vf sims
