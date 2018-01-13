;;; .emacs --- configuration file for AD Studio

;; Copyright (C) 2018 Arni Magnusson

;; Author:   Arni Magnusson
;; Keywords: emulations
;; URL:      http://admb-project.org/tools/adstudio/

(defconst adstudio-version "1.0" "AD Studio version number.")

;;; Commentary:
;;
;; Configuration file for a user-friendly environment for developing statistical
;; models with AD Model Builder (ADMB) and Template Model Builder (TMB).
;; Emulates common keybindings of basic editors, while disabling some of the
;; most used Emacs keybindings. This .emacs file is therefore not intended for
;; experienced Emacs users, although they may find it an interesting read.
;;
;; Usage:
;;
;; See the AD Studio manual.
;;
;; References:
;;
;; See the AD Studio manual.

;;; History:
;;
;; See the NEWS file.

;;; Code:

;; Section numbers match https://github.com/arnima-github/dot/blob/master/.emacs
;;==============================================================================
;;
;; 1  OS-SPECIFICS
;;
;;==============================================================================
(defvar adstudio-default-directory "~"
  "Directory where `find-file' and `write-file' start looking.")
;; In Windows maximize and UTF-8, Linux takes care of itself
(if (string-match "windows" (prin1-to-string system-type))
    (progn (modify-frame-parameters nil '((fullscreen . maximized)))
           (prefer-coding-system 'utf-8)
           (setq-default buffer-file-coding-system 'utf-8)
           (setq adstudio-default-directory "c:/")))
;;==============================================================================
;;
;; 2  INTERFACE
;;
;;==============================================================================
;;-------------
;; 2.1  Visual
;;-------------
(blink-cursor-mode 0             )
(column-number-mode t            )
(set-scroll-bar-mode 'right      )
(setq frame-title-format "%b"    )
(setq inhibit-startup-screen t   )
(setq initial-scratch-message nil)
(setq-default truncate-lines t   )
(show-paren-mode t               )
(setq tool-bar-map (make-sparse-keymap))
(setq tool-bar-style 'image) ; suppress fixed text labels on toolbar in Linux
(let ((undo-form '(and (not buffer-read-only)(not (eq t buffer-undo-list))
                       (if (eq last-command 'undo)(listp pending-undo-list)
                         (consp buffer-undo-list)))))
  (tool-bar-add-item "new" 'new-buffer 'new-buffer :help "New")
  (tool-bar-add-item "open" 'find-file 'find-file :help "Open")
  (tool-bar-add-item "save" 'save-buffer 'save-buffer :help "Save"
                     :enable '(buffer-modified-p))
  (tool-bar-add-item "cut" 'kill-region 'kill-region :help "Cut")
  (tool-bar-add-item "copy" 'copy-region-as-kill 'copy-region-as-kill
                     :help "Copy")
  (tool-bar-add-item "paste" 'yank 'yank :help "Paste")
  (tool-bar-add-item "undo" 'undo 'undo :help "Undo" :enable undo-form)
  (tool-bar-add-item "close" 'kill-this-buffer 'kill-this-buffer :help "Close"))
;;--------------
;; 2.2  Editing
;;--------------
(cua-mode t                                  )
(defalias 'yes-or-no-p 'y-or-n-p             )
(delete-selection-mode 1                     )
(require 'imenu)(setq imenu-max-items 43     )
(setq cua-prefix-override-inhibit-delay 0.001)
(setq cua-keep-region-after-copy t           )
(setq initial-major-mode 'text-mode          )
(setq-default indent-tabs-mode nil           )
(setq-default major-mode 'text-mode          )
(setq-default require-final-newline t        )
(setq save-abbrevs nil                       )
(setq w32-pass-alt-to-system t               )
(eval (list initial-major-mode)) ; for emacs -Q -l .emacs
;;------------
;; 2.3  Faces
;;------------
(defconst - 'unspecified)
(set-face-attribute 'font-lock-builtin-face       nil :foreground "red"        )
(set-face-attribute 'font-lock-comment-face       nil :foreground "gray70"     )
(set-face-attribute 'font-lock-constant-face      nil :foreground -
                    :underline t)
(set-face-attribute 'font-lock-function-name-face nil :foreground "saddlebrown"
                    :weight 'bold)
(set-face-attribute 'font-lock-keyword-face       nil :foreground "blue"       )
(set-face-attribute 'font-lock-string-face        nil :foreground "forestgreen")
(set-face-attribute 'font-lock-type-face          nil :foreground "magenta"    )
(set-face-attribute 'font-lock-variable-name-face nil :foreground "saddlebrown")
(set-face-attribute 'font-lock-warning-face       nil :weight 'normal          )
(set-face-attribute 'fringe                       nil :background -            )
(set-face-attribute 'isearch                      nil :background "yellow"
                    :foreground -)
(set-face-attribute 'isearch-lazy-highlight-face  nil
                    :background "palegoldenrod")
(set-face-attribute 'show-paren-match-face        nil :background "chartreuse" )
(set-face-attribute 'show-paren-mismatch-face     nil :background "red"        )
;;==============================================================================
;;
;; 3  FILES
;;
;;==============================================================================
;;-------------
;; 3.3  Backup
;;-------------
(setq make-backup-files nil)(setq auto-save-default nil)
(setq auto-save-list-file-prefix nil)
;;-------------
;; 3.4  Recent
;;-------------
;; (recentf-mode t)(message nil)
;;----------------
;; 3.5  Autoloads
;;----------------
(if (file-directory-p "~/emacs/lisp/")
    (progn (cd "~/emacs/lisp/")(normal-top-level-add-subdirs-to-load-path)))
(cd adstudio-default-directory)
(autoload 'admb-mode      "admb"          "Edit ADMB code."         t)
(autoload 'markdown-mode  "markdown-mode" "Edit Markdown document." t)
(autoload 'R              "ess-site"      "Interactive R session."  t)
(autoload 'R-mode         "ess-site"      "Edit R code."            t)
(autoload 'r-mode         "ess-site"                                 ) ;*-R-*
(autoload 'Rd-mode        "ess-site"      "Edit R documentation."   t)
(autoload 'Rnw-mode       "ess-site"      "Edit Sweave document."   t)
(autoload 'TeX-latex-mode "tex-site"      "Edit LaTeX document."    t)
(autoload 'tmb-mode       "tmb"           "Edit ADMB code."         t)
;;-------------------
;; 3.6  Associations
;;-------------------
(add-to-list 'auto-mode-alist '("\\.tpl$"      . admb-mode     ))
(add-to-list 'auto-mode-alist '("\\.ctl$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.dat$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.par$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.pin$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.rep$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.md$"       . markdown-mode ))
(add-to-list 'auto-mode-alist '("\\.Rmd$"      . markdown-mode ))
(add-to-list 'auto-mode-alist '("\\.R$"        . R-mode        ))
(add-to-list 'auto-mode-alist '("\\.Rprofile$" . R-mode        ))
(add-to-list 'auto-mode-alist '("/Redit"       . R-mode        ))
(add-to-list 'auto-mode-alist '("/tmp/Rtmp"    . R-mode        ))
(add-to-list 'auto-mode-alist '("\\.Rd$"       . Rd-mode       ))
(add-to-list 'auto-mode-alist '("\\.Rnw$"      . Rnw-mode      ))
(add-to-list 'auto-mode-alist '("\\.tex$"      . TeX-latex-mode))
;;==============================================================================
;;
;; 4  KEYBINDINGS
;;
;;==============================================================================
;; Ctrl-
;; Windows                                           ESC
;; Default       TAB     HOME END PGUP PGDN BKSP DEL
;; Custom    SPC     RET
;; Special     c     i   m          x         [
;; Default       e  h jkl       tu   y 0..9`-= ];'\  /~!@#$%^&*() +{}|:"<>?
;; Custom    ab d fg      nopqrs  vw  z            ,.
;; Suppress                                                      _
;;--------------
;; 4.1  Disable
;;--------------
(global-unset-key [f10]        ) ; menu-bar-open
(global-unset-key [f11]        ) ; toggle-frame-fullscreen
(global-unset-key [?\C-x ?\C-c])
(global-unset-key [?\C-x ?\C-f])
(global-unset-key [?\C-x ?h]   )
(global-unset-key [?\C-x ?u]   )
(global-unset-key [?\C-x ?\C-s])
(global-unset-key [?\C-x ?\C-w])
(global-unset-key [?\C-x ?\C-z])
(global-unset-key [?\M-g ?g]   )
;;------------
;; 4.2  Mouse
;;------------
(setq mouse-wheel-scroll-amount '(3 ((shift) . 10)((control) . 30)))
(setq mouse-wheel-progressive-speed nil)
(global-set-key [S-mouse-1]      'mouse-extend-region)
(global-set-key [S-down-mouse-1] 'mouse-extend-region) ; mouse-appearance-menu
(global-set-key        [mouse-3] 'ignore             ) ; mouse-save-then-kill
(global-set-key   [down-mouse-3] 'imenu              )
;;--------------
;; 4.3  Special
;;--------------
(global-set-key [escape]      'keyboard-escape-quit    ) ; prefix
(global-set-key [f1]          'adstudio-help           ) ; prefix
(global-set-key [S-f1]        'adstudio-version        )
(global-set-key [f2]          'admb-mode               ) ; prefix
(global-set-key [f3]          'tmb-mode                ) ; kmacro-start-macro...
(global-set-key [f4]          'R-mode                  ) ; kmacro-end-or-call...
(global-set-key [C-f4]        'kill-buffer-maybe-window)
(global-set-key [M-f4]        'save-buffers-kill-emacs )
(global-set-key [f5]          'revert-buffer           )
(global-set-key [f6]          'other-window            )
(global-set-key [C-f6]        'next-buffer             )
(global-set-key [M-f6]        'next-buffer             )
;; [f7]-[f10] are set in `adstudio-admb-hook' and `adstudio-tmb-hook'
;; [f11]-[f12] are set in in `admb-mode' and `tmb-mode'
(global-set-key [C-backspace] 'backward-delete-word    ) ; backward-kill-word
(global-set-key [C-delete]    'delete-word             ) ; kill-line
(global-set-key [S-return]    'comment-indent-new-line )
(global-set-key [?\C- ]       'dabbrev-expand          ) ; set-mark-command
(global-set-key [?\C-\M- ]    'recentf-open-files      ) ; C-M-space
;;------------------
;; 4.5  Two strokes
;;------------------
(global-set-key [?\C-x escape] 'ignore) ; prefix
(global-set-key [?\C-x ?\C-x]  'ignore) ; exchange-point-and-mark
;;-----------------
;; 4.6  One stroke
;;-----------------
(global-set-key [?\C-,]    'toggle-trailing-whitespace)
(global-set-key [?\C-.]    'which-function-mode       )
(global-set-key [?\C-a]    'mark-whole-buffer         ) ; move-beginning-of-line
(global-set-key [?\C-b]    'next-buffer               ) ; backward-char
(global-set-key [?\C-d]    'cd                        ) ; kill-word
(global-set-key [?\C-f]    'isearch-forward           ) ; forward-char
(global-set-key [?\C-g]    'goto-line                 ) ; keyboard-quit
(global-set-key [?\C-n]    'new-buffer                ) ; next-line
(global-set-key [?\C-o]    'find-file                 ) ; open-line
(global-set-key [?\C-p]    'find-file-other-window    ) ; previous-line
(global-set-key [?\C-q]    'save-buffers-kill-emacs   ) ; quoted-insert
(global-set-key [?\C-r]    'query-replace             ) ; isearch-backward
(global-set-key [?\C-s]    'save-buffer               ) ; isearch-forward
(global-set-key [33554451] 'write-file                ) ; C-S
(global-set-key [?\C-w]    'kill-buffer-maybe-window  ) ; kill-region
(global-set-key [?\M-,]    'delete-trailing-spc-tab-m ) ; tags-loop-continue
(global-set-key [?\M-a]    'menu-bar-open             ) ; backward-sentence
(global-set-key [?\M-b]    'menu-bar-open             ) ; backward-word
(global-set-key [?\M-e]    'menu-bar-open             ) ; forward-sentence
(global-set-key [?\M-f]    'menu-bar-open             ) ; forward-word
(global-set-key [?\M-h]    'menu-bar-open             ) ; mark-paragraph
(global-set-key [?\M-o]    'menu-bar-open             ) ; [map]
(global-set-key [?\M-t]    'menu-bar-open             ) ; transpose-words
;;-----------------
;; 4.7  Minibuffer
;;-----------------
(define-key minibuffer-local-map [escape] 'minibuffer-keyboard-quit)
;;==============================================================================
;;
;; 5  FUNCTIONS
;;
;;==============================================================================
;;-----------
;; 5.1  File
;;-----------
(defun kill-this-buffer ()
  "Kill current buffer." (interactive)(kill-buffer (current-buffer)))
(defun kill-buffer-maybe-window ()
  "Kill current buffer and window." (interactive)
  (kill-this-buffer)(if (> (length (window-list)) 1)(delete-window)))
(defun new-buffer ()
  "Create new buffer." (interactive)
  (switch-to-buffer (generate-new-buffer "Untitled"))
  (eval (list (default-value 'major-mode))))
;;-----------
;; 5.2  Edit
;;-----------
(defun backward-delete-word (n)
  "Delete previous N words." (interactive "*p")(delete-word (- n)))
(defun delete-word (n)
  "Delete following N words." (interactive "*p")
  (delete-region (point)(save-excursion (forward-word n)(point))))
(defun mouse-extend-region (click)
  "Extend region to mouse position." (interactive "e")
  (if (and mark-active transient-mark-mode)(mouse-set-point click)
    (mouse-save-then-kill click)))
;;-----------
;; 5.3  View
;;-----------
(defun toggle-trailing-whitespace ()
  "Toggle highlighting of trailing whitespace." (interactive)
  (setq show-trailing-whitespace (not show-trailing-whitespace))(redraw-display)
  (message "Trailing whitespace highlighting %s"
           (if show-trailing-whitespace "ON" "OFF")))
;;-------------
;; 5.5  Format
;;-------------
(defun delete-trailing-spc-tab-m ()
  "Delete spaces, tabs, and ^M glyphs from line ends." (interactive "*")
  (let ((count 0))
    (save-excursion
      (goto-char (point-min))
      (while (re-search-forward "[ \t\r]+$" nil t)(replace-match "")
             (setq count (+ count 1)))(message "Cleaned %d lines" count))))
;;-----------
;; 5.8  Help
;;-----------
(defun adstudio-help ()
  "Show help message for AD Studio." (interactive)
  (message "F2: ADMB mode      F3: TMB mode"))
(defun adstudio-version ()
  "Show AD Studio version number." (interactive)
  (message "AD Studio version %s" adstudio-version))
;;==============================================================================
;;
;; 6  LANGUAGE MODES
;;
;;==============================================================================
;;-----------
;; 6.2  ADMB
;;-----------
(require 'admb)
(eval-after-load "prog-mode" '(define-key prog-mode-map [?\C-\M-q] nil))
(defun adstudio-admb-hook ()
  (adstudio-help)
  (local-unset-key [S-f11]            )
  (local-unset-key [?\C-c C-backspace])
  (local-unset-key [?\C-c 127]        )
  (local-unset-key [?\C-c ?\C--]      )
  (local-unset-key [?\C-c ?\C-.]      )
  (local-unset-key [?\C-c ?\C-/]      )
  (local-unset-key [?\C-c ?\C-a]      )
  (local-unset-key [?\C-c ?\C-c]      )
  (local-unset-key [?\C-c ?\C-d]      )
  (local-unset-key [?\C-c ?\C-e]      )
  (local-unset-key [?\C-c ?\C-f]      )
  (local-unset-key [?\C-c ?\C-i]      )
  (local-unset-key [?\C-c ?\C-j]      )
  (local-unset-key [?\C-c ?\C-k]      )
  (local-unset-key [?\C-c ?\C-l]      )
  (local-unset-key [?\C-c ?\C-m]      )
  (local-unset-key [?\C-c ?\C-o]      )
  (local-unset-key [?\C-c ?\C-p]      )
  (local-unset-key [?\C-c ?\C-q]      )
  (local-unset-key [?\C-c ?\C-r]      )
  (local-unset-key [?\C-c ?\C-s]      )
  (local-unset-key [?\C-c ?\C-v]      )
  (local-unset-key [?\C-c ?\C-w]      )
  ;; Keybindings that should only be active in an ADMB buffer
  (local-set-key [f1]    'admb-help          ) ; adstudio-help
  (local-set-key [f7]    'admb-tpl2cpp       )
  (local-set-key [f8]    'admb-build         )
  (local-set-key [f9]    'admb-run           )
  (local-set-key [S-f9]  'admb-run-args      )
  (local-set-key [f10]   'admb-rep           ) ; menu-bar-open
  (local-set-key [S-f10] 'admb-cor           )
  (local-set-key [?\C--] 'admb-toggle-flag   ) ; negative-argument
  (local-set-key [?\C-.] 'admb-toggle-section)
  (local-set-key [?\C-p] 'admb-open          ) ; previous-line
  (local-set-key [?\M-w] 'admb-toggle-window)) ; kill-ring-save
(add-hook 'admb-mode-hook 'adstudio-admb-hook)
;;----------
;; 6.6  C++
;;----------
(defun adstudio-c-hook ()
  (message nil)
  (local-unset-key [?\C-\[])
  (local-unset-key [127]   )
  (local-unset-key [?#]    )
  (local-unset-key [?\(]   )
  (local-unset-key [?\)]   )
  (local-unset-key [?*]    )
  (local-unset-key [?,]    )
  (local-unset-key [?/]    )
  (local-unset-key [?:]    )
  (local-unset-key [?\;]   )
  (local-unset-key [?<]    )
  (local-unset-key [?>]    )
  (local-unset-key [?{]    )
  (local-unset-key [?}]    )
  (local-unset-key [S-return])
  (define-key c++-mode-map [?\C-c ?\C-e]           nil)
  (define-key c++-mode-map [?\C-c ?:]              nil)
  (define-key c-mode-base-map [?\C-c ?\C-a]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-b]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-c]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-d]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-l]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-n]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-o]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-p]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-q]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-s]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-u]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-w]        nil)
  (define-key c-mode-base-map [?\C-c ?\C-\\]       nil)
  (define-key c-mode-base-map [?\C-c ?.]           nil)
  (define-key c-mode-base-map [?\C-c ?\d]          nil) ; C-c DEL
  (define-key c-mode-base-map [?\C-c ?\C-\d]       nil) ; C-c C-DEL
  (define-key c-mode-base-map [?\C-c C-backspace]  nil) ; C-c <C-backspace>
  (define-key c-mode-base-map [?\C-c C-delete]     nil) ; C-c <C-delete>
  (define-key c-mode-base-map [?\C-c deletechar]   nil) ; C-c <C-deletechar>
  (define-key c-mode-base-map [?\C-c C-deletechar] nil) ; C-c C-c <C-deletechar>
  (define-key c-mode-base-map [?\C-d]              nil)
  (define-key c-mode-base-map [?\C-\M-a]           nil)
  (define-key c-mode-base-map [?\C-\M-e]           nil)
  (define-key c-mode-base-map [?\C-\M-h]           nil)
  (define-key c-mode-base-map [?\C-\M-j]           nil)
  (define-key c-mode-base-map [?\C-\M-q]           nil)
  (define-key c-mode-base-map [?\M-a]              nil)
  (define-key c-mode-base-map [?\M-e]              nil)
  (define-key c-mode-base-map [?\M-j]              nil)
  (define-key c-mode-base-map [?\M-q]              nil))
(add-hook 'c-mode-common-hook 'adstudio-c-hook)
(defun adstudio-gdb-hook ()
  (message nil)
  (setq indent-line-function 'gud-gdb-complete-command)(setq gdb-show-main t)
  (local-set-key [f5]          'gdb-restore-windows)
  (local-set-key [M-up]        'gdb-io-buffer-off  )
  (local-set-key [M-down]      'gdb-io-buffer-on   )
  (local-set-key [?\C-c ?\C-q] 'comint-quit-subjob )
  (defun gdb-io-buffer-off ()
    "Enable separate IO buffer." (interactive)(gdb-use-separate-io-buffer 0))
  (defun gdb-io-buffer-on ()
    "Disable separate IO buffer." (interactive)(gdb-use-separate-io-buffer t)))
(add-hook 'gdb-mode-hook 'adstudio-gdb-hook)
;;----------
;; 6.18 TMB
;;----------
(require 'tmb)
(defun adstudio-tmb-hook ()
  (adstudio-help)
  (set-face-attribute 'tmb-block-face     nil :foreground "chocolate")
  (set-face-attribute 'tmb-data-face      nil :foreground "chocolate")
  (set-face-attribute 'tmb-parameter-face nil :foreground "chocolate")
  (set-face-attribute 'tmb-report-face    nil :foreground "chocolate")
  (local-unset-key [?\C-c C-backspace])
  (local-unset-key [?\C-c ?\C-.])
  (local-unset-key [?\C-c ?\C-/])
  (local-unset-key [?\C-c ?\C-a])
  (local-unset-key [?\C-c ?\C-b])
  (local-unset-key [?\C-c ?\C-c])
  (local-unset-key [?\C-c ?\C-d])
  (local-unset-key [?\C-c ?\C-f])
  (local-unset-key [?\C-c ?\C-k])
  (local-unset-key [?\C-c ?\C-l])
  (local-unset-key [?\C-c ?\C-m])
  (local-unset-key [?\C-c ?\C-n])
  (local-unset-key [?\C-c ?\C-o])
  (local-unset-key [?\C-c ?\C-p])
  (local-unset-key [?\C-c ?\C-q])
  (local-unset-key [?\C-c ?\C-r])
  (local-unset-key [?\C-c ?\C-s])
  (local-unset-key [?\C-c ?\C-t])
  (local-unset-key [?\C-c ?\C-v])
  (local-unset-key [?\C-c ?\C-w])
  (local-set-key [f1]    'tmb-help          ) ; adstudio-help
  (local-set-key [f7]    'tmb-clean         )
  (local-set-key [f8]    'tmb-compile       )
  (local-set-key [f9]    'tmb-run           )
  (local-set-key [f10]   'tmb-debug         )
  (local-set-key [f11]   'tmb-open          ) ; menu-bar-open
  (local-set-key [f12]   'tmb-template-mini )
  (local-set-key [?\C-p] 'tmb-open-any      ) ; previous-line
  (local-set-key [?\M-m] 'tmb-multi-window  ) ; back-to-indentation
  (local-set-key [?\M-w] 'tmb-toggle-window)) ; previous-line
(add-hook 'tmb-mode-hook 'adstudio-tmb-hook)
;;==============================================================================
;;
;; 7  OTHER MODES
;;
;;==============================================================================
;;-------------
;; 7.5  Comint
;;-------------
(defun adstudio-comint-hook ()(local-set-key [home] 'comint-bol))
(add-hook 'comint-mode-hook 'adstudio-comint-hook)
;;-----------
;; 7.16 Help
;;-----------
(defun adstudio-help-hook ()(local-set-key [escape] 'kill-buffer-maybe-window))
(add-hook 'help-mode-hook 'adstudio-help-hook)
;;--------------
;; 7.26 Outline
;;--------------
(defvar outline-previous-mode '(admb-mode)
  "Mode to return to. See `outline-return'.")
(defun adstudio-outline-hook ()
  (message nil)
  (set-face-attribute 'outline-1 nil :inherit 'font-lock-keyword-face)
  (local-set-key [mouse-1] 'outline-mouse-select    )
  (local-set-key [escape]  'outline-window-or-return)
  (local-set-key [f11]     'outline-return          )
  (local-set-key [home]    'move-beginning-of-line  )
  (local-set-key [end]     'move-end-of-line        )
  (local-set-key [return]  'outline-return          )
  (local-set-key [up]      'outline-previous-heading)
  (local-set-key [down]    'outline-next-heading    )
  (local-set-key [left]    'hide-entry              )
  (local-set-key [right]   'show-entry              )
  (defun outline-mouse-select ()
    "Select position and return to `outline-previous-mode'." (interactive)
    (outline-return)(beginning-of-line))
  (defun outline-return ()
    "Return to `outline-previous-mode'." (interactive)
    (eval outline-previous-mode))
  (defun outline-window-or-return ()
    "Delete other windows or return to `outline-previous-mode'." (interactive)
    (if (> (length (window-list)) 1)(delete-other-windows)(outline-return))))
(add-hook 'outline-mode-hook 'adstudio-outline-hook)
;;--------------
;; 7.29 Recentf
;;--------------
(defun adstudio-recentf-hook ()(local-set-key [escape] 'recentf-cancel-dialog))
(add-hook 'recentf-dialog-mode-hook 'adstudio-recentf-hook)
;;-------------
;; 7.32 Search
;;-------------
(defun adstudio-isearch-hook ()
  (define-key isearch-mode-map [escape] 'isearch-exit           )
  (define-key isearch-mode-map [?\C-f]  'isearch-repeat-forward))
(add-hook 'isearch-mode-hook 'adstudio-isearch-hook)

(adstudio-help)

;; .emacs ends here
