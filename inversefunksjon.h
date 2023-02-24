#ifndef INVERSEFUNKSJON_H
#define INVERSEFUNKSJON_H
#include <eigen-3.4.0/Eigen/Dense>

#include "visualobject.h"

class InverseFunksjon : public VisualObject
{
public:
    InverseFunksjon();
    void constructCurve();

   float mA;
   float mB;
   float mC;
   float mD;

   void init(GLint matrixUniform) override;
   void draw() override;
private:

};

#endif // INVERSEFUNKSJON_H
