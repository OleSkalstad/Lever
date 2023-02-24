#ifndef S_XYZ_H
#define S_XYZ_H
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class S_XYZ : public VisualObject
{
public:
    S_XYZ(float x, float y);
   ~S_XYZ() override;
   void init(GLint matrixUniform) override;
   void draw() override;

   private:
};

#endif // S_XYZ_H
