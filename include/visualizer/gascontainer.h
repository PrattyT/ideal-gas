//
// Created by Pratyush Tulsian on 11/1/20.
//
#pragma once
#include "cinder/gl/gl.h"
#include "histograms.h"
#include <core/particle.h>

namespace idealgas {

const float kMinX = 100.0f;
const float kMaxX = 700.0f;
const float kMinY = 100.0f;
const float kMaxY = 700.0f;
const size_t kParticles = 15;
const float kBuffer = 20;

using std::vector;
using std::map;

/**
 * Represents a gas container.
 */
class GasContainer {

 public:

  /**
   * Create a new Gas container
   */
  GasContainer();

  /**
   * Create a new Gas container with particles
   */
  GasContainer(vector<Particle> &particles);

  /**
   * Displays the current state of the gas container in the Cinder application.
   */
  void Draw();

  /**
   * Update the particles by 1 frame and the particles
   */
  void Update();

  /**
   * Speed up all the particles velocities
   */
  void SpeedUp();

  /**
   * Slow down all the velocities
   */
  void SlowDown();

  /**
   * Set the color of the brush
   */
  void SetColor(ParticleColor color);

  /**
  * Spawns particles of a certain mass
  */
  void SpawnParticles(ParticleColor color, float mass, size_t amount);

  /**
   * Get the particles in this container
   */
  vector<Particle> &GetParticles();

 private:

  /**
   * Vector of all the particles in the simulation
   */
  vector<Particle> particles_;
};

} // namespace idealgas