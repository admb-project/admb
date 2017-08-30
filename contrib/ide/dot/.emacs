;;; .emacs --- configuration file for AD Model Builder IDE

;; Copyright (C) 2009, 2010, 2011, 2012, 2015, 2017 Arni Magnusson

;; Author:   Arni Magnusson
;; Keywords: emulations
;; URL:      http://admb-project.org/community/editing-tools/admb-ide/core

(defconst admb-ide-version "11.6" "ADMB-IDE version number.")

;; This .emacs file is provided under the general terms of the Simplified BSD
;; License.
;; Redistribution and use in source and binary forms, with or without
;; modification, are permitted provided that the following conditions are met:
;; 1 Redistributions of source code must retain the above copyright notice, this
;;   list of conditions and the following disclaimer.
;; 2 Redistributions in binary form must reproduce the above copyright notice,
;;   this list of conditions and the following disclaimer in the documentation
;;   and/or other materials provided with the distribution.
;; THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
;; WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
;; MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
;; EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;; SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;; WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;; OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
;; ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

;;; Commentary:
;;
;; Configuration file for a user-friendly integrated development environment
;; (IDE) for AD Model Builder (ADMB). Emulates common keybindings of basic
;; editors, while disabling some of the most used Emacs keybindings. This .emacs
;; file is therefore not intended for experienced Emacs users, although they may
;; find it an interesting read.
;;
;; Usage:
;;
;; See the AD Model Builder IDE manual.
;;
;; References:
;;
;; See the AD Model Builder IDE manual.

;;; History:
;;
;; 30 Aug 2017  11.6     Created function `easy-tmb-hook'. Disabled
;;                       `save-abbrevs'.
;; 12 Jan 2015  11.2     Reactivated C-h to access help system. Removed
;;                       dependency on `pc-selection-mode'. Set encoding to
;;                       UTF-8 on Windows. Let Linux decide encoding and initial
;;                       window size. Added ESS and AUCTeX.
;; 29 Feb 2012  4.5.2-1  Commented out `recentf-mode', which had been causing
;;                       long delays for many users. This feature can be turned
;;                       back on by uncommenting the line.
;; 17 Feb 2011  4.5.0-1  Added functions `admb-ide-version',
;;                       `delete-trailing-spc-tab-m', and
;;                       `toggle-trailing-whitespace'. Bound C-p to open model
;;                       file in other window, C-- to toggle compilation flags,
;;                       S-f1 to show ADMB-IDE version number, C-, to toggle
;;                       whether trailing whitespace is highlighted, M-, to
;;                       delete trailing whitespace, and S-return to end line
;;                       and indent next line. Unbound C-d and C-c C-r. Removed
;;                       configuration of `font-lock-doc-face'. Minor syntax
;;                       changes to avoid warnings in Emacs 23.2.
;; 19 Mar 2010  4.4.0-2  No changes (only updated admb-mode and manual).
;; 14 Mar 2010  4.4.0-1  Input and output files (ctl/dat/pin and par/rep) are
;;                       opened in `conf-unix-mode' to provide syntax
;;                       highlighting of #comments. Improved C-S-home and
;;                       C-S-end selection.
;; 14 Sep 2009  3.4.5-8  Bound C-. to toggle whether the current section is
;;                       indicated in the mode line, C-space to expand
;;                       recognized words, C-M-space to open recent files, and
;;                       S-f9 to run with args.
;;  6 Sep 2009  3.4.5-7  Added support for Emacs 23.
;;  7 Jul 2009  3.4.5-6  Bound M-f6 to switch to next buffer, in case C-f6 is
;;                       reserved in Linux KDE.
;;  3 Jun 2009  3.4.5-5  Unbound C-c C-- and C-c C-f.
;; 29 May 2009  3.4.5-4  No changes (only in manual).
;; 28 May 2009  3.4.5-3  No changes (only in manual and installer).
;; 27 May 2009  3.4.5-2  Bound Alt, M-a, M-b, M-e, M-f, M-h, M-o, and M-t to
;;                       activate menu, and unbound S-f11.
;; 24 May 2009  3.4.5-1  Created variables `easy-default-directory' and
;;                       `outline-previous-mode'. Created functions
;;                       `backward-delete-word', `delete-word',
;;                       `easy-admb-hook', `easy-conf-hook', `easy-gdb-hook',
;;                       `easy-help-hook', `easy-isearch-hook',
;;                       `easy-outline-hook', `easy-recentf-hook',
;;                       `gdb-io-buffer-off', `gdb-io-buffer-on',
;;                       `kill-buffer-maybe-window', `kill-this-buffer',
;;                       `mouse-extend-region', `new-buffer',
;;                       `outline-mouse-select', `outline-return', and
;;                       `outline-window-or-return'. Released ADMB-IDE to ADMB
;;                       Project.

;;; Code:

;; Section numbers match http://www.hafro.is/~arnima/.emacs
;;==============================================================================
;;
;; 1  OS-SPECIFICS
;;
;;==============================================================================
(defvar easy-default-directory "~"
  "Directory where `find-file' and `write-file' start looking.")
