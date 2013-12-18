#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char> > Matrix;


// Pre: Caracter que corresponde a la fila
// Post: Devuelve la cordenada como un "int"
int coord(char c) {
	int i = c - 'a';
	return i;
}


void read_matrix(Matrix& m) {
	int a = m.size();
	int b = m[0].size();
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			cin >> m[i][j];
		}
	}
}


void write_matrix(Matrix& m) {
	int a = m.size();
	int b = m[0].size();
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			cout << m[i][j];
		}
		cout << endl;
	}
}

// Pre: Matriz i posición en que se ha atacado
// Post: retorna si el barco esta "enfonsat" o no
//       si lo esta substitye por agua.
bool enfonsat(const int i,const int j, Matrix& m) {

	bool enfon = false;
	int flag_left = j; // Marcará el punto de mas a la izquierda
	int flag_right = j; // Marcará el punto de mas a la derecha
	bool check_left = true;
	bool check_right = true;
	
	// Comprovamos la parte izquierda de la nave
	while (check_left) {
		if (m[i][flag_left - 1] == '.') {
			enfon = true;
			check_left = false;
		}
		else if (m[i][flag_left - 1] == 'T') {
			--flag_left;
		}
		else {
			check_left = false;
		}
	}

	// Si por el lado izquierdo esta hundido el check_left tendrá
	// un veredicto "true"
	if (enfon) check_left = true;
	// Volvemos a poner a false "enfon" para comprovar la parte derecha
	enfon = false;

	// Comprovamos la parte derecha de la nave
	while (check_right) {
		if (m[i][flag_right + 1] == '.') {
			enfon = true;
			check_right = false;
		}
		else if (m[i][flag_right  + 1] == 'T') {
			++flag_right;
		}
		else {
			check_right = false;
		}
	}
	if (enfon) check_right = true;
	
	// Volvemos a poner a false "enfon" para comprovar la parte derecha
	enfon = false;
	
	// Comprovamos el estado final de la nave
	if (check_left and check_right) enfon = true;
	// En caso de estar completamente hundido ponemos agua en su lugar
	if (enfon) {
		for (int k = flag_left; k <= flag_right; ++k) {
			m[i][k] = '.';
		}
	}
	// Devolvemos si esta hundido o no
	return enfon;
}


int main() {
	int f, c;
	cin >> f >> c;
	Matrix m(f, vector<char>(c));
	read_matrix(m);
	char i_char; // Coordenada "i" que vendrá expresada en una letra
	int j; // Coordenada "j" que vendrá como un entero (columna)
	while (cin >> i_char >> j) {
		cout << i_char << j;
		int i = coord(i_char); // Convertimos la coordenada a numero
		if (m[i][j] == '.') cout << ": aigua";
		else if (m[i][j] == 'V' or m[i][j] == 'T') {
			m[i][j] = 'T';
			if (enfonsat(i,j,m)) cout << ": enfonsat";
			else cout << ": tocat";
		}
		cout << endl;
	}
	cout << endl;
	write_matrix(m);
}