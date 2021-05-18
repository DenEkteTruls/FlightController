/*
      Author: Robert Brenner Marhtins
      Version: 0.1.00
      Comments:

*/
float flyLat = 61;
float flyLng = 10;
float flyAlt = 0;

float punktLat = 60;
float punktLng = 10;
float punktAlt = 0;

void setup() {


}

void loop() {
  Serial.println(geoVinkel(flyLat, flyLng, punktLat, punktLng, flyAlt, punktAlt));
  delay(1000);

}

float geoVinkel(lat1, long1, lat2, long2, alt1, alt2) {
  float dN = lat2 - lat1;
  float dE = long2 - long1;
  float r = 6371 * 1000;
  float r2 = r * cos(lat1 * PI / 180);
  float dNm = sqrt(2 * (r ^ 2) - 2 * (r ^ 2) * cos(dN * PI / 180));
  float dEm = sqrt(2 * (r2 ^ 2) - 2 * (r2 ^ 2) * cos(dE * PI / 180));
  float dH = alt2 - alt1;
  if (dEm == 0) {
    dEm = 0.000000000001;
  }
  float Vh1 = atan(dNm / dEm) * 180 / PI;

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
  float L = sqrt(dNm ^ 2 + dEm ^ 2);
  float Al = sqrt(L ^ 2 + dH ^ 2);
  float Vv = atan(dH / L) * 180 / pi;

  return Al, Vv, Vh;
}
