#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "includes/SOIL.h"

GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;

GLfloat rtri;           // Угол для треугольник
GLfloat rquad;          // Угол для четырехугольника

GLfloat sphereTransX;
GLfloat sphereTransY;
GLfloat sphereTransZ;

// угол поворота камеры
float angle=0.0;
// координаты вектора направления движения камеры
float lx=0.0f, lz=-1.0f;
// XZ позиция камеры
float x=0.0f, z=5.0f;
//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

GLfloat LightPosition1[] = {sphereTransX, sphereTransY, sphereTransZ, 1.0f};     // Позиция света

void init(void) {
    //загрузка текстур с помощью библиотеки SOIL
    texture4 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL_basics/resources/textures/texture1.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    texture1 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL_basics/resources/textures/texture2.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    texture2 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL_basics/resources/textures/texture6.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    texture3 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL_basics/resources/textures/floor.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    texture5 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL_basics/resources/textures/texture3.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


    glShadeModel(GL_SMOOTH);      // Разрешение сглаженного закрашивания
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Черный фон
    glClearDepth(1.0f);           // Установка буфера глубины
    glDepthFunc(GL_LEQUAL);       // Тип теста глубины
    glEnable(GL_NORMALIZE);

    GLfloat LightAmbient1[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Значения фонового света
    GLfloat LightDiffuse1[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Значения диффузного света
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   // Позиция света
    glEnable(GL_LIGHT1); // Разрешение источника света номер один

//    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
//    glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,2.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);

    GLfloat LightPosition2[] = {0.0f, 0.0f, -11.0, 1.0f};     // Позиция света
    GLfloat LightAmbient2[] = {0.0f, 0.0f, 0.0f, 0.0f}; // Значения фонового света
    GLfloat LightDiffuse2[] = {0.0f, 1.0f, 0.0f, 1.0f}; // Значения диффузного света
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient2);    // Установка Фонового Света
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse2);    // Установка Диффузного Света
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition2);   // Позиция света
    glEnable(GL_LIGHT0); // Разрешение источника света номер один

    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