;; In Windows maximize and UTF-8, Linux takes care of itself
(if (string-match "windows" (prin1-to-string system-type))
    (progn (modify-frame-parameters nil '((fullscreen . maximized)))
           (prefer-coding-system 'utf-8)
           (setq-default buffer-file-coding-system 'utf-8)
           (setq easy-default-directory "c:/")))
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
(setq initial-major-mode 'admb-mode          )
(setq-default indent-tabs-mode nil           )
(setq-default major-mode 'text-mode          )
(setq-default require-final-newline t        )
(setq save-abbrevs nil                       )
(setq w32-pass-alt-to-system t               )
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
(cd easy-default-directory)
(autoload 'admb-mode      "admb"     "Edit ADMB code."        t)
(autoload 'R              "ess-site" "Interactive R session." t)
(autoload 'R-mode         "ess-site" "Edit R code."           t)
(autoload 'r-mode         "ess-site"                           ) ;*-R-*
(autoload 'Rd-mode        "ess-site" "Edit R documentation."  t)
(autoload 'Rnw-mode       "ess-site" "Edit Sweave document."  t)
(autoload 'TeX-latex-mode "tex-site" "Edit LaTeX document."   t)
;;-------------------
;; 3.6  Associations
;;-------------------
(add-to-list 'auto-mode-alist '("\\.tpl$"      . admb-mode     ))
(add-to-list 'auto-mode-alist '("\\.ctl$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.dat$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.par$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.pin$"      . conf-unix-mode))
(add-to-list 'auto-mode-alist '("\\.rep$"      . conf-unix-mode))
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
;; Default              l              0..9`-= ];'\, /~!@#$%^&*() +{}|:"<>?
;; Custom    ab   fg      nopqrs  vw  z             .
;; Suppress     de  h jk        tu   y                           _
;;--------------
;; 4.1  Disable
;;--------------
(global-unset-key [?\C-x ?\C-c])
(global-unset-key [?\C-x ?\C-f])
(global-unset-key [?\C-x ?h]   )
(global-unset-key [?\C-x ?u]   )
(global-unset-key [?\C-x ?\C-s])
(global-unset-key [?\C-x ?\C-w])
(global-unset-key [?\C-x ?\C-z])
(global-unset-key [?\M-g ?g]   )
(global-unset-key [?\C-_]      )
(global-unset-key [?\M-%]      )
;;------------
;; 4.2  Mouse
;;------------
(setq mouse-wheel-scroll-amount '(3 ((shift) . 10)((control) . 30)))
(setq mouse-wheel-progressive-speed nil)
(global-set-key [S-down-mouse-1] 'mouse-extend-region) ; mouse-appearance-menu
(global-set-key [S-drag-mouse-1] 'mouse-extend-region)
(global-set-key        [mouse-3] 'ignore             ) ; mouse-save-then-kill
(global-set-key   [down-mouse-3] 'imenu              )
;;--------------
;; 4.3  Special
;;--------------
(global-set-key [escape]      'keyboard-escape-quit    ) ; prefix
(global-set-key [f1]          'admb-help               ) ; prefix
(global-set-key [S-f1]        'admb-ide-version        )
(global-set-key [f2]          'admb-mode               ) ; prefix
(global-set-key [f3]          'conf-unix-mode          ) ; kmacro-start-macro...
(global-set-key [f4]          'admb-toggle-window      ) ; kmacro-end-or-call...
(global-set-key [C-f4]        'kill-buffer-maybe-window)
(global-set-key [M-f4]        'save-buffers-kill-emacs )
(global-set-key [f5]          'revert-buffer           )
(global-set-key [f6]          'other-window            )
(global-set-key [C-f6]        'next-buffer             )
(global-set-key [M-f6]        'next-buffer             )
;; [f7]-[f10] are set in `easy-admb-hook' and [f11]-[f12] in `admb-mode'
(global-set-key [C-backspace] 'backward-delete-word    ) ; backward-kill-word
(global-set-key [C-delete]    'delete-word             ) ; kill-line
(global-set-key [S-return]    'comment-indent-new-line )
(global-set-key [?\C- ]       'dabbrev-expand          ) ; set-mark-command
(global-set-key [?\C-\M- ]    'recentf-open-files      ) ; C-M-space
;;------------------
;; 4.5  Two strokes
;;------------------
(global-set-key [?\C-x escape] 'ignore)
(global-set-key [?\C-x ?\C-x]  'ignore)
;;-----------------
;; 4.6  One stroke
;;-----------------
(global-set-key [?\C--]    'admb-toggle-flag          ) ; negative-argument
(global-set-key [?\C-,]    'toggle-trailing-whitespace)
(global-set-key [?\C-a]    'mark-whole-buffer         ) ; move-beginning-of-line
(global-set-key [?\C-b]    'next-buffer               ) ; backward-char
(global-set-key [?\C-d]    'ignore                    ) ; delete-char
(global-set-key [?\C-e]    'ignore                    ) ; move-end-of-line
(global-set-key [?\C-f]    'isearch-forward           ) ; forward-char
(global-set-key [?\C-g]    'goto-line                 ) ; keyboard-quit
(global-set-key [?\C-j]    'ignore                    ) ; eval-print-last-sexp
(global-set-key [?\C-k]    'ignore                    ) ; kill-line
(global-set-key [?\C-l]    'recenter                  ) ; recenter-top-bottom
(global-set-key [?\C-n]    'new-buffer                ) ; next-line
(global-set-key [?\C-o]    'find-file                 ) ; open-line
(global-set-key [?\C-p]    'admb-open                 ) ; previous-line
(global-set-key [?\C-q]    'save-buffers-kill-emacs   ) ; quoted-insert
(global-set-key [?\C-r]    'query-replace             ) ; isearch-backward
(global-set-key [?\C-s]    'save-buffer               ) ; isearch-forward
(global-set-key [33554451] 'write-file                ) ; C-S
(global-set-key [?\C-t]    'ignore                    ) ; transpose-chars
(global-set-key [?\C-u]    'ignore                    ) ; universal-argument
(global-set-key [?\C-w]    'kill-buffer-maybe-window  ) ; kill-region
(global-set-key [?\C-y]    'ignore                    ) ; yank
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
(defun admb-ide-version ()
  "Show ADMB IDE version number." (interactive)
  (message "ADMB-IDE version %s" admb-ide-version))
;;==============================================================================
;;
;; 6  LANGUAGE MODES
;;
;;==============================================================================
;;-----------
;; 6.2  ADMB
;;-----------
(defun easy-admb-hook ()
  (message nil)
  (local-unset-key [S-f11]            )
  (local-unset-key [?\C-c C-backspace])
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
  (local-set-key [f7]    'admb-tpl2cpp        )
  (local-set-key [f8]    'admb-build          )
  (local-set-key [f9]    'admb-run            )
  (local-set-key [S-f9]  'admb-run-args       )
  (local-set-key [f10]   'admb-rep            ) ; menu-bar-open
  (local-set-key [S-f10] 'admb-cor            )
  (local-set-key [?\C-.] 'admb-toggle-section))
(add-hook 'admb-mode-hook 'easy-admb-hook)
;;----------
;; 6.5  C++
;;----------
(defun easy-gdb-hook ()
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
(add-hook 'gdb-mode-hook 'easy-gdb-hook)
;;----------
;; 6.17 TMB
;;----------
(require 'tmb)
(defun easy-tmb-hook ()
  (set-face-attribute 'font-lock-warning-face nil :weight 'normal     )
  (set-face-attribute 'tmb-block-face         nil :foreground "sienna")
  (set-face-attribute 'tmb-data-face          nil :foreground "sienna")
  (set-face-attribute 'tmb-parameter-face     nil :foreground "sienna")
  (set-face-attribute 'tmb-report-face        nil :foreground "sienna")
  (local-unset-key [?\C-c ?\C-.])
  (local-unset-key [?\C-c ?\C-/])
  (local-unset-key [?\C-c ?\C-b])
  (local-unset-key [?\C-c ?\C-c])
  (local-unset-key [?\C-c ?\C-d])
  (local-unset-key [?\C-c ?\C-k])
  (local-unset-key [?\C-c ?\C-l])
  (local-unset-key [?\C-c ?\C-m])
  (local-unset-key [?\C-c ?\C-n])
  (local-unset-key [?\C-c ?\C-p])
  (local-unset-key [?\C-c ?\C-q])
  (local-unset-key [?\C-c ?\C-r])
  (local-unset-key [?\C-c ?\C-t])
  (local-unset-key [?\C-c ?\C-v])
  (local-unset-key [?\C-c ?\C-w])
  (local-set-key [f7]  'tmb-clean         )
  (local-set-key [f8]  'tmb-compile       )
  (local-set-key [f9]  'tmb-run           )
  (local-set-key [f10] 'tmb-debug         )
  (local-set-key [f11] 'tmb-open          )
  (local-set-key [f12] 'tmb-template-mini))
(add-hook 'tmb-mode-hook 'easy-tmb-hook)
;;==============================================================================
;;
;; 7  OTHER MODES
;;
;;==============================================================================
;;-----------
;; 7.16 Help
;;-----------
(defun easy-help-hook ()(local-set-key [escape] 'kill-buffer-maybe-window))
(add-hook 'help-mode-hook 'easy-help-hook)
;;--------------
;; 7.26 Outline
;;--------------
(defvar outline-previous-mode '(admb-mode)
  "Mode to return to. See `outline-return'.")
(defun easy-outline-hook ()
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
(add-hook 'outline-mode-hook 'easy-outline-hook)
;;--------------
;; 7.29 Recentf
;;--------------
(defun easy-recentf-hook ()(local-set-key [escape] 'recentf-cancel-dialog))
(add-hook 'recentf-dialog-mode-hook 'easy-recentf-hook)
;;-------------
;; 7.32 Search
;;-------------
(defun easy-isearch-hook ()
  (define-key isearch-mode-map [escape] 'isearch-exit           )
  (define-key isearch-mode-map [?\C-f]  'isearch-repeat-forward))
(add-hook 'isearch-mode-hook 'easy-isearch-hook)

;; .emacs ends here
