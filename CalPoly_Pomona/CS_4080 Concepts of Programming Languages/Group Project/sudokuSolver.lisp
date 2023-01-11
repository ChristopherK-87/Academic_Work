;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Demo program for CS 4080 at Cal Poly Pomona
;; Author: Christopher Koepke
;; Date: 4/20/2022
;; 
;; Description: program to solve a sudoku board. sets a guess value (1-9) at an empty cell (0) and uses recursion to guess the next cell's value.
;;              if the current cell failed any check on all possible values than the program will backtrack to the previous cell and increment to
;;              that cell's next possible value, than continues to the next available cell until the board is filled.
;;
;; **NOTE** Program was created using a similar program as a reference. reference program found at:     http://www.ulisp.com/show?33J9
;;          Author unknown but is stated to be based upon a similar program authored by Daniele Mazzocchio, located at:     http://www.kernel-panic.it/software/sudokiller/sudokiller.lisp.html
;;          This program was written by scratch but follows the logic of the above referenced programs.;;         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; initialize a sudoku board for testing
(defvar sudokuBoard               
  #2A((2 0 0 0 0 0 6 9 0)
      (0 5 0 0 0 3 0 0 0)
      (1 7 0 0 0 9 4 0 5)
      (0 0 3 0 2 5 0 1 8)
      (0 0 0 0 4 0 0 0 0)
      (7 2 0 3 8 0 5 0 0)
      (5 0 2 6 0 0 0 4 1)
      (0 0 0 5 0 0 0 7 0)
      (0 6 7 0 0 0 0 0 3))
 ) ;; end of sudokuBoard


 ;; function to solve a sudoku board. if guessed element at current index passes check, than move on to next empty cell.
 (defun guess (index)             ;; if all guesses fail than backtrack to previous cell and insert another value and check conditions, than move onto next cell and continue. 
  (let ((row (truncate index 9))  ;; equivalent to floor math function; floor(index / 9) 
        (col (mod index 9)))      ;; index % 9
    (cond
     ((or (>= row 9) (>= col 9)) t) 
     ((plusp (aref sudokuBoard row col)) (guess (1+ index))) 
     (t
      (dotimes (i 9 (reset row col))
        (when (check (1+ i) row col)
          (setf (aref sudokuBoard row col) (1+ i))
          (when (guess (1+ index)) (return t)))))))
) ;; end of guess


 ;; reset given cell to zero. used when all guesses fail.
(defun reset (row col)                 
  (setf (aref sudokuBoard row col) 0)
  nil
) ;; end of reset
 

;; fucntion to check if given guess is in the row, column, or "box" of the sudoku board
(defun check (num row col)
  (let ((r (* (truncate row 3) 3))
        (c (* (truncate col 3) 3)))
    (dotimes (i 9 t)
      (when (or (= num (aref sudokuBoard row i))
                (= num (aref sudokuBoard i col))
                (= num (aref sudokuBoard (+ r (mod i 3))
                             (+ c (truncate i 3)))))
        (return nil))))
) ;; end of check


;; fucntion for formatted output of a solved sudoku board
(defun printBoard ()       
  (dotimes (r 9)
    (if (zerop (mod r 3))  ;; if r % 3 == 0
        (format t "~%-------------------------------------~%|") 
        (format t "~%|           |           |           |~%|")) ;; end if
    (dotimes (c 9)
      (if (= 2 (mod c 3))  ;; if c % 3 == 2
          (format t " ~a |" (aref sudokuBoard r c))
          (format t " ~a  " (aref sudokuBoard r c)))))  ;; end if, end do times
  (format t "~%-------------------------------------~%~%")
) ;; end of print board
 

;; handler function to solve a sudoku board; if guess fails than print "no solution"
(defun solveBoard ()  
  (if (guess 0) (printBoard)
    (format t "NO SOLUTION FOUND"))
);; end of solve


;; call to handler to solve a test sudoku board
(solveBoard)










