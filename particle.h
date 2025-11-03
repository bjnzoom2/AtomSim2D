#include "gl2d.h"
#include <iostream>

class Particle {
private:
	double getStrongForce(double distance) {
		const double repel_MeV = 90.0;
		const double attract_MeV = 40.0;
		const double repelRange_nm = 35;
		const double attractRange_nm = 10;
		const double MeV_to_J = 1.602176634e-13;
		double repel_J = repel_MeV * MeV_to_J;
		double attract_J = attract_MeV * MeV_to_J;
		double repelRange_m = repelRange_nm * 1e9;
		double attractRange_m = attractRange_nm * 1e9;

		double Frep = (repel_J / repelRange_m) * std::exp(-distance / repelRange_nm);
		double Fatt = (attract_J / attractRange_m) * std::exp(-distance / attractRange_nm);
		double Fstrong = Frep - Fatt;

		return Fstrong;
	}

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
		chargeMag = charge * 1.602e-19;
	};

	glm::dvec2 position = { 400, 400 };
	float size;
	glm::dvec2 velocity = {};

	int charge;
	double chargeMag;
	double mass;

	glm::dvec2 accumulatedForce = {};

	glm::vec4 color;

	void render(gl2d::Renderer2D& renderer) {
		renderer.renderCircleOutline(position, size, color, 3, 100);
	}

	void getAccumulatedForce(const double *CONST, Particle& otherParticle) {
		glm::dvec2 direction = glm::normalize(otherParticle.position - position);
		double distance = glm::distance(position, otherParticle.position);

		double Fgrav = CONST[0] * (mass * otherParticle.mass / (distance * distance) * 1e9);
		double Felec = CONST[1] * (chargeMag * -otherParticle.chargeMag / (distance * distance) * 1e9);

		double Fstrong = 0;
		if (charge != -1) {
			Fstrong = getStrongForce(distance);
		}

		double Fmag = Fgrav + Felec + Fstrong;
		accumulatedForce += direction * Fmag;
	}

	void step(float deltatime) {
		glm::dvec2 accel = accumulatedForce / mass;

		velocity += accel * (double)deltatime;
		position += velocity * (double)deltatime;

		accumulatedForce = glm::dvec2(0);
	}
};