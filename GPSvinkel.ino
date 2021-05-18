/*
      Author: Robert Brenner Marhtins
      Version: 0.2.00
      Comments:
      Virker til at alt skal fungere etter som stikkprøver v/ sammenlikning til python ga tilnærmet like resultater
*/
float flyLat = 61;
float flyLng = 10;
float flyAlt = 0;

float punktLat = 60;
float punktLng = 11;
float punktAlt = 100;

void setup() {
Serial.begin(9600);

}

void loop() {
  geoVinkel(flyLat, flyLng, punktLat, punktLng, flyAlt, punktAlt);
  delay(1000);

}

void geoVinkel(float lat1, float long1, float lat2, float long2, float alt1, float alt2) {
  float dN = lat2 - lat1;
  float dE = long2 - long1;
  unsigned long r = 6371000;
  float r2 = r * cos(lat1 * PI / 180);
  float dNm = sqrt(2 * (pow(r,2)) - 2 * (pow(r,2)) * cos(dN * PI / 180));
  float dEm = sqrt(2 * (pow(r2,2)) - 2 * (pow(r2,2)) * cos(dE * PI / 180));
  float dH = alt2 - alt1;
  if (dEm == 0) {
    dEm = 0.000000000001;
  }
  float Vh1 = atan(dNm / dEm) * 180 / PI;
  float Vh = 0;

  if (dN >= 0) {
    if (dE >= 0) {
      Vh = 90 - Vh1;
    }
    else {
      Vh = 270 + Vh1;
    }
  }
  if (dN < 0) {
    if (dE >= 0) {
      Vh = 90 + Vh1;
    }
    else {
      Vh = 270 - Vh1;
    }
  }
  float L = sqrt(pow(dNm,2) + pow(dEm,2));
  float Al = sqrt(pow(L,2) + pow(dH,2));
  float Vv = atan(dH / L) * 180 / PI;

 // return Al, Vv, Vh;
 Serial.println(Al); // Avstand
 Serial.println(Vv); // Vinkel vertikal
 Serial.println(Vh); // Vinkel horisontal
 Serial.println("\n");
}
