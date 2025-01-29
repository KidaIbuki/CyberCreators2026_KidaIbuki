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
 262;
 0.00000;1.02697;-9.41996;,
 6.66092;1.02697;-6.66092;,
 6.66092;-0.03627;-6.66092;,
 0.00000;-0.03627;-9.41996;,
 9.41996;1.02697;0.00000;,
 9.41996;-0.03627;0.00000;,
 6.66092;1.02697;6.66092;,
 6.66092;-0.03627;6.66092;,
 0.00000;1.02697;9.41996;,
 -0.00000;-0.03627;9.41996;,
 -6.66092;1.02697;6.66092;,
 -6.66092;-0.03627;6.66092;,
 -9.41996;1.02697;0.00000;,
 -9.41996;-0.03627;0.00000;,
 -6.66092;1.02697;-6.66092;,
 -6.66092;-0.03627;-6.66092;,
 0.00000;1.02697;-9.41996;,
 0.00000;-0.03627;-9.41996;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;-0.03627;-0.00000;,
 0.00000;1.71715;-6.23023;,
 4.40544;1.71715;-4.40544;,
 4.40544;1.02697;-4.40544;,
 0.00000;1.02697;-6.23023;,
 6.23023;1.71715;0.00000;,
 6.23023;1.02697;0.00000;,
 4.40544;1.71715;4.40544;,
 4.40544;1.02697;4.40544;,
 0.00000;1.71715;6.23023;,
 0.00000;1.02697;6.23023;,
 -4.40544;1.71715;4.40544;,
 -4.40544;1.02697;4.40544;,
 -6.23023;1.71715;0.00000;,
 -6.23023;1.02697;0.00000;,
 -4.40544;1.71715;-4.40544;,
 -4.40544;1.02697;-4.40544;,
 0.00000;1.71715;-6.23023;,
 0.00000;1.02697;-6.23023;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.71715;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;1.02697;0.00000;,
 0.00000;21.98032;-0.95132;,
 0.67269;21.98032;-0.67269;,
 0.67269;1.77870;-0.67269;,
 0.00000;1.77870;-0.95132;,
 0.95132;21.98032;0.00000;,
 0.95132;1.77870;0.00000;,
 0.67269;21.98032;0.67269;,
 0.67269;1.77870;0.67269;,
 0.00000;21.98032;0.95132;,
 0.00000;1.77870;0.95132;,
 -0.67269;21.98032;0.67269;,
 -0.67269;1.77870;0.67269;,
 -0.95132;21.98032;0.00000;,
 -0.95132;1.77870;0.00000;,
 -0.67269;21.98032;-0.67269;,
 -0.67269;1.77870;-0.67269;,
 0.00000;21.98032;-0.95132;,
 0.00000;1.77870;-0.95132;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;23.17508;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.00000;1.77870;0.00000;,
 0.89106;20.25468;-0.88604;,
 1.40542;20.34537;-0.88604;,
 2.59094;13.62195;-0.88604;,
 2.07658;13.53125;-0.88604;,
 1.40542;20.34537;-0.88604;,
 1.40542;20.34537;0.88604;,
 2.59094;13.62195;0.88604;,
 2.59094;13.62195;-0.88604;,
 1.40542;20.34537;0.88604;,
 0.89106;20.25468;0.88604;,
 2.07658;13.53125;0.88604;,
 2.59094;13.62195;0.88604;,
 0.89106;20.25468;0.88604;,
 0.89106;20.25468;-0.88604;,
 2.07658;13.53125;-0.88604;,
 2.07658;13.53125;0.88604;,
 1.40542;20.34537;-0.88604;,
 0.89106;20.25468;-0.88604;,
 2.07658;13.53125;-0.88604;,
 2.59094;13.62195;-0.88604;,
 -1.32744;20.34537;-0.88604;,
 -0.81308;20.25468;-0.88604;,
 -1.99860;13.53125;-0.88604;,
 -2.51296;13.62195;-0.88604;,
 -0.81308;20.25468;-0.88604;,
 -0.81308;20.25468;0.88604;,
 -1.99860;13.53125;0.88604;,
 -1.99860;13.53125;-0.88604;,
 -0.81308;20.25468;0.88604;,
 -1.32744;20.34537;0.88604;,
 -2.51296;13.62195;0.88604;,
 -1.99860;13.53125;0.88604;,
 -1.32744;20.34537;0.88604;,
 -1.32744;20.34537;-0.88604;,
 -2.51296;13.62195;-0.88604;,
 -2.51296;13.62195;0.88604;,
 -0.81308;20.25468;-0.88604;,
 -1.32744;20.34537;-0.88604;,
 -2.51296;13.62195;-0.88604;,
 -1.99860;13.53125;-0.88604;,
 -1.47392;12.58856;-0.88604;,
 -0.96303;12.47997;-0.88604;,
 -2.38247;5.80202;-0.88604;,
 -2.89336;5.91061;-0.88604;,
 -0.96303;12.47997;-0.88604;,
 -0.96303;12.47997;0.88604;,
 -2.38247;5.80202;0.88604;,
 -2.38247;5.80202;-0.88604;,
 -0.96303;12.47997;0.88604;,
 -1.47392;12.58856;0.88604;,
 -2.89336;5.91061;0.88604;,
 -2.38247;5.80202;0.88604;,
 -1.47392;12.58856;0.88604;,
 -1.47392;12.58856;-0.88604;,
 -2.89336;5.91061;-0.88604;,
 -2.89336;5.91061;0.88604;,
 -0.96303;12.47997;-0.88604;,
 -1.47392;12.58856;-0.88604;,
 -2.89336;5.91061;-0.88604;,
 -2.38247;5.80202;-0.88604;,
 0.93712;12.48827;-0.88604;,
 1.44893;12.59240;-0.88604;,
 2.81004;5.90231;-0.88604;,
 2.29823;5.79818;-0.88604;,
 1.44893;12.59240;-0.88604;,
 1.44893;12.59240;0.88604;,
 2.81004;5.90231;0.88604;,
 2.81004;5.90231;-0.88604;,
 1.44893;12.59240;0.88604;,
 0.93712;12.48827;0.88604;,
 2.29823;5.79818;0.88604;,
 2.81004;5.90231;0.88604;,
 0.93712;12.48827;0.88604;,
 0.93712;12.48827;-0.88604;,
 2.29823;5.79818;-0.88604;,
 2.29823;5.79818;0.88604;,
 1.44893;12.59240;-0.88604;,
 0.93712;12.48827;-0.88604;,
 2.29823;5.79818;-0.88604;,
 2.81004;5.90231;-0.88604;,
 -0.91155;20.31629;-0.96506;,
 -0.91155;20.40699;-1.47942;,
 -0.91155;13.68357;-2.66494;,
 -0.91155;13.59287;-2.15058;,
 -0.91155;20.40699;-1.47942;,
 0.86052;20.40699;-1.47942;,
 0.86052;13.68357;-2.66494;,
 -0.91155;13.68357;-2.66494;,
 0.86052;20.40699;-1.47942;,
 0.86052;20.31629;-0.96506;,
 0.86052;13.59287;-2.15058;,
 0.86052;13.68357;-2.66494;,
 0.86052;20.31629;-0.96506;,
 -0.91155;20.31629;-0.96506;,
 -0.91155;13.59287;-2.15058;,
 0.86052;13.59287;-2.15058;,
 -0.91155;20.40699;-1.47942;,
 -0.91155;20.31629;-0.96506;,
 -0.91155;13.59287;-2.15058;,
 -0.91155;13.68357;-2.66494;,
 -0.91215;20.40694;1.42913;,
 -0.91215;20.31624;0.91477;,
 -0.91215;13.59281;2.10029;,
 -0.91215;13.68351;2.61465;,
 -0.91215;20.31624;0.91477;,
 0.85992;20.31624;0.91477;,
 0.85992;13.59281;2.10029;,
 -0.91215;13.59281;2.10029;,
 0.85992;20.31624;0.91477;,
 0.85992;20.40694;1.42913;,
 0.85992;13.68351;2.61465;,
 0.85992;13.59281;2.10029;,
 0.85992;20.40694;1.42913;,
 -0.91215;20.40694;1.42913;,
 -0.91215;13.68351;2.61465;,
 0.85992;13.68351;2.61465;,
 -0.91215;20.31624;0.91477;,
 -0.91215;20.40694;1.42913;,
 -0.91215;13.68351;2.61465;,
 -0.91215;13.59281;2.10029;,
 -0.91215;12.56861;1.34042;,
 -0.91215;12.43343;0.83592;,
 -0.91215;5.83892;2.60291;,
 -0.91215;5.97410;3.10741;,
 -0.91215;12.43343;0.83592;,
 0.85992;12.43343;0.83592;,
 0.85992;5.83892;2.60291;,
 -0.91215;5.83892;2.60291;,
 0.85992;12.43343;0.83592;,
 0.85992;12.56861;1.34042;,
 0.85992;5.97410;3.10741;,
 0.85992;5.83892;2.60291;,
 0.85992;12.56861;1.34042;,
 -0.91215;12.56861;1.34042;,
 -0.91215;5.97410;3.10741;,
 0.85992;5.97410;3.10741;,
 -0.91215;12.43343;0.83592;,
 -0.91215;12.56861;1.34042;,
 -0.91215;5.97410;3.10741;,
 -0.91215;5.83892;2.60291;,
 0.85992;12.56861;-1.37930;,
 0.85992;12.43343;-0.87480;,
 0.85992;5.83892;-2.64179;,
 0.85992;5.97410;-3.14629;,
 0.85992;12.43343;-0.87480;,
 -0.91215;12.43343;-0.87480;,
 -0.91215;5.83892;-2.64179;,
 0.85992;5.83892;-2.64179;,
 -0.91215;12.43343;-0.87480;,
 -0.91215;12.56861;-1.37930;,
 -0.91215;5.97410;-3.14629;,
 -0.91215;5.83892;-2.64179;,
 -0.91215;12.56861;-1.37930;,
 0.85992;12.56861;-1.37930;,
 0.85992;5.97410;-3.14629;,
 -0.91215;5.97410;-3.14629;,
 0.85992;12.43343;-0.87480;,
 0.85992;12.56861;-1.37930;,
 0.85992;5.97410;-3.14629;,
 0.85992;5.83892;-2.64179;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 3;86,69,68;,
 3;87,72,69;,
 3;88,74,72;,
 3;89,76,74;,
 3;90,78,76;,
 3;91,80,78;,
 3;92,82,80;,
 3;93,84,82;,
 3;94,71,70;,
 3;95,70,73;,
 3;96,73,75;,
 3;97,75,77;,
 3;98,77,79;,
 3;99,79,81;,
 3;100,81,83;,
 3;101,83,85;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;114,107,118,119;,
 4;120,121,108,117;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;134,127,138,139;,
 4;140,141,128,137;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;154,147,158,159;,
 4;160,161,148,157;,
 4;162,163,164,165;,
 4;166,167,168,169;,
 4;170,171,172,173;,
 4;174,175,176,177;,
 4;174,167,178,179;,
 4;180,181,168,177;,
 4;182,183,184,185;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;194,195,196,197;,
 4;194,187,198,199;,
 4;200,201,188,197;,
 4;202,203,204,205;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;214,215,216,217;,
 4;214,207,218,219;,
 4;220,221,208,217;,
 4;222,223,224,225;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;234,235,236,237;,
 4;234,227,238,239;,
 4;240,241,228,237;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,256,257;,
 4;254,247,258,259;,
 4;260,261,248,257;;
 
 MeshMaterialList {
  3;
  120;
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
  0,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.028000;0.028000;0.028000;1.000000;;
   5.000000;
   0.420000;0.420000;0.420000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.540000;0.540000;0.540000;1.000000;;
   5.000000;
   0.264000;0.264000;0.264000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.190000;0.190000;0.190000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  59;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.681901;0.674707;-0.282454;,
  0.000000;0.334745;-0.942309;,
  0.666312;0.334747;-0.666312;,
  0.942309;0.334745;0.000000;,
  0.666312;0.334747;0.666312;,
  0.000000;0.334745;0.942309;,
  -0.666312;0.334747;0.666312;,
  -0.942309;0.334745;0.000000;,
  -0.666312;0.334747;-0.666312;,
  0.984808;0.173648;0.000000;,
  0.984808;-0.173648;-0.000000;,
  0.978148;-0.207911;-0.000000;,
  0.979925;0.199367;0.000000;,
  0.000000;0.173648;-0.984808;,
  0.000000;-0.173648;-0.984808;,
  0.000000;-0.258819;-0.965926;,
  -0.282454;0.674708;0.681901;,
  -0.553168;0.622905;-0.553168;,
  -0.984808;-0.173648;0.000000;,
  -0.173639;0.984809;0.000000;,
  0.173656;-0.984806;-0.000000;,
  -0.984808;0.173648;0.000000;,
  0.173639;0.984809;0.000000;,
  -0.173656;-0.984806;0.000000;,
  -0.978148;0.207911;0.000000;,
  0.207906;0.978149;0.000000;,
  -0.207906;-0.978149;0.000000;,
  -0.979925;-0.199367;0.000000;,
  -0.199371;0.979924;0.000000;,
  0.199370;-0.979924;-0.000000;,
  0.000000;-0.173648;0.984808;,
  0.000000;0.984806;0.173656;,
  0.000000;-0.984806;-0.173656;,
  0.000000;0.173648;0.984808;,
  0.000000;0.984806;-0.173656;,
  0.000000;-0.984806;0.173656;,
  0.000000;0.258819;0.965926;,
  0.000000;0.965926;-0.258818;,
  0.000000;-0.965926;0.258819;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.258819;0.965926;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.258819;-0.965926;,
  0.000000;0.965926;0.258818;,
  0.000000;-0.965926;-0.258819;;
  120;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,2,2,10;,
  4;2,11,11,2;,
  4;11,4,4,11;,
  4;4,12,12,4;,
  4;12,6,6,12;,
  4;6,13,13,6;,
  4;13,8,8,13;,
  4;8,10,10,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;15,16,2,10;,
  4;16,17,11,2;,
  4;17,18,4,11;,
  4;18,19,12,4;,
  4;19,20,6,12;,
  4;20,21,13,6;,
  4;21,22,8,13;,
  4;22,15,10,8;,
  3;14,16,15;,
  3;14,17,16;,
  3;14,18,17;,
  3;30,19,18;,
  3;30,20,19;,
  3;30,21,20;,
  3;31,22,21;,
  3;31,15,22;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,10,10,10;,
  4;23,23,23,23;,
  4;12,12,12,12;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;10,10,10,10;,
  4;24,24,24,24;,
  4;12,12,12,12;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;10,10,10,10;,
  4;25,25,25,25;,
  4;12,12,12,12;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;10,10,10,10;,
  4;26,26,26,26;,
  4;12,12,12,12;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;13,13,13,13;,
  4;27,27,27,27;,
  4;11,11,11,11;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;13,13,13,13;,
  4;28,28,28,28;,
  4;11,11,11,11;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;13,13,13,13;,
  4;29,29,29,29;,
  4;11,11,11,11;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;;
 }
 MeshTextureCoords {
  262;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
