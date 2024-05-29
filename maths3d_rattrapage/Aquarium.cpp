#include "Aquarium.h"
#include "math.h"

// Constructeur par d�faut de la classe Aquarium
Aquarium::Aquarium() : time(0.0f), shader{ 0 } {
    // Initialisation des hauteurs des vagues � z�ro
    for (int x = 0; x < waveResolution; x++) {
        for (int z = 0; z < waveResolution; z++) {
            waveHeights[x][z] = 0.0f;
        }
    }
}

// M�thode pour d�finir le shader de l'aquarium
void Aquarium::SetShader(Shader sh) {
    shader = sh;
}

// M�thode pour mettre � jour les vagues de l'aquarium en fonction du temps
void Aquarium::Update() {
    time += GetFrameTime(); // Mise � jour du temps �coul�

    // Calcul des hauteurs des vagues pour chaque point de la grille
    for (int x = 0; x < waveResolution; x++) {
        for (int z = 0; z < waveResolution; z++) {
            float fx = (float)x / (float)waveResolution;
            float fz = (float)z / (float)waveResolution;

            // Calcul de la hauteur de la vague � la position actuelle
            waveHeights[x][z] = waveAmplitude * sinf(waveFrequency * (fx * waveResolution + time * waveSpeed)) +
                waveAmplitude * cosf(waveFrequency * (fz * waveResolution + time * waveSpeed));
        }
    }
}

// M�thode pour dessiner l'aquarium avec les vagues
void Aquarium::Draw() const {
    float size = 10.0f; // Taille de l'aquarium
    Vector3 cubePosition = { 0.0f, -2.5f, 0.0f }; // Position du cube repr�sentant l'aquarium
    DrawCubeWires(cubePosition, size, 5.0f, size, LIGHTGRAY); // On dessine le conteneur de l'aquarium

    BeginShaderMode(shader); // D�but d'utilisation du shader d�fini pour l'aquarium
    for (int x = 0; x < waveResolution - 1; x++) {
        for (int z = 0; z < waveResolution - 1; z++) {
            // D�finition des coins des triangles pour chaque cellule de la grille
            Vector3 p1 = { (float)x / waveResolution * size - size / 2, waveHeights[x][z] + cubePosition.y, (float)z / waveResolution * size - size / 2 };
            Vector3 p2 = { (float)(x + 1) / waveResolution * size - size / 2, waveHeights[x + 1][z] + cubePosition.y, (float)z / waveResolution * size - size / 2 };
            Vector3 p3 = { (float)(x + 1) / waveResolution * size - size / 2, waveHeights[x + 1][z + 1] + cubePosition.y, (float)(z + 1) / waveResolution * size - size / 2 };
            Vector3 p4 = { (float)x / waveResolution * size - size / 2, waveHeights[x][z + 1] + cubePosition.y, (float)(z + 1) / waveResolution * size - size / 2 };

            // On dessine les triangles form�s par ces points avec une couleur BLEUE
            DrawTriangle3D(p1, p2, p3, BLUE);
            DrawTriangle3D(p1, p3, p4, BLUE);
        }
    }
    EndShaderMode(); // Fin de l'utilisation du shader
}

// M�thode pour obtenir la hauteur de la vague � une position sp�cifique
float Aquarium::GetWaveHeight(float x, float z) const {
    int ix = (int)((x + 5.0f) / 10.0f * waveResolution);
    int iz = (int)((z + 5.0f) / 10.0f * waveResolution);

    // V�rifie si les indices sont valides
    if (ix < 0 || ix >= waveResolution || iz < 0 || iz >= waveResolution) return 0.0f;

    // Retourne la hauteur de la vague � la position donn�e
    return waveHeights[ix][iz];
}