# from Data.table import  Table
import csv


class DataBase:
    def __init__(self):

        self.equipos = {}
        self.tiempos = {}

        with open("datafiles/equipos.csv") as file:
            equipos = csv.DictReader(file)
            for row in equipos:
                self.equipos[row["id"]] = dict(nombre=row["nombre"], equipo=row["equipo"], id_equipo=row["id_equipo"])

        with open("datafiles/tiempos.csv") as file:
            tiempos = csv.DictReader(file)
            for row in tiempos:
                self.tiempos[row["id_equipo"]] = dict(nombre=row["nombre"], i1=row["i1"], i2=row["i2"],
                                                      i3=row["i3"], final=row["final"])

    def get_tiempo_by_member(self, rut):
        try:
            return self.tiempos[self.equipos[rut]["id_equipo"]]
        except KeyError:
            return None

    def get_tiempo_by_equipo(self, id_equipo):
        try:
            return self.tiempos[id_equipo]
        except KeyError:
            return None
