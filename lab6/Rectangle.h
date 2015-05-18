#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private:
    float width;
    float height;
    t_point bottomLeft;
    t_point topRight;
    
public:
    Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height);
    
    virtual ~Rectangle();
    
    virtual void print () const;
    virtual void scale (float scaleFac);
    virtual float computeArea () const;
    virtual float computePerimeter () const;
    virtual void draw (easygl* window) const;
    virtual bool pointInside (float x, float y) const;
};
