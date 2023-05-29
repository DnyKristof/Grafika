#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "oszlop.h"
#include "madarka.h"
#include "floor.h"
#include <obj/model.h>

typedef struct Scene
{
    Madarka madarka;
    Floor floor;
    Material material;
    //Oszlop oszlop;
    double current_time;
    GLfloat fogposition;
    double last_time;
    bool lock_camera;
    Oszlop oszlop[18];
    bool help;
    GLuint helptex;

    bool running;
    GLuint gameover;

    bool invincible;

    float lights;

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene *scene,float x,float y,float z);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene( Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void set_camera_pos(Camera* camera, Scene* scene);

void madarka_kirajzol(const Scene* scene);

void oszlopka_kirajzol(const Scene* scene,float xpos,float yscale);

float *get_camera_position(const Scene *scene);





#endif /* SCENE_H */
