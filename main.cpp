#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#define rad (3.1416/180)
#define EN_SIZE 20

using namespace std;

float zoom=4;
int tola[5000][5000];
float tX=0,tY=0,tZ=-8,rX=0,rY=0,rZ=4;
float tZ1=-20,tZ2=-40,tZ3=-60,tZ4=-80,tZ5=-100,tZ6=-120;
float rotX=0,rotY=0,rotZ=0;
float cosX=0,cosY=1,cosZ=0;
float angle=0;
float xEye=0.0f,yEye=5.0f,zEye=30.0f;
float cenX=0,cenY=0,cenZ=0,roll=0;
float radius=0;
float theta=0,slope=0;
float speed = 0.1; // Change this value to adjust the speed
float angleBackFrac = 0.5; // Change this value to adjust the rotation speed
int TIME=0;
bool START = false;
float torusPosX[7] = {1,-2,3,-4,-2,0,2};
float torusPosY[7] = {2,3,10,6,7,4,1};
bool rot = false;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void balloon(){
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    // Balon utama
    glColor3d(1.0, 0.3, 0.3); // Warna merah
    glPushMatrix();
        glTranslated(0,2,0);
        glScaled(0.5, 0.5, 0.5); // Mengecilkan balon utama
        glutSolidSphere(2,50,50);
    glPopMatrix();

    // Keranjang balon
    glColor3d(0.6, 0.4, 0.2); // Warna coklat
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(0.3,0.3,0.3); // Mengecilkan keranjang
        glutSolidCube(1);
    glPopMatrix();

    // Tali
    glLineWidth(2.0); // Menambahkan ketebalan tali
    glColor3d(0.6, 0.6, 0.6); // Warna abu-abu
    glPushMatrix();
        glBegin(GL_LINES);
            glVertex3f(-0.15, 0.15, -0.15);
            glVertex3f(-0.15, 2, -0.15);
            glVertex3f(0.15, 0.15, -0.15);
            glVertex3f(0.15, 2, -0.15);
            glVertex3f(-0.15, 0.15, 0.15);
            glVertex3f(-0.15, 2, 0.15);
            glVertex3f(0.15, 0.15, 0.15);
            glVertex3f(0.15, 2, 0.15);
        glEnd();
    glPopMatrix();
    glLineWidth(1.0); // Mengembalikan ketebalan garis ke default
}


