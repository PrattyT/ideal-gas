//
// Created by Pratyush Tulsian on 11/1/20.
//

#include <visualizer/gascontainer.h>
#include <core/particle.h>
#include "random"
#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;
using std::uniform_real_distribution;
using std::default_random_engine;
using namespace ci;
using namespace gl;
using ci::Color;

idealgas::GasContainer::GasContainer() {
  SpawnParticles(ParticleColor::red, kRedMass, kParticles);
  SpawnParticles(ParticleColor::blue, kBlueMass, kParticles);
  SpawnParticles(ParticleColor::green, kGreenMass, kParticles);
}



void GasContainer::SpawnParticles(ParticleColor color, float mass, size_t amount) {

  // random generator code derived from: https://levelup.gitconnected.com/learning-c-generating-random-
  // numbers-the-c-11-way-f041bbe94f3errr
  default_random_engine random_engine;
  uniform_real_distribution<float> x_position(kMinX+kBuffer, kMaxX-kBuffer);
  uniform_real_distribution<float> y_position(kMinY+kBuffer, kMaxY-kBuffer);
  uniform_real_distribution<float> x_velocity(-5.0, 5.0);
  uniform_real_distribution<float> y_velocity(-5.0, 5.0);
  uniform_real_distribution<float> radius(2, 6);

  for (size_t p = 0; p < amount; p++) {

    float x = (float) x_position(random_engine);
    float y = (float) y_position(random_engine);
    float v1 = (float) x_velocity(random_engine);
    float v2 = (float) y_velocity(random_engine);
    float r = (float) radius(random_engine);

    vec2 position(x, y);
    vec2 velocity(v1, v2);
    Particle particle(velocity, position, r, mass, color);
    particles_.push_back(particle);
  }
}

void GasContainer::Draw() {

  color(Color::white());
  drawStrokedRect(ci::Rectf(kMinX, kMinY, kMaxX, kMaxY));

  for (Particle particle : particles_) {
    SetColor(particle.GetColor());
    drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }

}

void GasContainer::Update() {

  for (int i = 0; i <= particles_.size(); i++) {
    Particle &p = particles_[i];

    // check if colliding with another particle
    for (int j = 0; j < particles_.size(); j++) {
      if (i != j) { // skip self
          if (p.IsColliding(particles_[j])) p.Collide(particles_[j]);
      }
    }

    // check for wall collision
    p.HittingWall();

    // default
    p.UpdatePosition();
  }

}

void GasContainer::SlowDown() {
  for (Particle &particle : particles_) {
    particle.SlowDown();
  }
}

void GasContainer::SpeedUp() {
  for (Particle &particle : particles_) {
    particle.SpeedUp();
  }
}

void GasContainer::SetColor(ParticleColor c) {
  if (c == ParticleColor::red) {
    color(Color(255, 0, 0));
  }
  if (c == ParticleColor::blue) {
    color(Color(0, 0, 255));
  }
  if (c == ParticleColor::green) {
    color(Color(0, 255, 0));
  }
}

vector<Particle> &GasContainer::GetParticles() {
  return particles_;
}

GasContainer::GasContainer(vector<Particle> &particles) {
  for(Particle &p :particles)
    particles_.push_back(p);
}

} // namespce idealgas
