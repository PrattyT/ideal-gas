//
// Created by Pratyush Tulsian on 11/1/20.
//
#pragma clang diagnostic push
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

const vec2 kIncrement(1.1, 1.1);
const vec2 kDecrement(0.9, 0.9);

const float kRedMass = 10;
const float kGreenMass = 20;
const float kBlueMass = 30;

const float kRadius = 4;

enum ParticleColor { red, blue, green };

/**
 * Represents a Particle
 */
class Particle {

 public:

  /**
   * Create a new Particle Object
   */
  Particle(const vec2 &velocity, const vec2 &position, float radius, float mass, ParticleColor color);

  /**
   * Update the position of the particle after one frame
   */
  void UpdatePosition();

  /**
   * Check if two particles are colliding
   */
  bool IsColliding(Particle &other);

  /**
   * Update velocity based on hitting a wall
   */
  void HittingWall();

  /**
   * Update velocity of two colliding particles
   */
  void Collide(Particle &other);

  /**
  * Check if moving towards other particle
  */
  bool MovingTowards(Particle &other);

  /**
   * Decrement this particles velocity
   */
  void SlowDown();

  /**
   * Increment this particles velocity
   */
  void SpeedUp();

  /**
   * Get the color of this particle
   */
  ParticleColor GetColor();

  // getters
  vec2& GetVelocity();
  vec2& GetPosition();
  double GetRadius();
  double GetMass();

 private:


  /**
  * Calculate new velocity after coliding with other
  */
  vec2 CalculateVelocity(Particle &other);

  // member variables
  vec2 position_;
  vec2 velocity_;
  float radius_;
  float mass_;
  ParticleColor color_;
};

} // namespace idealgas
