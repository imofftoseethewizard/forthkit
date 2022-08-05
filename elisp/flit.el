;;; flit.el -- major mode for editing flit source files.

;; TODO: interactive refinement (re-fontify on edit kw), multiline strings

;; Text Properties

;; The flit reader has two modes. They affect how lines are
;; interpreted as comments or code.  The literate mode is designed so
;; that a valid Markdown document is valid flit code provided that the
;; lines indented by at least 4 spaces are valid flit code. The
;; interactive mode doesn't necessarily mean that the text itself
;; comes from an interactive tty, just that it is the mode typically
;; used when that is the case. Likewise, literate mode does not
;; necessarily mean that the code is being read from a file, but it is
;; a little awkward to use in an interactive session.

;; There are two basic types of lines in literate mode. Comment lines
;; and code lines. These are inspired by Markdown syntax, where code
;; is indented by four spaces, and comments are any line with a
;; non-space character in the first four columns. It differs from
;; Markdown in that a comment line adjacent to an indented line does
;; not make the indented line a comment line. This is strictly a
;; line-based rule and does not consider the context of the line.

;; Interactive mode only has code lines.

;; Code lines can be interpreted code, compiled code, symbolic code or
;; some mix of the two. Interpreted code is delimited by unnested
;; pairs of `[', `(', or `((' and `]', `)', or `))',
;; respectively. Note that strictly speaking, these do not need to
;; match, and a file could begin or end with any one of them and be
;; valid. They are more like switches than the nested delimiters they
;; usually represent. The first three switch from (presumably)
;; compiling to interpreting, and the latter three switch back. While
;; `[ [ ]' is likely not valid code, it ends in the interpreting state
;; regardless. Symbolic code is delimited by matched pairs of braces,
;; `{' and `}'.

;; The remainder of the text in a file is either a literal value in
;; one of a limited set of sublanguages, an identifier, or one of two
;; keywords in the language.

;; The keywords are `literate' and `interactive', and they switch from
;; the literal reader to the interactive reader.

;; Identifiers are really the catchall for anything else that doesn't
;; match one of the categories above, or one of the value sublanguages.

;; There are six value sublangauges currently: integers, symbols, stack
;; rearrangements, single-line strings, multi-line strings, and
;; comments. A integer is a non-empty sequence of hexidecimal digits
;; optionally beginning with a `-' or ending with a `.'. A symbol is a
;; sequence of non-blank characters following a `#'. A stack
;; rearrangement is a sequence of lowercase letters and dots delimited
;; by vertical bars. A single line string is a sequence of characters
;; enclosed by double quotes `"', following the usual `\' convention
;; for escaping special characters or the delimiter. A single line
;; string may also be enclosed by single quotes `'', but her the
;; backslash escape rule is not used, but rather the double-delimiter
;; rule. A multiline string begins with a `|+' similar to yaml. If
;; there are non-space characters in the remainder of the line after
;; the opening delimiter, the first space delimited group forms the
;; closing delimited, and the rest are quietly ignored. Similarly,
;; characters on subsequent lines in columns to the left of the
;; vertical bar are ignored (unless we are in literate mode and and
;; there is a character in columns 1, 2, 3, or 4). Comments follow the
;; Forth convention of beginning with a blackslash followed
;; immediately by a space, and then continuing through the end of the
;; line.

;; The design of flit enables the addition of other sublanguages. For
;; example, a format string sublanguage similar in capability to
;; Python's f-strings would be a useful addition, but it could be
;; something more complex, like a full embedding of SQL. Accordingly,
;; the design of this mode must be similarly modularized.

;; All of the above will be represented by the following faces:
;; `flit-literate-comment', `flit-line-comment', `flit-numeric-value',
;; `flit-symbolic-value', `flit-string-value', `flit-interpret',
;; `flit-compile', `flit-keyword'. There is also
;; `flit-warning' for syntactically troublesome spots (described
;; below). As is typical with Emacs modes, text properties provide a
;; cache of useful information to enable a fast determination of the
;; face for any given character in a buffer.

;; When determining the face of a character, the first consideration
;; is whether or not the line containing that character is in a
;; literate region or a interactive region. If it is a literate
;; region, we need to know the first 4 characters of the containing
;; line. If any is not a space, then we apply comment face. Otherwise,
;; we need to know whether or not we are in a multiline
;; string. There's no way to know that without (potentially) searching
;; all the way back to the start of the buffer. That is obviously
;; going to become problematic for large files. As such, we'll keep a
;; list of the staring and ending positions of all multiline strings.
;; If the character is not in a multiline string (or a literate
;; comment), it may be in one of the single-line sublanguage values,
;; or an ordinary word. In either case, we just need to scan forward
;; from the beginning of the line to the character. In the event that
;; none of the sublanguages apply, then it will be an ordinary
;; word. An ordinary word could be interpreted, compiled, or quoted
;; (in symbolic mode), and to determine which, we'll need to search
;; back in the file, skipping over any literate comments for an
;; indication what mode the interpreter ought to be in at that point.
;; While it is likely that there will be frequent transitions between
;; interpreter modes throughout the source such that back scanning in
;; this way is not costly, it may prove useful to cache this
;; information at the start of each line.

;; The preceding rough sketch of an algorithm requires that certain
;; data be maintained about the text in the buffer:

(defvar flit-keywords
  '("[" "(" "((" "{" "}" "]" ")" "))"))

;; I'd probably put in a default that you want, as opposed to nil
(defvar flit-tab-width 4 "Width of a tab for flit mode")

(defface flit-comment
  '((t :foreground "#a8fba8"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-char
  '((t :foreground "limegreen"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-string
  '((t :foreground "limegreen"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-multiline-text
  '((t :foreground "limegreen"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-keyword
  '((t :foreground "lightslategray"
       :weight bold
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-reader-keyword
  '((t :foreground "brightwhite"
       :weight bold
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-warning
  '((t :foreground "brightred"
       :weight bold
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-integer
  '((t :foreground "yellow"
       :weight bold
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-interpreted-word
  '((t :foreground "#e6d8ad"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-compiled-word
  '((t :foreground "lightblue"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-symbolic-word
  '((t :foreground "#e6add8"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-stack-rearrangement
  '((t :foreground "orange"
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defface flit-symbol
  '((t :foreground "white"
       :weight bold
       ))
  "Face for function parameters."
  :group 'flit-mode)

(defun flit-previous-property (pos prop &optional default)
  (let ((prev (previous-single-property-change pos prop)))
    (if (not prev)
        (list prev default)
      (let ((value (get-text-property prev prop)))
        (if value
            (list prev value)
          (flit-previous-property prev prop default))))))

(defun flit-previous-property-value (pos prop &optional default)
  (cadr (flit-previous-property pos prop default)))

(defun flit-reader-mode (pos)
  (flit-previous-property-value pos 'flit-reader-mode 'literate))

(defun flit-interpreter-mode (pos)
  (flit-previous-property-value pos 'flit-interpreter-mode 'compiling))

(defvar flit-interpreter-modes
  '())

(defvar flit-interpreter-modelist '(compiling))

(defun flit-compiling? ()
  (eq (car flit-interpreter-modelist) 'compiling))

(defun flit-interpreting? ()
  (eq (car flit-interpreter-modelist) 'interpreting))

(defun flit-multiline-string? ()
  (eq (car flit-interpreter-modelist) 'multiline-string))

(defun flit-quoting? ()
  (eq (car flit-interpreter-modelist) 'quoting))

(defun flit-set-interpreter-mode (mode)
  (setq flit-interpreter-modelist (cons mode (cdr flit-interpreter-modelist))))

(defun flit-set-compiling-mode ()
  (setq flit-interpreter-modelist (cons 'compiling (cdr flit-interpreter-modelist))))

(defun flit-set-interpreting-mode ()
  (setq flit-interpreter-modelist (cons 'interpreting (cdr flit-interpreter-modelist))))

(defun flit-push-interpreter-mode (mode)
  (setq flit-interpreter-modelist (cons mode flit-interpreter-modelist)))

(defun flit-pop-interpreter-mode ()
  (setq flit-interpreter-modelist (cdr flit-interpreter-modelist)))

(defvar flit-mode-syntax-table
  (let ((table (make-syntax-table))
        (char 0))

    ; All control characters plus space are whitespace
    (while (< char ?!)
      (modify-syntax-entry char " " table)
      (setq char (1+ char)))

    ; All ascii and extended ascii
    (while (< char 256)
      (modify-syntax-entry char "w" table)
      (setq char (1+ char)))

    table))

(defun flit-token-entry-re (token-entry)
  (concat "\\(" (cdr token-entry) "\\)"))

(defun flit-make-token-re (tokens)
  (concat "\\(?:"
	  (mapconcat 'flit-token-entry-re tokens "\\|")
	  "\\)"))

(defun flit-make-tokenset (tokens)
  `(,tokens
    ,(flit-make-token-re tokens)
    ,(+ 1 (length tokens))))

