#ifndef MADARKA_H
#define MADARKA_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Madarka
{
    Model model;
    GLuint texture;
    vec3 pos;
    vec3 speed;
    vec3 accelaration;
}Madarka;



#endif /* MADARKA_H */