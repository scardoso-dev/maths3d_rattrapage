#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <raylib.h>

class Aquarium {
public:
    // Constructeur par d�faut de la classe Aquarium
    Aquarium();

    // M�thode pour d�finir le shader utilis� pour dessiner l'aquarium
    void SetShader(Shader shader);

    // M�thode pour mettre � jour l'�tat de l'aquarium
    void Update();

    // M�thode pour dessiner l'aquarium
    void Draw() const;

    // M�thode pour obtenir la hauteur de la vague � une position donn�e
    float GetWaveHeight(float x, float z) const;

    // M�thode pour augmenter la vitesse des vagues
    void IncreaseWaveSpeed() { waveSpeed += 0.1f; }

    // M�thode pour diminuer la vitesse des vagues
    void DecreaseWaveSpeed() { waveSpeed -= 0.1f; }

private:
    float time;                                          // Temps �coul� depuis le d�but de l'application
    static const int waveResolution = 300;               // R�solution des vagues
    float waveHeights[waveResolution][waveResolution];   // Tableau 2D de hauteurs de vagues
    float waveSpeed = 2.0f;                              // Vitesse des vagues
    float waveAmplitude = 0.6f;                          // Amplitude des vagues
    float waveFrequency = 0.4f;                          // Fr�quence des vagues
    Shader shader;                                       // Shader utilis� pour dessiner l'aquarium
};

#endif