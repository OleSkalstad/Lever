#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H
#include <string>
#include "visualobject.h"

class TriangleSurface : public VisualObject
{
public:
    TriangleSurface();
    TriangleSurface(std::string filnavn);
    ~TriangleSurface() override;
    void construct3();
    void constructsurface();
    void readFile(std::string filnavn);
    void init(GLint matrixUniform) override;
    void draw() override;
    float f(const float x, const float y){
        return sin(x) + cos(y);
    }
};

#endif // TRIANGLESURFACE_H
