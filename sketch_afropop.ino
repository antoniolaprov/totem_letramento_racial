#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

int confirmar = 1;
int up = 2;
int down = 3;
int right = 4;
int left = 5;
int estado = 1;
int ponto = 0;
bool flag = false;
int aux = 0;
String botao;

String escritores[] = {"FRANTZ FANON; LELIA GONZALEZ; ACHILLE MBEMBE; CIDA BENTO; SUELI CARNEIRO; UPILE CHISALA; NNEDI OKORAFOR"};
String musicos[] = {"CASSIANO; LUEDJI LUNA; LARISSA LUZ; LINIKER; DONA IVONE LARA; LUIZ MELODIA"};
String diretores[] = {"SABRINA FIDALGO; ADÉLIA SAMPAIO; MARLON RIGGS; MAYA ANGELOU; NIA DA COSTA"};
int menuIndex = 0; 

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(confirmar, INPUT_PULLUP);
    pinMode(up, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);
    pinMode(left, INPUT_PULLUP);
}


void lerBotoes() {
    botao = "vazio";

    if (digitalRead(right) == LOW) {
        botao = "Direita";
    } else if (digitalRead(up) == LOW) {
        botao = "Cima";
    } else if (digitalRead(down) == LOW) {
        botao = "Baixo";
    } else if (digitalRead(left) == LOW) {
        botao = "Esquerda";
    } else if (digitalRead(confirmar) == LOW) {
        botao = "Select";
    }
}

void mostrarMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Recomendacoes");

    lcd.setCursor(0, 1);
    if (menuIndex == 0) lcd.print("> 1. Escritores");
    else lcd.print("1. Escritores");

    lcd.setCursor(0, 2);
    if (menuIndex == 1) lcd.print("> 2. Musicos");
    else lcd.print("2. Musicos");

    lcd.setCursor(0, 3);
    if (menuIndex == 2) lcd.print("> 3. Diretores");
    else lcd.print("3. Diretores");
}

void mostrarRecomendacoes(String recomendacoes[], int tamanho) {
    lcd.clear();
    for (int i = 0; i < tamanho; i++) {
        lcd.setCursor(0, 0);
        lcd.print(recomendacoes[i]);
        delay(3000);
        lcd.clear();
    }
}

