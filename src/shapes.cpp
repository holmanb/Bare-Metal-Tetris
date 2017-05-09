#include "shapes.h"
extern void redGreenBlue();
using namespace std;

/* Square Object */
Square::Square():Shape(ROW-1, MINX + 3,1)
{
}
Square::Square(int x, int y, int color):Shape(x, y, color)
{
	blocks[0].setLocation(x,y);
	blocks[1].setLocation(x+1,y);
	blocks[2].setLocation(x,y-1);
	blocks[3].setLocation(x+1,y-1);
	this->draw();
}
void Square::move_r()
{
	if(this->isClear_r())
	{
		blocks[3].move_r();
		blocks[1].move_r();
		blocks[2].move_r();
		blocks[0].move_r();
	}
}
void Square::move_l()
{
	if(this->isClear_l() )
	{
		blocks[0].move_l();
		blocks[2].move_l();
		blocks[1].move_l();
		blocks[3].move_l();
	}
}
void Square::move_d()
{
	if(this->isFalling())
	{
		blocks[2].move_d();
		blocks[3].move_d();
		blocks[1].move_d();
		blocks[0].move_d();
	}
}
bool Square::isClear_l()
{
	return (blocks[0].isClear_l() && blocks[2].isClear_l())?true:false;
}

bool Square::isClear_r()
{
	return (blocks[1].isClear_r() && blocks[3].isClear_r())?true:false;
}
bool Square::isFalling()
{
	return blocks[2].isFalling() && blocks[3].isFalling()?true:false;
}
void Square::setLocation(int x, int y)
{
	blocks[0].setLocation(x,y);
	blocks[1].setLocation(x+1,y);
	blocks[2].setLocation(x,y-1);
	blocks[3].setLocation(x+1,y-1);
}


void Square::rotate_r(){}
void Square::rotate_l(){}
void Square::make(int x, int y)
{
	this->setOrientation(0);
	this->setLocation(x,y);
}
bool Square::isClearRot_r(){return false;}
bool Square::isClearRot_l(){return false;}
int  Square::getType(){return 0;}	





/* Orientation Layout
	0 - **** (0)(1)(2)(3)
	1	- *(0)
	    *(1)
			*(2)
			*(3)
	2 - **** (3)(2)(1)(0)
	3	- *(3)
			*(2)
			*(1)
			*(0)
	*/
Line::Line():Shape(ROW-1, MINX + 3,1)
{	
		center = &blocks[1];
		orientation = 0;  // 
}
Line::Line(int x, int y, int color):Shape(x, y, color)
{
	blocks[0].setLocation(x,y);
	blocks[1].setLocation(x+1,y);
	blocks[2].setLocation(x+2,y);
	blocks[3].setLocation(x+3,y);
	orientation = 0;
	this->draw();
}
void Line::make(int x, int y)
{
	this->setOrientation(0);
	this->setLocation(x,y);
}	
void Line::draw()
{
	blocks[0].draw();
	blocks[1].draw();
	blocks[2].draw();
	blocks[3].draw();
}
void Line::move_r()
{
	if(this->isClear_r())
	{
		// Order Matters
		if(orientation == 0){
			blocks[3].move_r();
			blocks[2].move_r();
			blocks[1].move_r();
			blocks[0].move_r();
		}else if(orientation == 2){
			blocks[3].move_r();
			blocks[2].move_r();
			blocks[1].move_r();
			blocks[0].move_r();
		}else if(orientation == 1 || orientation == 3){
			blocks[3].move_r();
			blocks[2].move_r();
			blocks[1].move_r();
			blocks[0].move_r();
		}else redGreenBlue();
	}
}
void Line::move_l()
{
	if(this->isClear_l())
	{	
		// Order Matters
		if(orientation == 0){
			blocks[0].move_l();
			blocks[1].move_l();
			blocks[2].move_l();
			blocks[3].move_l();
		}else if(orientation == 2){
			blocks[3].move_l();
			blocks[2].move_l();
			blocks[1].move_l();
			blocks[0].move_l();
		}else if(orientation == 1 || orientation == 3){
			blocks[3].move_l();
			blocks[2].move_l();
			blocks[1].move_l();
			blocks[0].move_l();
		}else redGreenBlue();
	}
}
void Line::move_d()
{
	if(this->isFalling())
	{
		// Order Matters
		if(orientation == 1){
			blocks[3].move_d();
			blocks[2].move_d();
			blocks[1].move_d();
			blocks[0].move_d();
		}else if(orientation == 3){
			blocks[0].move_d();
			blocks[1].move_d();
			blocks[2].move_d();
			blocks[3].move_d();
		}else if(orientation == 0 || orientation == 2){
			blocks[3].move_d();
			blocks[2].move_d();
			blocks[1].move_d();
			blocks[0].move_d();
		}else redGreenBlue();
	}
}
bool Line::isClear_l()
{
	switch(orientation){
		case 0:
			this->draw();
			return blocks[0].isClear_l();
		case 1:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isClear_l()) return false;
			return true;
		case 2:
			this->draw();
			return blocks[3].isClear_l();
		case 3:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isClear_l()) return false;
			return true;		
		default:
				redGreenBlue();		
		return false;
	}
}

