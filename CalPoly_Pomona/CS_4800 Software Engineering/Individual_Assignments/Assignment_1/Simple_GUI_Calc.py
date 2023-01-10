########################################################################################################################
# AUTHOR: Christopher Koepke
# CLASS: CS4800.01
# SEMESTER: FALL 2022
#
# DESCRIPTION: This programming assignment is to design a simple GUI-based Calculator that
#              can perform the following operations: addition, subtraction, multiplication, and division.
#
#              The program will display a window that shows a calculator with buttons for the digits (0-9) and the
#              operations. The user will click on each digit to input their desired value and the operations requested.
#              The buttons will append each corresponding digit/operator to a string and the program will evaluate that
#              string when the equals (=) button is clicked, then display the results.
#
#              This is my first attempt at using python to create a program. All code is my own but have followed a
#              guide on how to implement this assignment.
########################################################################################################################
from tkinter import *

# Global variable for expression to solve
expression = ""


# Function to print corresponding button to text field
######################################################
def button_pressed(num):
    global expression
    expression = expression + str(num)
    input_equation.set(expression)
######################################################


# Function to evaluate expression upon clicking the equals button
#################################################################
def solve_expression():
    try:
        global expression
        total = str(eval(expression))
        input_equation.set(total)
        expression = ""
    except:
        input_equation.set(" ERROR ")
        expression = ""
#################################################################


# Function to clear the text field
##################################
def clear():
    global expression
    expression = ""
    input_equation.set("")
##################################


# Set up the window for the calculator
gui = Tk()
gui.configure(background="light grey")
gui.title("CS4600_Koepke Simple Calculator")
gui.geometry("350x200")

# Create an instance of the Tkinter StringVar object
input_equation = StringVar()

# Create the text entry box
input_field = Entry(gui, textvariable=input_equation)
input_field.grid(columnspan=4, ipadx=60)

# Define each button for the digits 0-9, the operators: add, sub, mul, div
# Define equals button to solve the equation, decimal point, and clear
button_1 = Button(gui, text=' 1 ', fg='black', bg='white', command=lambda: button_pressed(1),
                  height=1, width=7, padx=10, pady=5)
button_1.grid(row=2, column=0)

button_2 = Button(gui, text=' 2 ', fg='black', bg='white', command=lambda: button_pressed(2),
                  height=1, width=7, padx=10, pady=5)
button_2.grid(row=2, column=1)

button_3 = Button(gui, text=' 3 ', fg='black', bg='white', command=lambda: button_pressed(3),
                  height=1, width=7, padx=10, pady=5)
button_3.grid(row=2, column=2)

button_4 = Button(gui, text=' 4 ', fg='black', bg='white', command=lambda: button_pressed(4),
                  height=1, width=7, padx=10, pady=5)
button_4.grid(row=3, column=0)

button_5 = Button(gui, text=' 5 ', fg='black', bg='white', command=lambda: button_pressed(5),
                  height=1, width=7, padx=10, pady=5)
button_5.grid(row=3, column=1)

button_6 = Button(gui, text=' 6 ', fg='black', bg='white', command=lambda: button_pressed(6),
                  height=1, width=7, padx=10, pady=5)
button_6.grid(row=3, column=2)

button_7 = Button(gui, text=' 7 ', fg='black', bg='white', command=lambda: button_pressed(7),
                  height=1, width=7, padx=10, pady=5)
button_7.grid(row=4, column=0)

button_8 = Button(gui, text=' 8 ', fg='black', bg='white', command=lambda: button_pressed(8),
                  height=1, width=7, padx=10, pady=5)
button_8.grid(row=4, column=1)

button_9 = Button(gui, text=' 9 ', fg='black', bg='white', command=lambda: button_pressed(9),
                  height=1, width=7, padx=10, pady=5)
button_9.grid(row=4, column=2)

button_0 = Button(gui, text=' 0 ', fg='black', bg='white', command=lambda: button_pressed(0),
                  height=1, width=7, padx=10, pady=5)
button_0.grid(row=5, column=1)

button_add = Button(gui, text=' + ', fg='black', bg='light grey', command=lambda: button_pressed("+"),
                    height=1, width=7, padx=10, pady=5)
button_add.grid(row=2, column=3)

button_subtract = Button(gui, text=' - ', fg='black', bg='light grey', command=lambda: button_pressed("-"),
                         height=1, width=7, padx=10, pady=5)
button_subtract.grid(row=3, column=3)

button_multiply = Button(gui, text=' * ', fg='black', bg='light grey', command=lambda: button_pressed("*"),
                         height=1, width=7, padx=10, pady=5)
button_multiply.grid(row=4, column=3)

button_divide = Button(gui, text=' / ', fg='black', bg='light grey', command=lambda: button_pressed("/"),
                       height=1, width=7, padx=10, pady=5)
button_divide.grid(row=5, column=3)

button_left_parenthesis = Button(gui, text=' ( ', fg='black', bg='light grey', command=lambda: button_pressed("("),
                                 height=1, width=7, padx=10, pady=5)
button_left_parenthesis.grid(row=5, column=0)

button_right_parenthesis = Button(gui, text=' ) ', fg='black', bg='light grey', command=lambda: button_pressed(")"),
                                  height=1, width=7, padx=10, pady=5)
button_right_parenthesis.grid(row=5, column=2)

button_equal = Button(gui, text=' = ', fg='black', bg='light grey', command=solve_expression,
                      height=1, width=7, padx=10, pady=5)
button_equal.grid(row=6, column=2)

button_clear = Button(gui, text='Clear', fg='black', bg='light grey', command=clear,
                      height=1, width=7, padx=10, pady=5)
button_clear.grid(row=6, column=1)

button_decimal = Button(gui, text='.', fg='black', bg='light grey', command=lambda: button_pressed('.'),
                        height=1, width=7, padx=10, pady=5)
button_decimal.grid(row=6, column=0)


gui.mainloop()
