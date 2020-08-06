#pragma once
#pragma once
struct Kordinat
{
	float x, y, z, u, v;
};
struct Indices {
	int i1, i2, i3;
};

Kordinat* KordinatV = new Kordinat[512];
Indices* index = new Indices[718];
