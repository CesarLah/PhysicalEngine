
#include <iostream>
#include <math.h>
using namespace std;


class Vector{
public:
	float _x, _y, _m;
	//float _xnorm, _ynorm; // Componentes del vector normalizado.

	void iniciar(float x, float y);
	float modulo();
	void normalizar();
	void mostrar();
	Vector resta(Vector &v);
	void multiplicacion(float t);
};


class EntidadFisica{
private:  // Campor privado. Miembros dato de la clase. Por definicion los miembros dato de una clase son privados, pero al declararlo se enfatiza su uso privado.
	char _nombre[10];
	float _vel; //Velocidad.
	float _rad; // radio de colision.
	Vector _dir;
	Vector _pos;
public:// Campo publico. Miembros funcion de la clase. Son de caracter publico y accedemos a los miembros dato de la clase a partir de los miembros funcion.

	void nombre();
	void iniciar(float vel, float rad, Vector pos, Vector dir);
	void mostrar();
	Vector mover(float t, EntidadFisica &objeto);
	void colisionaCon(EntidadFisica &objeto1, EntidadFisica &objeto2);
	friend Vector resta(Vector &_pos);
	friend void iniciar(float x, float y);
	friend float modulo();
	friend void multiplicar(float t);
};


class MotorColision{
public:
	bool insertarEntidadFisica(EntidadFisica &objeto1, Vector &pos1, Vector &dir1, float vel1, float rad1, EntidadFisica &objeto2, Vector &pos2, Vector &dir2, float vel2, float rad2, float x, float y);
	Vector mover(float t, EntidadFisica &objeto1, EntidadFisica &objeto2);
	void mostrar(EntidadFisica &objeto);
	bool colisionan(EntidadFisica &objeto1, EntidadFisica &objeto2);
	friend Vector mover(float t, EntidadFisica &objeto);
	friend void EntidadFisica ::mostrar();
	friend void colisionaCon(EntidadFisica &objeto1, EntidadFisica &objeto2);
	friend Vector resta(Vector &_pos);
	friend void iniciar(float x, float y);
	friend float modulo();
	friend void multiplicar(float t);
};


int main() {
	Vector pos1, pos2, dir1, dir2; // Instancias de la clase vector. Posicion y direccion del Objetivo y el misil.
	MotorColision motor; //Instancia de la clase MotorColision.
	EntidadFisica objeto1, objeto2; //Declaramos el objeto. Una instancia de la clase EntidadFisica.
	float vel1, vel2, rad1, rad2, t, x, y;


	int i = 100;
	int j;
	while(i != 0)
	{	cout << "\n\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
		cout << "\MOTOR DE COLISIONES" << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ";
		cout << "\n1.Parametros iniciales";
		cout << "\n2.Mover entidades";
		cout << "\n3.Informacion de entidad";
		cout << "\n4.Comprobar colisiones";
		cout << "\n0.Salir";
		cout << "\nPulsa una opcion: "; cin >> i;
		switch(i)
		{
			case 1:
				motor.insertarEntidadFisica(objeto1, pos1, dir1, vel1, rad1, objeto2, pos2, dir2, vel2, rad2, x, y);
				break;
			case 2:
				cout << "\n\nIntroduce el numero de segundos que quieres que pasen: "; cin >> t;
				motor.mover(t, objeto1, objeto2);
				cout <<"Movimiento completado";
				break;
			case 3:
				cout << "\nSeleccione la entidad a visualizar:";
				cout << "\n0.Misil" << "\n1.Objetivo"; cout << "\nPulsa una opcion: "; cin >> j;
				if(j == 0)
				{
					cout << "\nEntidad: 0";
					motor.mostrar(objeto2);
				}
				else
				{
					cout << "\nEntidad: 1";
					motor.mostrar(objeto1);
				}
				break;
			case 4:
				cout << "\nSeleccione la primera entidad:";
				cout << "\n0.Misil" << "\n1.Objetivo"; cout << "\nPulsa una opcion: "; cin >> j; cout << "\nEntidad: " << j;
				cout << "\nSeleccione la segunda entidad:";
				cout << "\n0.Misil" << "\n1.Objetivo"; cout << "\nPulsa una opcion: "; cin >> j; cout << "\nEntidad: " << j;
				motor.colisionan(objeto1, objeto2);
				break;
			default:
				i = 0;
		}
	}


	return 0;
}





/////////////////////////////////////////////////////// FUNCIONES DE LA CLASE ENTIDADFISICA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntidadFisica ::nombre()
{
	cin >> _nombre;

}

void EntidadFisica ::iniciar(float vel, float rad, Vector pos, Vector dir)
{
	_vel = vel;
	_rad = rad;
	_pos = pos;
	_dir = dir;

}