void drawBuilding(float x, float y, float z, float height, int color) {
    float r = 0.8f, g = 0.8f, b = 0.8f; // Warna abu-abu untuk bangunan

    // Badan bangunan
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f, height, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Atap
    glColor3f(r * 0.6f, g * 0.6f, b * 0.6f); // Warna atap sedikit lebih gelap
    glPushMatrix();
    glTranslatef(x, y + height / 2.0f, z); // Menyesuaikan translasi atap
    glScalef(1.1f, 0.1f, 1.1f); // Atap lebih tipis
    glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela
    float windowSize = 0.2f; // Ukuran jendela
    float windowSpacing = 0.4f; // Jarak antara jendela
    float windowHeight = height * 0.25f; // Tinggi jendela
    float windowYOffset = height * 0.4f; // Offset vertikal untuk jendela

    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam untuk jendela

    // Jendela pada sisi depan
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(x + i * windowSpacing, y + windowYOffset, z + 0.51f);
        glScalef(windowSize, windowHeight, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x + i * windowSpacing, y - windowYOffset, z + 0.51f);
        glScalef(windowSize, windowHeight, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Jendela pada sisi belakang
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(x + i * windowSpacing, y + windowYOffset, z - 0.51f);
        glScalef(windowSize, windowHeight, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x + i * windowSpacing, y - windowYOffset, z - 0.51f);
        glScalef(windowSize, windowHeight, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Jendela pada sisi kiri
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(x - 0.51f, y + windowYOffset, z + i * windowSpacing);
        glScalef(0.01f, windowHeight, windowSize);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x - 0.51f, y - windowYOffset, z + i * windowSpacing);
        glScalef(0.01f, windowHeight, windowSize);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Jendela pada sisi kanan
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(x + 0.51f, y + windowYOffset, z + i * windowSpacing);
        glScalef(0.01f, windowHeight, windowSize);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x + 0.51f, y - windowYOffset, z + i * windowSpacing);
        glScalef(0.01f, windowHeight, windowSize);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Pintu
    float doorHeight = height * 0.4f;
    float doorWidth = 0.3f;
    glColor3f(0.5f, 0.25f, 0.0f); // Warna coklat untuk pintu
    glPushMatrix();
    glTranslatef(x, y - height / 2.0f + doorHeight / 2.0f, z + 0.51f);
    glScalef(doorWidth, doorHeight, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
}


void Building(int n, int R, int G) {
    for (int i = 0; i < n; i++) {
        glPushMatrix();
        glTranslatef(0, 0.8f + i, 0);
        drawBuilding(0.0f, 0.0f, 0.0f, i + 1, R); // Tinggi bangunan = i + 1, warna = R
        glPopMatrix();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void cloud() {
    // Warna putih untuk awan
    glColor3d(1.0, 1.0, 1.0);

    // Bagian-bagian dari awan
    glPushMatrix();
        glTranslated(0, 10, 0); // Mengangkat awan ke atas
        glutSolidSphere(0.5, 30, 30); // Bola tengah
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.6, 10.2, 0); // Bola kanan
        glutSolidSphere(0.4, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.6, 10.2, 0); // Bola kiri
        glutSolidSphere(0.4, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.3, 10.4, 0); // Bola kanan atas
        glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.3, 10.4, 0); // Bola kiri atas
        glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
}

void environment(int n) {
    // Ground
    glColor3d(0.3, 0.7, 0.3);
    glPushMatrix();
        glTranslated(0, 0, 0);
        glScaled(EN_SIZE * 2, 0.3, EN_SIZE * 2);
        glutSolidCube(1);
    glPopMatrix();

    // Awan 
    glPushMatrix();
        glTranslated(torusPosX[n], 0, torusPosY[n]);
        cloud();
    glPopMatrix();
    
	//gedung
    for(int i=-(EN_SIZE/2)+1;i<(EN_SIZE/2);i+=2){
        for(int j=-(EN_SIZE/2)+1;j<(EN_SIZE/2);j+=2){
            if(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]!=0){
                glPushMatrix();
                    glTranslated(i,0,j);
                    Building(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                glPopMatrix();
            }else if(i>=-5&&i<=5){}
            else{
                tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]=(rand()%5)+1;
                glPushMatrix();
                    glTranslated(i,0,j);
                    Building(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                glPopMatrix();
            }
        }
    }
    for (int i = -(EN_SIZE / 2) + 1; i < (EN_SIZE / 2); i += 2) {
        for (int j = -(EN_SIZE / 2) + 1; j < (EN_SIZE / 2); j += 2) {
            if (tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1] != 0) {
                glPushMatrix();
                glTranslatef(i, 0, j);
                drawBuilding(0.0f, 0.0f, 0.0f, tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1], i % 3); // Menggunakan warna berdasarkan posisi
                glPopMatrix();
            }
        }
    }    
}


