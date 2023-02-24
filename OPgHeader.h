#ifndef OPGHEADER_H
#define OPGHEADER_H
#include <istream>
#include <vector>

class Vertex0 {
public:
   float x;
   float y;
   float z;
   float r;
   float g;
   float b;
   float u;
   float v;

};

class Vertex {
    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);

 private:
    float m_xyz[3];       	// position i 3D
    float m_normal[3];    // normal in 3D or rgb colors
    float m_st[2];        	// texture coordinates if used



 public:
    Vertex();
    Vertex(float x, float y, float z, float r, float g, float b);


};



#endif // OPGHEADER_H
