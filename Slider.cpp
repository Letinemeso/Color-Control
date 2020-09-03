#include <glew.h>

#include <math.h>

#include <iostream>

class Slider {
	unsigned int vertexArray[3];
	unsigned int vertexBuffer[3];
	unsigned int colorBuffer[3];

	float centerX, centerY, centerZ, width, height;

	//BOX
	float boxCoords[12];
	float boxColors[12];

	//AXIS
	float axisCoords[12];
	float axisColors[12];
	float axisSize;

	//SLIDER
	float sliderCoords[12];
	float sliderColors[12];
	float sliderCurrentPosition;

	float sliderPosRatio = 1.0f;

	void setCoords() {
		//BOX SETTING
		{
			boxCoords[0] = centerX - width / 2;
			boxCoords[1] = centerY - height / 2;
			boxCoords[2] = centerZ;

			boxCoords[3] = centerX + width / 2;
			boxCoords[4] = centerY - height / 2;
			boxCoords[5] = centerZ;

			boxCoords[6] = centerX + width / 2;;
			boxCoords[7] = centerY + height / 2;
			boxCoords[8] = centerZ;

			boxCoords[9] = centerX - width / 2;;
			boxCoords[10] = centerY + height / 2;
			boxCoords[11] = centerZ;
		}

		//AXIS SETTING
		{
			axisCoords[0] = centerX - width / 20.0f;
			axisCoords[1] = centerY + (height / 2 - height / 10.0f);
			axisCoords[2] = centerZ;

			axisCoords[3] = centerX + width / 20.0f;
			axisCoords[4] = centerY + (height / 2 - height / 10.0f);
			axisCoords[5] = centerZ;

			axisCoords[6] = centerX + width / 20.0f;
			axisCoords[7] = centerY - (height / 2 - height / 10.0f);
			axisCoords[8] = centerZ;

			axisCoords[9] = centerX - width / 20.0f;
			axisCoords[10] = centerY - (height / 2 - height / 10.0f);
			axisCoords[11] = centerZ;

			axisSize = float(sqrt(pow(double(axisCoords[1]) - double(axisCoords[7]), 2)));
		}

		//SLIDER SETTING
		{
			sliderCurrentPosition = axisCoords[1];

			sliderCoords[0] = centerX - width / 5.0f;
			sliderCoords[2] = centerZ;

			sliderCoords[3] = centerX + width / 5.0f;
			sliderCoords[5] = centerZ;

			sliderCoords[6] = centerX + width / 5.0f;
			sliderCoords[8] = centerZ;

			sliderCoords[9] = centerX - width / 5.0f;
			sliderCoords[11] = centerZ;

			float halfWidth = float(sqrt(pow(double(sliderCoords[0]) - double(sliderCoords[3]), 2))) / 2.0f;

			sliderCoords[1] = sliderCurrentPosition - halfWidth * 0.9;
			sliderCoords[4] = sliderCurrentPosition - halfWidth * 0.9;
			sliderCoords[7] = sliderCurrentPosition + halfWidth * 0.9;
			sliderCoords[10] = sliderCurrentPosition + halfWidth * 0.9;
		}
	}

	void setBoxColors(float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float r4, float g4, float b4) {
		boxColors[0] = r1;
		boxColors[1] = g1;
		boxColors[2] = b1;
		boxColors[3] = r2;
		boxColors[4] = g2;
		boxColors[5] = b2;
		boxColors[6] = r3;
		boxColors[7] = g3;
		boxColors[8] = b3;
		boxColors[9] = r4;
		boxColors[10] = g4;
		boxColors[11] = b4;
	}
	void setAxisColors(float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float r4, float g4, float b4) {
		axisColors[0] = r1;
		axisColors[1] = g1;
		axisColors[2] = b1;
		axisColors[3] = r2;
		axisColors[4] = g2;
		axisColors[5] = b2;
		axisColors[6] = r3;
		axisColors[7] = g3;
		axisColors[8] = b3;
		axisColors[9] = r4;
		axisColors[10] = g4;
		axisColors[11] = b4;
	}
	void setSliderColors(float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float r4, float g4, float b4) {
		sliderColors[0] = r1;
		sliderColors[1] = g1;
		sliderColors[2] = b1;
		sliderColors[3] = r2;
		sliderColors[4] = g2;
		sliderColors[5] = b2;
		sliderColors[6] = r3;
		sliderColors[7] = g3;
		sliderColors[8] = b3;
		sliderColors[9] = r4;
		sliderColors[10] = g4;
		sliderColors[11] = b4;
	}

