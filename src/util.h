#ifndef UTIL_H
#define UTIL_H

#include "shapes.h"
#define brightness 50 //MAX ~2000
#define RED (1)
#define R2 (2)
#define GREEN (3)
#define G2 (4)
#define BLUE (5)
#define B2 (6)
#define RED_LED_POS (18)		// PORT B
#define GREEN_LED_POS (19)	// PORT B
#define BLUE_LED_POS (1)		// PORT D
#define CLOCK (0)
#define LAT (13)
#define MASK(x) (1UL << (x))  

// LEDs
#define a (10)
#define b (11)
#define c (12)

#define OE (16)

#define LT (17)
#define DN (7)
#define UP (8)
#define RT (9)

#define ALLPINS (MASK(RED) | MASK(R2) | MASK(GREEN) | MASK(G2) | MASK(BLUE) | MASK(B2) | MASK(CLOCK) | MASK(LAT) | MASK(a) | MASK(b) | MASK(c) | MASK(OE))
#define ROWPINS (MASK(a) | MASK(b) | MASK(c))
#define BUTTONPINS (MASK(LT) | MASK(DN) | MASK(UP) | MASK(RT))

extern const char winScreen[COL][ROW];
extern const char gameOverScreen[COL][ROW];
extern char screen[ROW][COL];

void drawScreen();
void delay_t(unsigned int time_del);
bool buttonRotate(Block &block);
bool buttonRotate(Shape &shape);
int checkButton(int);


bool isRowComplete(int row)
{
	for(int i = MINX; i<=MAXX;i++)
	{
		if(screen[row][i]==0)
			return false;
	}
	return true;
}

bool isRowEmpty(int row)
{
	for(int i = MINX; i<=MAXX;i++)
	{
		if(screen[row][i]!=0)
			return false;
	}
	return true;
}

void clearRow(int row)
{
	for(int i = MINX; i<=MAXX;i++)
	{
		screen[row][i]=0;
	}
}

void shiftRowDown(int row)
{
	for(int i = MINX; i<=MAXX;i++)
	{
		screen[row-1][i]=screen[row][i];
	}
	clearRow(row);
}

void gameOver(void)
{
	int i, j;
	if(screen[31][0]!=4)
	{
		for(i = 0; i < ROW; i++){
			for(j = 0; j < COL; j++){
				screen[i][j] = winScreen[j][i];
			}
		}		
	}else{
		// Game over
		for(i = 0; i < ROW; i++){
			for(j = 0; j < COL; j++){
				screen[i][j] = gameOverScreen[j][i];
			}
		}
	}
	while(1)
		drawScreen();
}


float difficulty_curve(int i)
{
	i<0?i=-i:true;
	return  1/(0.5*i+2)+0.5;
}
// Renders the screen and gets button push signal
void pause(unsigned int time_del, Block &block)
{
// delay is about 1 millisecond * time_del
	bool t;
	while (time_del--) 
	{
		if(time_del%10000)
			t = buttonRotate(block);
		drawScreen();
		if(t) break;
	}	
	while(t && time_del--)
		drawScreen();
}

void pause(unsigned int time_del, Shape &shape)
{
// delay is about 1 millisecond * time_del
	bool t;
	while (time_del--) 
	{
		if(time_del)//%10000)
			t = buttonRotate(shape);
		drawScreen();
		if(t) break;
	}	
	while(t && time_del--)
		drawScreen();
}

bool buttonRotate(Shape *shape)
{

		if(checkButton(LT)){
			(*shape).rotate_r();
			return true;
		}
		else if(checkButton(DN)){
			(*shape).rotate_l();
			return true;
		}
		else if(checkButton(UP)){
			(*shape).move_l();
			return true;
		}
		else if(checkButton(RT)){
			(*shape).move_r();
			return true;
		}
	return false;
}

bool buttonRotate(Shape &shape)
{

		if(checkButton(UP)){
			shape.rotate_r();
			return true;
		}
		else if(checkButton(DN)){
			shape.rotate_l();
			return true;
		}
		else if(checkButton(LT)){
			shape.move_l();
			return true;
		}
		else if(checkButton(RT)){
			shape.move_r();
			return true;
		}
	return false;
}

bool buttonRotate(Block &block)
{

		if(checkButton(UP)){
			block.move_r();
			return true;
		}
		else if(checkButton(DN)){
			block.move_l();
			return true;
		}
		else if(checkButton(LT)){
			block.move_l();
			return true;
		}
		else if(checkButton(RT)){
			block.move_r();
			return true;
		}
	return false;
}

void delay_t(unsigned int time_del)
{
// delay is about 1 millisecond * time_del
	volatile int t;
	while (time_del--) 
	{
		for (t=100; t>0; t--)
			;
	}
}



void delay(unsigned int time_del) 
{
	volatile int t;
	while (time_del--) {
		for (t=4; t>0; t--)
			;
	}
} 

