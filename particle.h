#include "gl2d.h"

class Particle {
	glm::dvec2 position = { 400, 400 };
	const float size = 20;
	glm::dvec2 velocity = {};

	const int charge = 0;
	const double mass = 1.67e-27;

	glm::dvec2 accumulatedForce = {};

	const glm::vec4 color = Colors_Orange;

	Particle(glm::dvec2 particlePos, float particleSize, glm::dvec2 particleVelocity, int particleCharge, double particleMass, glm::vec4 particleColor) : position(particlePos),
		size(particleSize), velocity(particleVelocity), charge(particleCharge), mass(particleMass), color(particleColor) {};

	void render(gl2d::Renderer2D& renderer) {
		renderer.renderCircleOutline(position, size, color, 4, 100);
	}
};