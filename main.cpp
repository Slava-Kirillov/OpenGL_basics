#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"

GLfloat height = 0.0;
GLfloat angle = 0.0;
GLuint tex_2d;

void init(void)
{
    //загрузка текстур с помощью библиотеки SOIL
    tex_2d = SOIL_load_OGL_texture
    (
     "/home/kirillov/CLionProjects/OpenGL/texture.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    //освещение
    GLfloat light_ambient[] =
    {0.9, 0.9, 0.95, 1.0};
    GLfloat light_diffuse[] =
    {1.0, 0.95, 0.8, 1.0};
    GLfloat light_specular[] =
    {1.0, 0.95, 0.8, 1.0};
    GLfloat light_position[] =
    {1.0, 0.5, 1.0, 0.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glHint ( GL_POLYGON_SMOOTH_HINT,         GL_NICEST );
    glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void drawCube (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2)
{
    glBegin(GL_POLYGON);
    // Передняя грань
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);     // Низ право
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);      // Верх право
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);     // Верх лево
    glEnd();
    
    // Задняя грань
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // Верх право
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // Верх лево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // Низ лево
    glEnd();
    
    // Верхняя грань
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // Верх лево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // Низ лево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);       // Низ право
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // Верх право
    glEnd();
    
    // Нижняя грань
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // Верх лево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);      // Низ лево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);     // Низ право
    glEnd();
    
    // Правая грань
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // Низ право
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // Верх право
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);       // Верх лево
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);      // Низ лево
    glEnd();
    
    // Левая грань
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);     // Низ право
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // Верх право
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // Верх лево
    glEnd();
}

//функция для рендеринга геометрии
void display(void)
{
    //очистка используемых буферов
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //для анимации будем использовать вращение, задаваемое углом angle
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //задаем ориентацию через углы Эйлера
    glRotatef(angle, 0.0, 0.0, 1.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(2.0, 2.0, angle / 140.0f);
    drawCube(5.0, 2.0, 0.0, 5.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, height, 0.0);
    drawCube(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
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
    angle = sin(glutGet ( GLUT_ELAPSED_TIME ) * 0.00030f) * 300.0f * 1.5;
    height = 0.1f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.003);
    //запрашиваем перерисовку экрана
    glutPostRedisplay();
}

//функция вызываемая при изменении размера окна
void reshape(int w, int h)
{
    //задаем область вывода в окне
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //задаем матрицу проектирования
    glMatrixMode(GL_PROJECTION);
    //загружаем в нее единичную матрицу
    glLoadIdentity();
    //задаем перспективное преобразование
    gluPerspective ( 90.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0 );
    //задаем параметры камеры
    gluLookAt(1.0, -1.0, 8.0, //откуда смотрим
              0.0, 0.0, 0.0,  //куда смотрим
              2.0, 8.0, 1.0); //направление вверх
    //задаем модельно-видовую матрицу
    glMatrixMode(GL_MODELVIEW);
    //делаем ее равной единичной матрице
    glLoadIdentity();
}

//функция вызываемая при нажатии на клавишу, используетьсядля выхода из программы
void key(unsigned char key, int x, int y)
{
    if ( key == 27 || key == 'q' || key == 'Q' )
        exit ( 0 );
}

int main(int argc, char **argv)
{
    //инициализация GLUT
    glutInit(&argc, argv);
    //задаем двойную буферезацию
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    //задаем размер окна в пикселах
    glutInitWindowSize(600, 600);
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


