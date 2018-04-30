void setup() {
  setup_print();
  delay(5000);
  setup_co2();
}

void loop() {
  delay(20000);
  uint co2 = get_co2();
  print_ppm(co2);
}
