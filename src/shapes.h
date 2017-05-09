#ifndef SHAPES_H
#define SHAPES_H

#include "classes.h"


class Square: public Shape{
public:
	Square();
	Square(int x, int y, int color);
  virtual void make(int x, int y);
	virtual void rotate_r();
  virtual void rotate_l();
	virtual void move_r();
	virtual void move_l();
	virtual void move_d();
  virtual bool isFalling();
	virtual bool isClear_l();
	virtual bool isClear_r();
	virtual void setLocation(int, int);  
	virtual bool isClearRot_r();
	virtual bool isClearRot_l();
	virtual int  getType();
private:
};

class Line: public Shape{
public:
	Line();
	Line(int x, int y, int color);
  virtual void make(int x, int y);
	virtual void rotate_r();
  virtual void rotate_l();
	virtual void move_r();
	virtual void move_l();
	virtual void move_d();
  virtual bool isFalling();
	virtual bool isClear_l();
	virtual bool isClear_r();
  virtual void draw();
	virtual void setLocation(int, int);  
	virtual bool isClearRot_r();
	virtual bool isClearRot_l();
	virtual int  getType();
private:
	Block *center;
};

class T: public Shape{
public:
	T();
	T(int x, int y, int color);
  virtual void make(int x, int y);
	virtual void rotate_r();
  virtual void rotate_l();
	virtual void move_r();
	virtual void move_l();
	virtual void move_d();
  virtual bool isFalling();
	virtual bool isClear_l();
	virtual bool isClear_r();
	virtual void setLocation(int, int);  
	virtual bool isClearRot_r();
	virtual bool isClearRot_l();
	virtual int  getType();

private:
};

class Z1: public Shape{
public:
	Z1();
	Z1(int x, int y, int color);
  virtual void make(int x, int y);
	virtual void rotate_r();
  virtual void rotate_l();
	virtual void move_r();
	virtual void move_l();
	virtual void move_d();
  virtual bool isFalling();
	virtual bool isClear_l();
	virtual bool isClear_r();
	virtual void setLocation(int, int);  
	virtual bool isClearRot_r();
	virtual bool isClearRot_l();
	virtual int  getType();
private:
};
#endif