void EntidadFisica ::mostrar()
{
	cout << "\nNombre: " << _nombre;
	cout << "\nPosicion:" << "(" << _pos._x << "," << _pos._y << ")";
	cout << "\nDireccion: " << "(" << _dir._x << "," << _dir._y << ")";
	cout << "\nVelocidad: " << _vel;
	cout << "\nRadio de colision: " << _rad;

}

Vector EntidadFisica ::mover(float t, EntidadFisica &objeto)
{
	objeto._dir.multiplicacion(t);
	_pos._x = _pos._x + _vel *  _dir._x;
	_pos._y = _pos._y + _vel *  _dir._y;
	return _pos;
}


void EntidadFisica ::colisionaCon(EntidadFisica &objeto1, EntidadFisica &objeto2)
{
	if(objeto1._pos.resta(objeto2._pos).modulo() <= objeto1._rad + objeto2._rad){cout << "\n\nHay colision.";}
	else{cout << "\n\nNo hay colision.";}


}




////////////////////////////////////////////////////////FUNCIONES DE LA CLASE VECTOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Vector ::iniciar(float x, float y)
{
	_x = x;
	_y = y;
}

float Vector ::modulo()
{
	_m = sqrt(_x * _x + _y * _y);
	return _m;
}

void Vector ::normalizar()
{
	_x = _x / _m;
	_y = _y / _m;

}

void Vector ::mostrar()
{
	cout << "\nCoordenas del vector: " << "(" << _x << "," << _y << ")";
	cout << "\nModulo del vector: " << modulo();
	normalizar();
	cout << "\nVector normalizado: " << "(" << _x << "," << _y << ")" << "\tModulo: " << sqrt(_x  * _x  + _y  * _y);
}


Vector Vector ::resta(Vector &v)
{
	Vector vResta;
	vResta.iniciar(_x - v._x, _y - v._y);
	return vResta;
}

void Vector ::multiplicacion(float t)
{
	_x = t * _x;
	_y = t * _y;
}





////////////////////////////////////////////////////////////  FUNCIONES DE LA CLASE MOTORCOLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MotorColision ::insertarEntidadFisica(EntidadFisica &objeto1, Vector &pos1, Vector &dir1, float vel1, float rad1, EntidadFisica &objeto2, Vector &pos2, Vector &dir2, float vel2, float rad2, float x, float y)
{
	cout << "\n\nCondiciones iniciales:";

	cout << "\nTeclea el nombre del objeto(Objetivo):";
	objeto1.nombre();
	cout << "\nPosicion inicial: ";
	cout << "\nIntroduce la coordenada x de la posicion: "; cin >> x;
	cout << "\nIntroduce la coordenada y de la posicion: "; cin >> y;
	pos1.iniciar(x, y);
	cout << "\nDireccion:";
	cout << "\nIntroduce la coordenada x de la direccion: "; cin >> x;
	cout << "\nIntroduce la coordenada y de la direccion: "; cin >> y;
	dir1.iniciar(x, y);
	dir1.modulo();
	dir1.normalizar();
	cout << "\nIntroduce la velocidad(m/s): "; cin >> vel1;
	cout << "\nIntroduce el radio(metros) de colision: "; cin >> rad1;
	objeto1.iniciar(vel1, rad1, pos1, dir1);

	cout << "\nTeclea el nombre del otro objeto(Misil):";
	objeto2.nombre();
	cout << "\nPosicion inicial: ";
	cout << "\nIntroduce la coordenada x de la posicion: "; cin >> x;
	cout << "\nIntroduce la coordenada y de la posicion: "; cin >> y;
	pos2.iniciar(x, y);
	cout << "\nDireccion:";
	cout << "\nIntroduce la coordenada x de la direccion: "; cin >> x;
	cout << "\nIntroduce la coordenada y de la direccion: "; cin >> y;
	dir2.iniciar(x, y);
	dir2.modulo();
	dir2.normalizar();
	cout <<"\nIntroduce la velocidad(m/s) del misil: "; cin >> vel2;
	cout << "\nIntroduce el radio(metros) de colision: "; cin >> rad2;
	objeto2.iniciar(vel2, rad2, pos2, dir2);
}


Vector MotorColision ::mover(float t, EntidadFisica &objeto1, EntidadFisica &objeto2)
{
	objeto1.mover(t, objeto1);
	objeto2.mover(t, objeto2);
}


void MotorColision ::mostrar(EntidadFisica &objeto)
{
	objeto.mostrar();
}





bool MotorColision ::colisionan(EntidadFisica &objeto1, EntidadFisica &objeto2)
{
	objeto1.colisionaCon(objeto1, objeto2);
}

