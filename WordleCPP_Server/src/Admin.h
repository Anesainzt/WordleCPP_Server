#ifndef ADMIN_H_
#define ADMIN_H_

class Admin{
private:
	char* nombre;
	char* contrasena;
	int numAdmin;

public:
	Admin(); //Constructor por defecto
	Admin(const char*, int); //Cnstructor espec�fico
	Admin(const Admin&); //Constructor copia
	~Admin(); //Destructor
	char* getNombre() const;
	void setNombre(const char*);
	char getContrasena() const;
	void setContrasena(char);
	int getNumAdmin();
	void setNumAdmin(int);
	void toString();
	void cargarAdministradores();
};



#endif /* ADMIN_H_ */