void loop() {
    lerBotoes();

    switch (estado) {
        case 1:
            ponto = 0;

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("  Bem vindo ao");
            lcd.setCursor(0, 1);
            lcd.print("   AfroPop Quiz!");

            delay(30); // delay 3000

            estado = 2;

            break;

        case 2:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Pressione Select ");
            lcd.setCursor(0, 1);
            lcd.print("Para iniciar JOGO");

            if (botao == "Select") {
                estado = 110;
            } else if (botao != "vazio") {
                teclaError();
            }

            delay(200);
            break;

        case 110:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Q1: O que foram os");
            lcd.setCursor(0, 1);
            lcd.print("Panteras Negras");
            lcd.setCursor(0, 2);
            lcd.print("nos EUA?");

            delay(6000);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("() Mov. cultural");
            lcd.setCursor(0, 1);
            lcd.print("ligado ao afrobeats");

            lcd.setCursor(0, 2);
            lcd.print("() Partido pela auto");
            lcd.setCursor(0, 3);
            lcd.print("defesa negra");

            delay(200);
            estado = 111;
            aux = 0;

            break;

        case 111:
            lerBotoes();

            if (botao == "Cima") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("(X) Mov. cultural");
                lcd.setCursor(0, 1);
                lcd.print("ligado ao afrobeats");

                lcd.setCursor(0, 2);
                lcd.print("() Partido pela auto");
                lcd.setCursor(0, 3);
                lcd.print("defesa negra");

                flag = false;
                aux++;

            } else if (botao == "Baixo") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("() Mov. cultural");
                lcd.setCursor(0, 1);
                lcd.print("ligado ao afrobeats");

                lcd.setCursor(0, 2);
                lcd.print("(X) Partido pela auto");
                lcd.setCursor(0, 3);
                lcd.print("defesa negra");

                flag = true;
                aux++;

            } else if (botao == "Select") {
                if (aux != 0) {
                    if (flag == true) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Acertou!"); 

                        ponto++;
                        estado = 120;
                        delay(3000);
                    }

                    if (flag == false) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Errou!");

                        estado = 120;
                        delay(3000);
                    }
                } 
            } else if (botao != "vazio") {
                teclaError();
            }

            break;

        case 120:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Q2: Qual a escritora");
            lcd.setCursor(0, 1);
            lcd.print("do Pequeno Manual");
            lcd.setCursor(0, 2);
            lcd.print("Antirracista?");

            delay(6000);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("() Djamila Ribeiro");

            lcd.setCursor(0, 2);
            lcd.print("() Chimamanda Adichie");

            delay(200);
            estado = 121;
            aux = 0;

            break;

        case 121:
            lerBotoes();

            if (botao == "Cima") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("(X) Djamila Ribeiro");
                lcd.setCursor(0, 1);
                lcd.print("() Chimamanda Adichie");

                flag = true;
                aux++;

            } else if (botao == "Baixo") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("() Djamila Ribeiro");
                lcd.setCursor(0, 1);
                lcd.print("(X) Chimamanda Adichie");

                flag = false;
                aux++;

            } else if (botao == "Select") {
                if (aux != 0) {
                    if (flag == true) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Acertou!");

                        ponto++;
                        estado = 130;
                        delay(3000);
                    }

                    if (flag == false) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Errou!");

                        estado = 130;
                        delay(3000);
                    }
                } 
            } else if (botao != "vazio") {
                teclaError();
            }

            break;
            
        case 130:            
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Q3: Triste Fim de");
            lcd.setCursor(0, 1);
            lcd.print("Policarpo Quaresma");
            lcd.setCursor(0, 2);
            lcd.print("eh uma obras litera");
            lcd.setCursor(0, 3);
            lcd.print("rias do escritor:");

            delay(6000);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("() Lima Barreto");

            lcd.setCursor(0, 2);
            lcd.print("() Guimaraes Rosa");

            delay(200);
            estado = 131;
            aux = 0;

            break;

        case 131:
            lerBotoes();

            if (botao == "Cima") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("(X) Lima Barreto");
                lcd.setCursor(0, 1);
                lcd.print("() Guimaraes Rosa");

                flag = true;
                aux++;

            } else if (botao == "Baixo") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("() Lima Barreto");
                lcd.setCursor(0, 1);
                lcd.print("(X) Guimaraes Rosa");

                flag = false;
                aux++;

            } else if (botao == "Select") {
                if (aux != 0) {
                    if (flag == true) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Acertou! ");

                        ponto++;
                        estado = 140;
                        delay(3000);
                    }

                    if (flag == false) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Errou!");


                        estado = 140;
                        delay(3000);
                    }
                } 
            } else if (botao != "vazio") {
                teclaError();
            }

            break;

        case 140: 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Q4: Os albuns");
            lcd.setCursor(0, 1);
            lcd.print("Um Banda Um, Realce");
            lcd.setCursor(0, 2);
            lcd.print("e Refavela sao de");
            lcd.setCursor(0, 3);
            lcd.print("que artista?");

            delay(6000);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("() Gilberto Gil");

            lcd.setCursor(0, 2);
            lcd.print("() Jorge Ben Jor");

            delay(200);
            estado = 141;
            aux = 0;

            break;

        case 141:
            lerBotoes();

            if (botao == "Cima") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("(X) Gilberto Gil");
                lcd.setCursor(0, 1);
                lcd.print("() Jorge Ben Jor");

                flag = true;
                aux++;

            } else if (botao == "Baixo") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("() Gilberto Gil");
                lcd.setCursor(0, 1);
                lcd.print("(X) Jorge Ben Jor");

                flag = false;
                aux++;

            } else if (botao == "Select") {
                if (aux != 0) {
                    if (flag == true) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Acertou! ");

                        ponto++;
                        estado = 170;
                        delay(3000);
                    }

                    if (flag == false) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Errou!");


                        estado = 170;
                        delay(3000);
                    }
                } 
            } else if (botao != "vazio") {
                teclaError();
            }

            break;

        case 170:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Q5: Qual album fez");
            lcd.setCursor(0, 1);
            lcd.print("dos Racionais");
            lcd.setCursor(0, 2);
            lcd.print("doutores pela honra?");

            delay(6000);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("() Transpiracao Continua");
            lcd.setCursor(0, 1);
            lcd.print("Prolongada, 1996");
            lcd.setCursor(0, 2);
            lcd.print("() Sobrevivendo no");
            lcd.setCursor(0, 3);
            lcd.print("Inferno, 1997");          

            delay(200);
            estado = 171;
            aux = 0;

            break;

        case 171:
            lerBotoes();

            if (botao == "Cima") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("(X) Transpiracao Continua");
                lcd.setCursor(0, 1);
                lcd.print("Prolongada, 1996");
                lcd.setCursor(0, 2);
                lcd.print("() Sobrevivendo no");
                lcd.setCursor(0, 3);
                lcd.print("Inferno, 1997");

                flag = false;
                aux++;

            } else if (botao == "Baixo") {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("() Transpiracao Continua");
                lcd.setCursor(0, 1);
                lcd.print("Prolongada, 1996");
                lcd.setCursor(0, 2);
                lcd.print("(X) Sobrevivendo no");
                lcd.setCursor(0, 3);
                lcd.print("Inferno, 1997");

                flag = true;
                aux++;

            } else if (botao == "Select") {
                if (aux != 0) {
                    if (flag == true) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Acertou!");

                        ponto++;
                        estado = 4;
                        delay(3000);
                    }

                    if (flag == false) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Errou!");


                        estado = 4;
                        delay(3000);
                    }
                } 
            } else if (botao != "vazio") {
                teclaError();
            }

            break;            

        case 4:
            mostrarMenu();
            estado = 5;
            delay(200);
            break;

        case 5:
            lerBotoes();

            if (botao == "Cima") {
                menuIndex = (menuIndex - 1 + 3) % 3;
                mostrarMenu();
                delay(200);
            } else if (botao == "Baixo") {
                menuIndex = (menuIndex + 1) % 3;
                mostrarMenu();
                delay(200);
            } else if (botao == "Select") {
                if (menuIndex == 0) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Frantz Fanon");
                    lcd.setCursor(0, 1);
                    lcd.print("Lelia Gonzalez");
                    lcd.setCursor(0, 2);
                    lcd.print("Achille Mbembe");
                    lcd.setCursor(0, 3);
                    lcd.print("Cida Bento");

                    delay(6000);

                } else if (menuIndex == 1) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Cassiano");
                    lcd.setCursor(0, 1);
                    lcd.print("Luedji Luna");
                    lcd.setCursor(0, 2);
                    lcd.print("Larissa Luz");
                    lcd.setCursor(0, 3);
                    lcd.print("Dona Ivone Lara");

                    delay(6000);

                } else if (menuIndex == 2) {

                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Sabrina Fidalgo");
                    lcd.setCursor(0, 1);
                    lcd.print("Adelia Sampaio");
                    lcd.setCursor(0, 2);
                    lcd.print("Gabriel Martins");
                    lcd.setCursor(0, 3);
                    lcd.print("Marlon Riggs");

                    delay(6000);

                }
                estado = 20;
                delay(200);
            } else if (botao != "vazio") {
                teclaError();
            }
            break;

        case 20:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Volte sempre! <3");

            delay(3000);
            estado = 1;
            ponto = 0;
            break;
    }
}

void teclaError() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tecla Invalida");
    delay(500);
}
