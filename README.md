# ProjectB_COMP350
System Calls

# Introduction

This project focuses on the use of BIOS system calls, one of the major services for an operating system.  Here we will write system calls to print a string to the video, read a line from the keyboard and read a sector from the disk.

# Team Members

Thomas O’Leary  
Jarrod LeComte

# Step 1 – Both Team Members

•	Uses interrupt 0x10 to print characters to the screen without the need for tracking the cursor position  
•	The current cursor position will print a character to the screen when AH = 0xE and AL = the ASCII character to be printed  
•	The function interrupt(0x10, AX, 0, 0, 0) is created to handle this step where AX = AH*256+AL  
•	The function printString(char*) is also created that takes a character array and prints it to the screen  
•	A for loop is used to iterate through the character array until it reaches 0x0, which then tells the program to stop and print the result  

# Step 2 – Thomas O’Leary

•	Uses BIOS interrupt 0x16 to read a character from the keyboard and display it to the screen  
•	A function readString(char*) that takes an empty character array with at least 80 elements and uses interrupt 0x16 to save   the results in the array until ENTER (ASCII 0xd) is pressed  
•	Interrupt 0x10 is used to print each character to the screen as well as 0x8 to handle the backspace key  
•	This is solved by running a loop until the ENTER key is pressed in which the program reiterates the characters typed and exits the loop  
•	If else statements are used to determine which key is pressed using interrupt 0x16 and printed to the screen using interrupt 0x10  
•	If the keystroke == ENTER, then a line feed (0xa) and an empty character (0x0) will be added to the end of the array, respectively  
•	Backspace and ASCII keystrokes require interrupt 0x10 to print either the character or a deletion (empty space) to the screen  

# Step 3 – Jarrod LeComte

•	Use the function readSector(char*, int) to accept in a character array and a sector number to read  
•	By calculating AX, CX, and DX, you pass them into interrupt() while calling 0x13  
•	After creating a message.txt with a message inside, you put it into sector 30 of diskc.img  
•	Running the diskc.img should now display the message that message.txt contained  

# Step 4 – Jarrod LeComte

•	Remove the comment tags from the functions makeInterrupt21() and interrupt21ServiceRoutine() from kernel.asm  
•	Create a handleInterrupt21(int, int, int, int) in kernel.c to take in AX, BX, CX, and DX  
•	Add a printString() inside it to display text if it is properly called  
•	To test it, call makeInterrupt21() and then interrupt(0x21, 0, 0, 0, 0) to see if the printString() is called from the interrupt call  

# Step 5 – Thomas O’Leary

•	Interrupt 0x21 handler provides printString, readString and readSector services.  
•	The value of AX will determine which function to run  
•	The printString function initiates when AX = 0 and BX becomes the address of the string to print  
•	The readString function initiates when AX = 1 and BX becomes the address of the character array where the keys entered will go  
•	The readSector function initiates when AX = 2. BX becomes the address of the character array where the sector will go and CX is the sector number  
•	AX >= 3 will print an error message  
•	Creates the function handleInterrupt21(int AX, int BX, int CX, int DX) which reads the value of AX and runs the appropriate function  
•	If else statements are used to determine the value of AX. AX = 0 runs printString, AX = 1 runs readString, AX = 2 runs readSector and AX >= 3 produces an error  

# Verify – GitHub 
https://github.com/TomJarrod350/ProjectB_COMP350/  
