#include "funksjon.h"
#include <iostream>
#include <cmath>
#include "s_xyz.h"
using namespace Eigen;

Funksjon::Funksjon()
{
    // (5,3), (1,-2), (0,5), (6,6), (2,0), (3,3), (7,1), (0,-1)
     mMatrix.setToIdentity();

    MatrixXd y(8,1);
    y(0,0) = 3;
    y(1,0) = -2;
    y(2,0) = 5;
    y(3,0) =  6;
    y(4,0) =  0;
    y(5,0) = -3;
    y(6,0) =  1;
    y(7,0) =  -1;

    MatrixXd A(8,3);
    A(0,0) = pow(5,2);    A(0,1) = 5;    A(0,2) = 1;
    A(1,0) = pow(1,2);    A(1,1) = 1;    A(1,2) = 1;
    A(2,0) = pow(0,2);  A(2,1) = 0;  A(2,2) = 1;
    A(3,0) = pow(6,2);    A(3,1) = 6;    A(3,2) = 1;
    A(4,0) = pow( 2,2);    A(4,1) =  2;    A(4,2) = 1;
    A(5,0) = pow( 3,2);    A(5,1) =  3;    A(5,2) = 1;
    A(6,0) = pow( 7,2);    A(6,1) =  7;    A(6,2) = 1;
    A(7,0) = pow( 0,2);    A(7,1) =  0;    A(7,2) = 1;

    MatrixXd B = A.transpose()*A;
    MatrixXd c = A.transpose()*y;
    MatrixXd x = B.inverse()*c;

    if (x(0,0))
            mB = x(0,0);
        if (x(1,0))
            mC = x(1,0);
        if (x(2,0))
            mD = x(2,0);

    std::cout<< x<< std::endl;
    constructCurve();
}

Funksjon::~Funksjon()
{

}

void Funksjon::constructCurve()
{

    float y = 0;
    float xmin = -4.0f, xmax = 4.0f, h = 0.25f;
    for (auto x = xmin; x < xmax; x += h)
    {
        float z = (mA * pow(x,3)) + (mB * pow(x,2)) + (mC * x) + mD;
        mVertices.push_back(Vertex{ x,y,z,1,1,0 });

        z = (mA * pow((x+h),3)) + (mB * pow((x+h),2)) + (mC * (x+h)) + mD;
        mVertices.push_back(Vertex{ x + h,y,z,1,1,0 });
    }


}


void Funksjon::init(GLint matrixUniform)
{
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
    mMatrix.rotate(-90,1,0,0);

}

void Funksjon::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINES, 0, mVertices.size());

}
