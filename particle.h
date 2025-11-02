#include "gl2d.h"

class Particle {
public:
	Particle(glm::dvec2 particlePos, glm::dvec2 particleVelocity, int particleCharge) : position(particlePos), velocity(particleVelocity), charge(particleCharge) {
		switch (charge) {
			case 1:
				color = Colors_Red;
				mass = 1.67e-27;
				size = 20;
				break;
			case 0:
				color = {1, 0.65, 0.34, 1};
				mass = 1.67e-27;
				size = 20;
				break;
			case -1:
				color = { 0, 1, 1, 1 };
				mass = 9.109e-31;
				size = 10;
				break;
		}
	};

	glm::dvec2 position = { 400, 400 };
	float size;
	glm::dvec2 velocity = {};

	int charge;
	double mass;

	glm::dvec2 accumulatedForce = {};

	glm::vec4 color;

	void render(gl2d::Renderer2D& renderer) {
		renderer.renderCircleOutline(position, size, color, 3, 100);
	}
};