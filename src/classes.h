
#ifndef CLASSES_H
#define CLASSES_H

#include <time.h>
#define MINX 3
#define MAXX 12 
#define MAXY 31
#define MINY 1
#define ROW 32
#define COL 16

extern char screen[ROW][COL];

class Block {
private:
protected:
	int x,y, color;
public:
	Block();
  Block(int color);
  Block(int x,int y,int color);
  void draw();
	void move_r();
  void move_l();
	void move_d();
	void setLocation(int x, int y);
	void setRelativeLocation(int X, int Y);
  void setX(int X);
  void setY(int Y);
  int getX();
  int getY();
	void setColor(int Color);
  void clear();
	void remove();
  bool isFalling();
  bool isClear_l();
  bool isClear_r();
	bool isScreenSet(int x, int y);
	bool isScreenSetRelative(int x, int y);
};


class Shape {
private:
protected:
	Block blocks[4];
  int x,y, orientation, color;
	virtual bool isClearRot_r()=0;
	virtual bool isClearRot_l()=0;
public:
	Shape();
	Shape(int color);
	Shape(int x, int y, int color);
	virtual void move_r()=0;
	virtual void move_l()=0;
	virtual void move_d()=0;
	virtual void rotate_r()=0;
  virtual void rotate_l()=0;
  virtual bool isFalling()=0;
	virtual bool isClear_l()=0;
	virtual bool isClear_r()=0;
	virtual int  getType()=0;
	virtual void setLocation(int x, int y)=0;
	virtual void make(int x, int y);
	void setOrientation(int orientation);	
	void setCenter(int x, int y);
	void clear();
	void draw();
	void moveR();
	void moveL();
	void moveD();
};


#endif
