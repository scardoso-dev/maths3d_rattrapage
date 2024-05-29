#include <raylib.h>
#include "Aquarium.h"
#include "Sphere.h"
#include <vector>

// Nombre de billes dans l'aquarium
const int NUM_SPHERES = 8;

int main() {
    // Initialisation de la fenêtre
    InitWindow(800, 600, "3D Aquarium with Waves and Rotating Spheres");
    SetTargetFPS(60);

    // Configuration de la caméra 3D
    Camera3D camera = { 0 };
    camera.position = { 0.0f, 10.0f, 20.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;

    // Chargement du shader des vagues
    Shader waveShader = LoadShader("wave.vs", "wave.fs");
    int timeLoc = GetShaderLocation(waveShader, "time");
    Vector3 lightPos = { 0.0f, 10.0f, 10.0f };
    SetShaderValue(waveShader, GetShaderLocation(waveShader, "lightPosition"), &lightPos, SHADER_UNIFORM_VEC3);

    // Création de l'aquarium et configuration du shader
    Aquarium aquarium;
    aquarium.SetShader(waveShader);

    // Création d'un vecteur de sphères
    std::vector<Sphere> spheres;
    float aquariumSize = 10.0f;                   // Taille de l'aquarium
    float spacing = aquariumSize / NUM_SPHERES;   // Espacement entre les billes
    for (int i = 0; i < NUM_SPHERES; i++) {
        // Positionnement des billes dans l'aquarium
        float x = -aquariumSize / 2.0f + i * spacing + spacing / 2.0f;

        // Descendre les billes sous la surface de l'eau

        float y = aquarium.GetWaveHeight(x, 0.0f) - 0.5f;
        // Ajout de la sphère au vecteur
        spheres.push_back(Sphere{ Vector3{ x, y, 0.0f } });
    }

    // Boucle principale de rendu
    while (!WindowShouldClose()) {

        float time = GetTime();
        SetShaderValue(waveShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        aquarium.Update();

        // Affichage des instructions pour le joueur
        DrawText("Clique gauche de votre souris pour augmenter la vitesse des vagues", 10, 60, 20, BLACK);
        DrawText("Cliquez droit de votre souris pour diminuer la vitesse des vagues", 10, 90, 20, BLACK);


        // Vérifier les clics de la souris pour ajuster la vitesse des vagues
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            aquarium.IncreaseWaveSpeed();
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            aquarium.DecreaseWaveSpeed();
        }

        // Mise à jour de chaque sphère
        for (auto& sphere : spheres) {
            sphere.Update(aquarium);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // On dessine l'aquarium
        aquarium.Draw();

        // On dessine chaque sphère
        for (auto& sphere : spheres) {
            sphere.Draw();
        }

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // Libération de la mémoire utilisée par le shader
    UnloadShader(waveShader);

    // Fermeture de la fenêtre
    CloseWindow();

    return 0;
}