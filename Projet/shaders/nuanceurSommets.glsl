varying vec3 normal, lightDir, eyeVec;

void main()
{
   // calculer la normale qui sera interpolee pour le nuanceur de fragment
   normal = gl_NormalMatrix * gl_Normal;
   //normal = normalize( gl_NormalMatrix * gl_Normal );

   // calculer la position du sommet dans l'espace de la camera ("eye-coordinate position")
   vec3 ecPosition = vec3( gl_ModelViewMatrix * gl_Vertex );

   // vecteur de la direction de la lumiere
   lightDir = vec3( gl_LightSource[1].position.xyz - ecPosition );
   eyeVec = -ecPosition; // vecteur qui pointe vers le (0,0,0), c'est-a-dire vers l'oeil

   // transformation standard du sommet (ModelView et Projection)
   gl_Position = ftransform();
}