#include <iostream>
#include <string>
#include <cstdlib> // para system()
#include <cctype>  // para toupper(), isalpha()
using namespace std;

// Função para limpar a tela de forma automática, dependendo do sistema operacional
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #elif __linux__ || __APPLE__
        system("clear"); // Linux e MacOS
    #else
        cout << "\n[Não foi possível limpar a tela automaticamente]\n";
    #endif
}

// Array com os desenhos do bonequinho da forca para cada número de erros
const string bonecoForca[] = {
R"(  
  +---+
  |   |
      |
      |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
      |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
  |   |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========
)"
};

int main() {
    int vitorias = 0; // contador de vitórias
    int derrotas = 0; // contador de derrotas
    char jogarNovamente = 's'; // controle do loop principal

    while (jogarNovamente == 's' || jogarNovamente == 'S') {
        string palavra, dica, letra;
        string letraDigitada; // armazena letras já digitadas
        int letraTamanho = 1; // garante que o usuário digite apenas uma letra
        int tentativas = 6; // número máximo de tentativas permitidas

        // Exibe título estilizado
        cout << "\033[1;35m";
        cout << "╔══════════════════════════╗\n";
        cout << "║  JOGO DA FORCA - INÍCIO  ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "\033[0m\n";

        // Entrada da palavra secreta
        cout << "Palavra para adivinhacao: ";
        getline(cin, palavra); // permite palavras com espaços

        // Entrada da dica
        cout << "Digite uma dica: ";
        getline(cin, dica);

        // Cria palavra secreta com underlines
        string palavraSecreta(palavra.size(), '_');

        limparTela();

        // Início do jogo
        while (tentativas > 0 && palavraSecreta != palavra) {
            cout << "A dica é: " << dica << endl;
            cout << "Tentativas restantes: " << tentativas << endl;
            cout << bonecoForca[6 - tentativas] << endl;
            cout << "Palavra secreta: " << palavraSecreta << endl;
            cout << "Letras já digitadas: " << letraDigitada << endl;

            // Entrada da letra com validações
            do {
                cout << "Digite uma letra(ou ! para adivinhar a palavra inteira): ";
                cin >> letra;

                // Verifica se o jogador quer chutar a palavra inteira
                if (letra == "!") {
                    string palavraInteira;
                    cin.ignore(); // limpa o buffer antes do getline
                    cout << "Digite a palavra inteira: ";
                    getline(cin, palavraInteira);

                    if (palavraInteira == palavra) {
                        palavraSecreta = palavra;
                        break; // jogador acertou a palavra inteira
                    } else {
                        cout << "Palpite incorreto! Você perde uma tentativa.\n";
                        tentativas--;
                        break; // sai do do-while e reinicia o loop
                    }
                }
                // Verifica se é uma letra válida
                else if (!isalpha(letra[0])) {
                    cout << "O caractere '" << letra[0] << "' NÃO é uma letra do alfabeto (a-z, A-Z).\n";
                    letra = "";
                    continue;
                }

                // Garante que o usuário digitou apenas uma letra
                if (letra.size() != letraTamanho) {
                    cout << "\nLetra inválida! \nDigite exatamente " << letraTamanho << " letra(s).\n";
                    letra = "";
                    continue;
                }

                // Converte para maiúscula
                char letraChar = toupper(letra[0]);

                // Verifica se a letra já foi tentada
                if (letraDigitada.find(letraChar) != string::npos) {
                    cout << "Você já tentou essa letra. Digite outra.\n";
                    letra = "";
                    continue;
                } else {
                    letraDigitada += letraChar; // adiciona ao histórico
                    break; // entrada válida
                }

            } while (true);

            // Verifica se acertou a letra na palavra
            bool acertou = false;
            char letraChar = toupper(letra[0]);

            for (int i = 0; i < palavra.size(); i++) {
                if (toupper(palavra[i]) == letraChar) {
                    palavraSecreta[i] = palavra[i];
                    acertou = true;
                }
            }

            if (!acertou) {
                tentativas--; // perde tentativa se errou
            }

            limparTela(); // limpa a tela a cada rodada
        }

        // Mensagem de vitória
        if (palavra == palavraSecreta) {
            vitorias++;
            cout << "\033[1;32m";
            cout << "╔═══════════════════════════╗\n";
            cout << "║   PARABÉNS, VOCÊ VENCEU!  ║\n";
            cout << "╚═══════════════════════════╝\n";
            cout << "\033[0m";
            cout << "\nPalavra: \033[1;33m" << palavra << "\033[0m" << endl;
        } else {
            derrotas++;
            cout << bonecoForca[6] << endl; // exibe boneco completo
            cout << "\033[1;31m";
            cout << "╔═══════════════════════╗\n";
            cout << "║   POXA, VOCÊ PERDEU!  ║\n";
            cout << "╚═══════════════════════╝\n";
            cout << "\033[0m";
            cout << "\nPalavra: \033[1;31m" << palavra << "\033[0m" << endl;
        }

        // Estatísticas da sessão
        cout << "\nTotal de vitórias: " << vitorias << endl;
        cout << "Total de derrotas: " << derrotas << endl;

        // Pergunta se o jogador deseja continuar
        cout << "\nQuer jogar novamente? (s/n): ";
        cin >> jogarNovamente;
        cin.ignore(); // limpa buffer
        limparTela();

        // Mensagem de despedida se o jogo terminar
        if (jogarNovamente == 'n' || jogarNovamente == 'N'){
            cout << "Obrigado por jogar! Até a próxima.\n";
            cout << "\nTotal de vitórias: " << vitorias << endl;
            cout << "Total de derrotas: " << derrotas << endl;
        }
    }

    return 0;
}
