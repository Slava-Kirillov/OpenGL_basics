#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "includes/SOIL.h"

GLuint texture1;
GLuint texture2;

GLfloat rtri;           // Угол для треугольник
GLfloat rquad;          // Угол для четырехугольника

GLfloat sphereTransX;
GLfloat sphereTransY;
GLfloat sphereTransZ;

GLfloat light1TransX;
GLfloat light1TransY;
GLfloat light1TransZ;

GLfloat LightPosition1[]= { light1TransX, light1TransY, light1TransZ, 1.0f };     // Позиция света

void init(void) {
    //загрузка текстур с помощью библиотеки SOIL
    texture1 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL/resources/textures/texture1.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture2 = SOIL_load_OGL_texture(
            "/home/vkirillov/CLionProjects/OpenGL/resources/textures/texture4.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    glShadeModel(GL_SMOOTH);      // Разрешение сглаженного закрашивания
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Черный фон
    glClearDepth(1.0f);           // Установка буфера глубины
    glEnable(GL_DEPTH_TEST);      // Разрешить тест глубины
    glDepthFunc(GL_LEQUAL);       // Тип теста глубины

    GLfloat LightAmbient1[]= { 0.5f, 0.5f, 0.5f, 1.0f }; // Значения фонового света
    GLfloat LightDiffuse1[]= { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   // Позиция света
    glEnable(GL_LIGHT1); // Разрешение источника света номер один

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void drawPyramid() {

    glBindTexture(GL_TEXTURE_2D, texture2);
    glPushMatrix();

    //Рисование пирамиды
    glLoadIdentity();                               // Сброс просмотра
    glTranslatef(-3.0, -2.0, -15.0f);                 // Сдвиг влево и вглубь экрана
    glRotatef(rtri, 0.0f, 1.0f, 0.0f);                 // Вращение пирамиды по оси Y

    glBegin(GL_TRIANGLES);                          // Начало рисования пирамиды
    glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Передняя)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);                  // Левая точка
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);                  // Правая точка

    glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Правая)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);                  // Лево треугольника (Правая)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);                 // Право треугольника (Правая)

    glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);                  // Низ треугольника (Сзади)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);                 // Лево треугольника (Сзади)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);                 // Право треугольника (Сзади)

    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Лево)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);                  // Лево треугольника (Лево)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);                  // Право треугольника (Лево)
    glEnd();                                                // Кончили рисовать пирамиду


    glBegin(GL_POLYGON);                          // Начало рисования основания пирамиды
    glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право
    glEnd();                                                // Кончили рисовать основание пирамиды

    glFlush();

    rtri += 1.0f;             // Увеличим переменную вращения для треугольника

    glPopMatrix();
}

void drawCube() {
    glBindTexture(GL_TEXTURE_2D, texture1);
    glPushMatrix();

    //Рислвание куба
    glLoadIdentity();
    glTranslatef(3.0f,-2.0f,-15.0f);          // Сдвинуть вправо и вглубь экрана
    glRotatef(rquad,1.0f,1.0f,1.0f);        // Вращение куба по X, Y & Z

    glBegin(GL_QUADS);
    // Передняя грань
    glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх лево

    // Задняя грань
    glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ лево

    // Верхняя грань
    glNormal3f( 0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право

    // Нижняя грань
    glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право

    // Правая грань
    glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево

    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево

    glEnd();                             // Закончили квадраты

    glFlush();

    rquad -= 0.3f;           // Уменьшим переменную вращения для квадрата

    glPopMatrix();
}

void drawLightSource() {
    glLoadIdentity();
    glTranslatef(sphereTransX, sphereTransY, sphereTransZ);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidSphere(0.5, 20, 20);
    glFlush();

    sphereTransX = 9.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001);
    sphereTransY = 1.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.001);
    sphereTransZ = -15.0 + 10.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}

void drawSphere() {
    glLoadIdentity();
    glTranslatef(0.0f,3.0f,-15.0f);          // Сдвинуть вправо и вглубь экрана
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidSphere(1.0, 20, 20);
    glFlush();
}

void drawLight() {
    light1TransY = 10.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001);
    light1TransY = 2.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.001);
    light1TransZ = -14.0 + 10.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.001);

    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   // Позиция света
}

//функция для рендеринга геометрии
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //очистка используемых буферов

    glEnable(GL_LIGHTING);   // Разрешить освещение
    glEnable(GL_TEXTURE_2D);      // Разрешить наложение текстуры
    drawCube();
    drawPyramid();
    glDisable(GL_TEXTURE_2D);
    drawLight();
    drawSphere();
    glDisable(GL_LIGHTING);   // Разрешить освещение

    drawLightSource();

    glutSwapBuffers();
}

//функция вызываемая при изменении размера окна
void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);//задаем область вывода в окне

    glMatrixMode(GL_PROJECTION);//задаем матрицу проектирования

    glLoadIdentity();//загружаем в нее единичную матрицу

    gluPerspective(45.0f, (GLfloat) w / (GLfloat) h, 0.1f, 100.0f);//задаем перспективное преобразование
    //задаем параметры камеры
//    gluLookAt(1.0, -1.0, 8.0, //откуда смотрим
//              0.0, 0.0, 0.0,  //куда смотрим
//              2.0, 8.0, 1.0); //направление вверх

    glMatrixMode(GL_MODELVIEW);    //задаем модельно-видовую матрицу

    glLoadIdentity();    //делаем ее равной единичной матрице
}

//функция вызываемая при нажатии на клавишу, используетьсядля выхода из программы
void key(unsigned char key, int x, int y) {
    if (key == 27 || key == 'q' || key == 'Q')
        exit(0);
}

//создание анимации с помощью библиотеки GLUT
void idle(void) {
    //запрашиваем перерисовку экрана
    glutPostRedisplay();
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
    glutIdleFunc(idle);
    glutKeyboardFunc(key);//нажатие клавиши
    glutMainLoop();//запускаем цикл обработки сообщений
    return 0;
}
