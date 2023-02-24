 #include "interactiveobject.h"

InteractiveObject::InteractiveObject() : mx(0.0f), my(0.0f), mz(0.0f)
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

}

InteractiveObject::~InteractiveObject()
{

}

void InteractiveObject::init(GLint matrixUniform)
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


}

void InteractiveObject::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

}

void InteractiveObject::move(float dx, float dy, float dz)
{
mx += dx;
my += dy;
mz += dz;
mMatrix.translate(mx,my,mz);
}
