import numpy as np
import math

flyLat = 61
flyLng = 10
flyAlt = 0

punktLat = 60
punktLng = 10
punktAlt = 0

def geoVinkel(lat1, long1, lat2, long2, alt1, alt2):
    dN = lat2-lat1
    dE = long2-long1
    r = 6371*1000
    r2 = r*math.cos(lat1*math.pi/180)
    dNm = math.sqrt(2*(r**2)-2*(r**2)*math.cos(dN*math.pi/180))
    dEm = math.sqrt(2*(r2**2)-2*(r2**2)*math.cos(dE*math.pi/180))
    dH = alt2 - alt1

    if dEm == 0:
        dEm = 0.000000000001
    Vh1 = math.atan(dNm/dEm)*180/math.pi

    if (dN >= 0):
        if (dE >= 0):
            Vh = 90 - Vh1
        else:
            Vh = 270+Vh1

    if (dN < 0):
        if (dE >= 0):
            Vh = 90+Vh1
        else:
            Vh = 270-Vh1

    L = math.sqrt(dNm**2+dEm**2)
    Al = math.sqrt(L**2+dH**2)
    Vv = math.atan(dH/L)*180/math.pi

    return Al, Vv, Vh


avstand, VertikalVinkel, HorisontalVinkel = geoVinkel(flyLat, flyLng, punktLat, punktLng, flyAlt, punktAlt)
print("Horisontal vinkel:\t{}\nVertikal vinkel:\t{}\nAvstand:\t{}".format(HorisontalVinkel, VertikalVinkel, avstand))
