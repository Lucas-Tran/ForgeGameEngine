#ifndef VAO_H_INCLUDED
#define VAO_H_INCLUDED

class VAO {
public:
    VAO();

    ~VAO();

    void Bind() const;

    static void Unbind();

    // This method is static because OpenGL is a state machine
    static void SetVertexAttribute(const unsigned int location, const unsigned int numberOfValuesPerAttrib, const unsigned int numberOfValuesPerVertex, const unsigned int numberOfValuesToAttrib);
private:
    unsigned int ID;
};

#endif