DROP DATABASE IF EXISTS Campeonato;
CREATE DATABASE Campeonato;

USE Campeonato;

CREATE TABLE Jugador (
    Identificador INTEGER PRIMARY KEY NOT NULL,
    NombreUsuario TEXT NOT NULL,
    Contraseña TEXT NOT NULL
) ENGINE = InnoDB;

CREATE TABLE Partida (
    Identificador INTEGER PRIMARY KEY NOT NULL,
    FechaHoraFinalizacion DATETIME NOT NULL,
    Duracion INTEGER NOT NULL,
    Ganador INTEGER,
    FOREIGN KEY (Ganador) REFERENCES Jugador (Identificador)
) ENGINE = InnoDB;

CREATE TABLE Participacion (
    Jugador INTEGER NOT NULL,
    Partida INTEGER NOT NULL,
    FOREIGN KEY (Jugador) REFERENCES Jugador (Identificador),
    FOREIGN KEY (Partida) REFERENCES Partida (Identificador)
) ENGINE = InnoDB;

INSERT INTO Jugador VALUES(1, 'Juan', 'pass123');
INSERT INTO Jugador VALUES(2, 'Maria', 'pass456');
INSERT INTO Jugador VALUES(3, 'Pedro', 'pass789');
INSERT INTO Jugador VALUES(4, 'Luis', 'pass101');
INSERT INTO Jugador VALUES(5, 'Julia', 'pass202');

INSERT INTO Partida VALUES(1, '2023-09-20 18:00:00', 90, 2);
INSERT INTO Partida VALUES(2, '2023-09-21 19:30:00', 120, 3); 
INSERT INTO Partida VALUES(3, '2023-09-22 20:15:00', 75, 5); 

INSERT INTO Participacion VALUES(1, 1);
INSERT INTO Participacion VALUES(2, 1);
INSERT INTO Participacion VALUES(3, 1);
INSERT INTO Participacion VALUES(4, 2);
INSERT INTO Participacion VALUES(5, 2);
INSERT INTO Participacion VALUES(1, 3);
INSERT INTO Participacion VALUES(3, 3);
INSERT INTO Participacion VALUES(4, 3);
