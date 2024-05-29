#version 330

// Définition des entrées du fragment shader
in vec3 fragPosition;    // Position du fragment dans l'espace monde
in vec2 fragTexCoord;    // Coordonnées de texture du fragment
in vec4 fragColor;       // Couleur du fragment

// Déclaration des uniformes (variables globales constantes)
uniform float time;      // Temps écoulé depuis le début de l'application
uniform vec3 lightPosition;   // Position de la source lumineuse

// Déclaration de la sortie du fragment shader
out vec4 finalColor;    // Couleur finale du fragment

// Fonction principale du fragment shader
void main()
{
    // Calcul de l'effet de vague en fonction de la position du fragment et du temps
    float wave = sin(fragPosition.x * 5.0 + time * 2.0) * 0.1 +
                 cos(fragPosition.z * 5.0 + time * 2.0) * 0.1;

    // Calcul de la normale en utilisant l'effet de vague
    vec3 normal = normalize(vec3(-wave, 1.0, -wave));
    // Calcul de la direction de la lumière
    vec3 lightDir = normalize(lightPosition - fragPosition);

    // Calcul de la composante diffuse de la lumière
    float diffuse = max(dot(normal, lightDir), 0.0);
    // Calcul de la couleur diffuse en fonction de la composante diffuse
    vec3 diffuseColor = vec3(0.2, 0.4, 0.8) * diffuse;

    // Attribution de la couleur finale avec une transparence ajustée
    finalColor = vec4(diffuseColor, 0.8); // Ajustement de la transparence 
}