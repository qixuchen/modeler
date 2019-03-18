// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "camera.h"
#include "vec.h"
#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label), leftIncrement(1), rightIncrement(-1){ }

    virtual void draw();
private:
	int leftIncrement;
	int rightIncrement;
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	if (ModelerApplication::Instance()->GetControlValue(FRAME_ALL) == 1) {
		Vec3f temp = this->m_camera->getLookAt();
		temp[0] = VAL(XPOS);
		temp[1] = VAL(YPOS);
		temp[2] = VAL(ZPOS);
		this->m_camera->setLookAt(temp);
		//this->m_camera->applyViewingTransform();
	}
    ModelerView::draw();

	if (ModelerApplication::Instance()->animation()) {
		int left = ModelerApplication::Instance()->GetControlValue(LEFTUPPERROTATE);
		int right = ModelerApplication::Instance()->GetControlValue(RIGHTUPPERROTATE);
		if (left == 60) {
			leftIncrement = -1;
		}
		if (left == -100) {
			leftIncrement = 1;
		}
		if (right == 60) {
			rightIncrement = -1;
		}
		if (right == -100) {
			rightIncrement = 1;
		}
		int z = ModelerApplication::Instance()->GetControlValue(ZPOS);
		if (left % 50 == 0) {
			z++;
		}
		ModelerApplication::Instance()->SetControlValue(LEFTUPPERROTATE, left + leftIncrement);
		ModelerApplication::Instance()->SetControlValue(RIGHTUPPERROTATE, right + rightIncrement);
		ModelerApplication::Instance()->SetControlValue(ZPOS, z);
	}


		// draw the floor	
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_RED);
		glPushMatrix();
		glTranslated(-5,0,-5);
		drawBox(10,0.01f,10);
		glPopMatrix();



		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GREEN);
		glPushMatrix();
		glTranslated(VAL(XPOS), VAL(YPOS),VAL(ZPOS));
		//draw the troso
			glPushMatrix();
			glTranslated(-1.1, 3.4, -0.8);
			drawBox(2.2, 3.1, 1.6);
			glTranslated(1.05, -0.2, 0.7);
			drawBox(0.2,0.2,0.2);
			glPopMatrix();

			//draw the beam
			glPushMatrix();
			glTranslated(0, 3.0, 0);
			glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
			glRotated(90, 0.0, 1.0, 0.0);
			glTranslated(0, 0, -1.25);
			if (VAL(DETAILS) >= 1) {
				drawCylinder(2.4, 0.25, 0.25);
			}
				//draw the left upper arm
				glPushMatrix();
				if(VAL(DETAILS) >= 2)
					drawCylinder(0.2, 0.3, 0.3);
				glTranslated(0.0, 0.0, 0.1);
				glRotated(-90, 0.0, 1.0, 0.0);
				glRotated(VAL(LEFTUPPERROTATE), 1.0, 0.0, 0.0);
				glRotated(115, 1.0, 0.0, 0.0);		
				if (VAL(DETAILS) >= 2)
					drawCylinder(1.0,0.2,0.3);
				glTranslated(0, 0, 1.2);

					//draw the left lower arm
					glPushMatrix();
					if (VAL(DETAILS) >= 3)
						drawSphere(0.25);
					glRotated(-65, 1.0, 0.0, 0.0);
					if (VAL(DETAILS) >= 3)
						drawCylinder(1.85, 0.2, 0.3);
					glTranslated(0.0,0.0,1.85);

						//draw the left hand 
						glPushMatrix();
						if (VAL(DETAILS) >= 4)
							drawSphere(0.2);
						glTranslated(-0.25, -0.05, 0);
						if (VAL(DETAILS) >= 4)
							drawBox(0.1, 0.2, 0.5);
						glTranslated(0.4, 0, 0);
						if (VAL(DETAILS) >= 4)
							drawBox(0.1, 0.2, 0.5);
						glPopMatrix();
					glPopMatrix();				
				glPopMatrix();

			glTranslated(0, 0, 2.4);
				//draw the right upper arm
				glPushMatrix();
				if (VAL(DETAILS) >= 2)
					drawCylinder(0.2, 0.3, 0.3);
				glTranslated(0.0, 0.0, 0.1);
				glRotated(-90, 0.0, 1.0, 0.0);
				glRotated(VAL(RIGHTUPPERROTATE), 1.0, 0.0, 0.0);
				glRotated(115, 1.0, 0.0, 0.0);
				if (VAL(DETAILS) >= 2)
					drawCylinder(1.0, 0.2, 0.3);
				glTranslated(0, 0, 1.2);

					//draw the right lower arm
					glPushMatrix();
					if (VAL(DETAILS) >= 3)
						drawSphere(0.25);
					glRotated(-65, 1.0, 0.0, 0.0);
					if (VAL(DETAILS) >= 3)
						drawCylinder(1.85, 0.2, 0.3);
					glTranslated(0.0, 0.0, 1.85);

						//draw the right hand 
						glPushMatrix();
						if (VAL(DETAILS) >= 4)
							drawSphere(0.2);
						glTranslated(-0.25, -0.05, 0);
						if (VAL(DETAILS) >= 4)
							drawBox(0.1, 0.2, 0.5);
						glTranslated(0.4, 0, 0);
						if (VAL(DETAILS) >= 4)
							drawBox(0.1, 0.2, 0.5);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();


	/*// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 1, 4);
		drawBox(1,1,1);
		glPopMatrix();

		// draw cannon
		glPushMatrix();
		glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(VAL(HEIGHT), 0.1, 0.1);

		glTranslated(0.0, 0.0, VAL(HEIGHT));
		drawCylinder(1, 1.0, 0.9);

		glTranslated(0.0, 0.0, 0.5);
		glRotated(90, 1.0, 0.0, 0.0);
		drawCylinder(4, 0.1, 0.2);
		glPopMatrix();

	glPopMatrix();
	*/
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[LEFTUPPERROTATE] = ModelerControl("Left Upper Arm", -100, 60, 1, -20);
	controls[RIGHTUPPERROTATE] = ModelerControl("Right Upper Arm", -100, 60, 1, -20);
	controls[DETAILS] = ModelerControl("Level of details", 0, 4, 1, 4);
	controls[FRAME_ALL] = ModelerControl("Frame all", 0, 1, 1, 0);
    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
