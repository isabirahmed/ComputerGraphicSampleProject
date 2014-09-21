#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<string.h>

void background();
void drawball();
void goalkeeper();
void gkmovement();
void menudisplay(void);
void bitmap_output(int x, int y, char *string, void *font);
void gameover();
void rules();


GLfloat a0=630.0,b0=620, c0=620, d0=630, e0=640, f0=640, g0=600, h0=630, i0=660, j0=630, k0=600, l0=660;
GLfloat a1=750, b1=740, c1=720, d1=700, e1=720, f1=740, g1=750, h1=700, i1=750, j1=650, k1=600, l1=600;
GLfloat m0=645,n0=680,o0=690,p0=680, q0=645, r0=610,s0=600,t0=610, u0=645;
GLfloat m1=0,n1=10,o1=45;p1=80, q1=90, r1=80,s1=45,t1=10,u1=45;
int goalkeepermovement=0,scale=2,menuin=0,goalkick=0,kickspeed=12,goal_score=0,temp=0,toexit=0,goalscored=0;
float transfactor=0.25;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if(menuin==0)
    menudisplay();
    else
    {
        background();
        goalkeeper();
    }
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
    if(menuin==1)
    {
        switch (key)
        {
            case 'm' : goalkick=1;
                        break;

            case 'q':exit(0);
        }
    }

    else if(menuin==0)
    {
        switch(key)
        {
            case '1' : menuin=1;
                        glutPostRedisplay();
                        break;
            case '2' : exit(0);
        }
    }
}

