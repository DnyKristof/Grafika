#include "functionality.h"
#include <math.h>

void madarka_kirajzol(const Scene *scene)
{

    glPushMatrix();
    glTranslatef(scene->madarka.pos.x, scene->madarka.pos.y, scene->madarka.pos.z);
    glScalef(0.05, 0.05, 0.05);
    glRotatef(-90, 0, 0, 1);
    glRotatef((scene->madarka.speed.z) * 90 / 8 + 10, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, scene->madarka.texture);
    draw_model(&(scene->madarka.model));
    glPopMatrix();
}

void init_oszlopok(Scene *scene)
{
    float y = 5;
    float x = 0.7;
    float z = 0;
    srand(time(NULL));

    for (int i = 0; i < 18; i += 6)
    {

        float randomheight1 = (rand() % 4) - 1;
        float randomheight2 = (rand() % 4) - 1;
        float randomheight3 = (rand() % 4) - 1;

        scene->oszlop[i].pos.y = y + i;
        scene->oszlop[i + 1].pos.y = y + i;
        scene->oszlop[i + 2].pos.y = y + i;
        scene->oszlop[i + 3].pos.y = y + i;
        scene->oszlop[i + 4].pos.y = y + i;
        scene->oszlop[i + 5].pos.y = y + i;

        scene->oszlop[i].pos.z = z + randomheight1 + 5;
        scene->oszlop[i + 1].pos.z = z + randomheight2 + 5;
        scene->oszlop[i + 2].pos.z = z + randomheight3 + 5;
        scene->oszlop[i + 3].pos.z = z + randomheight1 + 7;
        scene->oszlop[i + 4].pos.z = z + randomheight2 + 7;
        scene->oszlop[i + 5].pos.z = z + randomheight3 + 7;

        scene->oszlop[i].pos.x = 0;
        scene->oszlop[i + 1].pos.x = x;
        scene->oszlop[i + 2].pos.x = -x;
        scene->oszlop[i + 3].pos.x = 0;
        scene->oszlop[i + 4].pos.x = x;
        scene->oszlop[i + 5].pos.x = -x;
    }
}

void padlo_rajzol(const Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->floor.texture);
    glBegin(GL_QUADS);
    glPushMatrix();
    int start = scene->madarka.pos.y - 3;
    int end = scene->madarka.pos.y + 20;
    for (int i = start; i < end; i++)
    {

        for (int j = -10; j <= 10; j++)
        {
            glTexCoord2f(0, 1);
            glVertex3f(j, i, 0);

            glTexCoord2f(1, 1);
            glVertex3f(j + 1, i, 0);

            glTexCoord2f(1, 0);
            glVertex3f(j + 1, i + 1, 0);

            glTexCoord2f(0, 0);
            glVertex3f(j, i + 1, 0);
        }
    }
    glPopMatrix();
    glEnd();
}
void draw_oszlopsz(Scene *scene)
{

    for (int i = 0; i < 18; i++)
    {
        float ambient_material_color[] = {0.1f, 1.0f, 0.1f};
        float diffuse_material_color[] = {1.0f, 1.0f, 1.0f, 0.85f};
        float specular_material_color[] = {0.0f, 0.0f, 0.0f};

        float shininess = 50.0;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
        glPushMatrix();

        // első csoport
        if (scene->madarka.pos.y > scene->oszlop[0].pos.y + 2)
        {

            float randomheights[3] = {(rand() % 8) - 4, (rand() % 8) - 4, (rand() % 8) - 4};

            for (int j = 0; j <= 5; j++)
            {
                scene->oszlop[j].pos.y = scene->oszlop[17].pos.y + 5;
                scene->oszlop[j % 3].pos.z = randomheights[j % 3] + 5;
                scene->oszlop[j % 3 + 3].pos.z = randomheights[j % 3] + 7;
            }
        }
        // második csoport
        if (scene->madarka.pos.y > scene->oszlop[7].pos.y + 2)
        {
            float randomheights[3] = {(rand() % 8) - 4, (rand() % 8) - 4, (rand() % 8) - 4};

            for (int j = 6; j <= 11; j++)
            {
                scene->oszlop[j].pos.y = scene->oszlop[0].pos.y + 5;
                scene->oszlop[j % 3 + 6].pos.z = randomheights[j % 3] + 5;
                scene->oszlop[j % 3 + 9].pos.z = randomheights[j % 3] + 7;
            }
        }
        // harmadik csoport
        if (scene->madarka.pos.y > scene->oszlop[17].pos.y + 2)
        {
            float randomheights[3] = {(rand() % 8) - 4, (rand() % 8) - 4, (rand() % 8) - 4};

            for (int j = 12; j <= 17; j++)
            {
                scene->oszlop[j].pos.y = scene->oszlop[7].pos.y + 5;
                scene->oszlop[j % 3 + 12].pos.z = randomheights[j % 3] + 5;
                scene->oszlop[j % 3 + 15].pos.z = randomheights[j % 3] + 7;
            }
        }
        // felső oszlopok forgatása, hogy azokat felfelé nyújtsa, az alsókat meg lefelé
        glTranslatef(scene->oszlop[i].pos.x, scene->oszlop[i].pos.y, scene->oszlop[i].pos.z);
        if (i >= 3 && i <= 5 || i >= 9 && i <= 11 || i >= 15 && i <= 17)
        {
            glRotatef(180, 1, 0, 0);
        }

        glScalef(1, 1, -3);
        glRotatef(90, 1, 0, 0);
        // glBindTexture(GL_TEXTURE_2D, scene->oszlop[i].texture);
        draw_model(&(scene->oszlop[i].model));
        set_material(&(scene->material));
        glPopMatrix();
    }
}

