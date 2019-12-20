#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"

GLfloat height = 0.0;
GLfloat angle = 0.0;
GLuint tex_2d;

bool keys[256];      // Массив для процедуры обработки клавиатуры

GLfloat rtri;           // Угол для треугольник
GLfloat rquad;          // Угол для четырехугольника

void init(void) {
    //загрузка текстур с помощью библиотеки SOIL
    tex_2d = SOIL_load_OGL_texture
            (
                    "/home/kirillov/CLionProjects/OpenGL/texture.jpg",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0);
//    glDepthFunc(GL_LESS);
//    glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_SMOOTH);

//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void drawFigures() {
    glLoadIdentity();                               // Сброс просмотра
    glTranslatef(-1.5f,0.0f,-6.0f);                 // Сдвиг влево и вглубь экрана
    glRotatef(rtri,0.0f,1.0f,0.0f);                 // Вращение пирамиды по оси Y
    glBegin(GL_TRIANGLES);                          // Начало рисования пирамиды
    glColor3f(1.0f,0.0f,0.0f);                      // Красный
    glVertex3f( 0.0f, 1.0f, 0.0f);                  // Верх треугольника (Передняя)
    glColor3f(0.0f,1.0f,0.0f);                      // Зеленный
    glVertex3f(-1.0f,-1.0f, 1.0f);                  // Левая точка
    glColor3f(0.0f,0.0f,1.0f);                      // Синий
    glVertex3f( 1.0f,-1.0f, 1.0f);                  // Правая точка
    glColor3f(1.0f,0.0f,0.0f);                      // Красная
    glVertex3f( 0.0f, 1.0f, 0.0f);                  // Верх треугольника (Правая)
    glColor3f(0.0f,0.0f,1.0f);                      // Синия
    glVertex3f( 1.0f,-1.0f, 1.0f);                  // Лево треугольника (Правая)
    glColor3f(0.0f,1.0f,0.0f);                      // Зеленная
    glVertex3f( 1.0f,-1.0f, -1.0f);                 // Право треугольника (Правая)
    glColor3f(1.0f,0.0f,0.0f);                      // Красный
    glVertex3f( 0.0f, 1.0f, 0.0f);                  // Низ треугольника (Сзади)
    glColor3f(0.0f,1.0f,0.0f);                      // Зеленный
    glVertex3f( 1.0f,-1.0f, -1.0f);                 // Лево треугольника (Сзади)
    glColor3f(0.0f,0.0f,1.0f);                      // Синий
    glVertex3f(-1.0f,-1.0f, -1.0f);                 // Право треугольника (Сзади)
    glColor3f(1.0f,0.0f,0.0f);                      // Красный
    glVertex3f( 0.0f, 1.0f, 0.0f);                  // Верх треугольника (Лево)
    glColor3f(0.0f,0.0f,1.0f);                      // Синий
    glVertex3f(-1.0f,-1.0f,-1.0f);                  // Лево треугольника (Лево)
    glColor3f(0.0f,1.0f,0.0f);                      // Зеленный
    glVertex3f(-1.0f,-1.0f, 1.0f);                  // Право треугольника (Лево)
    glEnd();                                                // Кончили рисовать пирамиду

    glLoadIdentity();
    glTranslatef(1.5f,0.0f,-7.0f);          // Сдвинуть вправо и вглубь экрана
    glRotatef(rquad,1.0f,1.0f,1.0f);        // Вращение куба по X, Y & Z
    glBegin(GL_QUADS);                      // Рисуем куб
    glColor3f(0.0f,1.0f,0.0f);              // Синий
    glVertex3f( 1.0f, 1.0f,-1.0f);          // Право верх квадрата (Верх)
    glVertex3f(-1.0f, 1.0f,-1.0f);          // Лево верх
    glVertex3f(-1.0f, 1.0f, 1.0f);          // Лево низ
    glVertex3f( 1.0f, 1.0f, 1.0f);          // Право низ
    glColor3f(1.0f,0.5f,0.0f);              // Оранжевый
    glVertex3f( 1.0f,-1.0f, 1.0f);          // Верх право квадрата (Низ)
    glVertex3f(-1.0f,-1.0f, 1.0f);          // Верх лево
    glVertex3f(-1.0f,-1.0f,-1.0f);          // Низ лево
    glVertex3f( 1.0f,-1.0f,-1.0f);          // Низ право
    glColor3f(1.0f,0.0f,0.0f);              // Красный
    glVertex3f( 1.0f, 1.0f, 1.0f);          // Верх право квадрата (Перед)
    glVertex3f(-1.0f, 1.0f, 1.0f);          // Верх лево
    glVertex3f(-1.0f,-1.0f, 1.0f);          // Низ лево
    glVertex3f( 1.0f,-1.0f, 1.0f);          // Низ право
    glColor3f(1.0f,1.0f,0.0f);              // Желтый
    glVertex3f( 1.0f,-1.0f,-1.0f);          // Верх право квадрата (Зад)
    glVertex3f(-1.0f,-1.0f,-1.0f);          // Верх лево
    glVertex3f(-1.0f, 1.0f,-1.0f);          // Низ лево
    glVertex3f( 1.0f, 1.0f,-1.0f);          // Низ право
    glColor3f(0.0f,0.0f,1.0f);              // Синий
    glVertex3f(-1.0f, 1.0f, 1.0f);          // Верх право квадрата (Лево)
    glVertex3f(-1.0f, 1.0f,-1.0f);          // Верх лево
    glVertex3f(-1.0f,-1.0f,-1.0f);          // Низ лево
    glVertex3f(-1.0f,-1.0f, 1.0f);          // Низ право
    glColor3f(1.0f,0.0f,1.0f);              // Фиолетовый
    glVertex3f( 1.0f, 1.0f,-1.0f);          // Верх право квадрата (Право)
    glVertex3f( 1.0f, 1.0f, 1.0f);          // Верх лево
    glVertex3f( 1.0f,-1.0f, 1.0f);          // Низ лево
    glVertex3f( 1.0f,-1.0f,-1.0f);          // Низ право
    glEnd();                                // Закончили квадраты

    rtri+=0.4f;             // Увеличим переменную вращения для треугольника
    rquad-=0.3f;           // Уменьшим переменную вращения для квадрата
}

