uniform float facteurZ;
uniform sampler2D displacementMap;

void main( void )
{
   vec4 newVertexPos;
   vec4 dv;
   float df;
   facteurZ=30;
   
   gl_TexCoord[0] = gl_MultiTexCoord0  ;
   
   dv = texture2D( displacementMap, gl_MultiTexCoord0.xy);
   
   df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
   
   newVertexPos = vec4(-gl_Normal * (df/255.0) * facteurZ, 0.0) + gl_Vertex;
   //gl_TexCoord[0] = gl_MultiTexCoord0;
   
   gl_Position = gl_ModelViewProjectionMatrix * newVertexPos;
   //gl_Position = ftransform();
}