//    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SINGLE_COLOR);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void drawPyramid() {

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glPushMatrix();

    //Рисование пирамиды
    glLoadIdentity();                               // Сброс просмотра
    glTranslatef(2.5f, -2.0f, -12.0f);          // Сдвинуть вправо и вглубь экрана
    glRotatef(rtri, 0.0f, 1.0f, 0.0f);                 // Вращение пирамиды по оси Y

    glBegin(GL_TRIANGLES);                          // Начало рисования пирамиды
    glNormal3f(0.0f, 1.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Передняя)
    glNormal3f(0.0f, 1.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                  // Левая точка
    glNormal3f(0.0f, 1.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  // Правая точка

    glNormal3f(1.0f, 1.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Правая)
    glNormal3f(1.0f, 1.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  // Лево треугольника (Правая)
    glNormal3f(1.0f, 1.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 // Право треугольника (Правая)

    glNormal3f(0.0f, 1.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);                  // Низ треугольника (Сзади)
    glNormal3f(0.0f, 1.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 // Лево треугольника (Сзади)
    glNormal3f(0.0f, 1.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                 // Право треугольника (Сзади)

    glNormal3f(-1.0f, 1.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Лево)
    glNormal3f(-1.0f, 1.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                  // Лево треугольника (Лево)
    glNormal3f(-1.0f, 1.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                  // Право треугольника (Лево)
    glEnd();                                                // Кончили рисовать пирамиду


    glBegin(GL_POLYGON);                          // Начало рисования основания пирамиды
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Верх право
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);    // Верх лево
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);    // Низ лево
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ право
    glEnd();                                                // Кончили рисовать основание пирамиды

    rtri += 0.2f;             // Увеличим переменную вращения для треугольника

    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void drawLightCube() {
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -11.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.15f, -0.15f, 0.15f);    // Низ лево
    glVertex3f(0.15f, -0.15f, 0.15f);    // Низ право
    glVertex3f(0.15f, 0.15f, 0.15f);    // Верх право
    glVertex3f(-0.15f, 0.15f, 0.15f);    // Верх лево

    // Задняя грань
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.15f, -0.15f, -0.15f);    // Низ право
    glVertex3f(-0.15f, 0.15f, -0.15f);    // Верх право
    glVertex3f(0.15f, 0.15f, -0.15f);    // Верх лево
    glVertex3f(0.15f, -0.15f, -0.15f);    // Низ лево

    // Верхняя грань
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.15f, 0.15f, -0.15f);    // Верх лево
    glVertex3f(-0.15f, 0.15f, 0.15f);    // Низ лево
    glVertex3f(0.15f, 0.15f, 0.15f);    // Низ право
    glVertex3f(0.15f, 0.15f, -0.15f);    // Верх право

    // Нижняя грань
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.15f, -0.15f, -0.15f);    // Верх право
    glVertex3f(0.15f, -0.15f, -0.15f);    // Верх лево
    glVertex3f(0.15f, -0.15f, 0.15f);    // Низ лево
    glVertex3f(-0.15f, -0.15f, 0.15f);    // Низ право

    // Правая грань
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(0.15f, -0.15f, -0.15f);    // Низ право
    glVertex3f(0.15f, 0.15f, -0.15f);    // Верх право
    glVertex3f(0.15f, 0.15f, 0.15f);    // Верх лево
    glVertex3f(0.15f, -0.15f, 0.15f);    // Низ лево

    // Левая грань
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.15f, -0.15f, -0.15f);    // Низ лево
    glVertex3f(-0.15f, -0.15f, 0.15f);    // Низ право
    glVertex3f(-0.15f, 0.15f, 0.15f);    // Верх право
    glVertex3f(-0.15f, 0.15f, -0.15f);    // Верх лево

    glEnd();

    glPopMatrix();
}

void drawCube() {

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glPushMatrix();

    //Рислвание куба
    glLoadIdentity();
    glTranslatef(-2.5, -1.0, -9.0f);                 // Сдвиг влево и вглубь экрана
    glRotatef(rquad, 1.0f, 1.0f, 1.0f);        // Вращение куба по X, Y & Z

    glBegin(GL_QUADS);
    // Передняя грань
    glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ лево
    glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);    // Низ право
    glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);    // Верх право
    glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Верх лево

    // Задняя грань
    glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ право
    glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх право
    glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);    // Верх лево
    glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);    // Низ лево

    // Верхняя грань
    glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх лево
    glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Низ лево
    glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);    // Низ право
    glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);    // Верх право

    // Нижняя грань
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Верх право
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);    // Верх лево
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);    // Низ лево
    glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ право

    // Правая грань
    glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);    // Низ право
    glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);    // Верх право
    glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);    // Верх лево
    glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);    // Низ лево

    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ лево
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ право
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Верх право
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх лево

    glEnd();                             // Закончили квадраты

    rquad -= 0.4f;           // Уменьшим переменную вращения для квадрата

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}

