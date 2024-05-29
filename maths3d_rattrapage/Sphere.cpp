#include "Sphere.h"
#include <raymath.h>

// Constructeur prenant une position initiale
Sphere::Sphere(Vector3 pos) : position(pos), rotation(QuaternionIdentity()) {}

// Met à jour la position de la sphère en fonction de l'aquarium
void Sphere::Update(const Aquarium& aquarium) {
    position.y = aquarium.GetWaveHeight(position.x, position.z) + 0.5f; // Adjusted to be above the water surface
    rotation = QuaternionFromAxisAngle(Vector3{ 1.0f, 0.0f, 0.0f }, position.y);
}

// Dessine la sphère
void Sphere::Draw() const {
    DrawSphere(position, 0.5f, RED);
}