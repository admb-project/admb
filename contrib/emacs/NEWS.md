# ADMB Mode 13.2.0 (2026-03-09)

* Updated links in documentation.




# ADMB Mode 12.1-0 (2020-01-19)

* Improved `admb-clean` so it deletes "hesscheck" and "*.rhes".




# ADMB Mode 12.0-1 (2018-02-06)

* Maintenance release for Emacs 26.0.




# ADMB Mode 12.0-0 (2018-01-22)

* Bound M-up and M-down to `admb-scroll-up` and `admb-scroll-down`.




# ADMB Mode 11.5-0 (2016-06-24)

* Changed `admb-clean` to keep .std file.




# ADMB Mode 11.2-6 (2015-09-29)

* Simplified customization group.




# ADMB Mode 11.2-5 (2015-09-18)

* Removed user function `admb-new-buffer`.

* Simplified `admb-tool-bar-map`.

* Improved tab keybinding.




# ADMB Mode 11.2-4 (2015-09-08)

* Formatted code in 80 columns.




# ADMB Mode 11.2-3 (2015-09-08)

* Minor update before formatting code in 80 columns.




# ADMB Mode 11.2-2 (2015-08-17)

* Improved `admb-template`.

* Simplified `admb-run-args`.

* Removed explicit definition of `admb-mode-hook`.




# ADMB Mode 11.2-1 (2015-07-13)

* Added keywords "restore_dvar_vector_derivatives",
  "restore_dvar_matrix_derivatives", and "save_dvar_matrix_value".




# ADMB Mode 11.2-0 (2015-01-12)

* Adapted to new compilation flags (-f instead of -s, no more tpl2xxx -bounds).

* New version numbering system, to avoid confusion with old ADMB versions.




# ADMB Mode 8.1 (2013-12-06)

* Improved highlighing of function names.




# ADMB Mode 8.0 (2013-07-09)

* Rewritten using `define-derived-mode`.

* Defined internal variable `admb-mode-abbrev-table` implicitly.




# ADMB Mode 7.4 (2013-07-09)

* Minor update before experimenting with `define-derived-mode`; as of Emacs 24.1
  (see NEWS) all programming modes should be derived from `prog-mode`.




# ADMB Mode 7.3 (2013-06-23)

* Adapted `admb-template` and `admb-template-mini` to ADMB version 11, using PI
  and sumsq().




# ADMB Mode 7.2 (2013-02-22)

* Added GUI menu item for `admb-kill-process`.

* Added keyword "random_effects_number".




# ADMB Mode 7.1 (2013-01-19)

* Added keywords "df1b2matrix", "df1b2variable", and "df1b2vector".




# ADMB Mode 7.0 (2012-04-09)

* Added user function `admb-kill-process`, bound to C-c C-q.




# ADMB Mode 6.10 (2012-03-29)

* Improved keybindings on remote terminals.




# ADMB Mode 6.9 (2012-03-17)

* Improved `admb-for`.

* Added Fournier et al. (2012) reference.




# ADMB Mode 6.8 (2012-02-29)

* Improved `admb-template` and `admb-template-mini`.




# ADMB Mode 6.7 (2012-01-12)

* Improved `admb-open`.




# ADMB Mode 6.6 (2011-10-01)

* Added keywords "PI" and "sumsq".

* Made all keywords case-sensitive.

* Minor changes in `admb-template` and `admb-template-mini`.




# ADMB Mode 6.5 (2011-08-31)

* Improved documentation.




# ADMB Mode 6.4 (2011-03-01)

* Added issue regarding XEmacs.




# ADMB Mode 6.3 (2011-02-19)

* Added keywords "streampos" and "#undef".




# ADMB Mode 6.2 (2011-02-17)

* Added internal function `admb-send`, improving `admb-build`, `admb-compile`,
  `admb-link`, `admb-run-makefile`, and `admb-tpl2cpp`.

* Added keywords "prevariable_position", "restore_prevariable_derivative",
  "restore_prevariable_position", "restore_prevariable_value",
  "save_double_derivative", "save_prevariable_position", and
  "save_prevariable_value".

* Added GUI menu item for `admb-open`.




# ADMB Mode 6.1 (2010-12-01)

* Added keywords "allocate", "clock", "ctime", "difftime",
  "set_covariance_matrix", "strftime", "time", "time_t", and
  "vcubic_spline_function".




# ADMB Mode 6.0 (2010-10-10)

* Added user function `admb-toggle-flag`.

