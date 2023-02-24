#ifndef DISC_H
#define DISC_H

#include "visualobject.h"

class Disc : public VisualObject
{
public:
   Disc();
   Disc(std::string filnavn);
   ~Disc() override;
   void readFile(std::string filnavn);
   void writeFile(std::string filnavn);
   void init(GLint matrixUniform) override;
   void draw() override;
   void construct();
   void move(float dt) override;
protected:
   std::vector<GLuint> mIndices;   	// Til indeksering
   GLuint mIBO{0};                 		// for glDrawElements()


   float mRadius{0.5};			//
   // gjorde mRotation fra vector til matrise får at cpp skal funke
   QMatrix4x4 mRotation;
};

#endif // DISC_H
