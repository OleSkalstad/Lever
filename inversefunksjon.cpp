#include "inversefunksjon.h"
using namespace Eigen;
InverseFunksjon::InverseFunksjon()
{
    //punkter er (5,3), (4,2),(3,5),(2,1)
    MatrixXd y(4,1);
    y(0,0) = 3;
    y(1,0) = 2;
    y(2,0) = 5;
    y(3,0) = 1;

    MatrixXd A(4,4);
    A(0,1) = pow(5,3);  A(0,1) = pow(5,2);    A(0,2) = 5;    A(0,3) = 1;
    A(1,1) = pow(4,3);  A(1,1) = pow(4,2);    A(1,2) = 4;    A(1,3) = 1;
    A(2,1) = pow(3,3);  A(2,1) = pow(3,2);    A(2,2) = 3;    A(2,3) = 1;
    A(3,1) = pow(2,3);  A(3,1) = pow(2,2);    A(3,2) = 2;    A(3,3) = 1;


    MatrixXd x = A.inverse()*y;
    if (x(0,0))
        mA =x(0,0);
      if (x(1,0))
        mB = x(1,0);
      if (x(2,0))
        mC = x(2,0);
      if(x(3,0))
        mD = x(3,0);
    constructCurve();
}

void InverseFunksjon::constructCurve()
{

    float y = 0;
    float xmin = -4.0f, xmax = 4.0f, h = 0.25f;
    for (auto x = xmin; x < xmax; x += h)
    {
        float z = (mA * pow(x,3)) + (mB * pow(x,2)) + (mC * x) + mD;
        mVertices.push_back(Vertex{ x,y,z,0,1,0 });

        z = (mA * pow((x+h),3)) + (mB * pow((x+h),2)) + (mC * (x+h)) + mD;
        mVertices.push_back(Vertex{ x + h,y,z,0,1,0 });
    }
    mMatrix.setToIdentity();


}

void InverseFunksjon::init(GLint matrixUniform)
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

    mMatrix.setToIdentity();

}

void InverseFunksjon::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINES, 0, mVertices.size());

}
