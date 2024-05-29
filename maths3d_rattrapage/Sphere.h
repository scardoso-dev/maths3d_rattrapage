#ifndef SPHERE_H
#define SPHERE_H

#include <raylib.h>
#include "Aquarium.h"

class Sphere {
public:
    Sphere(Vector3 position);

    void Update(const Aquarium& aquarium);

    void Draw() const;

private:
    Vector3 position;       // Position de la sphère
    Quaternion rotation;    // Rotation de la sphère
};

#endif