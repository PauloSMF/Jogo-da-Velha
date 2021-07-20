//PAULO SÉRGIO MOREIRA FERREIRA
#include<iostream>
#include <ctime>
using namespace std;

//Impressão do tabuleiro
void PrintBoard(char current_board[9]){
    system("cls");
    cout << "Jogo da Velha\n";

    cout<<"Jogador (X)  -  Máquina (O)"<<endl<<endl;
    cout<< endl;

    cout<< " _____ _____ _____ " <<endl;
    cout<< "|     |     |     |" <<endl;
    cout<< "|  " << current_board[0]  << "  |  " << current_board[1] << "  |  " << current_board[2] << "  |  " << endl;

    cout<< "|_____|_____|_____|" <<endl;
    cout<< "|     |     |     |" <<endl;

    cout<<"|  "<<current_board[3]<<"  |  "<<current_board[4]<<"  |  "<<current_board[5]<<"  |  "<< endl;

    cout<<"|_____|_____|_____|"<<endl;
    cout<<"|     |     |     |"<<endl;

    cout<<"|  "<< current_board[6]<< "  |  "<< current_board[7]<<"  |  "<<current_board[8]<<"  |  "<<endl;
    cout<<"|_____|_____|_____|"<<endl<<endl;
}

//Computando jogada do jogador
void PlayerPlay(char current_board[9], char current_player, int &position){
    while(true){ //Enquanto o jogador não realiza uma entrada válida
        if(position == 0 && current_board[0] == '0'){
            current_board[0] = current_player;
            break;
        }
        else if(position == 1 && current_board[1] == '1'){
            current_board[1] = current_player;
            break;
        }
        else if(position == 2 && current_board[2] == '2'){
            current_board[2] = current_player;
            break;
        }
        else if(position == 3 && current_board[3] == '3'){
            current_board[3] = current_player;
            break;
        }
        else if(position == 4 && current_board[4] == '4'){
            current_board[4] = current_player;
            break;
        }
        else if(position == 5 && current_board[5] == '5'){
            current_board[5] = current_player;
            break;
        }
        else if(position == 6 && current_board[6] == '6'){
            current_board[6] = current_player;
            break;
        }
        else if(position == 7 && current_board[7] == '7'){
            current_board[7] = current_player;
            break;
        }
        else if(position == 8 && current_board[8] == '8'){
            current_board[8] = current_player;
            break;
        }
        else{ //O jogador fez um movimento inválido
            cout<<"Movimento inválido! Por favor faça um movimento válido: ";
            cin>>position;
        }
    }
}

int CheckEndgame(char current_board[9], char &player){ //Checando se o jogo acabou e retornando o ganhador
    if(current_board[0] == current_board[3] && current_board[0] == current_board[6]){
        player = current_board[0];
        return 1;
    }
    else if(current_board[1] == current_board[4] && current_board[1] == current_board[7]){
        player = current_board[1];
        return 1;
    }
    else if(current_board[2] == current_board[5] && current_board[2] == current_board[8]){
        player = current_board[2];
        return 1;
    }
    else if(current_board[0] == current_board[1] && current_board[0] == current_board[2]){
        player = current_board[0];
        return 1;
    }
    else if(current_board[3] == current_board[4] && current_board[3] == current_board[5]){
        player = current_board[3];
        return 1;
    }
    else if(current_board[6] == current_board[7] && current_board[6] == current_board[8]){
        player = current_board[6];
        return 1;
    }
    else if(current_board[0] == current_board[4] && current_board[0] == current_board[8]){
        player = current_board[0];
        return 1;
    }
    else if(current_board[2] == current_board[4] && current_board[2] == current_board[6]){
        player = current_board[2];
        return 1;
    }
    else
        return 0;
}