void drawFloor() {
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    for (int i = -7; i < 8; ++i) {
        for (int j = -7; j < 11; ++j) {
            glBindTexture(GL_TEXTURE_2D, texture3);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(i, -4.0f, j - 11.0f);          // Сдвинуть вправо и вглубь экрана
            glBegin(GL_QUADS);
            // Верхняя грань
            glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-0.5f, 0.5f, -0.51f);    // Верх лево
            glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-0.5f, 0.5f, 0.51f);    // Низ лево
            glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.5f, 0.5f, 0.51f);    // Низ право
            glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(0.5f, 0.5f, -0.51f);    // Верх право
            glEnd();                             // Закончили квадраты
            glPopMatrix();
        }
    }

    glBindTexture(GL_TEXTURE_2D, texture5);


    for (int i = -3; i < 5; ++i) {
        for (int j = -7; j < 11; ++j) {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(-8, i, j - 11.0f);          // Сдвинуть вправо и вглубь экрана
            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, -0.5f);    // Низ право
            glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(0.5f, 0.5f, -0.5f);    // Верх право
            glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0.5f, 0.5f, 0.5f);    // Верх лево
            glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.5f);    // Низ лево
            glEnd();                             // Закончили квадраты
            glPopMatrix();
        }
    }

    for (int i = -7; i < 8; ++i) {
        for (int j = -4; j < 8; ++j) {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(i, j, -8 - 11.0f);          // Сдвинуть вправо и вглубь экрана
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.5f);    // Низ лево
            glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.5f);    // Низ право
            glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(0.5f, 0.5f, 0.5f);    // Верх право
            glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-0.5f, 0.5f, 0.5f);    // Верх лево
            glEnd();                             // Закончили квадраты
            glPopMatrix();
        }
    }

    for (int i = -3; i < 6; ++i) {
        for (int j = -7; j < 11; ++j) {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(8, i, j - 11.0f);          // Сдвинуть вправо и вглубь экрана
            glBegin(GL_QUADS);
            glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, -0.5f);    // Низ лево
            glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.5f);    // Низ право
            glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-0.5f, 0.5f, 0.5f);    // Верх право
            glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-0.5f, 0.5f, -0.5f);    // Верх лево
            glEnd();                             // Закончили квадраты
            glPopMatrix();
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void drawLightSource() {
    glLoadIdentity();
    glTranslatef(sphereTransX, sphereTransY, sphereTransZ);
    glColor3f(0.8, 0.8, 0.8);
    glutSolidSphere(0.2, 20, 20);

    sphereTransX = 7.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.0007);
    sphereTransY = -2.0 + 0.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.0002);
    sphereTransZ = -11 + 7.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.0007);
}

void drawSphere() {
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
    glTranslatef(0.0f, 1.0f, -13.0f);          // Сдвинуть вправо и вглубь экрана
    glRotatef(rtri, 1.0f, 1.0f, 1.0f);                 // Вращение пирамиды по оси Y
    GLUquadricObj *Obj = gluNewQuadric();
    gluQuadricTexture(Obj, GL_TRUE);
    gluQuadricDrawStyle(Obj, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glPushMatrix();
    glBegin(GL_LINE);
    gluSphere(Obj, 0.8, 30, 30);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}

void drawLight() {
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   // Позиция света
}

//функция для рендеринга геометрии
void display(void) {

    //очистить буфер цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCube();
    drawFloor();
    drawPyramid();
    drawLight();
    drawSphere();
    drawLightCube();
    drawLightSource();

    glFinish();
    glFlush();
    glutSwapBuffers();
}

//функция вызываемая при изменении размера окна
void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);//задаем область вывода в окне

    glMatrixMode(GL_PROJECTION);//задаем матрицу проектирования

    glLoadIdentity();//загружаем в нее единичную матрицу

    gluPerspective(45.0f, (GLfloat) w / (GLfloat) h, 0.1f, 100.0f);//задаем перспективное преобразование

    gluLookAt(6.0, 8.0, 0.0, // Положение глаз, взгляд "из"
              0.0, -3.0, -11.0, // Цель, взгляд "на"
              0.0, 1.0, 0.0); // Пока игнорируем

    glMatrixMode(GL_MODELVIEW);    //задаем модельно-видовую матрицу

    glLoadIdentity();    //делаем ее равной единичной матрице
}

////создание анимации с помощью библиотеки GLUT
//void idle(void) {
//    //запрашиваем перерисовку экрана
//    glutPostRedisplay();
//}

void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 27)
        exit(0);
}

void pressKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

void mouseMove(int x, int y) {

    // this will only be true when the left button is down
    if (xOrigin >= 0) {

        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);//инициализация GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//задаем двойную буферезацию
    glutInitWindowSize(1200, 800);//задаем размер окна в пикселах
    glutInitWindowPosition(500, 500);//задаем координаты окна
    glutCreateWindow("Cubes and pyramid");

    init();

    glutDisplayFunc(display);//регестрируем функции-обработчики рендеринга в окно
    glutReshapeFunc(reshape);//изменение размера окна
    glutIdleFunc(display);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseButton);

    glutMainLoop();//запускаем цикл обработки сообщений
    return 0;
}
