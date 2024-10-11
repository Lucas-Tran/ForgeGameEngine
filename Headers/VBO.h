#ifndef VBO_H_INCLUDED
#define VBO_H_INCLUDED

class VBO {
public:
    VBO(const float *vertices, const unsigned int bufferSize);

    ~VBO();

    void Bind() const;

    static void Unbind();
private:
    unsigned int ID;
};

#endif