//Algoritmo de busca em profundidade, varre o espaço de busca de cima pra baixo e da esquerda para a
//direita, escolhendo o primeiro movimento que lhe garante a vitória, independente se este é o
//melhor ou não. No caso da busca em profundidade tradicional o parâmetro max_depth sempre é 9
//variando para a busca em profundidade com aprofundamento iterativo.
bool DepthFirstSearch(char current_board[9], int depth, int max_depth, bool cpu_turn){
    char winner;
    bool result; //Variável para armazenar

    if(CheckEndgame(current_board, winner) == 1){
        if(cpu_turn == true)
            return true;    //True caso o movimento possa levar a vitória da máquina
        else
            return false; //False caso o movimento possa levar a vitória do jogador
    }
    else{
        if(depth < max_depth){ //Caso a profundidade da árvore não tenha atingido o limite
            if(cpu_turn == true){
                for(int i = 0; i < 9; i++){
                    if(current_board[i] != 'X' && current_board[i] != 'O'){ //Caso a posição esteja livre
                        current_board[i] = 'O'; //Computando a tentativa de jogada da máquina
                        result = DepthFirstSearch(current_board, depth + 1, 9, false); //Caminhando recursivamente descendo
                        //no espaço de busca
                        if(result){ //Caso seja encontrada a primeira jogada que poderia levar ao fim de jogo
                            current_board[i] = '0' + i; //Desfazendo a jogada
                            return result;  //Retornando o resultado do fim do jogo
                        }

                        current_board[i] = '0' + i; //Desfazendo a jogada para demais testes
                    }
                }
            }
            else{
                for(int i = 0; i < 9; i++){
                    if(current_board[i] != 'X' && current_board[i] != 'O'){ //Caso a posição esteja livre
                        current_board[i] = 'X'; //Simulando uma jogada humana
                        result = DepthFirstSearch(current_board, depth + 1, 9, true);//Caminhando recursivamente descendo
                        //no espaço de busca
                        if(result){ //Caso seja encontrada a primeira jogada que poderia levar ao fim de jogo
                            current_board[i] = '0' + i; //Desfazendo a jogada
                            return result; //Retornando o resultado do fim do jogo
                        }

                        current_board[i] = '0' + i; //Desfazendo a jogada para demais testes
                    }
                }
            }
        }
        else //Caso o limite de profundidade foi atingido
            return false; //Linha referente ao término em empate
    }
}

int DepthFirstSearchMove(char current_board[9], int positions_played){
    int position = -1;  //Posição  a ser jogada em caso de vitória

    for(int i= 0; i < 9; i++){ //Varrendo o espaço de busca
        if(current_board[i] != 'X' && current_board[i] != 'O'){ //Procurando uma posição livre
            current_board[i] = 'O'; //Computando a jogada da máquina

            if(DepthFirstSearch(current_board, positions_played + 1, 9, true)){ //Caso há uma possibilidade de vitória
                current_board[i] = '0' + i; //Desfazendo a jogada
                position = i; //A posição a ser jogada é a primeira encontrada
                return position; //Retornando a posição
            }

            current_board[i] = '0' + i; //Desfazendo a jogada para demais testes
        }
    }

    for(int i = 0; i < 9; i++){ //Caso não fosse encontrada jogada que leve a vitória
        if(current_board[i] != 'X' && current_board[i] != 'O'){ //Varrendo o espaço de busca
            return i; //Realizando qualquer jogada
        }
    }
}

int IterativeDeepeningDFS(char current_board[9], int positions_played){
    int position = -1;  //Posição  a ser jogada em caso de vitória

    int max_depth = 5;  //É necessário 3 marcações para o fim de jogo, o
    //mínimo para se fazer isso é em 5 rodadas
    for(int i = max_depth; i < 9; i++){ //Caso o resultado seja encontrado em tal profundidade o movimento é feito
    //caso não seja, aumenta-se a profundidade
        for(int i= 0; i < 9; i++){ //Varrendo o espaço de busca
            if(current_board[i] != 'X' && current_board[i] != 'O'){ //Procurando uma posição livre
                current_board[i] = 'O'; //Computando a jogada da máquina

                if(DepthFirstSearch(current_board, positions_played + 1, max_depth, true)){ //Caso há uma possibilidade de vitória
                    current_board[i] = '0' + i; //Desfazendo a jogada
                    position = i; //A posição a ser jogada é a primeira encontrada
                    return position; //Retornando a posição
                }

                current_board[i] = '0' + i; //Desfazendo a jogada para demais testes
            }
        }
    }

    for(int i = 0; i < 9; i++){ //Caso não fosse encontrada jogada que leve a vitória
        if(current_board[i] != 'X' && current_board[i] != 'O'){ //Varrendo o espaço de busca
            return i; //Realizando qualquer jogada
        }
    }
}