//функция для рендеринга геометрии
void display(void) {
    //очистка используемых буферов
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //для анимации будем использовать вращение, задаваемое углом angle
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    drawFigures();
    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
    
}

//создание анимации с помощью библиотеки GLUT
void idle(void) {
    //обработка перемещений
//    angle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.00030f) * 300.0f * 1.5;
//    height = 0.1f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.003);
    //запрашиваем перерисовку экрана
    glutPostRedisplay();
}

//функция вызываемая при изменении размера окна
void reshape(int w, int h) {
    //задаем область вывода в окне
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //задаем матрицу проектирования
    glMatrixMode(GL_PROJECTION);
    //загружаем в нее единичную матрицу
    glLoadIdentity();
    //задаем перспективное преобразование
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    //задаем параметры камеры
//    gluLookAt(1.0, -1.0, 8.0, //откуда смотрим
//              0.0, 0.0, 0.0,  //куда смотрим
//              2.0, 8.0, 1.0); //направление вверх
    //задаем модельно-видовую матрицу
    glMatrixMode(GL_MODELVIEW);
    //делаем ее равной единичной матрице
    glLoadIdentity();
}

//функция вызываемая при нажатии на клавишу, используетьсядля выхода из программы
void key(unsigned char key, int x, int y) {
    if (key == 27 || key == 'q' || key == 'Q')
        exit(0);
}

int main(int argc, char **argv) {
    //инициализация GLUT
    glutInit(&argc, argv);
    //задаем двойную буферезацию
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //задаем размер окна в пикселах
    glutInitWindowSize(1200, 800);
    //задаем координаты окна
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Cubes and teapot");
    init();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.1, 0.1, 0.1, 0.1);
    //регестрируем функции-обработчики рендеринга в окно
    glutDisplayFunc(display);
    //изменение размера окна
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    //нажатие клавиши
    glutKeyboardFunc(key);
    //инициализация
    //запускаем цикл обработки сообщений
    glutMainLoop();

    return 0;
}


