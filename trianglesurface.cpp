#include "trianglesurface.h"
#include <iostream>

TriangleSurface::TriangleSurface()
{

    float xmin=0.0f, xmax=5.0f, h=1.0f, y=0;
    for (auto x=xmin; x<xmax; x+=h, y+=h)
    {

    mVertices.push_back(Vertex{x,y,f(x,y),1,0,0}); //rød

    }
    mMatrix.setToIdentity();
    construct3();
}

TriangleSurface::TriangleSurface(std::string filnavn)
{
    //std::ofstream file;
    //file.open(filNavn, std::ofstream::out | std::ofstream::trunc);
construct3();

}

TriangleSurface::~TriangleSurface()
{

}

void TriangleSurface::constructsurface()
{
    mVertices.clear();
    float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.25f;
    for (auto x=xmin; x<xmax; x+=h)
    for (auto y=ymin; y<ymax; y+=h)
    {
    float z = sin(M_PI*x)*sin(M_PI*y);
    mVertices.push_back(Vertex{x,y,z,x,y,z});
    z = sin(M_PI*(x+h))*sin(M_PI*y);
    mVertices.push_back(Vertex{x+h,y,z,x,y,z});
    z = sin(M_PI*x)*sin(M_PI*(y+h));
    mVertices.push_back(Vertex{x,y+h,z,x,y,z});
    mVertices.push_back(Vertex{x,y+h,z,x,y,z});
    z = sin(M_PI*(x+h))*sin(M_PI*y);
    mVertices.push_back(Vertex{x+h,y,z,x,y,z});
    z = sin(M_PI*(x+h))*sin(M_PI*(y+h));
    mVertices.push_back(Vertex{x+h,y+h,z,x,y,z});
    }
    mMatrix.setToIdentity();
}

void TriangleSurface::construct3()
{
    float sum, height = 0;
    float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.1f;
    for (auto x=xmin; x<xmax; x+=h)
        // x = 1
        // y = 1 - x (setter y<ymax - x)
        // da får ikke et kvadratisk område
        for (auto y=ymin; y<ymax - x; y+=h)
        {
            // The function
            float z = 2*x+y/2;

            mVertices.push_back(Vertex{x,y,z,x,y,z});

            height += z;

            z= 2*(x+h)+y/2;
            //z = 1-(x+h)-y;
            mVertices.push_back(Vertex{x+h,y,z,x,y,z});

            height += z;

            z = 2*x+(h+y)/2;
            //z = 1-x-(y+h);
            mVertices.push_back(Vertex{x,y+h,z,x,y,z});
            mVertices.push_back(Vertex{x,y+h,z,x,y,z});

            height += z;

            z= 2*(x+h)+y/2;
           // z = 1-(x+h)-y;
            mVertices.push_back(Vertex{x+h,y,z,x,y,z});
            z= 2*(x+h)+y;

            z= 2*(x+h) +(y+h)/2;
            //z = 1-(x+h)-(y+h);
            mVertices.push_back(Vertex{x+h,y+h,z,x,y,z});

            height += z;

            // calculate the volume of the given division.
            sum += pow(h,2) * ((height)/4);
            // reset height back to zero.
            height = 0;


            if (z < 0.00001)
                z = 0;
        }
    for (int i = 0;  i < mVertices.size(); i++)
    {
        std::cout << mVertices[i] << std::endl;
    }
    std::cout << "Volumet er : " << sum << "." << std::endl;
}

void TriangleSurface::readFile(std::string filnavn)
{

}

void TriangleSurface::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;
    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void TriangleSurface::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINES, 0, mVertices.size());
}
