#include <glew.h>

class Figure {
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int colorBuffer;

	unsigned int EAVertexArray;
	unsigned int EAVertexBuffer;
	unsigned int EAColorBuffer;

	float coords[9];
	float initialColors[9];
	float colors[9];

	void setCoords(float centerX, float centerY, float centerZ, float sideSize) {
		coords[0] = centerX - sideSize / 2.0f;
		coords[1] = centerY - (sideSize * 0.866025f) / 3.0f;
		coords[2] = centerZ;

		coords[3] = centerX + sideSize / 2.0f;
		coords[4] = centerY - (sideSize * 0.866025f) / 3.0f;
		coords[5] = centerZ;

		coords[6] = centerX;
		coords[7] = centerY + ((sideSize * 0.866025f) / 3.0f) * 2.0f;
		coords[8] = centerZ;
	}

	void setColors(float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3) {
		initialColors[0] = r1;
		initialColors[1] = g1;
		initialColors[2] = b1;
		initialColors[3] = r2;
		initialColors[4] = g2;
		initialColors[5] = b2;
		initialColors[6] = r3;
		initialColors[7] = g3;
		initialColors[8] = b3;

		colors[0] = r1;
		colors[1] = g1;
		colors[2] = b1;
		colors[3] = r2;
		colors[4] = g2;
		colors[5] = b2;
		colors[6] = r3;
		colors[7] = g3;
		colors[8] = b3;
	}

	void createObject() {
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 + 1, &coords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 + 1, &colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

public:
	Figure(
		float centerX, float centerY, float centerZ, float sideSize,
		float r1, float g1, float b1,
		float r2, float g2, float b2,
		float r3, float g3, float b3
	) {
		setCoords(centerX, centerY, centerZ, sideSize);

		setColors(r1, g1, b1, r2, g2, b2, r3, g3, b3);

		createObject();
	}

	void colorChange(float colorBrightness) {
		for (int i = 0; i < 9; ++i) {
			colors[i] = initialColors[i] * colorBrightness;
		}

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 + 1, &colors, GL_STATIC_DRAW);
	}

	void drawIt() {
		glBindVertexArray(vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
};