;Thomas OLeary
;Jarrod LeComte

void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);
void makeInterrupt21();
void main() {

	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	char* letters = "Hello World\0";
	char* line[80];
	char buffer[512];
	while(*letters != 0x0) {

		putInMemory(startVidMem, vidMemOffset, *letters);
		vidMemOffset++;
		putInMemory(startVidMem, vidMemOffset, white);
		vidMemOffset++;
		letters++;
	}
	/*
	printString("Enter a line: ");
	readString(line);
	printString(line);
	*/
	readSector(buffer,30);
	printString(buffer);
	
	makeInterrupt21();
	interrupt(0x21, 1, line, 0, 0);
	interrupt(0x21, 0, line, 0, 0);
	while(1);
}

void printString(char* chars){

	int i = 0;
	
	while(chars[i] != '\0'){
		int ch = chars[i];
			interrupt(0x10, 0xE*256+ch, 0, 0, 0);
		i++;	
	}
	
}

void readString(char* line){
	int enter = 0xd;
	int backsp = 0x8;
	int i = 0;
	while(1){
		int ascii = interrupt(0x16, 0, 0, 0, 0);
		if (ascii == enter){
			line[i] = 0xa;
			i++;
			line[i] = 0x0;
			break;
		}
		else if (ascii == backsp){
			if (i > 1){
				line[i] = 0x0;
				i--;
				interrupt(0x10, 0xe*256+0x8, 0, 0, 0);
				i++;
				interrupt(0x10, 0xe*256+0x0, 0, 0, 0);
				i--;
				interrupt(0x10, 0xe*256+0x8, 0, 0, 0);
			}

		}
		else{
			line[i] = ascii;
			interrupt(0x10, 0xe*256+ascii, 0, 0, 0);
			i++;

		}
		
   }


}

void readSector(char* buffer, int sector){

	int ah = 2; //Tells BIOS to read
	int al = 1; // Number of sectors to read
	int bx = buffer; // Address where the data should be stored to
	int ch = 0; // Track number
	int cl = sector + 1; //Relative sector number (sector+1)
	int dh = 0; // Head number
	int dl = 0x80; //Device number (0x80 for hard disk)

	int ax = ah*256+al;
	int cx = ch*256+cl;
	int dx = dh*256+dl;

	interrupt(0x13, ax, bx, cx, dx);


}

void handleInterrupt21(int AX, int BX, int CX, int DX){

	if (AX == 0){
		printString(BX);
	}
	else if (AX == 1){
		readString(BX);
	}
	else if (AX == 2){
		readSector(BX, 30);
	}
	else if (AX > 2){
		printString("Error\0");
	}

}
