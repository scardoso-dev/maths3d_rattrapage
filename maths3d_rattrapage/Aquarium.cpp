#include "Aquarium.h"
#include "math.h"

// Constructeur par défaut de la classe Aquarium
Aquarium::Aquarium() : time(0.0f), shader{ 0 } {
    // Initialisation des hauteurs des vagues à zéro
    for (int x = 0; x < waveResolution; x++) {
        for (int z = 0; z < waveResolution; z++) {
            waveHeights[x][z] = 0.0f;
        }
    }
}

// Méthode pour définir le shader de l'aquarium
void Aquarium::SetShader(Shader sh) {
    shader = sh;
}

// Méthode pour mettre à jour les vagues de l'aquarium en fonction du temps
void Aquarium::Update() {
    time += GetFrameTime(); // Mise à jour du temps écoulé

    // Calcul des hauteurs des vagues pour chaque point de la grille
    for (int x = 0; x < waveResolution; x++) {
        for (int z = 0; z < waveResolution; z++) {
            float fx = (float)x / (float)waveResolution;
            float fz = (float)z / (float)waveResolution;

            // Calcul de la hauteur de la vague à la position actuelle
            waveHeights[x][z] = waveAmplitude * sinf(waveFrequency * (fx * waveResolution + time * waveSpeed)) +
                waveAmplitude * cosf(waveFrequency * (fz * waveResolution + time * waveSpeed));
        }
    }
}

// Méthode pour dessiner l'aquarium avec les vagues
void Aquarium::Draw() const {
    float size = 10.0f; // Taille de l'aquarium
    Vector3 cubePosition = { 0.0f, -2.5f, 0.0f }; // Position du cube représentant l'aquarium
    DrawCubeWires(cubePosition, size, 5.0f, size, LIGHTGRAY); // On dessine le conteneur de l'aquarium

    BeginShaderMode(shader); // Début d'utilisation du shader défini pour l'aquarium
    for (int x = 0; x < waveResolution - 1; x++) {
        for (int z = 0; z < waveResolution - 1; z++) {
            // Définition des coins des triangles pour chaque cellule de la grille
            Vector3 p1 = { (float)x / waveResolution * size - size / 2, waveHeights[x][z] + cubePosition.y, (float)z / waveResolution * size - size / 2 };
            Vector3 p2 = { (float)(x + 1) / waveResolution * size - size / 2, waveHeights[x + 1][z] + cubePosition.y, (float)z / waveResolution * size - size / 2 };
            Vector3 p3 = { (float)(x + 1) / waveResolution * size - size / 2, waveHeights[x + 1][z + 1] + cubePosition.y, (float)(z + 1) / waveResolution * size - size / 2 };
            Vector3 p4 = { (float)x / waveResolution * size - size / 2, waveHeights[x][z + 1] + cubePosition.y, (float)(z + 1) / waveResolution * size - size / 2 };

            // On dessine les triangles formés par ces points avec une couleur BLEUE
            DrawTriangle3D(p1, p2, p3, BLUE);
            DrawTriangle3D(p1, p3, p4, BLUE);
        }
    }
    EndShaderMode(); // Fin de l'utilisation du shader
}

// Méthode pour obtenir la hauteur de la vague à une position spécifique
float Aquarium::GetWaveHeight(float x, float z) const {
    int ix = (int)((x + 5.0f) / 10.0f * waveResolution);
    int iz = (int)((z + 5.0f) / 10.0f * waveResolution);

    // Vérifie si les indices sont valides
    if (ix < 0 || ix >= waveResolution || iz < 0 || iz >= waveResolution) return 0.0f;

    // Retourne la hauteur de la vague à la position donnée
    return waveHeights[ix][iz];
}