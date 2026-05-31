#ifndef VAO_H_INCLUDED
#define VAO_H_INCLUDED

class VAO {
public:
    VAO();

    ~VAO();

    void Bind() const;

    static void Unbind();

    // This method is static because OpenGL is a state machine
    static void SetVertexAttribute(const unsigned int location, const unsigned int attribSize, const unsigned int stride, const unsigned int depth);
private:
    unsigned int ID;
};

#endif