uniform sampler2D colorMap;

void main( void )
{  
   vec4 color_map = texture2D( colorMap, gl_TexCoord[0].st);
   gl_FragColor = color_map;
   //gl_FragColor = vec4( 0.0, 0.0, 0.0, 1.0 );
}
