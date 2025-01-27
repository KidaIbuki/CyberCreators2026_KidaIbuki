xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 48;
 -22.37079;6.94232;-3.30464;,
 -0.04586;0.96037;-3.30464;,
 -0.31237;-0.03429;-4.46155;,
 -22.63730;5.94766;-4.46155;,
 -0.57889;-1.02894;-3.30464;,
 -22.90382;4.95301;-3.30464;,
 -0.04586;0.96037;-3.30464;,
 -0.04586;0.96037;-1.15888;,
 -0.31237;-0.03429;-1.15888;,
 -0.31237;-0.03429;-4.46155;,
 -0.04586;0.96037;0.98688;,
 -0.31237;-0.03429;0.98688;,
 -0.04586;0.96037;3.13265;,
 -0.31237;-0.03429;2.46696;,
 -0.57889;-1.02894;-1.15888;,
 -0.57889;-1.02894;-3.30464;,
 -0.57889;-1.02894;0.98688;,
 -0.57889;-1.02894;3.13265;,
 -0.04586;0.96037;3.13265;,
 -22.37079;6.94232;3.13265;,
 -22.63730;5.94766;2.46696;,
 -0.31237;-0.03429;2.46696;,
 -22.90382;4.95301;3.13265;,
 -0.57889;-1.02894;3.13265;,
 -22.37079;6.94232;3.13265;,
 -22.37079;6.94232;0.98688;,
 -22.63730;5.94766;0.98688;,
 -22.63730;5.94766;2.46696;,
 -22.37079;6.94232;-1.15888;,
 -22.63730;5.94766;-1.15888;,
 -22.37079;6.94232;-3.30464;,
 -22.63730;5.94766;-4.46155;,
 -22.90382;4.95301;0.98688;,
 -22.90382;4.95301;3.13265;,
 -22.90382;4.95301;-1.15888;,
 -22.90382;4.95301;-3.30464;,
 -0.04586;0.96037;0.98688;,
 -22.37079;6.94232;0.98688;,
 -0.04586;0.96037;-1.15888;,
 -22.37079;6.94232;-1.15888;,
 -0.04586;0.96037;-3.30464;,
 -22.37079;6.94232;-3.30464;,
 -22.90382;4.95301;0.98688;,
 -0.57889;-1.02894;0.98688;,
 -22.90382;4.95301;-1.15888;,
 -0.57889;-1.02894;-1.15888;,
 -22.90382;4.95301;-3.30464;,
 -0.57889;-1.02894;-3.30464;;
 
 22;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;10,12,13,11;,
 4;9,8,14,15;,
 4;8,11,16,14;,
 4;11,13,17,16;,
 4;18,19,20,21;,
 4;21,20,22,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;27,26,32,33;,
 4;26,29,34,32;,
 4;29,31,35,34;,
 4;24,12,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 4;42,43,17,33;,
 4;44,45,43,42;,
 4;46,47,45,44;;
 
 MeshMaterialList {
  15;
  22;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  13,
  0,
  0,
  13,
  0;;
  Material {
   0.624000;0.624000;0.624000;1.000000;;
   5.000000;
   0.216000;0.216000;0.216000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.298400;0.019200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.514400;0.800000;0.329600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.661600;0.661600;0.661600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.279200;0.191200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.790400;0.589600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.436000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.269600;0.269600;0.269600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;0.660000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.179200;0.800000;0.132000;0.860000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.539608;0.768627;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.241893;0.902757;-0.355692;,
  0.193329;0.721514;-0.664862;,
  -0.241893;-0.902758;-0.355691;,
  0.965928;-0.258811;-0.000000;,
  0.965928;-0.258811;-0.000000;,
  0.965926;-0.258817;-0.000000;,
  0.965926;-0.258817;-0.000000;,
  0.965925;-0.258823;-0.000000;,
  0.965928;-0.258811;-0.000000;,
  0.965926;-0.258817;-0.000000;,
  0.965925;-0.258823;-0.000000;,
  -0.140512;-0.524399;0.839798;,
  -0.965928;0.258811;0.000000;,
  -0.965928;0.258811;0.000000;,
  -0.965926;0.258818;0.000000;,
  -0.965926;0.258818;0.000000;,
  0.140513;0.524402;0.839797;,
  -0.965924;0.258825;0.000000;,
  -0.193330;-0.721516;-0.664860;,
  -0.965928;0.258811;0.000000;,
  0.258819;0.965926;0.000000;,
  0.258819;0.965926;0.000000;,
  0.258819;0.965926;0.000000;,
  -0.258819;-0.965926;0.000000;,
  -0.258819;-0.965926;0.000000;;
  22;
  4;0,0,1,1;,
  4;18,18,2,2;,
  4;4,3,5,6;,
  4;3,4,6,5;,
  4;4,8,9,6;,
  4;6,5,7,10;,
  4;5,6,7,7;,
  4;6,9,10,7;,
  4;11,11,11,11;,
  4;16,16,16,16;,
  4;19,12,14,14;,
  4;12,13,15,14;,
  4;13,13,15,15;,
  4;14,14,17,17;,
  4;14,15,17,17;,
  4;15,15,17,17;,
  4;20,20,21,21;,
  4;21,21,22,22;,
  4;22,22,0,0;,
  4;23,23,23,23;,
  4;24,24,23,23;,
  4;2,2,24,24;;
 }
 MeshTextureCoords {
  48;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
