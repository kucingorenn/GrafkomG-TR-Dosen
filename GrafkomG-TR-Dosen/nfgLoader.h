#pragma once
#include <iostream>
#include "struct.h"

int loadnfg(const char* nfgPath) {
	int line, nx, ny, nz, bnx, bny, bnz, tx, ty, tz, jmlVtx = 0, jmlindx;
	float tmp;
	FILE* nfg;
	fopen_s(&nfg, nfgPath, "r");
	if (!nfg) {
		printf("Not NFG file");
		return 0;
	}

	fscanf_s(nfg, "NrVertices:%d", &jmlVtx);
	for (int i = 0; i < jmlVtx; i++) {
		fscanf_s(nfg, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&line, &KordinatV[i].x, &KordinatV[i].y, &KordinatV[i].z, &nx, &ny, &nz, &bnx, &bny, &bnz, &tx, &ty, &tz, &KordinatV[i].u, &KordinatV[i].v
		);
	}

	fscanf_s(nfg, "\nNrIndices:%d", &jmlindx);
	for (int i = 0; i < jmlindx; i++) {
		fscanf_s(nfg, "   %d.    %d,    %d,    %d", &line, &index[i].i1, &index[i].i2, &index[i].i3);
	}
}
