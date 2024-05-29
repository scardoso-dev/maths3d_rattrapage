#version 330

// D�finition des entr�es du fragment shader
in vec3 fragPosition;    // Position du fragment dans l'espace monde
in vec2 fragTexCoord;    // Coordonn�es de texture du fragment
in vec4 fragColor;       // Couleur du fragment

// D�claration des uniformes (variables globales constantes)
uniform float time;      // Temps �coul� depuis le d�but de l'application
uniform vec3 lightPosition;   // Position de la source lumineuse

// D�claration de la sortie du fragment shader
out vec4 finalColor;    // Couleur finale du fragment

// Fonction principale du fragment shader
void main()
{
    // Calcul de l'effet de vague en fonction de la position du fragment et du temps
    float wave = sin(fragPosition.x * 5.0 + time * 2.0) * 0.1 +
                 cos(fragPosition.z * 5.0 + time * 2.0) * 0.1;

    // Calcul de la normale en utilisant l'effet de vague
    vec3 normal = normalize(vec3(-wave, 1.0, -wave));
    // Calcul de la direction de la lumi�re
    vec3 lightDir = normalize(lightPosition - fragPosition);

    // Calcul de la composante diffuse de la lumi�re
    float diffuse = max(dot(normal, lightDir), 0.0);
    // Calcul de la couleur diffuse en fonction de la composante diffuse
    vec3 diffuseColor = vec3(0.2, 0.4, 0.8) * diffuse;

    // Attribution de la couleur finale avec une transparence ajust�e
    finalColor = vec4(diffuseColor, 0.8); // Ajustement de la transparence 
}