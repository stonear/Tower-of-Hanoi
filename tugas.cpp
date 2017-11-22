#include <stdio.h>
#include <GL/glut.h>
#include "imageloader.h"
GLuint _gambar, _wood;

GLUquadric * obj;
double torus_translate_1=100;
double rotate_y=0, rotate_x=0;
double column[3] = {10, 32, 54}, jenis[3] = {18, 21, 24};
int a[4] = {2, 1, 0, -1}, b[4] = {-1, -1, -1, -1}, c[4] = {-1, -1, -1, -1};
int animate_torus = -1, animate_tower = -1, win = 0;

GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat position[] = {0.5f, 1.0f, -0.5f, 1.0f};

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void init(void) 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	Image * image = loadBMP("win.bmp");
	_gambar = loadTexture(image);
	Image * image2 = loadBMP("wood.bmp");
	_wood = loadTexture(image2);
}

void tower(void)
{
    obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _wood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 5.0, 5.0, 140.0, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, 75.0, 0.0);
	glutSolidSphere(5, 50, 50);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void papan(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _wood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPushMatrix();
	glTranslatef(0.0, -65.0, 0.0);
//	210,105,30
//	glColor3f(0.82, 0.41, 0.12);
	glColor3f(1.0, 1.0, 0.0);
	
	//papan samping
	glBegin(GL_QUAD_STRIP);
	glNormal3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-100, 0, 100);
	glNormal3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(-100, -10, 100);	
	glNormal3f(0.5f, 0.5f, 0.5f);
	glVertex3f(100, 0, 100);
	glNormal3f(0.5f, 0.0f, 0.5f);
	glVertex3f(100, -10, 100);	
	glNormal3f(0.5f, 0.5f, -0.5f);	
	glVertex3f(100, 0, -100);
	glNormal3f(0.5f, 0.0f, -0.5f);
	glVertex3f(100, -10, -100);	
	glNormal3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-100, 0, -100);
	glNormal3f(-0.5f, 0.0f, -0.5f);
	glVertex3f(-100, -10, -100);
	glNormal3f(-0.5f, 0.5f, 0.5f);	
	glVertex3f(-100, 0, 100);
	glNormal3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(-100, -10, 100);
	glEnd();
	
	//papan atas
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100, 0, 100);
	glNormal3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100, 0, 100);
	glNormal3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100, 0, -100);
	glNormal3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100, 0, -100);
	glEnd();
	
	//papan bawah
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100, -10, 100);
	glNormal3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100, -10, 100);
	glNormal3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100, -10, -100);
	glNormal3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100, -10, -100);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void torus(int x, int y)
{
	glPushMatrix();
	glTranslatef(0.0, column[x], 0.0);
	if(y == 2) glColor3f(1.0, 0.0, 0.0);
	if(y == 1) glColor3f(0.0, 1.0, 0.0);
	if(y == 0) glColor3f(0.0, 0.0, 0.1);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidTorus(8.0, jenis[y], 150, 150);
	glPopMatrix();
}

void torus_animated(int x, int y)
{
	glPushMatrix();
	glTranslatef(0.0, torus_translate_1+column[x], 0.0);
	if(y == 2) glColor3f(1.0, 0.0, 0.0);
	if(y == 1) glColor3f(0.0, 1.0, 0.0);
	if(y == 0) glColor3f(0.0, 0.0, 0.1);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidTorus(8.0, jenis[y], 50, 50);
	glPopMatrix();
}

