import re
import string

def printsomething():
	print("Hello from python!")

def PrintMe(v):
	print("You send me: " + v)
	return 100

def squareValue(v):
	return v * v

def PrintMenu():											# Printing Menu for loop. 
	print("1: Display a Multiplication Table")
	print("2: Double a Value")
	print("3: Exit")
	print("Enter your selection as a number 1, 2, or 3.")

def DoubleValue(v):											# Function to double a value. 
	return v * 2

def MultiplicationTable(v):
	for i in range(1, 11):									# For loop used to go through numbers 1-10
		print(str(i) + " * " + str(v) + " =", end =" ")		# str() function used to concatenate print string
		print(i * v)										# printing integer
	return 0