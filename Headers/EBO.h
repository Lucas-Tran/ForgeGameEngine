#ifndef EBO_H_INCLUDED
#define EBO_H_INCLUDED

class EBO {
public:
    EBO(const unsigned int *elements, const unsigned int bufferSize);

    ~EBO();

    void Bind() const;

    static void Unbind();
private:
    unsigned int ID;
};

#endif