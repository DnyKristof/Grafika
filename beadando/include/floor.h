#ifndef FLOOR_H
#define FLOOR_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Floor
{
    Model model;
    GLuint texture;
    vec3 pos;
    Material material;
}Floor;



#endif /* FLOOR_H */