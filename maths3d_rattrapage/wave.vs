#version 330

// Définition des entrées pour les attributs du sommet
layout(location = 0) in vec3 vertexPosition;   // Position du sommet
layout(location = 1) in vec2 vertexTexCoord;   // Coordonnées de texture du sommet
layout(location = 2) in vec4 vertexColor;      // Couleur du sommet

// Déclaration des uniformes (variables globales constantes)
uniform mat4 mvp;     // Matrice de projection-modèle-vue
uniform float time;   // Temps écoulé depuis le début de l'application

// Déclaration des sorties vers le fragment shader
out vec3 fragPosition;   // Position du fragment dans l'espace monde
out vec2 fragTexCoord;   // Coordonnées de texture du fragment
out vec4 fragColor;      // Couleur du fragment

// Fonction principale du vertex shader
void main()
{
    // Calcul de la position du vertex, avec une oscillation sinusoïdale en fonction du temps
    vec3 position = vertexPosition;
    position.y += sin(position.x * 5.0 + time * 2.0) * 0.1 +
                  cos(position.z * 5.0 + time * 2.0) * 0.1;
                  
    // Transmission des données vers le fragment shader
    fragPosition = position;    // Transmission de la position du vertex
    fragTexCoord = vertexTexCoord;   // Transmission des coordonnées de texture du vertex
    fragColor = vertexColor;    // Transmission de la couleur du vertex
    
    // Calcul de la position finale du vertex dans l'espace projeté
    gl_Position = mvp * vec4(position, 1.0);
}