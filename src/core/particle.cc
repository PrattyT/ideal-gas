//
// Created by Pratyush Tulsian on 11/1/20.
//

#include <core/particle.h>
#include <visualizer/gascontainer.h>
#include <glm/ext/quaternion_geometric.hpp>

namespace idealgas {
using std::pow;

Particle::Particle(const vec2 &velocity, const vec2 &position, float radius, float mass, ParticleColor color) {
  velocity_ = velocity;
  position_ = position;
  radius_ = radius;
  mass_ = mass;
  color_ = color;
}

void Particle::UpdatePosition() {
  position_ += velocity_;

  // CHECKS BOUNDS
  if (position_.x >= kMaxX) position_.x = kMaxX;
  if (position_.x <= kMinX) position_.x = kMinX;
  if (position_.y >= kMaxY) position_.y = kMaxY;
  if (position_.y <= kMinY) position_.y = kMinY;

}

bool Particle::IsColliding(Particle &other) {
  double dist = glm::distance(position_, other.position_);
  return dist < radius_ + other.radius_ && MovingTowards(other);
}

void Particle::Collide(Particle &other) {
  vec2 new_v1 = CalculateVelocity(other);
  vec2 new_v2 = other.CalculateVelocity(*this);
  other.velocity_ = new_v2;
  velocity_ = new_v1;
}

vec2 &Particle::GetPosition() {
  return position_;
}

vec2 &Particle::GetVelocity() {
  return velocity_;
}

vec2 Particle::CalculateVelocity(Particle &other) {
  vec2 dv = velocity_ - other.velocity_;
  vec2 dx = position_ - other.position_;
  double length_squared = pow(glm::length(position_ - other.position_), 2);
  double mass_coefficient = 2 * other.mass_ / (mass_ + other.mass_);
  double coefficient = mass_coefficient * (glm::dot(dv, dx) / length_squared);
  dx *= coefficient;
  return velocity_ - dx;
}

void Particle::HittingWall() {
  if (position_.x <= (kMinX + radius_) || position_.x >= (kMaxX - radius_)) {
    velocity_.x *= -1;
  }
  if (position_.y <= (kMinY + radius_) || position_.y >= kMaxY - radius_) {
    velocity_.y *= -1;
  }
}

double Particle::GetRadius() {
  return radius_;
}

bool Particle::MovingTowards(Particle &other) {
  vec2 dv = velocity_ - other.velocity_;
  vec2 dx = position_ - other.position_;
  return glm::dot(dv, dx) < 0;
}

double Particle::GetMass() {
  return mass_;
}

void Particle::SlowDown() {
  velocity_ *= kDecrement;
}

void Particle::SpeedUp() {
  if(glm::length(velocity_) > kMaxSpeed) return;
  velocity_ *= kIncrement;
}

ParticleColor Particle::GetColor() {
  return color_;
}

} // namespace idealgas