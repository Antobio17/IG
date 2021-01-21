#include "textura.h"
#include "jpg_imagen.hpp"

// *****************************************************************************
//
// Clase Textura
//
// *****************************************************************************

Textura::Textura(std::string archivo){
    jpg::Imagen * pimg = NULL;
    unsigned char * texels;
    
    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();

    texels = pimg->leerPixels();
    for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			texels = pimg->leerPixel(j, height - i - 1);  // Empieza en la esquina superior izquierda
			// R
			data.push_back(*texels);
			texels++;
			// G
			data.push_back(*texels);
			texels++;
			// B
			data.push_back(*texels);
			texels++;
		}
	}

    textura_id = -1;
}

void Textura::activar(){
    // Lo colocaremos en otro lado
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
    //////////////////////////////
    glEnable( GL_TEXTURE_2D );

    // Que hacer cuando los valores s,t superan 1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Utilizar la interpolación linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (textura_id == -1){
		glGenTextures(1, &textura_id);

        glBindTexture(GL_TEXTURE_2D, textura_id);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	}

    glBindTexture(GL_TEXTURE_2D, textura_id);
}