//Algoritmo MiniMax, realiza uma busca em profundidade buscando o melhor resultado
//possível para realizar a jogada. Recebe o tabuleiro, a profundidade e o caso de
//estar na jogada da CPU (Maximizador).
int MiniMax(char current_board[9], int depth, bool cpu_turn){
    char winner;
    int score = 0;  //Variável para armazenar a pontuação da caminho
    int best_score = 0; //Variável para armazenar o melhor caminho já visitado

    if(CheckEndgame(current_board, winner) == 1){ //Caso o jogo tenha acabado
        if(cpu_turn == true) //No turno da máquina
            return -1; //Resultado bom para a máquina (máximo)
        else
            return +1; //Resultado ruim para a máquina (mínimo)
    }
    else{
        if(depth < 9){ //Caso a profundidade da árvore não tenha atingido o limite
            if(cpu_turn == true){ //No turno da CPU a ação maximizadora é executada
                best_score = -1000;

                for(int i = 0; i < 9; i++){ //Varrendo o tabuleiro (espaço de busca)
                    if(current_board[i] != 'X' && current_board[i] != 'O'){ //Caso a posição esteja livre
                        current_board[i] = 'O'; //Computando a tentativa de jogada da máquina
                        score = MiniMax(current_board, depth + 1, false); //Calculando a pontuação do caminho
                        current_board[i] = '0' + i; //Desfazendo a jogada para demais testes

                        if(score > best_score)  //Caso o caminho computado é melhor que o atual
                            best_score = score;
                    }
                }

                return best_score;  //Restornando o melhor caminho
            }
            else{ //A ação minimizadora tenta simular a melhor jogada que o jogador pode fazer
                best_score = 1000;

                for(int i = 0; i < 9; i++){ //Varrendo o tabuleiro (espaço de busca)
                    if(current_board[i] != 'X' && current_board[i] != 'O'){ //Caso a posição esteja livre
                        current_board[i] = 'X'; //Simulando uma jogada humana
                        score = MiniMax(current_board, depth + 1, true); //Calculando a pontuação do caminho
                        current_board[i] = '0' + i; //Desfazendo a jogada para demais testes

                        if(score < best_score) //Caso o caminho computado é melhor que o atual
                            best_score = score;
                    }
                }

                return best_score; //Restornando o melhor caminho
            }
        }
        else //Caso o limite de profundidade foi atingido
            return 0; //Linha referente ao término em empate
    }
}

//Função para disparar a busca utilizando o algoritmo minimax e escolher o melhor caminho
int MiniMaxMove(char current_board[9], int positions_played){
    int position = -1;  //Posição  a ser jogada
    int score = 0;  //Pontuação de um caminho
    int best_score = -1000; //Melhor pontuação de caminho

    for(int i = 0; i < 9; i++){ //Varrendo o espaço de busca
        if(current_board[i] != 'X' && current_board[i] != 'O'){ //Procurando uma posição livre
            current_board[i] = 'O'; //Computando a jogada da máquina
            score = MiniMax(current_board, positions_played + 1, false); //Armazenando a pontuação do caminho
            current_board[i] = '0' + i; //Desfazendo o movimento para demais testes

            if(score > best_score){ //Caso a pontuação do caminho atual seja a melhor visitada
                best_score = score; //Armazenando a informação
                position = i; //Escolhendo a melhor jogada
            }
        }
    }

    return position; //Retornando a posição da melhor jogada
}