void rules()
{
    GLint w=1200;
    GLint h=1000;
    bitmap_output(30, 160, "Controls : ", GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(30, 115, "Press M to Launch the Ball", GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(30, 75, "Press Q to Quit the Game",GLUT_BITMAP_TIMES_ROMAN_24);
    if(toexit==1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        bitmap_output(550, 600, "Game Over !!!! ",GLUT_BITMAP_TIMES_ROMAN_24);
        bitmap_output(530, 500, "Thanks for Playing",GLUT_BITMAP_TIMES_ROMAN_24);
        glutSwapBuffers();
        glFlush();
        sleep(3);
        exit(0);
    }
    if(goalscored==1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        bitmap_output(550, 600, "Goal Scored!!!! ",GLUT_BITMAP_TIMES_ROMAN_24);
        glutSwapBuffers();
        glFlush();
        sleep(2);
        goalscored=0;
    }
    glutPostRedisplay();
}

void goalkeeper()
{
    rules();
    menuin=1;
    drawball();

//Face
    glColor3f(1,0.4,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(a0,a1);
        glVertex2f(b0,b1);
        glVertex2f(c0,c1);
        glVertex2f(d0,d1);
        glVertex2f(e0,e1);
        glVertex2f(f0,f1);
        glVertex2f(a0,a1);
    glEnd();

//Neck
    glLineWidth(5);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(d0,d1);
        glVertex2f(h0,h1);
    glEnd();

//Stomach
    glListBase(20);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex2f(h0,h1);
        glVertex2f(j0,j1);
    glEnd();

//Legs
    glLineWidth(5);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(j0,j1);
        glVertex2f(k0,k1);
        glVertex2f(j0,j1);
        glVertex2f(l0,l1);
    glEnd();

//Hands
    glLineWidth(5);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(h0,h1);
        glVertex2f(g0,g1);
        glVertex2f(h0,h1);
        glVertex2f(i0,i1);
    glEnd();

//Border for Goal Post
    glLineWidth(3);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(300,600);
        glVertex2f(150,400);
        glVertex2f(150,400);
        glVertex2f(1050,400);
        glVertex2f(1050,400);
        glVertex2f(900,600);
    glEnd();
    gkmovement();
}

void gkmovement()
{
        if(goalkick==1 && s1<=600)
        {
            s1+=kickspeed; m1+=kickspeed; n1+=kickspeed; o1+=kickspeed; p1+=kickspeed; q1+=kickspeed; r1+=kickspeed; t1+=kickspeed; u1+=kickspeed;
            t0+=transfactor; s0+=transfactor; r0+=transfactor; p0-=transfactor; o0-=transfactor; n0-=transfactor;
        }

        if(s1>=600)
        {
            temp=scale;
            scale=0;
            //Condition for Goal
            if((s0>l0 && o0>l0) || (s0<k0 && o0<k0))
            {

                printf("Goal Score is %d\n",++goal_score);
                sleep(1);
                scale=temp+2;
                m0=645,n0=680,o0=690,p0=680, q0=645, r0=610,s0=600,t0=610, u0=645;
                m1=0,n1=10,o1=45;p1=80, q1=90, r1=80,s1=45,t1=10,u1=45;
                goalkick=0;
                goalscored=1;
            }
            else
            {
                toexit=1;
                printf("Goal not Scored!!!\n");
                sleep(2);
            }
        }
        if(goalkeepermovement==0)
        {
            a0+=scale,b0+=scale,c0+=scale,d0+=scale,e0+=scale,f0+=scale,g0+=scale,h0+=scale,i0+=scale,j0+=scale,k0+=scale,l0+=scale;
            if(i0+scale>=900)
            {
                goalkeepermovement=1;
            }
        }
        if(goalkeepermovement==1)
        {
            a0-=scale,b0-=scale,c0-=scale,d0-=scale,e0-=scale,f0-=scale,g0-=scale,h0-=scale,i0-=scale,j0-=scale,k0-=scale,l0-=scale;
            if(g0-scale<=300)
            {
                goalkeepermovement=0;
            }
        }
    glutPostRedisplay();
}

void drawball()
{
    glEnable(GL_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex2f(m0,m1);
        glVertex2f(n0,n1);
        glVertex2f(o0,o1);
        glVertex2f(p0,p1);
        glVertex2f(q0,q1);
        glVertex2f(r0,r1);
        glVertex2f(s0,s1);
        glVertex2f(t0,t1);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(t0,t1);
        glVertex2f(u0,u1);
        glVertex2f(m0,m1);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(n0,n1);
        glVertex2f(o0,o1);
        glVertex2f(u0,u1);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(p0,p1);
        glVertex2f(u0,u1);
        glVertex2f(q0,q1);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(s0,s1);
        glVertex2f(u0,u1);
        glVertex2f(r0,r1);
    glEnd();
}

void background()
{   // For Green Background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1200, 0, 1000);
    glScalef(1, 1, 1);
    glTranslatef(0, 0, 0);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(1200,0,0);
    glVertex3f(1200,600,0);
    glVertex3f(0,600,0);
    glEnd();

    // For Blue Background
    glColor3f(0,0.6,1);
    glBegin(GL_POLYGON);
    glVertex3f(0,600,0);
    glVertex3f(1200,600,0);
    glVertex3f(1200,1000,0);
    glVertex3f(0,1000,0);
    glEnd();

    // For Pole
    glColor3f(1,1,1);
    glLineWidth(25.0);
    glBegin(GL_LINES);
    glVertex3f(300,600,0);
    glVertex3f(300,900,0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(300,900,0);
    glVertex3f(900,900,0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(900,900,0);
    glVertex3f(900,600,0);
    glEnd();

    // Draw the mesh
    glLineWidth(1.0);
    GLint x0=300,y0=605,x1=900,y1=605;

    while(y0<=895){

    glBegin(GL_LINES);
    glVertex3f(x0,y0,0);
    glVertex3f(x1,y1,0);
    glEnd();
    y0+=20;
    y1+=20;
    }
     x0=305,y0=600,x1=305,y1=900;

    while(x0<=895){

    glBegin(GL_LINES);
    glVertex3f(x0,y0,0);
    glVertex3f(x1,y1,0);
    glEnd();
    x0+=20;
    x1+=20;
    }

}

void bitmap_output(int x, int y, char *string, void *font)
{
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
      glutBitmapCharacter(font, string[i]);
    }
}

void menudisplay(void)
{
    GLint w=1200;
    GLint h=1000;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);
    bitmap_output(450, 35, "Welcome to Entropy Football Fun...",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(40, 100, "This is a game we have developed in C using OpenGL, in which the gamer has to score as many goals as possible with ",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(40, 145, "goalkeeper defending the goal post. The Player can shoot the ball by pressing the 'M' key on the keyboard or may wait",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(40, 190, "until he finds a Clear Shot. Points are given based on the number of goals scored. The Level of Difficulty is increased by",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(400, 235, "increasing the movement of the goalkeeper. ",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(550, 360, "Press 1 to play the Game.",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(599, 420, "Press 2 to Exit ",GLUT_BITMAP_TIMES_ROMAN_24);

    bitmap_output(20, 620, "Rules for the Game : ",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(20, 660, "Controls : Press M for Launching the Ball",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(110, 700, "Press Q to Quit",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(20, 800, "Developers of the Game : Shailesh Kumar C (1PE10CS087)",GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(245, 840, "Sabir Ahmed      (1PE10CS079)",GLUT_BITMAP_TIMES_ROMAN_24);
    glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1200,1000);
	glutInitWindowPosition(0,0);
    glutCreateWindow("Entropy Football Fun");
    glutDisplayFunc(display);
    glutFullScreen();
    glutKeyboardFunc(keyboard);
	glutMainLoop();
    return 0;
}