* Removed user function `admb-set-flags`.

* Rebound C-c C-- and restructured GUI menu accordingly.




# ADMB Mode 5.1 (2010-10-01)

* Improved documentation.




# ADMB Mode 5.0 (2010-09-20)

* Added user function `admb-open`.

* Improved `admb-cor`, `admb-cpp`, `admb-par`, `admb-pin`, and `admb-rep` so
  that files are opened in secondary window.

* Changed section highlighting to new `admb-section-face`.

* Bound C-c C-o to `admb-open` and C-c C-r to `admb-rep`.




# ADMB Mode 4.8 (2010-07-14)

* Added internal function `admb-split-window`.




# ADMB Mode 4.7 (2010-07-08)

* Improved documentation.




# ADMB Mode 4.6 (2010-06-28)

* Renamed `admb-version` to `admb-mode-version`.

* Unbound C-return and S-return.




# ADMB Mode 4.5 (2010-06-16)

* Added keywords "diagonal", "dvar4_array", "dvar5_array", "dvar6_array",
  "dvar7_array", "d4_array", "d5_array", "d6_array", "d7_array", "factln",
  "first_difference", "gamma_density", "log_gamma_density", and "sgamma".

* Improved highlighting of comments.




# ADMB Mode 4.4 (2010-05-20)

* Improved user functions `admb-build`, `admb-compile`, `admb-link`, `admb-par`,
  `admb-pin`, `admb-rep`, `admb-run`, `admb-run-args`, `admb-run-makefile`, and
  `admb-tpl2cpp`.

* Added keybinding and GUI menu item for `admb-version`.




# ADMB Mode 4.3 (2010-04-23)

* Improved `admb-run-args` and `admb-template`.

* Added constant `admb-version`.

* Added user function `admb-version`.

* Added keyword "cube".

* Added Emacs Lisp ;;;###autoload cookie.




# ADMB Mode 4.2 (2010-03-19)

* Changed user function `admb-rep` so .rep file is opened with Emacs rather than
  external browser.

* Renamed old function `admb-rep-browser`.




# ADMB Mode 4.1 (2010-03-16)

* Improved `admb-run-args` so it suggests same args as user passed last time.

* Improved documentation.




# ADMB Mode 4.0 (2010-03-14)

* Added user functions `admb-par` and `admb-pin`.

* Added keywords "#define", "adstring_array", "c_str", "change_datafile_name",
  "change_pinfile_name", "empty", "erase", "find", "find_first_of",
  "find_last_of", "global_datafile", "insert", "length", "line_adstring",
  "nvarcalc", "replace", "rfind", "set_ARRAY_MEMBLOCK_SIZE",
  "set_CMPDIF_BUFFER_SIZE", "set_GRADSTACK_BUFFER_SIZE", "set_MAX_DLINKS",
  "set_MAX_NVAR_OFFSET", "set_NUM_DEPENDENT_VARIABLES", "set_NUM_RETURN_ARRAYS",
  "set_RETURN_ARRAYS_SIZE", "showpoint", "strchr", "strcmp", "strcspn",
  "string", "strncat", "strncmp", "strncpy", "strpbrk", "strrchr", "strspn",
  "strstr", "strtok", "substr", and "using".

* Removed keywords "ad_comm", "argc", "argv", "gradient_structure", "ios", and
  "report".

* Added highlighting of libraries and namespaces.

* Improved highlighting of function names.

* Improved `admb-template`.




# ADMB Mode 3.8 (2009-10-26)

* Rolled back to version 3.6, due to syntax highlighting problems.

* Added issue regarding underscores.




# ADMB Mode 3.7 (2009-10-23)

* Improved cursor motion inside underscore_separated_words.




# ADMB Mode 3.6 (2009-09-30)

* Improved syntax highlighting of function names.




# ADMB Mode 3.5 (2009-09-14)

* Added user function `admb-toggle-section`.

* Improved syntax highlighting of function names.

* Added issue regarding indentation.




# ADMB Mode 3.4 (2009-07-07)

* Improved user functions `admb-run` and `admb-run-args` so Emacs doesn't hang
  up while model runs and optimization progress is reported live.

* Shuffled GUI menu order.




# ADMB Mode 3.3 (2009-06-03)

* Added current directory to local PATH in Linux.




# ADMB Mode 3.2 (2009-06-01)

* Improved filename handling of `admb-cpp`, `admb-cor`, `admb-run`, and
  `admb-run-args`.




