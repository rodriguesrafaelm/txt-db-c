#include <stdio.h>
#include <string.h>

//Limitando 10 registros em memória 
#define MAX_REGISTROS 10

typedef struct {
    int id;
    char telefone[10];
    int idade;
    char nome[255];
    char email[255];
} Contato;
Contato bancoDeDados[MAX_REGISTROS];
int numeroContatosRegistrados;


//Inicializando "DB"
int inicializarBancoDados() {
    FILE *arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de contatos.\n");
        return 1;
    }

    numeroContatosRegistrados = 0;

    while (fscanf(arquivo, "%d,%[^,],%[^,],%d,%s\n", &bancoDeDados[numeroContatosRegistrados].id,
                                                bancoDeDados[numeroContatosRegistrados].nome,
                                                bancoDeDados[numeroContatosRegistrados].email,
                                                &bancoDeDados[numeroContatosRegistrados].idade,
                                                bancoDeDados[numeroContatosRegistrados].telefone) == 5) {
        numeroContatosRegistrados++;
        if (numeroContatosRegistrados == MAX_REGISTROS) {
            break;
        }
    }

    printf("Atualmente, o banco de dados possui %d contatos.\n", numeroContatosRegistrados);
    fclose(arquivo);
    return 0;
}

//Prompt pra inserir novo usuário
Contato pedirNovoContato(){
    Contato dadosContato;
    printf("Insira o nome do contato:");
    scanf("%s", dadosContato.nome);
    printf("Insira o email do contato:");
    scanf("%s", dadosContato.email);
    printf("Insira a idade do contato:");
    scanf("%d", &dadosContato.idade);
    printf("Insira o telefone do contato:");
    scanf("%s", dadosContato.telefone);
    return dadosContato;
}

//Função de inserção na lista em memória
void inserirContato(Contato novoContato) {
    if(numeroContatosRegistrados == MAX_REGISTROS){
        printf("Limite de contatos atingido.");
    } else {
    novoContato.id = numeroContatosRegistrados + 1;
    bancoDeDados[numeroContatosRegistrados] = novoContato;
    numeroContatosRegistrados++;
    }
};

//Salvar dados da memória no arquivo.txt
int salvarContatos() {
    FILE *arquivo = fopen("contatos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de contatos.");
        return -1;
    }

    for (int i = 0; i < numeroContatosRegistrados; i++) {
        fprintf(arquivo, "%d,%s,%s,%d,%s\n", bancoDeDados[i].id, bancoDeDados[i].nome, bancoDeDados[i].email, bancoDeDados[i].idade, bancoDeDados[i].telefone);
    }

    fclose(arquivo);
    return 0;
}

//Ler e exibir todos os contatos presentes no banco de dados
int lerContatos() {
    FILE *arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de contatos.");
        return -1;
    }

    Contato contato;
    //Ler dados separados por virgula
    while (fscanf(arquivo, "%d,%[^,],%[^,],%d,%s\n", &contato.id, contato.nome, contato.email, &contato.idade, contato.telefone) == 5) {
        printf("Nome: %s Email: %s Telefone: %s Idade: %d\n", contato.nome, contato.email, contato.telefone, contato.idade);
    }

    fclose(arquivo);
    return 0;
}

int buscarPorId(int id) {
    int indice = -1;
    for (int i = 0; i < numeroContatosRegistrados; i++) {
        if(bancoDeDados[i].id == id){
            Contato contato = bancoDeDados[i];
            printf("Os dados do contato são:\nNome: %s, Email: %s, Idade: %d, Telefone: %s\n", contato.nome, contato.email, contato.idade, contato.telefone);  
            return 0;
        }
    printf("Nenhum usuário com o id %d foi encontrado.", id);
    return -1;
    }
}

void atualizarContato(int id) {
    int indice = -1;
    for (int i = 0; i < numeroContatosRegistrados; i++) {
        if (bancoDeDados[i].id == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Contato com o ID %d não encontrado.\n", id);
        return;
    }

    Contato novoContato = pedirNovoContato();
    novoContato.id = id;
    bancoDeDados[indice] = novoContato;
    printf("Contato atualizado com sucesso.\n");
}

void excluirContato(int id) {
    int indice = -1;
    for (int i = 0; i < numeroContatosRegistrados; i++) {
        if (bancoDeDados[i].id == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Contato com o ID %d não encontrado.\n", id);
        return;
    }

    for (int i = indice; i < numeroContatosRegistrados - 1; i++) {
        bancoDeDados[i] = bancoDeDados[i + 1];
    }

    numeroContatosRegistrados--;
    printf("Contato excluído com sucesso.\n");
}

int main() {
    inicializarBancoDados();
    inserirContato(pedirNovoContato());
    lerContatos();
    buscarPorId(3);
    excluirContato();
    salvarContatos();
    return 0;
}