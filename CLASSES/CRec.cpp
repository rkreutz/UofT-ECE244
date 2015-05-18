#include "CRec.h"

CRectangle::CRectangle (int a, int b) {
  width = a;
  height = b;
}

CRectangle::CRectangle () {
  width = 1;
  height = 1;
}

int CRectangle::Area() {
    return width*height;
}