(defun flit-tokenset-tokens (ts)
  (nth 0 ts))

(defun flit-tokenset-re (ts)
  (nth 1 ts))

(defun flit-tokenset-re-group-count (ts)
  (nth 2 ts))

(defconst flit-ordinary-tokenset
  (flit-make-tokenset
   '((begin-interpret        . "\\<\\(?:\\[\\|(\\{1,2\\}\\)\\>")
     (end-interpret          . "\\<\\(?:]\\|)\\{1,2\\}\\)\\>")
     (reader-keyword         . "\\<interactive\\|literate\\>")
     (begin-quote            . "\\<{\\>")
     (end-quote              . "\\<}\\>")
     (begin-multiline-string . "\\<|\\+\\>")
     (char                   . "\\<'\\\\?.'\\>")
     (comment                . "\\<\\<\\\\[^\n]*\\>")
     (integer                . "\\<-?\\(?:[0-9]+\\|0b[01]+\\|0[xX][0-9a-fA-F]+\\)[lL]?\\>")
     (stack-rearrangement    . "\\<|[a-z.]+|\\>")
     (string                 . "\\<\"\\(?:[^\"\\]\\|\\\\.\\)*\"\\>")
     (symbol                 . "\\<#[^ ]*\\>")
     (word                   . "\\<[[:word:]]+\\>"))))

