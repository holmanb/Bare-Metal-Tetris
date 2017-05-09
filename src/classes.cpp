#include "classes.h"

extern void redGreenBlue();

Block::Block()
{
	x = 0;
	y = 0;
	color = 1;
}
Block::Block(int color)
{
	this->color = color;
}
Block::Block(int x, int y, int color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}
void Block::setLocation(int X, int Y)
{
	//this->remove();
	x = X;
	y = Y;
	this->draw();
}
void Block::setRelativeLocation(int X, int Y)
{
	this->setLocation(this->x+X,this->y+Y);
}
void Block::setColor(int color)
{
	this->color = color;
}
void Block::move_r()
{
		screen[y][x] = 0;
		this->setX(x+1);
		this->draw();
}
void Block::move_l()
{
		screen[y][x] = 0;
		this->setX(x-1);
		this->draw();
}

void Block::move_d()
{
	this->clear();//screen[y][x] = 0;
	this->setY(y-1);
	this->draw();
}	
void Block::draw()
{
	screen[y][x] = color;
}
void Block::clear()
{
	screen[y][x] = 0;
}
void Block::remove()
{
	color = 0;
	screen[y][x] = 0;
}
bool Block::isFalling()
{
		return (screen[y-1][x] == 0);

}
void Block::setX(int X)
{
	this->x = X;
}
void Block::setY(int Y)
{
	this->y = Y;
}
int Block::getX()
{
	return x;
}
int Block::getY()
{
	return y;
}

bool Block::isClear_l()
{
	return (screen[y][(this->x-1)]==0);
}

bool Block::isClear_r()
{
	return (screen[y][(this->x+1)]==0);
}

bool Block::isScreenSet(int x, int y)
{
	return !(screen[y][x]==0);
}
bool Block::isScreenSetRelative(int x, int y)
{
	return this->isScreenSet(this->getX()+x,this->getY()+y);
}



Shape::Shape() 
{
	  //(rand() % (MAXX-MINX) + MINX), ROW-5, 1
		blocks[0] = Block();
		blocks[1] = Block();
		blocks[2] = Block();
		blocks[3] = Block();
	  x=0;
	  y=0;
		orientation=0;
}
Shape::Shape(int color) 
{
	  //(rand() % (MAXX-MINX) + MINX), ROW-5, 1
		blocks[0] = Block();
		blocks[1] = Block();
		blocks[2] = Block();
		blocks[3] = Block();
	  x=0;
	  y=0;
		orientation=0;
}
Shape::Shape(int x, int y, int color)
{	
		blocks[0] = Block(color);
		blocks[1] = Block(color);
		blocks[2] = Block(color);
		blocks[3] = Block(color);
}

void Shape::draw()
{
	for(int i =0;i<4;i++)
		blocks[i].draw();
}
void Shape::setCenter(int x, int y)
{
	this->x=x;
	this->y=y;
}

void Shape::setOrientation(int orientation)
{
	if(orientation>3||orientation<0) 	redGreenBlue();
	this->orientation = orientation;
}

void Shape::make(int x, int y){}
void Shape::clear()
{
	for(int i=0;i<4;i++) blocks[i].clear();
}
void Shape::moveR()
{
	this->clear();
	for(int i=0;i<4;i++)
		blocks[i].setX(blocks[i].getX()+1);
	this->draw();	
}
void Shape::moveL()
{
	this->clear();
	for(int i=0;i<4;i++)
		blocks[i].setX(blocks[i].getX()-1);
	this->draw();
}
void Shape::moveD()
{
	this->clear();
	for(int i=0;i<4;i++)
		blocks[i].setY(blocks[i].getY()-1);
	this->draw();
}