bool Line::isClear_r()
{
	switch(orientation){
		case 0:
			this->draw();
			return blocks[3].isClear_r();
		case 1:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isClear_r()) return false;
			return true;
		case 2:
			this->draw();
			return blocks[0].isClear_r();
		case 3:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isClear_r()) return false;
			return true;		
		default:
			redGreenBlue();
			return false;
	}
}

bool Line::isFalling()
{
	switch(orientation){
		case 0:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isFalling()) return false;
			return true;
		case 1:
			return blocks[3].isFalling();
		case 2:
			for(int i=0; i<4 ;i++)
				if(!blocks[i].isFalling()) return false;
			return true;
		case 3:
			return blocks[0].isFalling();
		default:
			redGreenBlue();	
		return false;
	}
}
void Line::setLocation(int x, int y)
{
	blocks[0].setLocation(x,y);
	blocks[1].setLocation(x+1,y);
	blocks[2].setLocation(x+2,y);
	blocks[3].setLocation(x+3,y);
}

/* Orientation Layout
	rotate on left middle position

	0 - **** (0)(1)(2)(3)

	1	- *				(0)
	    *				(1)
			*				(2)
			*				(3)
	2 - **** (3)(2)(1)(0)

	3	- *				(3)
			*				(2)
			*				(1)
			*				(0)
	*/

void Line::rotate_r()
{
	if(this->isClearRot_r())
	{
		for(int i=0;i<4;i++)
			blocks[i].clear();
	 		// Order Matters
		switch(this->orientation)
		{
			case 0:
				this->setOrientation(1);
				blocks[0].setRelativeLocation(1,1);
				blocks[1].setRelativeLocation(0,0);
				blocks[2].setRelativeLocation(-1,-1);
				blocks[3].setRelativeLocation(-2,-2);
				break;
			case 1:	
				center = &blocks[2];
				this->setOrientation(2);
				blocks[0].setRelativeLocation(2,-1);
				blocks[1].setRelativeLocation(1,0);
				blocks[2].setRelativeLocation(0,1);
				blocks[3].setRelativeLocation(-1,2);
				break;
			case 2:
				this->setOrientation(3);
				blocks[0].setRelativeLocation(-2,-2);
				blocks[1].setRelativeLocation(-1,-1);
				blocks[2].setRelativeLocation(0,0);
				blocks[3].setRelativeLocation(1,1);
				break;
			case 3:
				this->setOrientation(0);
				center = &blocks[1];
				blocks[0].setRelativeLocation(-1,2);
				blocks[1].setRelativeLocation(0,1);
				blocks[2].setRelativeLocation(1,0);
				blocks[3].setRelativeLocation(2,-1);
				break;
			default: redGreenBlue();
		}
	}
}

