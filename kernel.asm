;kernel.asm
;Michael Black, 2007

;Thomas OLeary
;Jarrod LeComte

;kernel.asm contains assembly functions that you can use in your kernel

	.global _putInMemory
	.global _interrupt
	.global _makeInterrupt21
	.extern _handleInterrupt21

;void putInMemory (int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret
;int interrupt(int number, int AX, int BX, int CX, int DX)
_interrupt:
	push bp
	mov bp,sp
	mov ax,[bp+4] ;get the interrupt number in AL
	push ds       ;use self-modifying code to call the right interrupt
	mov bx,cs
	mov ds,bx
	mov si,#intr
	mov [si+1],al ;change the 00 below to the contents of AL
	pop ds
	mov ax,[bp+6] ;get the other parameters AX,BX,CX,DX
	mov bx,[bp+8]
	mov cx,[bp+10]
	mov dx,[bp+12]

	intr: int #0x00 ;call the interrupt(00 will be changed above)

		mov ah,#0 ;only want AL returned
		pop bp
		ret

	;void makeInterrupt21()
	;this sets up the interrupt 0x21 vector
	;when an interrupt 0x21 is called in the future,
	;_interrupt21ServiceRoutine will run

_makeInterrupt21:
	get the address of the service routine
	mov dx,#_interrupt21ServiceRoutine
	push ds
	mov ax,#0interrupts are in lowest memory
	mov ds,ax
	mov si,#0x84interrupt 0x21 vector (21*4=84)
	mov ax,cshave interrupt go to the current segment
	mov [si+2],ax
	mov [si],dxset up our vector
	pop ds
	ret

_interrupt21ServiceRoutine:
	push dx
	push cx
	push bx
	push ax
	call _handleInterrupt21
	pop ax
	pop bx
	pop cx
	pop dx
	iret

