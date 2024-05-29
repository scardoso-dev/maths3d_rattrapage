#version 330

// D�finition des entr�es pour les attributs du sommet
layout(location = 0) in vec3 vertexPosition;   // Position du sommet
layout(location = 1) in vec2 vertexTexCoord;   // Coordonn�es de texture du sommet
layout(location = 2) in vec4 vertexColor;      // Couleur du sommet

// D�claration des uniformes (variables globales constantes)
uniform mat4 mvp;     // Matrice de projection-mod�le-vue
uniform float time;   // Temps �coul� depuis le d�but de l'application

// D�claration des sorties vers le fragment shader
out vec3 fragPosition;   // Position du fragment dans l'espace monde
out vec2 fragTexCoord;   // Coordonn�es de texture du fragment
out vec4 fragColor;      // Couleur du fragment

// Fonction principale du vertex shader
void main()
{
    // Calcul de la position du vertex, avec une oscillation sinuso�dale en fonction du temps
    vec3 position = vertexPosition;
    position.y += sin(position.x * 5.0 + time * 2.0) * 0.1 +
                  cos(position.z * 5.0 + time * 2.0) * 0.1;
                  
    // Transmission des donn�es vers le fragment shader
    fragPosition = position;    // Transmission de la position du vertex
    fragTexCoord = vertexTexCoord;   // Transmission des coordonn�es de texture du vertex
    fragColor = vertexColor;    // Transmission de la couleur du vertex
    
    // Calcul de la position finale du vertex dans l'espace projet�
    gl_Position = mvp * vec4(position, 1.0);
}