// Symetric rotation
void Line::rotate_l()
{
	this->rotate_r();
}
	
bool Line::isClearRot_r(){
		switch(orientation)
		{
			case 0:
				return !(
					blocks[2].isScreenSetRelative(0,1) ||
					blocks[2].isScreenSetRelative(0,-1)||
					blocks[2].isScreenSetRelative(0,-2)
				);				
			case 2:

				return !(
					blocks[2].isScreenSetRelative(0,1) ||
					blocks[2].isScreenSetRelative(0,-1)||
					blocks[2].isScreenSetRelative(0,-2)
				);
			case 1:
					return !(
						blocks[1].isScreenSetRelative(1,0) ||
						blocks[1].isScreenSetRelative(2,0)||
						blocks[1].isScreenSetRelative(-1,0)
					);
			case 3:
				return !(
					blocks[3].isScreenSetRelative(1,0) ||
					blocks[3].isScreenSetRelative(2,0)||
					blocks[3].isScreenSetRelative(-1,0)
				);
				default:
					redGreenBlue();
		}
		// should never get here
		redGreenBlue();
		return false;
}
bool Line::isClearRot_l(){return this->isClearRot_r();}
int Line::getType(){return 1;}






/* T Shape */
T::T():Shape(ROW-1, MINX + 3,4)
{
		orientation = 0;  
}
T::T(int x, int y, int color):Shape(x, y, color)
{
	this->setLocation(x,y);
	orientation = 0;
	this->draw();
}
void T::setLocation(int x, int y)
{
	switch(this->orientation)
	{
		case 0:
			blocks[0].setLocation(x,y);
			blocks[1].setLocation(x+1,y);
			blocks[2].setLocation(x-1,y);
			blocks[3].setLocation(x,y+1);			
			break;
		case 1:
			blocks[0].setLocation(x,y);
			blocks[1].setLocation(x,y-1);
			blocks[2].setLocation(x,y+1);
			blocks[3].setLocation(x+1,y);			
			break;
		case 2:
			blocks[0].setLocation(x,y);
			blocks[1].setLocation(x,y-1);
			blocks[2].setLocation(x,y+1);
			blocks[3].setLocation(x+1,y);				
			break;
		case 3:
			blocks[0].setLocation(x,y);
		  blocks[1].setLocation(x-1,y);
			blocks[2].setLocation(x+1,y);
			blocks[3].setLocation(x+1,y-1);	
			break;		
	}
}  