(defvar flit-multiline-string-tokenset nil)

(defun flit-tokenset (pos)
  ;(eq 'multiline-string (flit-interpreter-mode pos))
  (if (flit-multiline-string?)
      flit-multiline-string-tokenset
    flit-ordinary-tokenset))

(defun flit-next-tokenset-token (ts pos)
  (let ((token-re (flit-tokenset-re ts))
        (token-re-group-count (flit-tokenset-re-group-count ts))
        (tokens (flit-tokenset-tokens ts)))
    (if (re-search-forward token-re pos t)
      (let ((n 1))
        (while (and (eq nil (match-string n))
                    (<= n token-re-group-count))
          (setq n (+ n 1)))
        `(,(car (nth (- n 1) tokens)) ,(match-beginning n) . ,(match-end n)))
    nil)))

(defun flit-next-token (pos)
  (flit-next-tokenset-token (flit-tokenset pos) pos))

(defun flit-begin-interpreting (from to)
  (add-text-properties from to
                       '(flit-interpreter-mode interpreting face flit-keyword fontified t))
  (flit-set-interpreting-mode))

(defun flit-begin-compiling (from to)
  (add-text-properties from to
                       '(flit-interpreter-mode compiling face flit-keyword fontified t))
  (flit-set-compiling-mode))

(defun flit-begin-quoting (from to)
  (add-text-properties from to
                       '(flit-interpreter-mode quoting face flit-keyword fontified t))
  (flit-push-interpreter-mode 'quoting))

(defun flit-multiline-string-tokens (prefix-length)
  `((end-multiline-string         . ,(format "^ \\{%d\\}|\\>" (- prefix-length 1)))
    (multiline-indent             . ,(format "^ \\{%d\\}" prefix-length))
    (multiline-out-of-bounds-text . ,(format "^[^\n]\\{0,%d\\}" prefix-length))
    (multiline-text               . "[^\n]*")))

(defun flit-multiline-string-prefix-length ()
  (- (current-column) 1))

(defun flit-update-multiline-string-tokenset ()
  (setq flit-multiline-string-tokenset
        (flit-make-tokenset
         (flit-multiline-string-tokens (flit-multiline-string-prefix-length)))))

(defun flit-begin-multiline-string (from to)
  (flit-update-multiline-string-tokenset)
  (flit-push-interpreter-mode 'multiline-string)
  (add-text-properties from to
                       '(flit-interpreter-mode multiline-string face flit-string fontified t))
  (if (re-search-forward " *\n" to t)
      (backward-char)
    (add-text-properties to (line-end-position) '(face flit-warning fontified t))
    (end-of-line)))

(defun flit-end-complex-value-mode (from to)
  (let ((face (if (flit-multiline-string?) 'flit-string 'flit-keyword)))
    (flit-pop-interpreter-mode)

    (add-text-properties from to
                         `(flit-interpreter-mode ,(car flit-interpreter-modelist)
                           face ,face
                           fontified t))))

(defconst flit-simple-token-types
  '(char comment integer multiline-text stack-rearrangement string symbol))

(defun flit-fontify-token (token)
  (if token
      (let ((type (car token))
            (from (cadr token))
            (to (cddr token)))

        (cond
         ((and (eq type 'begin-interpret) (flit-compiling?))
          (flit-begin-interpreting from to))

         ((and (eq type 'end-interpret) (flit-interpreting?))
          (flit-begin-compiling from to))

         ((and (eq type 'begin-quote)
               (or (flit-compiling?)
                   (flit-interpreting?)))
          (flit-begin-quoting from to))

         ((eq type 'begin-multiline-string)
          (flit-begin-multiline-string from to))

         ((memq type '(end-multiline-string end-quote))
          (flit-end-complex-value-mode from to))

         ((memq type flit-simple-token-types)
          (add-text-properties from to
                               `(face ,(intern (concat "flit-" (symbol-name type))) fontified t)))

         ((and (memq type '(begin-interpret end-interpret)) (flit-quoting?))

          (add-text-properties from to
                               '(face flit-symbolic-word fontified t)))

         ((and (eq type 'reader-keyword)
               (flit-interpreting?))

          (add-text-properties from to
                               `(flit-reader-mode ,(intern (buffer-substring from to))
                                                  face flit-reader-keyword fontified t)))

         ((eq type 'word)
          (let ((face (cond
                       ((flit-compiling?)
                        'flit-compiled-word)

                       ((flit-interpreting?)
                        'flit-interpreted-word)

                       ((flit-multiline-string?)
                        'flit-string)

                       ((flit-quoting?)
                        'flit-symbolic-word)

                       (t
                        (message "unknown mode: %s" (car flit-interpreter-modelist))
                        'flit-warning))))

            (remove-text-properties from to
                                    '(flit-reader-mode nil
                                                       flit-interpreter-mode nil))

            (add-text-properties from to `(face ,face fontified t))))

         (t
          (message "warning face: %s" type)
          (add-text-properties from to '(face flit-warning fontified t))))))

  token)

(defun flit-set-code-properties (pos)
  (flit-set-interpreter-mode (flit-interpreter-mode (point)))
  (while (and (< (point) pos)
              (flit-fontify-token (flit-next-token pos)))))

(defconst flit-literate-comment-re "^ \\{0,3\\}[^ \n].*")

(defun flit-line-category (prior-category)
  (save-excursion
      (if (and (eq (flit-reader-mode (point)) 'literate)
               (re-search-forward flit-literate-comment-re (line-end-position) t))
          'literate-comment
        'code)))

(defvar flit-set-text-properties-last-pos nil)
(defvar flit-set-text-properties-reset-threshold 100)

(defun flit-requires-interpreter-mode-reset (pos)
  (or (not flit-set-text-properties-last-pos)
          (> flit-set-text-properties-last-pos pos)
          (< flit-set-text-properties-reset-threshold
             (abs (- flit-set-text-properties-last-pos pos)))))

(defun flit-reset-interpreter-mode (pos)
  (let ((prev pos)
        (modelist nil)
        (count 3))
    (while (and (> count 0)
                prev
                (not (memq (car modelist) '(compiling interpreting))))
      (let ((prev-value (flit-previous-property prev 'flit-interpreter-mode 'compiling)))
        (setq prev (and (car prev-value) (- (car prev-value) 1)))
        (setq count (- count 1))
        (setq modelist (append modelist (cdr prev-value)))
        (message "flit-reset-interpreter-mode (inner): %d %s" (or prev -1) modelist)))
    (message "flit-reset-interpreter-mode: %d %s" (or prev -1)  modelist)
    (setq flit-interpreter-modelist modelist)))

(defun flit-set-text-properties (pos)
  (with-silent-modifications
    (save-excursion
      (save-match-data

        (if (flit-requires-interpreter-mode-reset pos)
            (flit-reset-interpreter-mode pos))

        (setq flit-set-text-properties-last-pos pos)

        (forward-line 0)
        (let ((prior-category (get-text-property (point) 'flit-line-category))
              (limit (min (+ 1 pos) (point-max))))
          (while (< (point) limit)
            (let ((line-category (flit-line-category prior-category)))
              (add-text-properties (point) (line-end-position) `(flit-line-category ,line-category))

              (cond
               ((eq line-category 'literate-comment)
                (add-text-properties (point) (line-end-position)
                                     '(face flit-comment fontified t)))

               ((eq line-category 'code)
                (flit-set-code-properties (line-end-position))))

              (setq prior-category line-category))
            (forward-line)))))))

(defun flit-fontification-function (pos)
  (flit-set-text-properties pos))

(defun flit-after-change-function (from to len)
  (save-excursion
    (goto-char from)
    (flit-set-text-properties to)))

(define-derived-mode flit-mode fundamental-mode "Flit"

  (when flit-tab-width
    (setq tab-width flit-tab-width))

  (make-local-variable 'fontification-functions)
  (make-local-variable 'after-change-functions)

  (add-hook 'fontification-functions 'flit-fontification-function))

(add-hook 'flit-mode-hook 'superword-mode)
(add-hook 'flit-mode-hook
          (lambda ()
            (message "flit mode")
            (add-hook 'after-change-functions 'flit-after-change-function)
            (set-syntax-table flit-mode-syntax-table)
            (save-excursion
              (goto-char (point-min))
              (flit-set-text-properties (point-max)))))

(provide 'flit-mode)
