;;; admb.el --- Major mode for creating statistical models with AD Model Builder

;; Copyright (C) 2003-2020 Arni Magnusson

;; Author:   Arni Magnusson
;; Keywords: languages
;; URL:      https://github.com/admb-project/admb/blob/main/contrib/emacs

(defconst admb-mode-version "12.1-0" "ADMB Mode version number.")

;;; Commentary:
;;
;; Major mode for editing AD Model Builder (ADMB) code. Provides syntax
;; highlighting, IDE compilation and file manipulation, outline code navigation,
;; templates, and smaller tools. The syntax groups for highlighting are:
;;
;; Face                          Example
;; admb-section-face             DATA_SECTION
;; font-lock-builtin-face        objective_function_value
;; font-lock-comment-face        //
;; font-lock-constant-face       PI
;; font-lock-function-name-face  [FUNCTION] myfunction
;; font-lock-keyword-face        log
;; font-lock-type-face           int
;;
;; Installation:
;;
;; 1. Copy this file (admb.el) to a directory in `load-path', or edit .emacs to
;;    add the directory to `load-path':
;;      (add-to-list 'load-path "mypath/admb")
;; 2. Byte-compile this file to admb.elc for faster startup:
;;      M-x byte-compile-file
;; 3. Edit .emacs so that `admb-mode' is autoloaded and assigned to *.tpl files:
;;      (autoload 'admb-mode "admb" "Edit ADMB code." t)
;;      (add-to-list 'auto-mode-alist '("\\.tpl$" . admb-mode))
;; 4. If you're running an older Emacs (<=24.3) in MS Windows, add a line so
;;    *.tpl files are not treated as binary:
;;      (setq file-name-buffer-file-type-alist nil)
;; 5. You may want to assign a mode that recognizes #comments in *.dat files
;;    (perl-mode, conf-space-mode, or R-mode):
;;      (add-to-list 'auto-mode-alist '("\\.dat$" . conf-space-mode))
;;
;; Customization:
;;
;; If you want to set compilation commands, syntax colors, or keybindings, here
;; is an example that does that:
;; (defun my-admb-hook ()
;;   (setq admb-build-command "myadmb")
;;   (setq admb-comp-command "myadcomp")
;;   (setq admb-link-command "myadlink")
;;   (set-face-attribute 'font-lock-function-name-face nil :foreground "brown"
;;                       :weight 'bold)
;;   (local-set-key [f9] 'admb-build)
;;   (local-set-key [down-mouse-3] 'imenu))
;; (add-hook 'admb-mode-hook 'my-admb-hook)
;;
;; See also AD Studio (https://github.com/admb-project/adstudio) for special use
;; of `admb-mode'.
;;
;; Usage:
;;
;; See documentation of function `admb-mode'.
;;
;; References:
;;
;; Fournier, D. An introduction to AD Model Builder for use in nonlinear
;;   modeling and statistics.
;;   [http://admb-project.org/docs/manuals/]
;; Fournier, D. AUTODIF: A C++ array language extension with automatic
;;   differentiation for use in nonlinear modeling and statistics.
;;   [http://admb-project.org/docs/manuals/]
;; Fournier, D.A., H.J. Skaug, J. Ancheta, J. Ianelli, A. Magnusson, M.N.
;;   Maunder, A. Nielsen, and J. Sibert. 2012. AD Model Builder: Using automatic
;;   differentiation for statistical inference of highly parameterized complex
;;   nonlinear models. Optimization Methods and Software 27:233-249.
;; Magnusson, A. 2009. ADMB-IDE: Easy and efficient user interface. ADMB
;;   Foundation Newsletter 1(3):1-2. [http://admb-foundation.org/wp-content/
;;   uploads/Newsletter/ADMBNewsletterJuly2009.pdf]
;; Skaug, H. and D. Fournier. Random effects in AD Model Builder: ADMB-RE user
;;   guide. [http://admb-project.org/docs/manuals/]
;;
;; Known issues:
;;
;; Indendation is not very smart.
;; Cursor motion and deletions swallow entire underscore_separated_object_name,
;;   instead of pausing at each underscore.
;; Does not work in XEmacs, reportedly.

;;; History:
;;
;; See the NEWS file.

;;; Code:

;; 1  Preamble

(require 'outline)
(defgroup admb nil
  "Major mode for editing AD Model Builder code."
  :tag "ADMB" :group 'languages)
(if (not (string-match "windows" (prin1-to-string system-type)))
    (setenv "PATH" (concat ".:" (getenv "PATH"))))

;; 2  User variables

(defcustom admb-build-command "admb"
  "Shell command to build executable from TPL, using `admb-build'."
  :tag "Build" :type 'string)
(defcustom admb-comp-command "adcomp"
  "Shell command to compile C++ to object code, using `admb-compile'."
  :tag "Compile" :type 'string)
(defcustom admb-link-command "adlink"
  "Shell command to link object code to executable, using `admb-link'."
  :tag "Link" :type 'string)
(defcustom admb-init ""
  "String to prepend before ADMB compilation commands.\n
Pasted without space before `admb-build-command', `admb-tpl2cpp-command',
`admb-comp-command', and `admb-link-command', e.g. a shell script followed by a
command separator."
  :tag "Init" :type 'string)
(defcustom admb-run-makefile-command "make"
  "Shell command to run makefile, using `admb-run-makefile'."
  :tag "Makefile" :type 'string)
(defcustom admb-window-right t
  "Non-nil places secondary window on the right, nil places it below.\n
The secondary window shows compilation and model runs, among other things."
  :tag "Window right" :type 'boolean)
(defface admb-section-face '((t :weight bold))
  "Font Lock mode face used to highlight ADMB sections." :tag "Section")
(defvar admb-section-face 'admb-section-face
  "Face name to use for ADMB sections.")

;; 3  Internal variables

(defvar admb-flags ""
  "Compilation flags for `admb-build', `admb-compile', and `admb-link'.\n
Any combination of space-separated -d, -f, -g, and -r, specifying that the build
target should be a DLL, fast, a debug model, and/or an ADMB-RE model.\n
Use `admb-toggle-flag' to set `admb-flags', `admb-tpl2cpp-command', and
`admb-tpl2cpp-flags' simultaneously.")
(defvar admb-tpl2cpp-command "tpl2cpp"
  "Shell command to translate TPL to C++, using `admb-tpl2cpp'.\n
Use `admb-toggle-flag' to set `admb-flags', `admb-tpl2cpp-command', and
`admb-tpl2cpp-flags' simultaneously.")
(defvar admb-tpl2cpp-flags ""
  "Translation flags for `admb-tpl2cpp'.\n
Any combination of space-separated -bound and -dll, specifying that the build
target should be a DLL and/or in safe mode.\n
Use `admb-toggle-flag' to set `admb-flags', `admb-tpl2cpp-command', and
`admb-tpl2cpp-flags' simultaneously.")
(defvar admb-font-lock-keywords
  (eval-when-compile
    (let ((SECTIONS
           '("^DATA_SECTION" "^INITIALIZATION_SECTION" "^PARAMETER_SECTION"
             "^PRELIMINARY_CALCS_SECTION" "^PROCEDURE_SECTION" "^FUNCTION"
             "^SEPARABLE_FUNCTION" "^REPORT_SECTION" "^RUNTIME_SECTION"
             "^TOP_OF_MAIN_SECTION" "^GLOBALS_SECTION" "^BETWEEN_PHASES_SECTION"
             "^NORMAL_PRIOR_FUNCTION" "^FINAL_SECTION"))
          (CONSTANTS
           '("LOC_CALCS" "LOCAL_CALCS" "END_CALCS" "PI" "USER_CODE"))
          (DATATYPES
           '(;; C
             "time_t"
             ;; C++
             "bool" "char" "double" "int" "long" "signed" "streampos" "string"
             "unsigned" "void"
             ;; AUTODIF
             "_CONST" "CLASS" "dvariable" "dvar_vector" "dvar_matrix"
             "dvar3_array" "dvar4_array" "dvar5_array" "dvar6_array"
             "dvar7_array" "dvector" "dmatrix" "d3_array" "d4_array" "d5_array"
             "d6_array" "d7_array"
             ;; Plain variables
             "adstring" "adstring_array" "line_adstring" "ivector" "imatrix"
             "number" "vector" "matrix" "3darray" "4darray" "5darray" "6darray"
             "7darray" "dev_vector"
             ;; Input data and parameters
             "init_int" "init_ivector" "init_imatrix" "init_number"
             "init_vector" "init_number_vector" "init_matrix"
             "init_bounded_number" "init_bounded_vector" "init_bounded_matrix"
             "init_vector_vector" "init_matrix_vector"
             "init_bounded_number_vector" "init_bounded_vector_vector"
             "init_bounded_matrix_vector" "init_bounded_dev_vector"
             "init_3darray" "init_4darray" "init_5darray" "init_6darray"
             "init_7darray" "init_adstring"
             ;; Random effects
             "df1b2matrix" "df1b2variable" "df1b2vector" "normal_prior"
             "random_effects_number" "random_effects_vector"
             "random_effects_bounded_vector" "random_effects_matrix"
             "random_effects_bounded_matrix"
             ;; DLL variables
             "dll_int" "dll_imatrix" "dll_number" "dll_vector" "dll_matrix"
             "dll_3darray" "dll_adstring"
             ;; DLL data and parameters
             "dll_init_int" "dll_init_imatrix" "dll_init_number"
             "dll_init_vector" "dll_init_matrix" "dll_init_bounded_number"
             "dll_init_bounded_vector" "dll_init_3darray"
             ;; Special objects
             "banded_lower_triangular_dvar_matrix"
             "banded_symmetric_dvar_matrix" "constant_model_parameters"
             "dvar_vector_position" "dvar_matrix_position" "extern" "fmm"
             "funnel_dvariable" "independent_variables" "model_data"
             "model_parameters" "prevariable" "prevariable_position"
             "likeprof_number" "random_number_generator" "sdreport_number"
             "sdreport_vector" "sdreport_matrix" "variable_model_parameters"
             "vcubic_spline_function"))
          (FUNCTIONS
           '(;; C++
             "break" "case" "const" "default" "define" "if" "else" "for" "goto"
             "return" "sizeof" "switch" "using" "while"
             ;; C++ I/O
             "cerr" "cin" "cout" "endl" "setf" "setfixed" "setprecision"
             "setscientific" "setw" "showpoint"
             ;; C strings
             "atof" "atoi" "printf" "sprintf" "strcat" "strchr" "strcmp"
             "strcpy" "strcspn" "strlen" "strncat" "strncmp" "strncpy" "strpbrk"
             "strrchr" "strspn" "strstr" "strtok"
             ;; C++ strings
             "c_str" "empty" "erase" "find" "find_first_of" "find_last_of"
             "insert" "length" "replace" "rfind" "substr"
             ;; C time
             "clock" "ctime" "difftime" "strftime" "time"
             ;; AUTODIF
             "allocated" "nvarcalc" "set_covariance_matrix"
             ;; Basic math
             "abs" "ceil" "cube" "exp" "fabs" "factln" "first_difference"
             "floor" "gammln" "log" "log10" "log_comb" "mfexp" "modf" "posfun"
             "pow" "sfabs" "square" "sqrt"
             ;; Trigonometry
             "acos" "asin" "atan" "cos" "cosh" "sin" "sinh" "tan" "tanh"
             ;; Random variates and density
             "betai" "cumd_cauchy" "cumd_norm" "gamma_density" "inv_cumd_cauchy"
             "inv_cumd_norm" "log_gamma_density" "log_negbinomial_density"
             "randn" "randnegbinomial" "randpoisson" "randu" "sgamma"
             ;; Vectors and matrices, basics
             "colsum" "column" "elem_div" "elem_prod" "extract_column"
             "extract_row" "max" "mean" "min" "row" "rowsum" "size_count" "sort"
             "std_dev" "sum" "trans"
             ;; Vectors and matrices, linear algebra
             "choleski_decomp" "det" "diagonal" "eigenvalues" "eigenvectors"
             "empirical_covariance" "extract_diagonal" "identity_matrix" "inv"
             "ln_det" "norm" "norm2" "outer_prod" "regression"
             "robust_regression" "solve" "sumsq"
             ;; Dot methods
             "allocate" "fill" "fill_multinomial" "fill_seqadd" "fill_randbi"
             "fill_randn" "fill_randn_ni" "fill_randpoisson" "fill_randu"
             "fill_randu_ni" "indexmax" "indexmin" "initialize"
             ;; Dot methods, col*, row*, and slice*
             "colfill" "colfill_randn" "colfill_randu" "colfill_seqadd" "colmax"
             "colmin" "colshift" "colsize" "rowfill" "rowfill_randn"
             "rowfill_randu" "rowfill_seqadd" "rowmax" "rowmin" "rowshift"
             "rowsize" "slicemax" "slicemin" "sliceshift" "slicesize"
             ;; Phases
             "active" "current_phase" "initial_params" "last_phase"
             "mceval_phase" "sd_phase"
             ;; Adjoint code
             "AD_SET_DERIVATIVES" "AD_SET_DERIVATIVES2" "AD_SET_DERIVATIVES4"
             "ADJOINT_CODE" "elem" "elem_value" "restore_prevariable_derivative"
             "restore_prevariable_position" "restore_prevariable_value"
             "restore_dvar_vector_derivatives" "restore_dvar_vector_position"
             "restore_dvar_vector_value" "restore_dvar_matrix_derivatives"
             "restore_dvar_matrix_position" "restore_dvar_matrix_value"
             "save_double_derivative" "save_prevariable_position"
             "save_prevariable_value" "save_dvector_derivatives"
             "save_dvar_vector_position" "save_dvar_vector_value"
             "save_dmatrix_derivatives" "save_dvar_matrix_position"
             "save_dvar_matrix_value" "save_identifier_string" "set_value"
             "size" "sub" "value" "verify_identifier_string"
             ;; Special functions
             "ad_printf" "ad_begin_funnel" "ad_exit" "adromb" "boundp"
             "boundpin" "gradcalc" "histogram" "mf_upper_bound" "option_match"
             "set_stepnumber" "set_stepsize" "shift"))
          (IMPORTANT
           '(;; Shell
             "exit" "system"
             ;; File input/output
             "adprogram_name" "change_datafile_name" "change_pinfile_name"
             "close" "global_datafile" "ifstream" "ofstream" "open" "uistream"
             "uostream"
             ;; Allocations (TOP_OF_MAIN_SECTION)
             "arrmblsize" "set_ARRAY_MEMBLOCK_SIZE" "set_CMPDIF_BUFFER_SIZE"
             "set_GRADSTACK_BUFFER_SIZE" "set_MAX_DLINKS" "set_MAX_NVAR_OFFSET"
             "set_NUM_DEPENDENT_VARIABLES" "set_NUM_RETURN_ARRAYS"
             "set_RETURN_ARRAYS_SIZE"
             ;; Minimization settings
             "convergence_criteria" "objective_function_value"
             "maximum_function_evaluations"
             ;; Adjoint code and preprocessing (GLOBALS_SECTION)
             "defined" "#define" "#elif" "#else" "#endif" "#if" "#ifdef"
             "#ifndef" "#include" "RETURN_ARRAYS_DECREMENT"
             "RETURN_ARRAYS_INCREMENT" "#undef")))
      (list
       '("\\([A-Za-z_]*\\)::" (1 font-lock-constant-face))
       '("<\\([A-Za-z_]*\\)>" (1 font-lock-constant-face))
       '("^[A-Z_]*\\(FUNCTION\\| *#define\\)\
[^(\n]+?\\([a-zA-Z0-9_]+\\)\\( *//\\|[(\n]\\)"
         (2 font-lock-function-name-face)) ; skip type
       (cons (concat "\\<\\(" (mapconcat 'eval SECTIONS "\\|") "\\)\\>")
             'admb-section-face)
       (cons (regexp-opt CONSTANTS 'words) font-lock-constant-face)
       (cons (regexp-opt DATATYPES 'words) font-lock-type-face)
       (cons (regexp-opt FUNCTIONS 'words) font-lock-keyword-face)
       (cons (regexp-opt IMPORTANT 'words) font-lock-builtin-face)))))
(defvar admb-menu
  '("ADMB"
    ["Translate"            admb-tpl2cpp       ]
    ["Compile"              admb-compile       ]
    ["Link"                 admb-link          ]
    ["Build"                admb-build         ]
    "--"
    ["Run"                  admb-run           ]
    ["Run with Args"        admb-run-args      ]
    ["Run Makefile"         admb-run-makefile  ]
    ["Stop"                 admb-kill-process  ]
    "--"
    ["View Report"          admb-rep           ]
    ["View Estimates"       admb-cor           ]
    ["View Point Estimates" admb-par           ]
    ["View Initial Values"  admb-pin           ]
    ["View C++"             admb-cpp           ]
    ["View Any"             admb-open          ]
    ["Clean Directory"      admb-clean         ]
    "--"
    ["Outline"              admb-outline       ]
    ["Imenu"                imenu              ]
    ["Template"             admb-template      ]
    ["Mini Template"        admb-template-mini ]
    ["Toggle Section"       admb-toggle-section]
    ["Toggle Window"        admb-toggle-window ]
    "--"
    ["Target"               admb-toggle-flag   ]
    ["-d: DLL"             (admb-toggle-flag "d")
     :style toggle :selected (string-match ".*d.*" admb-flags)]
    ["-f: Fast"            (admb-toggle-flag "f")
     :style toggle :selected (string-match ".*f.*" admb-flags)]
    ["-g: Debug"           (admb-toggle-flag "g")
     :style toggle :selected (string-match ".*g.*" admb-flags)]
    ["-r: Random Effects"  (admb-toggle-flag "r")
     :style toggle :selected (string-match ".*r.*" admb-flags)]
    "--"
    ["Help"                 admb-help          ]
    ["ADMB Mode Version"    admb-mode-version  ]))
(defvar admb-mode-map
  ;; Don't use C-c C-                        x
  ;; Special   C-c C-        h
  ;; Custom    C-c C- a cdef  ijklm opqrs  vw
  ;; Available C-c C-  b    g      n     tu   yz
  (let ((map (make-sparse-keymap)))
    (easy-menu-define nil map nil admb-menu)
    ;; could bind [f10] here, but rep and cor can be opened with C-c C-o
    (define-key map [f11]               'admb-outline       )
    (define-key map [S-f11]             'imenu              )
    (define-key map [f12]               'admb-template      )
    (define-key map [S-f12]             'admb-template-mini )
    (define-key map [?\t]               'indent-relative    )
    (define-key map [M-return]          'admb-endl          )
    (define-key map [?\C-\M-m]          'admb-endl          )
    (define-key map [?\C-c C-backspace] 'admb-clean         )
    (define-key map [?\C-c 127]         'admb-clean         )
    (define-key map [M-up]              'admb-scroll-up     )
    (define-key map [M-down]            'admb-scroll-down   )
    (define-key map [?\C-c ?\C--]       'admb-toggle-flag   )
    (define-key map [?\C-c ?\C-.]       'admb-mode-version  )
    (define-key map [?\C-c ?\C-/]       'admb-help          )
    (define-key map [?\C-c ?\C-a]       'admb-run-args      )
    (define-key map [?\C-c ?\C-c]       'admb-build         )
    (define-key map [?\C-c ?\C-d]       'admb-cpp           )
    (define-key map [?\C-c ?\C-e]       'admb-cor           )
    (define-key map [?\C-c ?\C-f]       'admb-for           )
    (define-key map [?\C-c ?\C-i]       'admb-pin           )
    (define-key map [?\C-c ?\C-j]       'admb-tpl2cpp       )
    (define-key map [?\C-c ?\C-k]       'admb-compile       )
    (define-key map [?\C-c ?\C-l]       'admb-link          )
    (define-key map [?\C-c ?\C-m]       'admb-run-makefile  )
    (define-key map [?\C-c ?\C-o]       'admb-open          )
    (define-key map [?\C-c ?\C-p]       'admb-par           )
    (define-key map [?\C-c ?\C-q]       'admb-kill-process  )
    (define-key map [?\C-c ?\C-r]       'admb-rep           )
    (define-key map [?\C-c ?\C-s]       'admb-toggle-section)
    (define-key map [?\C-c ?\C-v]       'admb-run           )
    (define-key map [?\C-c ?\C-w]       'admb-toggle-window )
    map))
(defvar admb-tool-bar-map
  (let ((map (tool-bar-make-keymap)))
    (tool-bar-local-item "separator" 'ignore nil map :help "" :enable nil)
    (tool-bar-local-item "disconnect" 'admb-tpl2cpp 'Translate map)
    (tool-bar-local-item "connect" 'admb-build 'Build map)
    (tool-bar-local-item "jump-to" 'admb-run 'Run map)
    (tool-bar-local-item "describe" 'admb-rep 'View map :help "View report")
    map))
(defvar admb-mode-syntax-table
  (let ((table (make-syntax-table)))
    ;; Highlight preprocessor directives like #include
    (modify-syntax-entry ?# "w" table)
    ;; Ignore keywords inside underscore like_int_this (affects cursor motion)
    (modify-syntax-entry ?_ "w" table)
    ;; C++ comment delimiters (from Emacs Lisp manual)
    (modify-syntax-entry ?/ ". 124b" table)
    ;; C++ comment delimiters (from Emacs Lisp manual)
    (modify-syntax-entry ?* ". 23" table)
    ;; C++ comment delimiters (from Emacs Lisp manual)
    (modify-syntax-entry ?\n "> b" table)
    table))

;; 4  User functions

(defun admb-build ()
  "Build executable from TPL.\n
This command combines `admb-init', `admb-build-command' and `admb-flags'."
  (interactive)(save-buffer)(admb-split-window)
  (admb-send (concat admb-init admb-build-command " " admb-flags " "
                     (file-name-sans-extension (buffer-name))))
  (with-current-buffer "*compilation*" (setq show-trailing-whitespace nil)))
(defun admb-clean ()
  "Remove temporary files." (interactive)
  (let* ((model (file-name-sans-extension (buffer-name))) ; fmin.log in Linux
         (pattern (concat "admodel\\..*"        "\\|" "classcode\\.tmp"
                          "\\|" "eigv\\..*"     "\\|" "fmin.log"
                          "\\|" "hesscheck"     "\\|" "hessian.bin"
                          "\\|" "sims"          "\\|" "variance"
                          "\\|" model "\\.b0.*" "\\|" model "\\.bar"
                          "\\|" model "\\.bgs"  "\\|" model "\\.cpp"
                          "\\|" model "\\.ecm"  "\\|" model "\\.eva"
                          "\\|" model "\\.exp"  "\\|" model "\\.hes"
                          "\\|" model "\\.hst"  "\\|" model "\\.htp"
                          "\\|" model "\\.lib"  "\\|" model "\\.log"
                          "\\|" model "\\.luu"  "\\|" model "\\.mc2"
                          "\\|" model "\\.mcm"  "\\|" model "\\.o"
                          "\\|" model "\\.obj"  "\\|" model "\\.p0.*"
                          "\\|" model "\\.r0.*" "\\|" model "\\.rhes"
                          "\\|" model "\\.tds"))
         (files (directory-files "." nil pattern t)))
    (dolist (x files)(delete-file x)))(message "Removed ADMB temporary files"))
(defun admb-compile ()
  "Compile C++ to object code.\n
This command combines `admb-init', `admb-comp-command', and `admb-flags'."
  (interactive)(admb-split-window)
  (admb-send (concat admb-init admb-comp-command " " admb-flags " "
                     (file-name-sans-extension (buffer-name))))
  (with-current-buffer "*compilation*" (setq show-trailing-whitespace nil)))
(defun admb-cor ()
  "Open ADMB estimates (.cor) file." (interactive)(admb-open "cor"))
(defun admb-cpp ()
  "Open C++ file translated from TPL file." (interactive)(admb-open "cpp"))
(defun admb-endl ()
  "Insert << endl; (or just endl;) and newline." (interactive)
  (delete-horizontal-space)
  (if (string-equal (char-to-string (preceding-char)) "<")
      (insert " endl;")(insert " << endl;")))
(defun admb-for ()
  "Insert for(int i=1; i<=; i++)." (interactive)
  (insert "for(int i=1; i<=; i++)")(search-backward ";"))
(defun admb-help ()
  "Show help page for `admb-mode'." (interactive)
  (describe-function 'admb-mode)(switch-to-buffer "*Help*")
  (delete-other-windows)(message nil))
(defun admb-kill-process ()
  "Stop ADMB compilation or model run." (interactive)
  (kill-process (car (process-list))))
(defun admb-link ()
  "Link object code to executable.\n
This command combines `admb-init', `admb-link-command', and `admb-flags'."
  (interactive)(admb-split-window)
  (admb-send (concat admb-init admb-link-command " " admb-flags " "
                     (file-name-sans-extension (buffer-name))))
  (with-current-buffer "*compilation*" (setq show-trailing-whitespace nil)))
(defun admb-mode-version ()
  "Show ADMB Mode version number." (interactive)
  (message "ADMB Mode version %s" admb-mode-version))
(defun admb-open (ext)
  "Open file with extension EXT in secondary window."
  (interactive "sExtension: ")
  (let ((file (concat (file-name-sans-extension (buffer-name)) "." ext))
        (tpl-window (selected-window)))
    (if (not (file-regular-p file))(error "File %s not found" file)
      (admb-split-window)(find-file-noselect file)
      (set-window-buffer (next-window) file)(select-window tpl-window))))
(defun admb-outline ()
  "Navigate within ADMB file using `outline-mode'.\n
If you haven't already configured an `outline-mode-hook', here is an example
that makes it easy to return to `admb-mode':\n
\(defun my-outline-hook ()
  (local-set-key [mouse-1] 'outline-mouse-select)
  (local-set-key [return]  'admb-mode           )
  (defun outline-mouse-select ()
    \"Select position and return to `admb-mode'.\" (interactive)
    (admb-mode)(beginning-of-line)))
\(add-hook 'outline-mode-hook 'my-outline-hook)"
  (interactive)
  (let ((outreg outline-regexp))
    (outline-mode)(setq outline-regexp outreg))
  (outline-mode)(outline-hide-body))
(defun admb-par ()
  "Open ADMB point estimates (.par) file." (interactive)(admb-open "par"))
(defun admb-pin ()
  "Open ADMB initial values (.pin) file." (interactive)(admb-open "pin"))
(defun admb-rep ()
  "Open ADMB report (.rep) file." (interactive)(admb-open "rep"))
(defun admb-rep-browser ()
  "Open ADMB report (.rep) file with `browse-url'.\n
The idea is to show the report file in an external browser, but the actual
behavior of `browse-url' varies between machines. In Windows, the .rep file
ending may need to be associated with the desired browser program."
  (interactive)
  (let ((rep-file (concat (file-name-sans-extension buffer-file-name) ".rep")))
    (if (file-regular-p rep-file)(progn (browse-url rep-file)(message nil))
      (error "Report file %s not found" rep-file))))
(defun admb-run ()
  "Run ADMB program." (interactive)
  (let ((cmd (file-name-sans-extension (buffer-name)))(resize-mini-windows nil))
    ;; Split, prepare, show, run
    (admb-split-window)(get-buffer-create "*ADMB Output*")
    (with-current-buffer "*ADMB Output*" (kill-region (point-min)(point-max))
                         (setq show-trailing-whitespace nil))
    (set-window-buffer (next-window) "*ADMB Output*")
    (start-process-shell-command cmd "*ADMB Output*" cmd)))
(defun admb-run-args (args)
  "Run ADMB program with ARGS."
  (interactive (list (read-shell-command "Args: " (car shell-command-history)
                                         (cons 'shell-command-history 1))))
  (let ((cmd (concat (file-name-sans-extension (buffer-name)) " " args))
        (resize-mini-windows nil))
    (admb-split-window)(get-buffer-create "*ADMB Output*")
    (with-current-buffer "*ADMB Output*" (kill-region (point-min)(point-max))
                         (setq show-trailing-whitespace nil))
    (set-window-buffer (next-window) "*ADMB Output*")
    (start-process-shell-command cmd "*ADMB Output*" cmd)))
(defun admb-run-makefile ()
  "Run Makefile in current directory, using `admb-run-makefile-command'."
  (interactive)(save-buffer)
  (admb-split-window)(admb-send admb-run-makefile-command)
  (with-current-buffer "*compilation*" (setq show-trailing-whitespace nil)))
(defun admb-scroll-down (n)
  "Scroll other window down N lines, or visit next error message.\n
The behavior of this command depends on whether the compilation buffer is
visible."
  (interactive "p")
  (if (null (get-buffer-window "*compilation*"))(scroll-other-window n)
    (next-error n)))
(defun admb-scroll-up (n)
  "Scroll other window up N lines, or visit previous error message.\n
The behavior of this command depends on whether the compilation buffer is
visible."
  (interactive "p")
  (if (null (get-buffer-window "*compilation*"))(scroll-other-window (- n))
    (previous-error n)))
(defun admb-template ()
  "Insert AD Model Builder template." (interactive)
  (goto-char (point-min))(insert "\
//------------------------------------------------------------------------------
// File:
// Model:
// Parameters:
// Fitted data:
// Likelihood:
// Notes:
// Warning:
// History:
//------------------------------------------------------------------------------

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)

PARAMETER_SECTION
  init_number b0
  init_number b1
  init_number logsigma
  number RSS
  sdreport_number sigma
  vector yfit(1,n)
  matrix summary(1,n,1,3)  // | x | y | yfit |
  objective_function_value neglogL

PROCEDURE_SECTION
  yfit = b0 + b1*x;
  RSS = sumsq(y-yfit);
  sigma = mfexp(logsigma);
  neglogL = 0.5*n*log(2.0*PI) + n*logsigma + RSS/(2.0*square(sigma));
  if(mceval_phase())
    write_mcmc();

REPORT_SECTION
  get_summary();
  report<<\"# b0\"     <<endl<<b0     <<endl
        <<\"# b1\"     <<endl<<b1     <<endl
        <<\"# RSS\"    <<endl<<RSS    <<endl
        <<\"# sigma\"  <<endl<<sigma  <<endl
        <<\"# neglogL\"<<endl<<neglogL<<endl<<endl;
  report<<\"# Model summary\"<<endl
        <<\" x y yfit\"<<endl
        <<summary<<endl;

FUNCTION get_summary
  summary.colfill(1,x);
  summary.colfill(2,y);
  summary.colfill(3,yfit);

FUNCTION write_mcmc
  if(mcmc_lines == 0)
    mcmc_report<<\"neglogL,b0,b1,sigma\"<<endl;
  mcmc_report<<neglogL<<\",\"<<b0<<\",\"<<b1<<\",\"<<sigma<<endl;
  mcmc_lines++;

GLOBALS_SECTION
  #include \"admodel.h\"
  ofstream mcmc_report(\"mcmc.csv\");
  int mcmc_lines = 0;
")(goto-char (point-min)))
(defun admb-template-mini ()
  "Insert minimal AD Model Builder template." (interactive)
  (goto-char (point-min))(insert "\
DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)

PARAMETER_SECTION
  init_number b0
  init_number b1
  vector yfit(1,n)
  objective_function_value RSS

PROCEDURE_SECTION
  yfit = b0 + b1*x;
  RSS = sumsq(y-yfit);
")(goto-char (point-min)))
(defun admb-toggle-flag (flag)
  "Toggle compilation option.\n
FLAG is a string: \
\"d\" (dll), \"f\" (fast), \"g\" (debug), or \"r\" (random effects).\n
This command sets `admb-tpl2cpp-command', `admb-tpl2cpp-flags', and `admb-flags'
simultaneously."
  (interactive "sToggle compilation option: ")
  (let ((SS nil)) ; string splits, a list
    (cond ((string-match "-?d" flag)
           (setq SS (split-string admb-tpl2cpp-flags)) ; tpl2cpp flags
           (if (member "-dll" SS)(setq SS (remove "-dll" SS))
             (setq SS (sort (cons "-dll" SS) 'string-lessp)))
           (setq admb-tpl2cpp-flags (mapconcat 'eval SS " "))
           (setq SS (split-string admb-flags)) ; admb flags
           (if (member "-d" SS)(setq SS (remove "-d" SS))
             (setq SS (sort (cons "-d" SS) 'string-lessp)))
           (setq admb-flags (mapconcat 'eval SS " ")))
          ((string-match "-?f" flag)
           (setq SS (split-string admb-flags)) ; admb flags
           (if (member "-f" SS)(setq SS (remove "-f" SS))
             (setq SS (sort (cons "-f" SS) 'string-lessp)))
           (setq admb-flags (mapconcat 'eval SS " ")))
          ((string-match "-?g" flag)
           (setq SS (split-string admb-flags)) ; admb flags
           (if (member "-g" SS)(setq SS (remove "-g" SS))
             (setq SS (sort (cons "-g" SS) 'string-lessp)))
           (setq admb-flags (mapconcat 'eval SS " ")))
          ((string-match "-?r" flag)
           (setq admb-tpl2cpp-command
                 (if (string-equal admb-tpl2cpp-command "tpl2rem")
                     "tpl2cpp" "tpl2rem"))
           (setq SS (split-string admb-flags)) ; admb flags
           (if (member "-r" SS)(setq SS (remove "-r" SS))
             (setq SS (sort (cons "-r" SS) 'string-lessp)))
           (setq admb-flags (mapconcat 'eval SS " "))))
    (message (if (= (length admb-tpl2cpp-flags) 0)
                 "Compilation options: %s %s   (%s%s)"
               "Compilation options: %s %s   (%s %s)")
             admb-build-command admb-flags admb-tpl2cpp-command
             admb-tpl2cpp-flags)))
(defun admb-toggle-section ()
  "Toggle whether the current section is indicated in the mode line."
  (interactive)
  (which-function-mode (if which-function-mode 0 1))
  (message "Section indicator %s" (if which-function-mode "ON" "OFF")))
(defun admb-toggle-window ()
  "Toggle whether secondary window is on the right or below." (interactive)
  (delete-other-windows)(setq admb-window-right (not admb-window-right))
  (message "Secondary window %s" (if admb-window-right "RIGHT" "BELOW")))
(defun admb-tpl2cpp ()
  "Translate TPL to C++.\n
This command combines `admb-init', `admb-tpl2cpp-command',
and `admb-tpl2cpp-flags'."
  (interactive)(save-buffer)(admb-split-window)
  (admb-send (concat admb-init admb-tpl2cpp-command " " admb-tpl2cpp-flags " "
                     (file-name-sans-extension (buffer-name))))
  (with-current-buffer "*compilation*" (setq show-trailing-whitespace nil)))

;; 5  Internal functions

(defun admb-send (cmd)
  "Send shell compilation command CMD, after cleaning up spaces."
  (compile (replace-regexp-in-string "  +" " " cmd)))
(defun admb-split-window ()
  "Split window if it is the only window, otherwise do nothing.\n
The orientation of the split depends on the value of `admb-window-right'."
  ;; (if (one-window-p) (if admb-window-right   ; like so in Emacs 24.1 onwards
  ;;                        (split-window-right)(split-window-below))))
  (if (one-window-p)(if admb-window-right
                        (split-window-horizontally)(split-window-vertically))))

;; 6  Main function

(if (< emacs-major-version 24)
    (define-derived-mode prog-mode fundamental-mode "Prog"))
;;;###autoload
(define-derived-mode admb-mode prog-mode "ADMB"
  "Major mode for creating statistical models with AD Model Builder.\n
The `admb-help' command shows this page.\n
Start a new model from `admb-template' or `admb-template-mini'. Navigate between
sections using `admb-outline', `imenu', or `outline-minor-mode'. Indicate the
current section in the mode line with `admb-toggle-section', and use
`admb-endl', `admb-for', and `dabbrev-expand' to save keystrokes.\n
Compile using `admb-build', or `admb-tpl2cpp', `admb-compile', and `admb-link'.
Configure these compilation commands with `admb-toggle-flag' and by setting the
variables `admb-init', `admb-build-command', `admb-comp-command', and
`admb-link-command'. Stop compilation or model run with `admb-kill-process'.\n
Use `admb-toggle-window' to set `admb-window-right' to your viewing preference.
After compiling, use `admb-cpp' to debug, `admb-clean' to remove temporary
files, and `admb-pin' to set initial parameter values. Run model with `admb-run'
or `admb-run-args', and view model output with `admb-cor', `admb-par',
`admb-rep', and `admb-rep-browser'. Use the general `admb-open' to open other
model-related files.\n
While staying in the ADMB window, navigate the secondary window with
\\<admb-mode-map>\
\\[beginning-of-buffer-other-window], \\[scroll-other-window-down], \
\\[admb-scroll-up] (home, page up, line up), and
\\[end-of-buffer-other-window], \\[scroll-other-window], \
\\[admb-scroll-down] (end, page down, line down).
This is particularly efficient for navigating error messages listed
in the compilation buffer.\n
The `admb-run-makefile' command supports makefile-based workflow.\n
\\{admb-mode-map}"
  (set (make-local-variable 'comment-start) "//")
  (set (make-local-variable 'font-lock-defaults)
       '(admb-font-lock-keywords nil nil)) ; case-sensitive keywords
  (set (make-local-variable 'imenu-generic-expression) '((nil "^[A-Z].*" 0)))
  (set (make-local-variable 'indent-line-function) 'indent-relative)
  (set (make-local-variable 'outline-regexp) "[A-Z]")
  (set (make-local-variable 'tab-stop-list) '(2)) ; first line in section
  (set (make-local-variable 'tool-bar-map) admb-tool-bar-map)
  (set-syntax-table admb-mode-syntax-table))

(provide 'admb)

;;; admb.el ends here
