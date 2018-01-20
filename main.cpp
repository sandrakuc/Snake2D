/* Uproszczony Snake,
Lista zadan:
*naprawic swiatlo
*naprawic zbieranie zarcia
*sprawic, aby ogon rosl
*kolizja lba z ogone, */


#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tgmath.h>
#include "SnakeEngine.h"

#define ANIM_FPS	40 //liczba klatek

using namespace std;

enum
{
    FULL_WINDOW,
    ASPECT_1_1,
    EXIT
}; // do menu

bool areSame(double a, double b)
{
    return fabs(a - b) < 0.01;
}

SnakeEngine snakeEngine;

int Aspect = FULL_WINDOW;

ofstream ofile;
ifstream ifile; // pliki do zapisywania wyniku gry

GLdouble eyex = 0;
GLdouble eyey = 5;
GLdouble eyez = 0.3; // polozenie obserwatora

GLint points = 0; // punkty

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = -11; // punkt, w kierunku ktorego obserwator jest zwrocony

GLfloat lightAmb[] = {0, 0, 0, 1};
GLfloat lightDif[] = {1, 1, 1, 1};
GLfloat lightPos[] = {0, 0, 1, 0};
GLfloat lightSpec[] = {1, 1, 1, 1}; // macierze dla swiatla

void Menu( int value );

void setupScene(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 100);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
} // funkcja odpowiedzialna za ustawienie swiatla

void drawPoint(double x, double z, double red, double green, double blue) {
    glPushMatrix();
        glColor3f(red,green,blue);
        glBegin(GL_POLYGON);
            glVertex3f( x, 0.0, z );
            glVertex3f( x, 0.0, z-0.1 );
            glVertex3f( x+0.1, 0.0, z-0.1);
            glVertex3f( x+0.1, 0.0, z);

            glVertex3f( x, 0.1, z );
            glVertex3f( x, 0.1, z-0.1 );
            glVertex3f( x+0.1, 0.1, z-0.1);
            glVertex3f( x+0.1, 0.1, z);

            glVertex3f( x, 0.0, z );
            glVertex3f( x, 0.0, z-0.1 );
            glVertex3f( x, 0.1, z -0.1);
            glVertex3f( x, 0.1, z);

            glVertex3f( x, 0.0, z );
            glVertex3f( x, 0.1, z );
            glVertex3f( x+0.1, 0.1, z);
            glVertex3f( x+0.1, 0.0, z);

            glVertex3f( x+0.1, 0.1, z );
            glVertex3f( x+0.1, 0.1, z-0.1 );
            glVertex3f( x+0.1, 0.0, z-0.1);
            glVertex3f( x+0.1, 0.0, z);

            glVertex3f( x, 0.1, z-0.1 );
            glVertex3f( x, 0.1, z-0.1 );
            glVertex3f( x+0.1, 0.0, z-0.1);
            glVertex3f( x+0.1, 0.0, z-0.1);
        glEnd();
    glPopMatrix();
}