	void createObject() {
		//BOX INITIALIZATION
		glGenVertexArrays(1, &vertexArray[0]);
		glBindVertexArray(vertexArray[0]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vertexBuffer[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &boxCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glGenBuffers(1, &colorBuffer[0]);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &boxColors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//AXIS INITIALIZATION
		glGenVertexArrays(1, &vertexArray[1]);
		glBindVertexArray(vertexArray[1]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vertexBuffer[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &axisCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glGenBuffers(1, &colorBuffer[1]);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &axisColors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//SLIDER INITIALIZATION
		glGenVertexArrays(1, &vertexArray[2]);
		glBindVertexArray(vertexArray[2]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vertexBuffer[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &sliderCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glGenBuffers(1, &colorBuffer[2]);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &sliderColors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	bool pressedOnSlider = false;
public:
	Slider(
		float centerX, float centerY, float centerZ, float width, float height,

		float br1, float bg1, float bb1,
		float br2, float bg2, float bb2,
		float br3, float bg3, float bb3,
		float br4, float bg4, float bb4,

		float ar1, float ag1, float ab1,
		float ar2, float ag2, float ab2,
		float ar3, float ag3, float ab3,
		float ar4, float ag4, float ab4,

		float sr1, float sg1, float sb1,
		float sr2, float sg2, float sb2,
		float sr3, float sg3, float sb3,
		float sr4, float sg4, float sb4
	) {
		this->centerX = centerX;
		this->centerY = centerY;
		this->centerZ = centerZ;
		this->width = width;
		this->height = height;

		setCoords ();
		
		setBoxColors (br1,  bg1,  bb1, br2,  bg2,  bb2, br3,  bg3,  bb3, br4,  bg4,  bb4);
		setAxisColors(ar1, ag1, ab1, ar2, ag2, ab2, ar3, ag3, ab3, ar4, ag4, ab4);
		setSliderColors(sr1, sg1, sb1, sr2, sg2, sb2, sr3, sg3, sb3, sr4, sg4, sb4);

		createObject();
	}

	void buttonPressedAtASliderChecker(float whereX, float whereY) {
		if (((whereX > sliderCoords[0]) && (whereX < sliderCoords[3])) && ((whereY < sliderCoords[7]) && (whereY > sliderCoords[1]))) {
			pressedOnSlider = true;
		}
	}

	void buttonReleased() {
		pressedOnSlider = false;
	}

	void moveIt(float whereX, float whereY) {
		if (pressedOnSlider) {
			if ((whereY < axisCoords[1]) && (whereY > axisCoords[7])) {
				sliderCurrentPosition = whereY;

				sliderCoords[0] = centerX - width / 5.0f;
				sliderCoords[2] = centerZ;

				sliderCoords[3] = centerX + width / 5.0f;
				sliderCoords[5] = centerZ;

				sliderCoords[6] = centerX + width / 5.0f;
				sliderCoords[8] = centerZ;

				sliderCoords[9] = centerX - width / 5.0f;
				sliderCoords[11] = centerZ;

				float halfWidth = float(sqrt(pow(double(sliderCoords[0]) - double(sliderCoords[3]), 2))) / 2.0f;

				sliderCoords[1] = sliderCurrentPosition - halfWidth * 0.9;
				sliderCoords[4] = sliderCurrentPosition - halfWidth * 0.9;
				sliderCoords[7] = sliderCurrentPosition + halfWidth * 0.9;
				sliderCoords[10] = sliderCurrentPosition + halfWidth * 0.9;

				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12 + 1, &sliderCoords, GL_STATIC_DRAW);
				
				sliderPosRatio = float(sqrt(pow(double(sliderCurrentPosition) - double(axisCoords[7]), 2))) / axisSize;
			}
		}
	}

	float returnColorBrightness() {
		return sliderPosRatio;
	}

	void drawIt() {
		for (int i = 0; i < 3; ++i) {
			glBindVertexArray(vertexArray[i]);
			glDrawArrays(GL_QUADS, 0, 4);
		}
		glBindVertexArray(0);
	}
};