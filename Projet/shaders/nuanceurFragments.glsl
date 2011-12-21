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
