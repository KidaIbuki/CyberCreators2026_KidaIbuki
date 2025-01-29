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
 270;
 -6.11940;20.53497;-3.90500;,
 -19.21280;11.03613;-3.90500;,
 -19.21280;11.03613;3.90500;,
 -6.11940;20.53497;3.90500;,
 0.00000;0.14497;-3.90500;,
 0.00000;0.14497;3.90500;,
 14.41791;6.11707;-3.90500;,
 14.41791;6.11707;3.90500;,
 20.39000;20.53497;-3.90500;,
 20.39000;20.53497;3.90500;,
 14.41790;34.95288;-3.90500;,
 14.41790;34.95288;3.90500;,
 0.00000;40.92497;-3.90500;,
 0.00000;40.92497;3.90500;,
 -21.27246;29.28291;-3.90500;,
 -21.27246;29.28291;3.90500;,
 -6.11940;20.53497;-3.90500;,
 -6.11940;20.53497;3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;-3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 0.00000;20.53497;3.90500;,
 -10.14327;35.42853;-2.98000;,
 -16.68034;47.46831;0.00000;,
 -8.29144;36.43399;-2.10718;,
 -16.68034;47.46831;0.00000;,
 -7.52439;36.85046;0.00000;,
 -16.68034;47.46831;0.00000;,
 -8.29144;36.43399;2.10718;,
 -16.68034;47.46831;0.00000;,
 -10.14327;35.42853;2.98000;,
 -16.68034;47.46831;0.00000;,
 -11.99509;34.42307;2.10718;,
 -16.68034;47.46831;0.00000;,
 -12.76214;34.00659;-0.00000;,
 -16.68034;47.46831;0.00000;,
 -11.99509;34.42307;-2.10718;,
 -16.68034;47.46831;0.00000;,
 -10.14327;35.42853;-2.98000;,
 -10.14327;35.42853;0.00000;,
 -10.14327;35.42853;-2.98000;,
 -8.29144;36.43399;-2.10718;,
 -7.52439;36.85046;0.00000;,
 -8.29144;36.43399;2.10718;,
 -10.14327;35.42853;2.98000;,
 -11.99509;34.42307;2.10718;,
 -12.76214;34.00659;-0.00000;,
 -11.99509;34.42307;-2.10718;,
 -24.92765;17.09591;-2.98500;,
 -5.44025;21.59493;-2.98500;,
 -5.21079;20.60107;-2.98500;,
 -27.38317;15.48217;-2.98500;,
 -4.98135;19.60721;-2.98500;,
 -24.46875;15.10819;-2.98500;,
 -5.44025;21.59493;-2.98500;,
 -5.44025;21.59493;2.98500;,
 -5.21079;20.60107;2.98500;,
 -5.21079;20.60107;-2.98500;,
 -4.98135;19.60721;2.98500;,
 -4.98135;19.60721;-2.98500;,
 -5.44025;21.59493;2.98500;,
 -24.92765;17.09591;2.98500;,
 -27.38317;15.48217;2.98500;,
 -5.21079;20.60107;2.98500;,
 -24.46875;15.10819;2.98500;,
 -4.98135;19.60721;2.98500;,
 -24.92765;17.09591;2.98500;,
 -24.92765;17.09591;-2.98500;,
 -27.38317;15.48217;-2.98500;,
 -27.38317;15.48217;2.98500;,
 -24.46875;15.10819;-2.98500;,
 -24.46875;15.10819;2.98500;,
 -5.44025;21.59493;-2.98500;,
 -24.92765;17.09591;-2.98500;,
 -24.46875;15.10819;-2.98500;,
 -4.98135;19.60721;-2.98500;,
 -7.93302;25.29234;-4.74955;,
 -5.38744;26.34676;-4.74955;,
 -5.38744;26.34676;4.94357;,
 -7.93302;25.29234;4.94357;,
 -4.33302;28.89234;-4.74955;,
 -4.33302;28.89234;4.94357;,
 -2.31985;32.68636;-4.74955;,
 -2.31985;32.68636;4.94357;,
 -7.93302;31.22954;-4.74955;,
 -7.93302;31.22954;4.94357;,
 -10.29216;29.84399;-4.74955;,
 -10.29216;29.84399;4.94357;,
 -11.53302;28.89234;-4.74955;,
 -11.53302;28.89234;4.94357;,
 -10.47861;26.34676;-4.74955;,
 -10.47861;26.34676;4.94357;,
 -7.93302;25.29234;-4.74955;,
 -7.93302;25.29234;4.94357;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;-4.74955;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 -7.93302;28.89234;4.94357;,
 0.12424;22.22894;-5.47372;,
 2.88065;19.22085;-5.47372;,
 -11.86490;5.70904;-5.47372;,
 -14.62132;8.71714;-5.47372;,
 2.88065;19.22085;-5.47372;,
 2.88065;19.22085;-4.02372;,
 -11.86490;5.70904;-4.02372;,
 -11.86490;5.70904;-5.47372;,
 2.88065;19.22085;-4.02372;,
 0.12424;22.22894;-4.02372;,
 -14.62132;8.71714;-4.02372;,
 -11.86490;5.70904;-4.02372;,
 0.12424;22.22894;-4.02372;,
 0.12424;22.22894;-5.47372;,
 -14.62132;8.71714;-5.47372;,
 -14.62132;8.71714;-4.02372;,
 2.88065;19.22085;-5.47372;,
 0.12424;22.22894;-5.47372;,
 -14.62132;8.71714;-5.47372;,
 -11.86490;5.70904;-5.47372;,
 -11.63874;11.60087;-5.47372;,
 -14.64683;8.84446;-5.47372;,
 -22.40260;17.30840;-5.47372;,
 -19.39451;20.06480;-5.47372;,
 -14.64683;8.84446;-5.47372;,
 -14.64683;8.84446;-4.02372;,
 -22.40260;17.30840;-4.02372;,
 -22.40260;17.30840;-5.47372;,
 -14.64683;8.84446;-4.02372;,
 -11.63874;11.60087;-4.02372;,
 -19.39451;20.06480;-4.02372;,
 -22.40260;17.30840;-4.02372;,
 -11.63874;11.60087;-4.02372;,
 -11.63874;11.60087;-5.47372;,
 -19.39451;20.06480;-5.47372;,
 -19.39451;20.06480;-4.02372;,
 -14.64683;8.84446;-5.47372;,
 -11.63874;11.60087;-5.47372;,
 -19.39451;20.06480;-5.47372;,
 -22.40260;17.30840;-5.47372;,
 -20.33253;23.85665;-4.16372;,
 -19.25142;20.88631;-4.16372;,
 -19.25142;20.88631;-5.33372;,
 -20.33253;23.85665;-5.33372;,
 -20.58729;18.02150;-4.16372;,
 -20.58729;18.02150;-5.33372;,
 -23.55763;16.94039;-4.16372;,
 -23.55763;16.94039;-5.33372;,
 -26.42243;18.27627;-4.16372;,
 -26.42243;18.27627;-5.33372;,
 -27.50355;21.24661;-4.16372;,
 -27.50355;21.24661;-5.33372;,
 -26.16767;24.11141;-4.16372;,
 -26.16767;24.11141;-5.33372;,
 -23.19734;25.19253;-4.16372;,
 -23.19734;25.19253;-5.33372;,
 -20.33253;23.85665;-4.16372;,
 -20.33253;23.85665;-5.33372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-4.16372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -23.37750;21.06646;-5.33372;,
 -1.80729;18.78909;3.64055;,
 -0.99386;22.78720;3.64055;,
 18.60464;18.79985;3.64055;,
 17.79122;14.80174;3.64055;,
 -0.99386;22.78720;3.64055;,
 -0.99386;22.78720;5.09055;,
 18.60464;18.79985;5.09055;,
 18.60464;18.79985;3.64055;,
 -0.99386;22.78720;5.09055;,
 -1.80729;18.78909;5.09055;,
 17.79122;14.80174;5.09055;,
 18.60464;18.79985;5.09055;,
 -1.80729;18.78909;5.09055;,
 -1.80729;18.78909;3.64055;,
 17.79122;14.80174;3.64055;,
 17.79122;14.80174;5.09055;,
 -0.99386;22.78720;3.64055;,
 -1.80729;18.78909;3.64055;,
 17.79122;14.80174;3.64055;,
 18.60464;18.79985;3.64055;,
 13.70512;15.51969;3.64055;,
 17.70322;14.70626;3.64055;,
 15.41446;3.45673;3.64055;,
 11.41637;4.27015;3.64055;,
 17.70322;14.70626;3.64055;,
 17.70322;14.70626;5.09055;,
 15.41446;3.45673;5.09055;,
 15.41446;3.45673;3.64055;,
 17.70322;14.70626;5.09055;,
 13.70512;15.51969;5.09055;,
 11.41637;4.27015;5.09055;,
 15.41446;3.45673;5.09055;,
 13.70512;15.51969;5.09055;,
 13.70512;15.51969;3.64055;,
 11.41637;4.27015;3.64055;,
 11.41637;4.27015;5.09055;,
 17.70322;14.70626;3.64055;,
 13.70512;15.51969;3.64055;,
 11.41637;4.27015;3.64055;,
 15.41446;3.45673;3.64055;,
 8.90006;1.28248;4.95055;,
 10.66765;3.90304;4.95055;,
 10.66765;3.90304;3.78055;,
 8.90006;1.28248;3.78055;,
 13.77054;4.50619;4.95055;,
 13.77054;4.50619;3.78055;,
 16.39110;2.73860;4.95055;,
 16.39110;2.73860;3.78055;,
 16.99425;-0.36429;4.95055;,
 16.99425;-0.36429;3.78055;,
 15.22666;-2.98484;4.95055;,
 15.22666;-2.98484;3.78055;,
 12.12376;-3.58800;4.95055;,
 12.12376;-3.58800;3.78055;,
 9.50321;-1.82040;4.95055;,
 9.50321;-1.82040;3.78055;,
 8.90006;1.28248;4.95055;,
 8.90006;1.28248;3.78055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;4.95055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;,
 12.94717;0.45909;3.78055;;
 
 146;
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
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;42,43,44;,
 3;44,45,46;,
 3;46,47,48;,
 3;48,49,50;,
 3;51,52,53;,
 3;51,53,54;,
 3;51,54,55;,
 3;51,55,56;,
 3;51,56,57;,
 3;51,57,58;,
 3;51,58,59;,
 3;51,59,52;,
 4;60,61,62,63;,
 4;63,62,64,65;,
 4;66,67,68,69;,
 4;69,68,70,71;,
 4;72,73,74,75;,
 4;75,74,76,77;,
 4;78,79,80,81;,
 4;81,80,82,83;,
 4;78,67,84,85;,
 4;86,87,70,83;,
 4;88,89,90,91;,
 4;89,92,93,90;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 3;106,89,88;,
 3;107,92,89;,
 3;108,94,92;,
 3;109,96,94;,
 3;110,98,96;,
 3;111,100,98;,
 3;112,102,100;,
 3;113,104,102;,
 3;114,91,90;,
 3;115,90,93;,
 3;116,93,95;,
 3;117,95,97;,
 3;118,97,99;,
 3;119,99,101;,
 3;120,101,103;,
 3;121,103,105;,
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
 4;163,166,167,164;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 4;172,174,175,173;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 3;180,163,162;,
 3;181,166,163;,
 3;182,168,166;,
 3;183,170,168;,
 3;184,172,170;,
 3;185,174,172;,
 3;186,176,174;,
 3;187,178,176;,
 3;188,165,164;,
 3;189,164,167;,
 3;190,167,169;,
 3;191,169,171;,
 3;192,171,173;,
 3;193,173,175;,
 3;194,175,177;,
 3;195,177,179;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;208,201,212,213;,
 4;214,215,202,211;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;228,221,232,233;,
 4;234,235,222,231;,
 4;236,237,238,239;,
 4;237,240,241,238;,
 4;240,242,243,241;,
 4;242,244,245,243;,
 4;244,246,247,245;,
 4;246,248,249,247;,
 4;248,250,251,249;,
 4;250,252,253,251;,
 3;254,237,236;,
 3;255,240,237;,
 3;256,242,240;,
 3;257,244,242;,
 3;258,246,244;,
 3;259,248,246;,
 3;260,250,248;,
 3;261,252,250;,
 3;262,239,238;,
 3;263,238,241;,
 3;264,241,243;,
 3;265,243,245;,
 3;266,245,247;,
 3;267,247,249;,
 3;268,249,251;,
 3;269,251,253;;
 
 MeshMaterialList {
  5;
  146;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.389020;0.690196;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.260000;0.464000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.567843;0.567843;0.567843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.740392;0.505098;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  85;
  0.000000;0.000000;-1.000000;,
  -0.587216;0.809431;0.000000;,
  -0.061463;-0.998109;0.000000;,
  0.707107;-0.707107;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  -0.054002;0.998541;0.000000;,
  -0.480088;0.877220;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.101420;0.186791;-0.977151;,
  0.505799;0.516484;-0.690950;,
  0.757317;0.653047;0.000000;,
  0.505799;0.516484;0.690950;,
  -0.101420;0.186791;0.977151;,
  -0.708638;-0.142902;0.690950;,
  -0.960156;-0.279465;0.000000;,
  -0.708638;-0.142902;-0.690950;,
  0.477160;-0.878817;0.000000;,
  -0.493146;-0.869946;0.000000;,
  -0.499971;-0.866042;0.000000;,
  0.477160;-0.878817;-0.000000;,
  0.477161;-0.878816;-0.000001;,
  0.477160;-0.878816;0.000000;,
  0.477161;-0.878816;0.000001;,
  0.477159;-0.878817;0.000001;,
  0.477160;-0.878817;0.000000;,
  0.477159;-0.878817;-0.000001;,
  0.000000;0.000000;-1.000000;,
  0.974368;0.224960;0.000000;,
  0.974370;0.224950;0.000000;,
  0.974372;0.224941;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.393240;0.919436;0.000000;,
  -0.549205;0.835688;0.000000;,
  -0.127277;-0.991867;0.000000;,
  0.049614;-0.998768;-0.000000;,
  -0.224951;0.974370;0.000000;,
  0.224951;-0.974370;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000001;-1.000000;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.904636;-0.426184;-0.000000;,
  0.883347;-0.468719;-0.000000;,
  -0.382486;0.923961;0.000000;,
  -0.558555;0.829468;0.000000;,
  -0.608562;0.793506;0.000000;,
  -0.707107;-0.707106;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.251213;0.967932;0.000000;,
  -0.923880;-0.382682;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.675590;-0.737277;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.737278;-0.675590;0.000000;,
  0.737277;0.675590;0.000000;,
  0.999048;-0.043618;-0.000000;,
  0.675592;-0.737276;-0.000000;,
  -0.043620;-0.999048;0.000000;,
  -0.737278;-0.675590;0.000000;,
  -0.999048;0.043618;0.000000;,
  -0.675591;0.737276;0.000000;,
  0.043617;0.999048;0.000000;,
  -0.675590;0.737277;0.000000;,
  0.737277;0.675591;0.000000;,
  -0.737276;-0.675591;0.000000;,
  0.737277;0.675590;0.000000;,
  0.675590;-0.737278;-0.000000;,
  -0.675589;0.737278;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.199368;0.979925;0.000000;,
  0.000000;0.000000;1.000000;,
  0.979924;-0.199369;-0.000000;,
  -0.979925;0.199366;0.000000;,
  -0.551938;0.833885;0.000000;,
  0.833885;0.551938;0.000000;,
  0.979925;-0.199368;-0.000000;,
  0.551938;-0.833885;-0.000000;,
  -0.199367;-0.979925;0.000000;,
  -0.833886;-0.551937;0.000000;,
  -0.199368;-0.979925;0.000000;,
  -0.979925;0.199368;0.000000;,
  0.979925;-0.199366;-0.000000;,
  -0.979925;0.199368;0.000000;,
  0.199369;0.979924;0.000000;,
  -0.199368;-0.979925;0.000000;;
  146;
  4;1,1,1,1;,
  4;18,2,2,18;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;19,19,19,19;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,10,10;,
  3;10,10,11;,
  3;11,12,12;,
  3;12,12,13;,
  3;13,14,14;,
  3;14,14,15;,
  3;15,16,16;,
  3;16,16,9;,
  3;17,20,21;,
  3;17,21,22;,
  3;17,22,23;,
  3;17,23,20;,
  3;17,20,24;,
  3;17,24,25;,
  3;17,25,26;,
  3;17,26,20;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,29,29;,
  4;29,29,30,30;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;32,32,33,33;,
  4;34,34,35,35;,
  4;32,36,36,32;,
  4;35,37,37,35;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;48,43,43,48;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;49,46,46,49;,
  4;46,39,39,46;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;50,50,50,50;,
  4;53,53,53,53;,
  4;52,52,52,52;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,54,54,61;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;68,68,68,68;,
  4;71,71,71,71;,
  4;70,70,70,70;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;72,73,73,72;,
  4;73,69,69,73;,
  4;69,74,74,69;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,72,72,78;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;70,70,70;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;;
 }
 MeshTextureCoords {
  270;
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
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.937500;1.000000;;
 }
}
