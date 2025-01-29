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
 33;
 -3.36076;-0.12828;-2.19187;,
 -3.36076;4.37805;0.03573;,
 -1.43160;-0.12828;1.14953;,
 -3.36076;4.37805;0.03573;,
 -5.28992;-0.12828;1.14953;,
 -3.36076;4.37805;0.03573;,
 -3.36076;-0.12828;-2.19187;,
 -3.36076;-0.12828;0.03573;,
 -3.36076;-0.12828;-2.19187;,
 -1.43160;-0.12828;1.14953;,
 -5.28992;-0.12828;1.14953;,
 -0.14644;-0.12828;-0.81076;,
 -0.14644;6.53992;1.41684;,
 1.78272;-0.12828;2.53064;,
 -0.14644;6.53992;1.41684;,
 -2.07560;-0.12828;2.53064;,
 -0.14644;6.53992;1.41684;,
 -0.14644;-0.12828;-0.81076;,
 -0.14644;-0.12828;1.41684;,
 -0.14644;-0.12828;-0.81076;,
 1.78272;-0.12828;2.53064;,
 -2.07560;-0.12828;2.53064;,
 2.90355;-0.12828;-2.26564;,
 2.90355;3.43588;-0.03804;,
 4.83271;-0.12828;1.07576;,
 2.90355;3.43588;-0.03804;,
 0.97439;-0.12828;1.07576;,
 2.90355;3.43588;-0.03804;,
 2.90355;-0.12828;-2.26564;,
 2.90355;-0.12828;-0.03804;,
 2.90355;-0.12828;-2.26564;,
 4.83271;-0.12828;1.07576;,
 0.97439;-0.12828;1.07576;;
 
 18;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;7,8,9;,
 3;7,9,10;,
 3;7,10,8;,
 3;11,12,13;,
 3;13,14,15;,
 3;15,16,17;,
 3;18,19,20;,
 3;18,20,21;,
 3;18,21,19;,
 3;22,23,24;,
 3;24,25,26;,
 3;26,27,28;,
 3;29,30,31;,
 3;29,31,32;,
 3;29,32,30;;
 
 MeshMaterialList {
  1;
  18;
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
  0;;
  Material {
   0.436078;0.605490;0.250980;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.840726;0.239943;-0.485393;,
  -0.000000;0.239943;0.970787;,
  0.000000;-1.000000;-0.000000;,
  0.854192;0.164749;-0.493168;,
  -0.000000;0.164749;0.986335;,
  0.826604;0.298275;-0.477240;,
  -0.000000;0.298275;0.954480;,
  -0.840726;0.239943;-0.485394;,
  -0.854191;0.164749;-0.493168;,
  -0.826604;0.298275;-0.477240;;
  18;
  3;0,0,0;,
  3;1,1,1;,
  3;7,7,7;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,3,3;,
  3;4,4,4;,
  3;8,8,8;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;5,5,5;,
  3;6,6,6;,
  3;9,9,9;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;;
 }
 MeshTextureCoords {
  33;
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
