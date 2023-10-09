#pragma once
#include "Personaje.h"
namespace benito {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			objPersonaje = new Personaje();
			teclapulsada = Direccion::Ninguno;
			objPersonaje->cambiarX(370);
			objPersonaje->cambiarY(150);
			objPersonaje->cambiar_imagen("images/gato.png");//el primero es el file y el segundo el nombre del archivo
			//debes de poner que tipo de imagen es> gnp, jpn, etc

		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		Graphics^ canvas;
		Personaje* objPersonaje;
		Direccion teclapulsada;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(914, 504);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

		teclapulsada = Direccion::Ninguno;
		if (e->KeyCode == Keys::Up) teclapulsada = Direccion::Arriba;
		if (e->KeyCode == Keys::Down) teclapulsada = Direccion::Abajo;
		if (e->KeyCode == Keys::Right) teclapulsada = Direccion::Derecha;
		if (e->KeyCode == Keys::Left) teclapulsada = Direccion::Izquierda;


	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		//canvas del formulario		
		canvas = this->CreateGraphics();
		//se reserva un espacio para el buffer
		BufferedGraphicsContext^ espacio_buffer = BufferedGraphicsManager::Current;

		//crea un canvas dentro del espacio del buffer, utilizando el canvas del formulario
		BufferedGraphics^ buffer = espacio_buffer->Allocate(canvas, this->ClientRectangle);

		//A partir de aqui todos los dibujos se hacen en el canvas del buffer: BufferedGraphics^ buffer 
		buffer->Graphics->Clear(Color::White);

		//animacion
		objPersonaje->cambiar_dx_dy(teclapulsada);
		objPersonaje->mover(buffer->Graphics, teclapulsada);

		//LIMITES

		if (objPersonaje->retornarX() + objPersonaje->retornarW() + objPersonaje->retornar_dx() > canvas->VisibleClipBounds.Width)
			teclapulsada = Direccion::Izquierda;

		if (objPersonaje->retornarX() + objPersonaje->retornar_dx() < 1)
			teclapulsada = Direccion::Derecha;
		//-------

		buffer->Render(canvas);//dibuja en el canvas del formulario

		delete buffer;
		delete espacio_buffer;
		delete canvas;

	}
	};
}
