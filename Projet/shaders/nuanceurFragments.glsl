// les étudiants peuvent utiliser l'exemple du cours pour démarrer:
//    http://www.cours.polymtl.ca/inf2705/nuanceurs/pointlight.glsl.html

// Les paramètres de la source de lumière sont définis ainsi:
// struct gl_LightSourceParameters
// {
//    vec4 ambient;
//    vec4 diffuse;
//    vec4 specular;
//    vec4 position;
//    vec4 halfVector;
//    vec3 spotDirection;
//    float spotExponent;
//    float spotCutoff;          // ( [0.0,90.0], 180.0 )
//    float spotCosCutoff;       // == cos(spotCutoff) ( [1.0,0.0], -1.0 )
//    float constantAttenuation;
//    float linearAttenuation;
//    float quadraticAttenuation;
// };
// uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];

//void main(void)
//{
//   gl_FragColor = vec4( 0.5, 0.5, 0.5, 1.0 ); // gris!
//}

varying vec3 normal, lightDir, eyeVec;
uniform sampler2D colorMap;

void main (void)
{
   //vec4 couleur = texture2D( colorMap, gl_TexCoord[0].st);
   vec4 couleur = ( ( gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient ) +
             ( gl_LightSource[1].ambient  *  gl_FrontMaterial.ambient ) );

   // vecteur normal
   vec3 N = normalize( normal );
   // direction de la lumiere
   vec3 L = normalize( lightDir );
   // direction du spot
   vec3 S = normalize( gl_LightSource[1].spotDirection );
   // produit scalaire pour le calcul de la reflexion diffuse
   float NdotL = dot( N, L );
   // produit scalaire pour le calcul du spot
   float LdotS = dot(-L,S);

   // calcul de l'eclairage seulement si le produit scalaire est positif
   if(LdotS > gl_LightSource[1].spotCosCutoff) {
      if ( NdotL > 0.0)
      {
         // calcul de la composante diffuse
         couleur += gl_LightSource[1].diffuse * gl_FrontMaterial.diffuse * NdotL;
   
         // calcul de la composante speculaire
         vec3 E = normalize( eyeVec );
         vec3 R = -reflect( L, N ); // r�flexion de L par rapport a N
         // produit scalaire pour la reflexion speculaire
         float NdotHV = max( dot( R, E ), 0.0 );
         couleur += gl_LightSource[1].specular * gl_FrontMaterial.specular * pow( NdotHV, gl_FrontMaterial.shininess );
         
      }
   }
   gl_FragColor = couleur;
}