void T::make(int x, int y)
{
	this->setOrientation(0);
	this->setLocation(x,y);
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void T::move_d()
{
	if(this->isFalling())
		this->moveD();
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void T::move_r()
{
		if( this->isClear_r() )this->moveR();
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void T::move_l()
{
	if(this->isClear_l())
		this->moveL();
}

void T::rotate_r()
{
	if(this->isClearRot_r())
	{
		for(int i=0;i<4;i++)
			blocks[i].clear();
	 		// Order Matters
		switch(this->orientation)
		{
			case 0:
				this->setOrientation(1);
				blocks[1].setRelativeLocation(-1,-1);
				blocks[2].setRelativeLocation(1,1);
				blocks[3].setRelativeLocation(1,-1);
				break;
			case 1:	
				this->setOrientation(2);
				blocks[1].setRelativeLocation(-1,1);
				blocks[2].setRelativeLocation(1,-1);
				blocks[3].setRelativeLocation(-1,-1);
				break;
			case 2:
				this->setOrientation(3);
				blocks[1].setRelativeLocation(1,1);
				blocks[2].setRelativeLocation(-1,-1);
				blocks[3].setRelativeLocation(-1,1);
				break;
			case 3:
				this->setOrientation(0);
				blocks[1].setRelativeLocation(1,-1);
				blocks[2].setRelativeLocation(-1,1);
				blocks[3].setRelativeLocation(1,1);
				break;
			default: redGreenBlue();
		}
		blocks[0].draw();
	}
}
 void T::rotate_l()
{
if((this->isClearRot_l()))
	{
		for(int i=0;i<4;i++)
			blocks[i].clear();
	 		// Order Matters
		
		switch(this->orientation)
		{
		/*	case 0:
				this->setOrientation(3);
				blocks[1].setRelativeLocation(-1,1);
				blocks[2].setRelativeLocation(1,-1);
				blocks[3].setRelativeLocation(-1,-1);
			case 1:
				this->setOrientation(0);
				blocks[1].setRelativeLocation(1,1);
				blocks[2].setRelativeLocation(-1,-1);
				blocks[3].setRelativeLocation(-1,1);
			case 2:
				this->setOrientation(1);
				blocks[1].setRelativeLocation(1,-1);
				blocks[2].setRelativeLocation(-1,1);
				blocks[3].setRelativeLocation(1,1);
			case 3:
				this->setOrientation(2);
				blocks[1].setRelativeLocation(-1,-1);
				blocks[2].setRelativeLocation(1,1);
				blocks[3].setRelativeLocation(1,-1);

			*/
			case 0:
				this->setOrientation(1);
				blocks[1].setRelativeLocation(-1,-1);
				blocks[2].setRelativeLocation(1,1);
				blocks[3].setRelativeLocation(1,-1);
				break;
			case 1:	
				this->setOrientation(2);
				blocks[1].setRelativeLocation(-1,1);
				blocks[2].setRelativeLocation(1,-1);
				blocks[3].setRelativeLocation(-1,-1);
				break;
			case 2:
				this->setOrientation(3);
				blocks[1].setRelativeLocation(1,1);
				blocks[2].setRelativeLocation(-1,-1);
				blocks[3].setRelativeLocation(-1,1);
				break;
			case 3:
				this->setOrientation(0);
				blocks[1].setRelativeLocation(1,-1);
				blocks[2].setRelativeLocation(-1,1);
				blocks[3].setRelativeLocation(1,1);
				break;
				
			default: redGreenBlue();
		}
		blocks[0].draw();
	} 
}

bool T::isFalling()
{
	switch(this->orientation)
	{
		case 0:
			return (
				blocks[0].isFalling()&&
				blocks[1].isFalling()&&
				blocks[2].isFalling()
			);
		case 1:
			return (
				blocks[1].isFalling() &&
				blocks[3].isFalling()
			);
		case 2:
			return (
				blocks[1].isFalling() &&
				blocks[2].isFalling()	&&
				blocks[3].isFalling()
			);
		case 3:
			return (
				blocks[2].isFalling() &&
				blocks[3].isFalling()
			);
	} 
	redGreenBlue();
	return false;
}
	bool T::isClear_l(){	
		
		switch(this->orientation)
		{
		case 0:
			return
			(
				blocks[2].isClear_l() &&
				blocks[3].isClear_l() 
			);
		case 1:
			return (
			blocks[0].isClear_l()&&
			blocks[1].isClear_l()&&
			blocks[2].isClear_l()
			);	
		case 2:
			return(
				blocks[1].isClear_l()&&
				blocks[3].isClear_l()		
			);

		case 3:	
		  return (
				blocks[1].isClear_l()&&
				blocks[2].isClear_l()&&
				blocks[3].isClear_l()
			);			
		}
	redGreenBlue();
	return false;
}
 bool T::isClear_r()
{	
	switch(this->orientation)
	{
		case 0:
			return (
				blocks[1].isClear_r() &&
				blocks[3].isClear_r()
				);		

		case 1:
			return (
				blocks[1].isClear_r() &&
				blocks[2].isClear_r() &&
				blocks[3].isClear_r()
			);
		case 2:
			return 
			(
				blocks[2].isClear_r() &&
				blocks[3].isClear_r()
			);	

		case 3:
			return (
				blocks[0].isClear_r() &&
				blocks[1].isClear_r() &&
				blocks[2].isClear_r() 
			);
	}
	redGreenBlue();
	return false;
}


bool T::isClearRot_r()
{
	switch(this->orientation)
		{
			case 0:
				return !blocks[0].isScreenSetRelative(0,-1);
			case 1:	
				return !blocks[0].isScreenSetRelative(-1,0);
			case 2:
				return !blocks[0].isScreenSetRelative(0,1);
			case 3:
				return !blocks[0].isScreenSetRelative(1,0);
			default: redGreenBlue();
		}
		redGreenBlue();
		return false;
}
bool T::isClearRot_l(){return this->isClearRot_r();}
	 
int  T::getType(){return 2;}




/* Z1 shape */
Z1::Z1():Shape(ROW-1, MINX + 3,5)
{
		orientation = 0;  
}
Z1::Z1(int x, int y, int color):Shape(x, y, color)
{
	orientation = 0;
	this->setLocation(x,y);
	this->draw();
}
void Z1::setLocation(int x, int y)
{
	switch(this->orientation)
	{
		case 0:
			blocks[0].setLocation(x-1,y);
			blocks[1].setLocation(x,y);
			blocks[2].setLocation(x,y-1);
			blocks[3].setLocation(x+1,y-1);			
			break;
		case 1:
			blocks[0].setLocation(x,y+1);
			blocks[1].setLocation(x,y);
			blocks[2].setLocation(x-1,y);
			blocks[3].setLocation(x-1,y-1);			
			break;
	}
}  

void Z1::make(int x, int y)
{
	this->setOrientation(0);
	this->setLocation(x,y);
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void Z1::move_d()
{
	if(this->isFalling())
		this->moveD();
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void Z1::move_r()
{
		if( this->isClear_r() )this->moveR();
}

// Wrapper for the shape-level implementation
// If this works for all shapes, we will remove the move_d() series of functions
void Z1::move_l()
{
	if(this->isClear_l())
		this->moveL();
}

void Z1::rotate_r()
{
	if(this->isClearRot_r())
	{
		this->clear();
		this->setOrientation((this->orientation+1)%2);
		this->setLocation(blocks[1].getX(),blocks[1].getY() );
	}
}
 void Z1::rotate_l(){	this->rotate_r();}

bool Z1::isFalling()
{
	switch(this->orientation)
	{	
		case 0:
			return (
				blocks[0].isFalling()&&
				blocks[2].isFalling()&&
				blocks[3].isFalling()
			);

		case 1:
			return (
				blocks[3].isFalling() &&
				blocks[1].isFalling()
			);	
			default: redGreenBlue();
	} 
	redGreenBlue();
	return false;
}

bool Z1::isClear_l(){	
		switch(this->orientation)
		{
			case 0:
				return
				(
					blocks[0].isClear_l() &&
					blocks[2].isClear_l() 
				);
			case 1:
				return (
				blocks[0].isClear_l()&&
				blocks[2].isClear_l()&&
				blocks[3].isClear_l()
				);	
		}
	redGreenBlue();
	return false;
}
 bool Z1::isClear_r()
{	
	switch(this->orientation)
	{
		case 0:
			return (
				blocks[1].isClear_r() &&
				blocks[3].isClear_r()
				);		

		case 1:
			return (
				blocks[0].isClear_r() &&
				blocks[1].isClear_r() &&
				blocks[3].isClear_r()
			);
	}
	redGreenBlue();
	return false;
}

bool Z1::isClearRot_r()
{
	switch(this->orientation)
		{
			case 0:
				return !(
					blocks[1].isScreenSetRelative(0,1)	||
					blocks[1].isScreenSetRelative(-1,-1)	
				);
			case 1:	
				return !(
					blocks[1].isScreenSetRelative(1,-1)	||
					blocks[1].isScreenSetRelative(0,-1)
				);
		}
		redGreenBlue();
		return false;
}
bool Z1::isClearRot_l(){return this->isClearRot_r();}
	 
int  Z1::getType(){return 3;}