void regulate_madarka_sidespeed(Scene *scene)
{
    if (scene->madarka.pos.x > 0.7)
    {
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = 0.7;
    }
    if (scene->madarka.pos.x < 0.04 && scene->madarka.pos.x > -0.04)
    {
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = 0;
    }
    if (scene->madarka.pos.x < -0.7)
    {
        scene->madarka.speed.x = 0;
        scene->madarka.pos.x = -0.7;
    }
}

void fogthings(Scene *scene)
{
    float fog[4] = {0.5f, 0.5f, 0.5f, 0.5f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.0005f);
    glFogfv(GL_FOG_COLOR, fog);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, scene->fogposition - 30);
    glFogf(GL_FOG_END, scene->fogposition);
}

int collision(Scene *scene)
{

    
    if(scene->madarka.pos.z <  -0.1){
        return 1;
    }

    float yhitbox = 0.4;

    //bal sáv
    for(int i = 2;i<18;i+=6){
        if (scene->madarka.pos.x < -0.69 &&
        scene->madarka.pos.x > -0.71 &&
      ((scene->madarka.pos.z < scene->oszlop[i].pos.z) || (scene->madarka.pos.z > scene->oszlop[i+3].pos.z)) &&
       (fabs(scene->madarka.pos.y - scene->oszlop[i].pos.y) < yhitbox))
    {
        return 1;
    }
    }

    // közép sáv
    for(int i = 0;i<18;i+=6){
        if (scene->madarka.pos.x < 0.1 &&
        scene->madarka.pos.x > -0.1 &&
      ((scene->madarka.pos.z < scene->oszlop[i].pos.z) || (scene->madarka.pos.z > scene->oszlop[i+3].pos.z)) &&
       (fabs(scene->madarka.pos.y - scene->oszlop[i].pos.y) < yhitbox))
    {
        return 1;
    }
    }

    //jobb sáv
    for(int i = 1;i<18;i+=6){
        if (scene->madarka.pos.x < 0.71 &&
        scene->madarka.pos.x > 0.69 &&
      ((scene->madarka.pos.z < scene->oszlop[i].pos.z) || (scene->madarka.pos.z > scene->oszlop[i+3].pos.z)) &&
       (fabs(scene->madarka.pos.y - scene->oszlop[i].pos.y) < yhitbox))
    {
        return 1;
    }
    }

    return 0;
}