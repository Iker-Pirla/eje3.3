#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	// Inicializar la conexiￃﾳn al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error creando la conexiￃﾳn: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	// Inicializar la conexiￃﾳn
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "Campeonato", 0, NULL, 0);
	
	if (conn == NULL) {
		printf("Error inicializando la conexiￃﾳn: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//IMPORTANTE: He variado la consulta realizada un poco ya que esta no tenia nada que ver con la base de datos creada.
	// He realizado la siguiente consulta: He sumado la duraci￳n de todos los minutos jugados por una persona (pedida por consola).
	
	char player_name[20];
	// Solicitar el nombre del jugador
	printf("Dame el nombre de un jugador\n");
	scanf("%19s", player_name);  // Limitar la entrada para evitar desbordamiento de buffer
	
	char query[256];  // Aumentar el tamaￃﾱo para acomodar consultas mￃﾡs largas
	// Construir la consulta SQL
	strcpy(query, "SELECT SUM(Partida.Duracion) FROM Jugador, Partida, Participacion WHERE Jugador.NombreUsuario = '");
	strcat(query, player_name);
	strcat(query, "' AND Jugador.Identificador = Participacion.Jugador AND Participacion.Partida = Partida.Identificador");
	
	// Ejecutar la consulta
	err = mysql_query(conn, query);
	if (err != 0) {
		printf("Error al consultar la base de datos: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);  // Siempre cerrar la conexiￃﾳn en caso de error
		exit(1);
	}
	
	// Almacenar el resultado de la consulta
	result = mysql_store_result(conn);
	if (result == NULL) {  // Comprobar si hubo error
		printf("Error almacenando el resultado: %u %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}
	
	// Obtener y mostrar el resultado
	row = mysql_fetch_row(result);
	if (row == NULL) {
		printf("El jugador '%s' no ha jugado ninguna partida o no existe.\n", player_name);
	} else {
		// Imprimir la suma total de minutos jugados por el jugador
		printf("El jugador '%s' ha jugado un total de %s minutos.\n", player_name, row[0]);
	}
	
	// Liberar recursos
	mysql_free_result(result);  
	mysql_close(conn);          
	exit(0);
}