void Display() //wyswietlenie sceny
{
    srand(time(NULL)); //losowanie polozenia zarcia
    glClearColor( 0, 0, 0, 1 ); //kolor tla
    glClear( GL_COLOR_BUFFER_BIT ); //czyszczenie bufora
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0 ); //widok
   // glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glPushMatrix(); //macierz
        glColor3f( 0.0, 1.0, 0.0 ); //zielony kolor
        glBegin( GL_POLYGON); //kwadrat
            glVertex3f( -3.0, 0.0, 0.0 );
            glVertex3f( -3.0, 0.0, -2.0 );
            glVertex3f( 3.0, 0.0, -2.0 );
            glVertex3f( 3.0, 0.0, 0.0 ); //wierzcholki
        glEnd(); //koniec
    glPopMatrix(); //koniec macierz



    //rysowanie snejka
    for(Point p : snakeEngine.getSnakePoints()) {
        drawPoint(p.getConvertedX(), p.getConvertedZ(), 1,0,1); //narysowanie glowy weza
    }

    //rysowanie walla
    for(Point p : snakeEngine.getWallPoints()) {
        drawPoint(p.getConvertedX(), p.getConvertedZ(), 1,0,1); //narysowanie glowy weza
    }

    //rysowanie jedzonka
    drawPoint(snakeEngine.food.getConvertedX(), snakeEngine.food.getConvertedZ(), 1,0,0); //narysowanie glowy weza

    if(!snakeEngine.tick()) {
        //zapisywanie wynikow do pliku, gameover
        ofile.open("score.dat",std::ios::trunc);
        ofile<<points<<endl;
        ofile.close();
        ifile.open("score.dat",std::ios::in);
        char a[4];
        ifile>>a;
        std::cout<<a;
        char tekst[50]= "Zdobyte punkty: ";
        strcat(tekst,a);
        MessageBox(NULL,tekst,"Game Over",0);
        Menu(EXIT);
    }

    //glDisable( GL_LIGHTING );
    //glDisable( GL_COLOR_MATERIAL );
    glFlush();
    glutSwapBuffers();
}



void ZegarFun(int val) { //funkcja zegarowa dla animacji
    glutPostRedisplay();
	glutTimerFunc(5000/ANIM_FPS, ZegarFun, 0);
}


void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if( Aspect == ASPECT_1_1 )
    {
        if( width < height && width > 0 )
             glFrustum( - 2.0, 2.0, - 2.0 * height / width, 2.0 * height / width, 1.0, 5.0 );
        else
        if( width >= height && height > 0 )
             glFrustum( - 2.0 * width / height, 2.0 * width / height, - 2.0, 2.0, 1.0, 5.0 );

    }
    else
         glFrustum( - 2.0, 2.0, - 2.0, 2.0, 1.0, 5.0 );
    Display();
} //funkcja do przeksztalcania


void Keyboard( unsigned char key, int x, int y )
{
    if( key == '+' )
         eyez -= 0.1;
    if( key == '-' )
         eyez += 0.1;
    if(key == 'w' || key == 'W')
        snakeEngine.setDirection(SnakeEngine::UP);
    if(key == 'd' || key == 'D')
        snakeEngine.setDirection(SnakeEngine::RIGHT);
    if(key == 's' || key == 'S')
        snakeEngine.setDirection(SnakeEngine::DOWN);
    if(key == 'a' || key == 'A')
        snakeEngine.setDirection(SnakeEngine::LEFT);

    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}
// obsluha klawiatury

void SpecialKeys( int key, int x, int y )
{
    switch( key )
    {
    case GLUT_KEY_LEFT:
        eyex += 0.1;
        break;

    case GLUT_KEY_UP:
        eyey -= 0.1;
        break;

    case GLUT_KEY_RIGHT:
        eyex -= 0.1;
        break;

    case GLUT_KEY_DOWN:
        eyey += 0.1;
        break;

    }

    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
} // bsluga klawiszy z biblioteki GLUT

void Menu( int value )
{
    switch( value )
    {
    case FULL_WINDOW:
        Aspect = FULL_WINDOW;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;

    case ASPECT_1_1:
        Aspect = ASPECT_1_1;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;

    case EXIT:
        exit( 0 );
    }
} // menu

int main( int argc, char * argv[] )
{
    snakeEngine = SnakeEngine();


     // wyszukaæ zrodlo bugow
    glutInit( & argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 400, 400 );
    glutCreateWindow( "Snake 3D" );
    glutDisplayFunc( Display );
    glutReshapeFunc( Reshape );
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeys);
    glutCreateMenu( Menu );
    glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
    //setupScene(); //UWAGA!!! Bug!!! jak sie odkomentuje to zamiast ustawionego oswietlenia wszystko robi sie czarne
    // szukaj zakomentowanych funkcji w Display()


    glutMainLoop();

    return 0;
}

