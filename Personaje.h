#pragma once
#include "String.h";
enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguno };
using namespace System::Drawing;

class Personaje
{
private:
	int X, Y;
	int dx, dy;
	char* imagen;//para el nombre del archivo imagen
	int W, H; //dimensiones de la imagen
	int indiceH, indiceW;

public:
	Personaje();
	~Personaje();
	//metodos de acceso SET
	void cambiarX(int valor);
	void cambiarY(int valor);
	void cambiar_dx_dy(Direccion teclapulsada);
	void cambiar_imagen(char* valor);
	//Metodos GET
	int retornarX();
	int retornarY();
	int retornar_dx();
	int retornar_dy();
	int retornarW();
	int retornarH();
	//para la animacion
	void mostrar(Graphics^ canvas);
	void mover(Graphics^ canvas, Direccion teclapulsada);

};
//IMPLEMENTACION
Personaje::Personaje()
{
	X = Y = 0;
	dx = 1; dy = 0;
	indiceH = indiceW = 0;
	imagen = new char[15];
}

void Personaje::cambiar_dx_dy(Direccion teclapulsada)
{
	switch (teclapulsada)
	{
	case Arriba:dx = 0; dy = -4;		break;
	case Abajo:dx = 0; dy = 4;			break;
	case Izquierda:dx = -4; dy = 0;			break;
	case Derecha:dx = 4; dy = 0;			break;
	}
}

void Personaje::cambiar_imagen(char* valor)
{
	//lo que viene en el param valor lo copiamos a imagen
	//copia valor a imagen
	strcpy(imagen, valor);

	//cargar imagen
	Bitmap^ bitmap = gcnew Bitmap(gcnew System::String(imagen));
	//bitmap tiene la imagen cargada

	W = bitmap->Width / 3;
	H = bitmap->Height / 4;

	delete bitmap;
}

void Personaje::mostrar(Graphics^ canvas)
{
	//vuelvo a cargar la imagen completa... el sprite completo

	Bitmap^ bitmap = gcnew Bitmap(gcnew System::String(imagen));


	//se obtiene un recuadro o porcion del sprite
	Rectangle cuadro = Rectangle(indiceW * W, indiceH * H, W, H);
	//X,        Y,       ancho, alto	
//para hacer zoom
	Rectangle zoom = Rectangle(X, Y, W * 3, H * 3);

	//dibujar cuadro en el canvas del formulario
	canvas->DrawImage(bitmap, zoom, cuadro, GraphicsUnit::Pixel);

}


void Personaje::mover(Graphics^ canvas, Direccion teclapulsada)
{
	if (teclapulsada == Direccion::Abajo) indiceH = 0;
	if (teclapulsada == Direccion::Arriba) indiceH = 3;
	if (teclapulsada == Direccion::Derecha) indiceH = 2;
	if (teclapulsada == Direccion::Izquierda) indiceH = 1;

	indiceW++;
	if (indiceW > 2) indiceW = 0;

	X = X + dx;
	Y = Y + dy;

	mostrar(canvas);

}

//Metodos GET y SET

int Personaje::retornarX() { return this->X; }
int Personaje::retornarY() { return this->Y; }
int Personaje::retornar_dx() { return this->dx; }
int Personaje::retornar_dy() { return this->dy; }
int Personaje::retornarW() { return this->W; }
int Personaje::retornarH() { return this->H; }

void Personaje::cambiarX(int valor) { this->X = valor; }
void Personaje::cambiarY(int valor) { this->Y = valor; }


