# from Data.table import  Table
import csv


class DataBase:
    def __init__(self, folder):

        self._equipos = {}
        self._tiempos = {}

        with open(folder + "/equipos.csv") as file:
            equipos = csv.DictReader(file)
            for row in equipos:
                self._equipos[row["id"]] = dict(nombre=row["nombre"], equipo=row["equipo"], id_equipo=row["id_equipo"])

        with open(folder + "/tiempos.csv") as file:
            tiempos = csv.DictReader(file)
            for row in tiempos:
                self._tiempos[row["id_equipo"]] = dict(nombre=row["nombre"], i1=row["i1"], i2=row["i2"],
                                                      i3=row["i3"], final=row["final"])

        self.mostrar()

    def get_tiempo_by_member(self, rut):
        try:
            tiempo = self._tiempos[self._equipos[rut]["id_equipo"]]
            err = None
        except KeyError:
            tiempo, err = "", None
        return tiempo, err


    def get_tiempo_by_equipo(self, id_equipo):
        try:
            return self._tiempos[id_equipo]
        except KeyError:
            return None

    def mostrar(self):
        print("-----------------BASE de Datos---------------------")
        print("___________________________________________________")
        for i, v in self._equipos.items():
            print(i,":", v)
        print("___________________________________________________")
        for i, v in self._tiempos.items():
            print(i,":",v)
        print("-----------------_____________---------------------")
