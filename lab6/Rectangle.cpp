#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height)
            : Shape (_name, _colour, _xcen, _ycen) {
    width = _width;
    height = _height;
    bottomLeft.x = _xcen - (_width/2.0);
    bottomLeft.y = _ycen - (_height/2.0);
    topRight.x = _xcen + (_width/2.0);
    topRight.y = _ycen + (_height/2.0);                
}

Rectangle::~Rectangle() {
    
}

void Rectangle::print() const {
    Shape::print();
    cout << "width: " << width << " height: " << height << endl;
}

void Rectangle::scale(float scaleFac){
    width *= scaleFac;
    height *= scaleFac;
}

float Rectangle::computeArea() const {
    return (height*width);   
}

float Rectangle::computePerimeter() const {
    return (2.0*height + 2.0*width);   
}

void Rectangle::draw(easygl* window) const {
    window->gl_setcolor(getColour());
    window->gl_fillrect (bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);   
}

bool Rectangle::pointInside(float x, float y) const {
    t_point click;
    
    click.x = x - getXcen();
    click.y = y - getYcen();
    
    if( click.x >= (-(width/2.0)) && click.x <= (width/2.0) && click.y <= (height/2.0) && click.y >=  (-(height/2.0)) )
        return true;
        
    return false;   
}