# ADMB Mode 3.1 (2009-05-27)

* Improved documentation.




# ADMB Mode 3.0 (2009-05-24)

* Added user variables `admb-init` and `admb-run-makefile-command`.

* Renamed user variable `admb-make-command` to `admb-build-command`.

* Redefined user variable `admb-tpl2cpp-command` as internal variable.

* Added user functions `admb-cor`, `admb-help`, `admb-new-buffer`,
  `admb-run-makefile`, `admb-set-flags`, and `admb-toggle-window`.

* Renamed user function `admb-make` to `admb-build`.

* Improved user function `admb-rep` so it checks if report file exists.

* Improved user function `admb-tpl2cpp` to support `admb-init` and
  `admb-tpl2cpp-flags`.

* Improved user functions `admb-build`, `admb-compile`, and `admb-link` to
  support `admb-init` and `admb-flags`.

* Improved screen output from `admb-run` and `admb-run-args`.

* Added internal variables `admb-flags`, `admb-menu`, `admb-tool-bar-map`, and
  `admb-tpl2cpp-flags`.

* Added local variable `tool-bar-map`.

* Added keywords "#elif", "#else", "#endif", "#if", "#ifdef", "#ifndef",
  "defined" "dll_3darray", "dll_adstring", "dll_imatrix", "dll_init_3darray",
  "dll_init_bounded_number", "dll_init_bounded_vector", "dll_init_imatrix",
  "dll_init_int", "dll_init_matrix", "dll_init_number", "dll_init_vector",
  "dll_int", "dll_matrix", "dll_number", "dll_vector", "init_number_vector", and
  "log_negbinomial_density".

* Added GUI menu and toolbar icons.

* Adopted Simplified BSD License.




# ADMB Mode 2.5 (2009-04-08)

* Improved documentation strings of user variables and user functions.




# ADMB Mode 2.4 (2009-03-31)

* Improved screen output from user functions `admb-run` and `admb-run-args`.

* Improved indendation.




# ADMB Mode 2.3 (2009-03-27)

* Improved screen output from user functions `admb-run` and `admb-run-args`.




# ADMB Mode 2.2 (2009-03-22)

* Improved screen output from user functions `admb-run` and `admb-run-args`.




# ADMB Mode 2.1 (2009-03-20)

* Added user variable `admb-window-right`.

* Improved screen output from user functions `admb-compile`, `admb-link`,
  `admb-make`, `admb-run`, `admb-run-args`, and `admb-tpl2cpp`.

* Improved user function `admb-make` so it saves buffer before calling
  `admb-make-command`.

* Added keyword "randnegbinomial".




# ADMB Mode 2.0 (2009-03-09)

* Complete rewrite.

* Added user variables `admb-comp-command`, `admb-link-command`,
  `admb-make-command`, and `admb-tpl2cpp-command`.

* Added user functions `admb-clean`, `admb-compile`, `admb-cpp`, `admb-endl`,
  `admb-for`, `admb-link`, `admb-make`, `admb-rep`, `admb-run`, `admb-run-args`,
  and `admb-tpl2cpp`.

* Added internal variables `admb-font-lock-keywords`, `admb-mode-abbrev-table`,
  `admb-mode-map`, and `admb-mode-syntax-table`.

* Added local variables `comment-start`, `imenu-generic-expression`,
  `indent-line-function`, and `outline-regexp`.

* Added keywords "4darray", "5darray", "6darray", "7darray", "bool",
  "init_4darray", "init_5darray", "init_6darray", "init_7darray",
  "normal_prior", "NORMAL_PRIOR_FUNCTION", "random_effects_bounded_matrix",
  "random_effects_bounded_vector", and "sizeof".

* Added commentary on installation, customization, and usage.




# ADMB Mode 1.4 (2009-09-28)

* Added keyword "close", changed face names, and released to ADMB Project.




# ADMB Mode 1.3 (2008-12-11)

* Added keyword "SEPARABLE_FUNCTION".




# ADMB Mode 1.2 (2008-11-28)

* Added keywords "LOC_CALCS", "random_effects_vector", and
  "random_effects_matrix".




# ADMB Mode 1.1 (2008-07-23)

* Added user function `admb-outline`.




# ADMB Mode 1.0 (2007-09-25)

* Added user functions `admb-template` and `admb-template-mini`.




# ADMB Mode 0.9 (2003-08-26)

* Created main function `admb-mode`, user variable `admb-mode-hook`, and local
  variable `font-lock-defaults`.
