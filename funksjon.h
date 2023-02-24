#ifndef FUNKSJON_H
#define FUNKSJON_H
#include <cmath>
#include "visualobject.h"
#include <eigen-3.4.0/Eigen/Dense>



class Funksjon : public VisualObject
{
public:
    Funksjon();
  ~Funksjon();

    void constructCurve();

   float mA;
   float mB;
   float mC;
   float mD;


    void init(GLint matrixUniform) override;
    void draw() override;
private:

};

#endif // FUNKSJON_H
