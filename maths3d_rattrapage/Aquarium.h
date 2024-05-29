#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <raylib.h>

class Aquarium {
public:
    // Constructeur par défaut de la classe Aquarium
    Aquarium();

    // Méthode pour définir le shader utilisé pour dessiner l'aquarium
    void SetShader(Shader shader);

    // Méthode pour mettre à jour l'état de l'aquarium
    void Update();

    // Méthode pour dessiner l'aquarium
    void Draw() const;

    // Méthode pour obtenir la hauteur de la vague à une position donnée
    float GetWaveHeight(float x, float z) const;

    // Méthode pour augmenter la vitesse des vagues
    void IncreaseWaveSpeed() { waveSpeed += 0.1f; }

    // Méthode pour diminuer la vitesse des vagues
    void DecreaseWaveSpeed() { waveSpeed -= 0.1f; }

private:
    float time;                                          // Temps écoulé depuis le début de l'application
    static const int waveResolution = 300;               // Résolution des vagues
    float waveHeights[waveResolution][waveResolution];   // Tableau 2D de hauteurs de vagues
    float waveSpeed = 2.0f;                              // Vitesse des vagues
    float waveAmplitude = 0.6f;                          // Amplitude des vagues
    float waveFrequency = 0.4f;                          // Fréquence des vagues
    Shader shader;                                       // Shader utilisé pour dessiner l'aquarium
};

#endif