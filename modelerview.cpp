#include "modelerview.h"
#include "camera.h"

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.h>
#include <FL/gl.h>
#include <GL/glu.h>
#include <cstdio>

static const int	kMouseRotationButton			= FL_LEFT_MOUSE;
static const int	kMouseTranslationButton			= FL_MIDDLE_MOUSE;
static const int	kMouseZoomButton				= FL_RIGHT_MOUSE;

bool ModelerView::bTwist = false;
bool ModelerView::bDrag = false;

ModelerView::ModelerView(int x, int y, int w, int h, char *label)
: Fl_Gl_Window(x,y,w,h,label)
{
    m_camera = new Camera();
}

ModelerView::~ModelerView()
{
	delete m_camera;
}
int ModelerView::handle(int event)
{
    unsigned eventCoordX = Fl::event_x();
	unsigned eventCoordY = Fl::event_y();
	unsigned eventButton = Fl::event_button();
	unsigned eventState  = Fl::event_state();

	switch(event)	 
	{
	case FL_PUSH:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
				if(!bTwist)
					m_camera->clickMouse(kActionRotate, eventCoordX, eventCoordY );
				else {
					//cout << "twist" << endl;
					bTwist = false;
					m_camera->clickMouse(kActionTwist, eventCoordX, eventCoordY);
				}
				break;
			case kMouseTranslationButton:
				m_camera->clickMouse(kActionTranslate, eventCoordX, eventCoordY );
				break;
			case kMouseZoomButton:
				m_camera->clickMouse(kActionZoom, eventCoordX, eventCoordY );
				break;
			}
           // printf("push %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_DRAG:
		{
			bDrag = true;
			m_camera->dragMouse(eventCoordX, eventCoordY);
            //printf("drag %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_RELEASE:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
				{
					if (bDrag == false) {
						bTwist = true;
					}
					bDrag = false;
					m_camera->releaseMouse(eventCoordX, eventCoordY);
					break;
				}
			case kMouseTranslationButton:
			case kMouseZoomButton:
				{
					bTwist = false;
					m_camera->releaseMouse(eventCoordX, eventCoordY);
					bDrag = false;
					break;
				}
			}
          //  printf("release %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	default:
		return 0;
	}
	
	redraw();

	return 1;
}

static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
static GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static GLfloat lightSpecular0[] = { 0.5, 0.5, 0.7, 1 };
static GLfloat lightPosition1[] = { -4, 2, 4, 0 };
static GLfloat lightDiffuse1[]  = { 1, 1, 1, 1 };
static GLfloat lightSpecular1[] = { 0.5, 0.5, 0.7, 1 };
static GLfloat lightPosition2[] = { 4, 4, 5, 0 };
static GLfloat lightDiffuse2[] = { 0.7, 1, 1, 1 };


void ModelerView::draw()
{
    if (!valid())
    {
        glShadeModel( GL_SMOOTH );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
        glEnable( GL_LIGHT1 );
		//glEnable(GL_LIGHT2);
		glEnable( GL_NORMALIZE );
    }

  	glViewport( 0, 0, w(), h() );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,float(w())/float(h()),1.0,100.0);
				
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_camera->applyViewingTransform();

    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	//glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
}