//LED toggle on/off control
void pulse(int pin)
{
	PTC->PTOR = MASK(pin);
	PTC->PTOR = MASK(pin);
}


//identify player's key/button function if pressed
int checkButton(int button)
{
	return ~(PTC->PDIR) & MASK(button);
}

void redGreenBlue(void)
{
	 // set just red led on
	PTB->PDOR = ~ MASK(RED_LED_POS);
	PTD->PDOR = 0xFFFFFFFF;
	delay_t(500);
	
	// set just green led on
	PTB->PDOR = ~ MASK(GREEN_LED_POS);
	PTD->PDOR = 0xFFFFFFFF;
	delay_t(500);
	
	// set just blue led on
	PTB->PDOR = 0xFFFFFFFF;
	PTD->PDOR = ~ MASK(BLUE_LED_POS);
	delay_t(500);
}

void initLED(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1); 
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1); 
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1); 
	
	// Set PORTs to outputs: PORT Data Direction Register (PDDR)
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
	PTB->PSOR = MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PSOR = MASK(BLUE_LED_POS);
}

void init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTC->PCR[RED] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[RED] |= PORT_PCR_MUX(1);
	PORTC->PCR[R2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[R2] |= PORT_PCR_MUX(1);
	PORTC->PCR[GREEN] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[GREEN] |= PORT_PCR_MUX(1);
	PORTC->PCR[G2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[G2] |= PORT_PCR_MUX(1);
	PORTC->PCR[BLUE] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[BLUE] |= PORT_PCR_MUX(1);
	PORTC->PCR[B2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[B2] |= PORT_PCR_MUX(1);

	PORTC->PCR[a] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[a] |= PORT_PCR_MUX(1);
	PORTC->PCR[b] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[b] |= PORT_PCR_MUX(1);
	PORTC->PCR[c] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[c] |= PORT_PCR_MUX(1);

	PORTC->PCR[CLOCK] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[CLOCK] |= PORT_PCR_MUX(1);

	PORTC->PCR[LAT] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[LAT] |= PORT_PCR_MUX(1);

	PORTC->PCR[OE] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[OE] |= PORT_PCR_MUX(1);

	PTC->PDDR |= ALLPINS;

	PTC->PCOR = ALLPINS;
	PTC->PSOR = MASK(OE);

	PORTC->PCR[LT] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[DN] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[UP] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[RT] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[LT] |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK) | PORT_PCR_PS_MASK;
	PORTC->PCR[DN] |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK) | PORT_PCR_PS_MASK;
	PORTC->PCR[UP] |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK) | PORT_PCR_PS_MASK;
	PORTC->PCR[RT] |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK) | PORT_PCR_PS_MASK;
}

//LED on/off control
void set(int pin)
{
	PTC->PSOR = MASK(pin);
}
//LED on/off control
void clear(int pin)
{
	PTC->PCOR = MASK(pin);
}

void setCOL(int row)
{
	PTC->PCOR = ROWPINS;
	switch(row){
	case 0: case 8: //000
		PTC->PCOR = MASK(a) | MASK(b) | MASK(c);
		break;
	case 1: case 9: //001
		PTC->PCOR = MASK(b) | MASK(c);
		PTC->PSOR = MASK(a);
		break;
	case 2: case 10: //010
		PTC->PCOR = MASK(a) | MASK(c);
		PTC->PSOR = MASK(b);
		break;
	case 3: case 11: //011
		PTC->PCOR = MASK(c);
		PTC->PSOR = MASK(a) | MASK(b);
		break;
	case 4: case 12: //100
		PTC->PCOR = MASK(a) | MASK(b);
		PTC->PSOR = MASK(c);
		break;
	case 5: case 13: //101
		PTC->PCOR = MASK(b);
		PTC->PSOR = MASK(a) | MASK(c);
		break;
	case 6: case 14: //110
		PTC->PCOR = MASK(a);
		PTC->PSOR = MASK(b) | MASK(c);
		break;
	case 7: case 15: //111
		PTC->PSOR = MASK(a) | MASK(b) | MASK(c);
		break;
	}
}
void setColor(int i, int j)
{

	if(screen[i][j] & 1)
		set(RED);	else	clear(RED);
	if(screen[i][j+8] & 1)
		set(R2);	else	clear(R2);

	if(screen[i][j] & 2)
		set(GREEN);	else	clear(GREEN);
	if(screen[i][j+8] & 2)
		set(G2);	else	clear(G2);

	if(screen[i][j] & 4)
		set(BLUE);	else	clear(BLUE);
	if(screen[i][j+8] & 4)
		set(B2);	else	clear(B2);
}
void drawScreen()
{
	int i, j;
	for(j = 0; j < 8; j++){
		set(OE);
		setCOL(j);
		for(i = 0; i < 32; i++){
			setColor(i, j);
			delay(2);
			pulse(CLOCK);
		}
		pulse(LAT);
		clear(OE);
		delay(brightness);
	}
	set(OE);
}

#endif
