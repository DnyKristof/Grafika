#include "scene.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->madarka.model), "assets/models/cube.obj");
    scene->madarka.texture = load_texture("assets/textures/cube.png");

    load_model(&(scene->floor), "assets/models/floor.obj");
    scene->floor_tex = load_texture("assets/textures/floor.jpg");


    init_oszlopok(scene);


    Model oszlopka;
    GLuint oszloptex;
    load_model(&(oszlopka), "assets/models/pilar2.obj");
    oszloptex = load_texture("assets/textures/floor.jpg");
    
    for(int i=0;i<18;i++){
        scene->oszlop[i].model = oszlopka;
        scene->oszlop[i].texture = oszloptex;
    }
    

    //load_model(&(scene->oszlop.model), "assets/models/pilar2.obj");
    //scene->texture_id = load_texture("assets/textures/cube.png");

    
    
    
    scene->lock_camera=1;
    /*scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 10.0;*/

    scene->madarka.pos.x = 0.0;
    scene->madarka.pos.y = 0.0;
    scene->madarka.pos.z = 5;
    scene->madarka.speed.x = 0.0;
    scene->madarka.speed.z = 0.0;
    scene->madarka.speed.y = 0.1;
    scene->madarka.accelaration.z = 1.0;


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    
    //
}



void set_lighting()
{
    float ambient_light[] = { 4.0f, 4.0f, 4.0f, 4.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
    scene->current_time = (double)SDL_GetTicks() / 1000;

    double time = (scene->current_time-scene->last_time);
    scene->madarka.pos.y += 0.1;//time*scene->madarka.speed.y;
    scene->madarka.pos.x += time*scene->madarka.speed.x;
    scene->madarka.pos.z += time*scene->madarka.speed.z;

    /*if(scene->madarka.pos.x > 0.7 || scene->madarka.pos.x < -0.7 || (scene->madarka.pos.x < 0.03 && scene->madarka.pos.x > -0.03)){
        scene->madarka.speed.x = 0;
    }*/
    regulate_madarka_sidespeed(scene);
    

    if(scene->madarka.speed.z > -5){
        scene->madarka.speed.z -= 0.25;
    }
    
    
    scene->last_time = scene->current_time;
}

void regulate_madarka_sidespeed(Scene* scene){
    if(scene->madarka.pos.x > 0.7){
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = 0.7;
    }
    if(scene->madarka.pos.x < 0.05 && scene->madarka.pos.x > -0.05){
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = 0;
    }
    if(scene->madarka.pos.x < -0.7){
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = -0.7;
    }
}



void render_scene( Scene* scene)
{
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->floor_tex);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->floor));
    glPopMatrix();

    glPushMatrix();
    madarka_kirajzol(scene);
    glPopMatrix();
    
    draw_oszlopsz(scene);

}

void draw_oszlopsz(Scene* scene){

    for(int i=0;i<18;i++){
        glPushMatrix();
        //első csoport
        if(scene->madarka.pos.y > scene->oszlop[0].pos.y){

            float randomheights[3] ={(rand() % 8) -4,(rand() % 8) -4,(rand() % 8) -4};

            for(int j=0;j<=5;j++){
                scene->oszlop[j].pos.y = scene->oszlop[17].pos.y +5;
                scene->oszlop[j%3].pos.z = randomheights[j%3] + 5;
                scene->oszlop[j%3+3].pos.z = randomheights[j%3] + 7;
            }
            
        }
        //második csoport
        if(scene->madarka.pos.y > scene->oszlop[7].pos.y){
            float randomheights[3] ={(rand() % 8) -4,(rand() % 8) -4,(rand() % 8) -4};

            for(int j=6;j<=11;j++){
                scene->oszlop[j].pos.y = scene->oszlop[0].pos.y +5;
                scene->oszlop[j%3+6].pos.z = randomheights[j%3] + 5;
                scene->oszlop[j%3+9].pos.z = randomheights[j%3] + 7;
            }
            
        }
        //harmadik csoport
        if(scene->madarka.pos.y > scene->oszlop[17].pos.y){
            float randomheights[3] ={(rand() % 8) -4,(rand() % 8) -4,(rand() % 8) -4};
            
            for(int j=12;j<=17;j++){
                scene->oszlop[j].pos.y = scene->oszlop[7].pos.y +5;
                scene->oszlop[j%3+12].pos.z = randomheights[j%3] + 5;
                scene->oszlop[j%3+15].pos.z = randomheights[j%3] + 7;
            }
            
        }
        //felső oszlopok forgatása, hogy azokat felfelé nyújtsa, az alsókat meg lefelé
        glTranslatef(scene->oszlop[i].pos.x,scene->oszlop[i].pos.y,scene->oszlop[i].pos.z);
        if(i>=3 && i<=5 || i>=9 && i<=11 || i>=15 && i<=17){
            glRotatef(180,1,0,0);
        }

        glScalef(1,1,-3);
        glRotatef(90, 1, 0, 0);
        glColor3f(1,1,1);
        draw_model(&(scene->oszlop[i].model));
        glPopMatrix();
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

void madarka_kirajzol(const Scene* scene){

    glPushMatrix();
    glTranslatef(scene->madarka.pos.x ,scene->madarka.pos.y,scene->madarka.pos.z );
    glScalef(0.05,0.05,0.05);
    glRotatef(-90,0,0,1);
    glRotatef((scene->madarka.speed.z)*90/8 + 10,0,1,0);
    glBindTexture(GL_TEXTURE_2D, scene->madarka.texture);
    draw_model(&(scene->madarka.model));
    glPopMatrix();

}

void init_oszlopok(Scene* scene){
    float y = 5;
    float x = 0.7;
    float z = 0;
    srand(time(NULL));

    
    
    for(int i = 0;i<18;i+=6){

        float randomheight1 = (rand() % 4) -1;
        float randomheight2 = (rand() % 4) -1;
        float randomheight3 = (rand() % 4) -1;
        
        scene->oszlop[i].pos.y = y + i;
        scene->oszlop[i+1].pos.y = y+ i;
        scene->oszlop[i+2].pos.y = y+ i;
        scene->oszlop[i+3].pos.y = y+ i;
        scene->oszlop[i+4].pos.y = y+ i;
        scene->oszlop[i+5].pos.y = y+ i;

        scene->oszlop[i].pos.z = z + randomheight1 +5;
        scene->oszlop[i+1].pos.z = z + randomheight2 +5 ;
        scene->oszlop[i+2].pos.z = z + randomheight3 +5;
        scene->oszlop[i+3].pos.z = z + randomheight1 + 7;
        scene->oszlop[i+4].pos.z = z + randomheight2 + 7;
        scene->oszlop[i+5].pos.z = z + randomheight3 + 7;

        scene->oszlop[i].pos.x = 0;
        scene->oszlop[i+1].pos.x = x;
        scene->oszlop[i+2].pos.x = -x;
        scene->oszlop[i+3].pos.x = 0;
        scene->oszlop[i+4].pos.x = x;
        scene->oszlop[i+5].pos.x = -x;

    }

}
