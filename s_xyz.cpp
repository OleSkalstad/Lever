#include "s_xyz.h"
#include <cmath>
S_XYZ::S_XYZ(float x, float y)
{




    mVertices.push_back(Vertex{0,0,0,0,1,0}); //grønn
    mVertices.push_back(Vertex{0.5,-0.5,0,0,0,1}); //blå
    mVertices.push_back(Vertex{-0.5,-0.5,0,1,0,0}); //rød


    mVertices.push_back(Vertex{0,0,0,0,1,0}); //grønn
    mVertices.push_back(Vertex{0.5,-0.5,0,0,0,1}); //blå
    mVertices.push_back(Vertex{0,-0.25,0.5,1,0,1}); //lilla

    mVertices.push_back(Vertex{0,0,0,0,1,0}); //grønn
    mVertices.push_back(Vertex{-0.5,-0.5,0,1,0,0}); //rød
    mVertices.push_back(Vertex{0,-0.25,0.5,1,0,1}); //lilla

    mVertices.push_back(Vertex{0.5,-0.5,0,0,0,1}); //blå
    mVertices.push_back(Vertex{-0.5,-0.5,0,1,0,0}); //rød
    mVertices.push_back(Vertex{0,-0.25,0.5,1,0,1}); //lilla
       mMatrix.setToIdentity();

    mMatrix.translate(x,y,0.0f);
    mMatrix.scale(0.25);



}
S_XYZ::~S_XYZ() {    }

void S_XYZ::init(GLint matrixUniform) {
   mMatrixUniform = matrixUniform;
   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

   glBindVertexArray(0);
}

void S_XYZ::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());


}


