#ifndef OSZLOP_H
#define OSZLOP_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Oszlop
{
    Model model;
    GLuint texture;
    vec3 pos;
    Material material;
}Oszlop;



#endif /* OSZLOP_H */