void win_image(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _gambar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	
	if(win && torus_translate_1 <= 0) win_image();
	else
	{
		glRotatef( rotate_x, 1.0, 0.0, 0.0 );
		glRotatef( rotate_y, 0.0, 1.0, 0.0 );

		glScalef (0.005, 0.005, 0.005);
		
		//papan
		papan();
	
		//tower kiri
		glPushMatrix();	
		glTranslatef(-65.0, -65.0, 0.0);
		tower();	
		for(int i=0; i<3; i++)
		{
			if(a[i] != -1)
			{
				if(animate_tower == 0 && animate_torus == i) torus_animated(i, a[i]);
				else torus(i, a[i]);
			}
		}	
		glPopMatrix();
	
		//tower tengah
		glPushMatrix();	
		glTranslatef(0.0, -65.0, 0.0);
		tower();
		for(int i=0; i<3; i++)
		{
			if(b[i] != -1)
			{
				if(animate_tower == 1 && animate_torus == i) torus_animated(i, b[i]);		
				else torus(i, b[i]);
			}
		}
		glPopMatrix();
	
		//tower kanan
		glPushMatrix();	
		glTranslatef(65.0, -65.0, 0.0);
		tower();
		for(int i=0; i<3; i++)
		{
			if(c[i] != -1)
			{
				if(animate_tower == 2 && animate_torus == i) torus_animated(i, c[i]);
				else torus(i, c[i]);
			}
		}
		glPopMatrix();
	}
	glFlush();
}

void specialKeys( int key, int x, int y )
{
	int temp_asal = -1;
	int temp_tujuan = -1;
	if (key == GLUT_KEY_RIGHT) rotate_y += 5;
	else if (key == GLUT_KEY_LEFT) rotate_y -= 5; 
	else if (key == GLUT_KEY_UP) rotate_x += 5; 
	else if (key == GLUT_KEY_DOWN) rotate_x -= 5;
	else if (key == GLUT_KEY_F1) //kiri ke tengah
	{
		for(int i=0; i<4; i++)
		{
			if(a[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(b[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && a[temp_asal] > b[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			b[temp_tujuan] = a[temp_asal];
			a[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 1;
			torus_translate_1 = 100;
		}
	}
	else if (key == GLUT_KEY_F2) //kiri ke kanan
	{
		for(int i=0; i<4; i++)
		{
			if(a[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(c[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && a[temp_asal] > c[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			c[temp_tujuan] = a[temp_asal];
			a[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 2;
			torus_translate_1 = 100;
		}
	}
	else if (key == GLUT_KEY_F3) //tengah ke kiri
	{
		for(int i=0; i<4; i++)
		{
			if(b[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(a[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && b[temp_asal] > a[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			a[temp_tujuan] = b[temp_asal];
			b[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 0;
			torus_translate_1 = 100;
		}
	}
	else if (key == GLUT_KEY_F4) //tengah ke kanan
	{
		for(int i=0; i<4; i++)
		{
			if(b[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(c[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && b[temp_asal] > c[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			c[temp_tujuan] = b[temp_asal];
			b[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 2;
			torus_translate_1 = 100;
		}
	}
	else if (key == GLUT_KEY_F5) //kanan ke kiri
	{
		for(int i=0; i<4; i++)
		{
			if(c[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(a[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && c[temp_asal] > a[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			a[temp_tujuan] = c[temp_asal];
			c[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 0;
			torus_translate_1 = 100;
		}
	}
	else if (key == GLUT_KEY_F6) //kanan ke tengah
	{
		for(int i=0; i<4; i++)
		{
			if(c[i] == -1)
			{
				temp_asal = i - 1;
				break;
			}
		}
		for(int i=0; i<3; i++)
		{
			if(b[i] == -1)
			{
				temp_tujuan = i;
				break;
			}
		}
		if(temp_tujuan > 0 && c[temp_asal] > b[temp_tujuan-1])
		{
			temp_asal = -1;
			temp_tujuan = -1;
		}
		if(temp_asal != -1 && temp_tujuan != -1)
		{
			b[temp_tujuan] = c[temp_asal];
			c[temp_asal] = -1;
			
			animate_torus = temp_tujuan;
			animate_tower = 1;
			torus_translate_1 = 100;
		}
	}
	//  Request display update
	glutPostRedisplay(); 
}

void idle(void)
{
	if(torus_translate_1 <= 0) animate_torus = animate_tower = -1;
	if(torus_translate_1 > 0) torus_translate_1 -= 1.5;
	if(c[0] == 2 && c[1] == 1 && c[2] == 0) win = 1;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1080, 720);
	glutCreateWindow("Tower of Hanoi");
	init();
	glutDisplayFunc(display); 
	glutSpecialFunc(specialKeys);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