//Função para jogar uma partida, recebe qual o método de busca usado
//1 - Busca em Profundidade
//2 - Busca em Profundidade com Aprofundamento Iterativo
//3 - Minimax
void StartGame(int search_method){
    char current_board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'}; //Definição do tabuleiro
    //X - Humano
    //O - Máquina
    char current_player; //Variável para reconhecimento a qual jogador pertence a jogada
    char winner = 'N';  //Armazenando o vencedor do jogo

    int position; //Armazenando a posição que a jogada será registrada
    int endgame = 0; //Variável para reconhecimento de fim de jogo
    int positions_played = 0; //Variável para reconhecimento de quantas jogadas já foram feitas das 9 possíveis
    int first_player = 2; //Variável para reconhecimento de quem
    //jogará primeiro
    while(first_player != 0 && first_player != 1){
        cout<<endl<<"Quem joga primeiro? 0-Máquina 1-Jogador: ";
        cin>>first_player;
    }

    if(first_player == 0)
        current_player = 'O'; //Definindo que a máquina joga primeiro
    else
        current_player = 'X'; //Definindo o que o humano inicia o jogo

    cout<<endl;
    PrintBoard(current_board); //Imprimindo o tabuleiro

    while(endgame == 0 &&  positions_played != 9){  //Enquanto não há vitória ou empate
        if(current_player == 'X'){ //Caso seja o turno do jogador humano
            //Captura do movimento do jogador
            cout<<"Insira um número para realizar um movimento: ";
            cin>>position;
            //Computando o movimento do jogador
            PlayerPlay(current_board, current_player, position);
            //Incrementando o número de jogadas feitas e trocando de jogador
            positions_played++;
            current_player = 'O';
        }
        else{
            if(search_method == 1)
                position = DepthFirstSearchMove(current_board, positions_played); //Algoritmo de Busca em Profundidade
            else if(search_method == 2)
                position = IterativeDeepeningDFS(current_board, positions_played); //Algoritmo de Busca em Profundidade
                //com Aprofundamento Iterativo
            else
                position = MiniMaxMove(current_board, positions_played); //Algoritmo Minimax
            //Computando o movimento da máquina
            current_board[position] = 'O';
            //Incrementando o número de jogadas feitas e trocando de jogador
            positions_played++;
            current_player = 'X';
        }

        PrintBoard(current_board); //Imprimindo o tabuleiro
        endgame = CheckEndgame(current_board, winner); //Checando se o jogo acabou
    }

    if(endgame == 1){ //Se chegou ao fim do jogo
        if(winner == 'X'){  //Checando o vencedor
            cout<<"O jogador venceu!"<<endl<<endl;
            system("pause");
            system("CLS");
        }
        else{
            cout<<"A máquina venceu!"<<endl<<endl;
            system("pause");
            system("CLS");
        }
    }
    else{ //Se o fim de jogo foi disparado e a variável endgame está definida como 0
        cout<<endl<<"Empate!"<<endl<<endl; //Ocorreu um empate
        system("pause");
        system("CLS");
    }
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    int op; //Menu

    do{
        cout<<"||MENU||"<<endl<<endl;
        cout<<"1 - Jogar contra algoritmo de Busca em Profundidade."<<endl;
        cout<<"2 - Jogar contra algoritmo de Busca em Profundidade com Aprofundamento Iterativo."<<endl;
        cout<<"3 - Jogar contra algoritmo MiniMax."<<endl;
        cout<<"4 - Sair."<<endl<<endl;
        cout<<"Escolha uma opção: ";
        cin>>op;

        switch(op){
            case 1:
                StartGame(1);
                break;
            case 2:
                StartGame(2);
                break;
            case 3:
                StartGame(3);
                break;
            case 4:
                cout<<endl<<"Saindo..."<<endl;
                break;
            default:
                cout<<endl<<"Opção inválida!"<<endl<<endl;
                system("pause");
                system("CLS");
        }
    }while(op != 4);

    return 0;
}
