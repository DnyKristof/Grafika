#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include <time.h>
#include "madarka.h"
#include "oszlop.h"

#include <obj/model.h>


void madarka_kirajzol(const Scene* scene);
void init_oszlopok(Scene* scene);
void padlo_rajzol(const Scene *scene);
void draw_oszlopsz(Scene* scene);
void regulate_madarka_sidespeed(Scene* scene);
int collision(Scene *scene);

#endif /* OSZLOP_H */