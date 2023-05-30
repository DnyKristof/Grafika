#include "scene.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    load_model(&(scene->madarka.model), "assets/models/cube.obj");
    scene->madarka.texture = load_texture("assets/textures/cube.png");

    load_model(&(scene->floor.model), "assets/models/floor.obj");
    scene->floor.texture = load_texture("assets/textures/floor.jpg");

    init_oszlopok(scene);

    Model oszlopka;
    load_model(&(oszlopka), "assets/models/pilar2.obj");

    scene->help = 0;
    scene->helptex = load_texture("assets/textures/help.jpg");

    GLuint oszloptex;
    oszloptex = load_texture("assets/textures/floor.jpg");

    scene->running = 1;
    scene->gameover = load_texture("assets/textures/gameover.jpg");

    for (int i = 0; i < 18; i++)
    {
        scene->oszlop[i].model = oszlopka;
        // scene->oszlop[i].texture =  oszloptex;
    }

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->lights = 1;
    scene->invincible = 0;
    scene->fogposition = 14;
    scene->lock_camera = 1;
    scene->madarka.pos.x = 0.0;
    scene->madarka.pos.y = -5.0;
    scene->madarka.pos.z = 5;
    scene->madarka.speed.x = 0.0;
    scene->madarka.speed.z = 0.0;
    scene->madarka.speed.y = 1;
    scene->madarka.accelaration.z = 1.0;
    scene->visszae=0;
}

void set_lighting(Scene *scene,float x, float y, float z)
{
    float ambient_light[] = {scene->lights, scene->lights, scene->lights, scene->lights};
    float diffuse_light[] = {scene->lights, scene->lights,scene->lights, scene->lights};
    float specular_light[] = {scene->lights, scene->lights, scene->lights, scene->lights};
    float position[] = {x, y + 5, z + 5, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    
    if (scene->running)
    {
        set_lighting(scene,scene->madarka.pos.x, scene->madarka.pos.y, scene->madarka.pos.z);
        fogthings(scene);
        scene->current_time = (double)SDL_GetTicks() / 1000;

        double time = (scene->current_time - scene->last_time);
        scene->madarka.pos.y += 0.1 * scene->madarka.speed.y;
        scene->madarka.pos.x += time * scene->madarka.speed.x;
        scene->madarka.pos.z += time * scene->madarka.speed.z;

        
        
        regulate_madarka_sidespeed(scene);

        if (scene->madarka.speed.z > -5)
        {
            scene->madarka.speed.z -= 0.25;
        }

        printf("%d\n",scene->visszae);

        if(!scene->visszae){
            scene->madarka.speed.y+=0.001;
        }else{
            
            scene->madarka.speed.y-=0.01;
        }
        
        scene->last_time = scene->current_time;

        if (!scene->invincible)
        {
            if (collision(scene))
            {
                scene->running = 0;
            }
        }
    }
}

void render_scene(Scene *scene)
{
    set_material(&(scene->material));
    padlo_rajzol(scene);

    set_material(&(scene->oszlop[0].material));

    madarka_kirajzol(scene);

    draw_oszlopsz(scene);

    if (scene->help)
    {
        help(scene->helptex);
    }

    if (!(scene->running))
    {
        help(scene->gameover);
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

float *get_camera_position(const Scene *scene)
{
    static float camera_position[3];
    camera_position[0] = scene->madarka.pos.x;
    camera_position[1] = scene->madarka.pos.y - 1.5;
    camera_position[2] = scene->madarka.pos.z + 1;
    return camera_position;
}

void help(GLuint texture)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2.5, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2.5, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2.5, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2.5, -1.5, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
}
