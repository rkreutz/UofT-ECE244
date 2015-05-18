#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
#define pi 3.1415
using namespace std;

Circle::Circle(string _name, string _colour, float _xcen, float _ycen, float _radius)
        : Shape (_name, _colour, _xcen, _ycen) {
    radius = _radius;
}

Circle::~Circle(){
    
}

void Circle::print() const {
    Shape::print();
    cout << "radius: " << radius << endl;
}

void Circle::scale(float scaleFac){
    radius *= scaleFac;    
}

float Circle::computeArea() const {
    return (pi*radius*radius);   
}

float Circle::computePerimeter() const {
    return (2.0*pi*radius);   
}

void Circle::draw(easygl* window) const {
    window->gl_setcolor(getColour());
    window->gl_fillarc (getXcen(), getYcen(), radius, 0, 360);   
}

bool Circle::pointInside(float x, float y) const {
    t_point click;
    
    click.x = x - getXcen();
    click.y = y - getYcen();
    
    if( sqrt( pow(click.x,2) + pow(click.y,2) ) <= radius )
        return true;
        
    return false;   
}