void draw(){
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    TIME = t;

    ///Balloon
    if(rotX>11)rotX=11;
    if(rotX<-11)rotX=-11;
    if(rotZ>10)rotZ=10;
    if(rotZ<-15)rotZ=-15;

    glPushMatrix();
        glTranslated(0,1,0);
        glRotated(90,0,1,0);
        glRotated(5,0,0,1);
        glRotated(rotX,1,0,0);
        glRotated(rotY,0,1,0);
        glRotated(rotZ,0,0,1);

        glScaled(0.3,0.3,0.3); // Mengecilkan seluruh balon udara
        balloon();
    glPopMatrix();

    ///Environment
    if(tX>=4.1)tX=4.1;
    if(tX<=-4.1)tX=-4.1;
    if(tY>0.1)tY= 0.1;
    if(tY<-15)tY= -15;

    glPushMatrix();
        glTranslated(tX,tY,tZ);
        environment(2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ2);
        environment(3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ3);
        environment(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ4);
        environment(5);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ5);
        environment(4);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ6);
        environment(2);
    glPopMatrix();

    tZ+=speed;
    tZ1+=speed;
    tZ2+=speed;
    tZ3+=speed;
    tZ4+=speed;
    tZ5+=speed;
    tZ6+=speed;

    if(tZ>=20)tZ=-110;
    if(tZ1>=20)tZ1=-110;
    if(tZ2>=20)tZ2=-110;
    if(tZ3>=20)tZ3=-110;
    if(tZ4>=20)tZ4=-110;
    if(tZ5>=20)tZ5=-110;
    if(tZ6>=20)tZ6=-110;

    if(rotX>0)rotX-=angleBackFrac;
    if(rotX<0)rotX+=angleBackFrac;
    if(rotY>0)rotY-=angleBackFrac;
    if(rotY<0)rotY+=angleBackFrac;
    if(rotZ>0)rotZ-=angleBackFrac;
    if(rotZ<0)rotZ+=angleBackFrac;

    speed += 0.0002;
    if(speed>=1)speed=1;
}

//////////////////////////////////////////////////////////////////////////////////////////

void drawBitmapText(char *str,float x,float y,float z)
{
	char *c;
	glRasterPos3f(x,y+8,z);

	for (c=str; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void drawStrokeText(const char* str, int x, int y, int z)
{
    const char* c;
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black

    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.002f, 0.002f, z); // Decrease the scaling factor

    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeText2(char* str, int x, int y, int z)
{
    char* c;
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black

    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.005f, 0.005f, z); // Decrease the scaling factor

    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeChar(char c,float x,float y,float z)
{
	  glPushMatrix();
          glTranslatef(x, y+8,z);
          glScalef(0.002f,0.002f,z);
          glutStrokeCharacter(GLUT_STROKE_ROMAN , c);
	  glPopMatrix();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;
    double aa=a;

    if(!rot){
        a=0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(	0.0, 4.5, 10.0,
                0, 4, 0,
                0, 1.0f, 0.0f);

    if(START){

        glPushMatrix();
            glTranslated(0,0,0);
            glScaled(zoom,zoom,zoom);
            glRotated(a,0,1,0);
            draw();
        glPopMatrix();

        drawStrokeText("UP: W, DOWN: S, LEFT: A, RIGHT: D, MAIN MENU: M ",-8,0.9,0);
        drawStrokeText("Zoom In : z , Zoom Out : Z",-8,-1,0);
        drawStrokeText("TIME : ",3,0,0);
        int mod,number=0;
        while(TIME){
            mod=TIME%10;
            number=number*10+mod;
            TIME/=10;
        }
        float tmp=0;
        while(number){
            mod=number%10;
            drawStrokeChar(mod+48,4+tmp,0,0);
            number/=10;
            tmp+=0.2;
        }
    }
    else{

        glPushMatrix();
		    glTranslated(0, 1, 0); // Translasi balon di main menu
		    glRotated(aa, 0, 1, 0);
		    glScaled(1.5, 1.5, 1.5);
		    balloon();
		glPopMatrix();

        drawStrokeText("Press G to Start",-1,-2,0);
        drawStrokeText2("By Syakira , Pujiani n Muthi ",-1,-1,0);
        drawStrokeText2("Tugas Besar GKV",-8,0,0);
    }

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    float frac = 0.3;
    float rotFrac = 1;
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'r':
            rot=true;
            break;
        case 't':
            rot=false;
            break;
        case 'Z':
            zoom+=0.05;
            break;
        case 'z':
            zoom-=0.05;
        case 'W':
            tY-=frac;
            rotZ+=rotFrac;
            break;
        case 'S':
            tY+=frac;
            rotZ-=rotFrac;
            break;
        case 'A':
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;
        case 'D':
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
        case 'G':
            START=true;
            break;
        case 'M':
            START=false;
            break;

    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
	glutInitWindowSize(1366,720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("Simulator Balon Udara");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.725,0.9,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
