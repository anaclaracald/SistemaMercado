#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

typedef struct _produto
{
    int codigo;
    char nome[50];
    float preco;
} Produto;

typedef struct _carrinho
{
    Produto produto;
    int quantidade;
    double subtotal;
} Carrinho;

void SystemClear();        // limpar console 
void menu();               // Gerencia o fluxo do programa e as opcoes do usuario.
void listarProdutos();     // Exibe todos os produtos cadastrados.
void comprarProduto();     // Adiciona produtos, suas quantidades e o calculo do subtotal dos itens ao carrinho.
void visualizarCarrinho(); // Exibe os produtos do carrinho.
void fecharPedido();       // Calcula e exibe o valor total da compra e esvazia o carrinho.
void removerCarrinho();    // Remove item do carrinho
void atualizarNome();      // Renomeia o produto 

Produto *cadastrarProduto();     // Permite o cadastro de novos produtos.
Produto pegarProdutoPorCodigo(); // Retorna um produto a partir do codigo informado.

bool validaCodigo(int codigo); // Verifica se o código ja foi utilizado em outro produto
bool validaNome();             // Valida o nome digitado pelo usuario em caso de string vazia
int temNoCarrinho();           // Verifica se o produto ja esta no carrinho

int operacao, totalProdutos = 0, indiceCarrinho = 0; // variaveis globais

Produto *listaProdutos[50];
Carrinho *carrinho[50];

int main(){
    SystemClear();
    menu();
    return 0;
}

void SystemClear(){
    system("cls");
}

void menu(){
    puts("\n=========================Sistema de Mercado========================\n");
    puts("[0] Sair do sistema");
    puts("[1] Menu");
    puts("[2] Cadastrar produto");
    puts("[3] Listar produtos");
    puts("[4] Comprar produto");
    puts("[5] Visualizar carrinho");
    puts("[6] Renomear produto");
    puts("[7] Remover item do carrinho");
    puts("[8] Fechar pedido");
    printf("\nDigite o numero da operacao desejada: ");
    scanf("%d", &operacao);
    puts("\n===================================================================");

    switch (operacao)
    {
    case 1:
        menu();
        break;
    case 2:
        cadastrarProduto();
        menu();
        break;
    case 3:
        listarProdutos();
        menu();
        break;
    case 4:
        comprarProduto();
        menu();
        break;
    case 5:
        visualizarCarrinho();
        menu();
        break;
    case 6:
        atualizarNome();
        menu();
        break;
    case 7:
        removerCarrinho();
        menu();
        break;
    case 8:
        fecharPedido();
        menu();
        break;
    default:
        break;
    }
}

void listarProdutos(){
    // Lista todos os produtos cadastrados, exibindo o codigo, nome e preco de cada produto.
    int i = 0;

    if (totalProdutos == 0)
    {
        printf("\n\nA lista de produtos esta vazia.\n\n");
    }
    else
    {
        for (i = 0; i < totalProdutos; i++)
        {
            Produto *produto = listaProdutos[i];
            printf("\n\n#Produto %d", i + 1);
            printf("\nCodigo: %d\n", produto->codigo);
            printf("Nome: %s\n", produto->nome);
            printf("Preco: R$%.2f\n\n", produto->preco);
        }
    }
}

void comprarProduto() {
    // seleciona um produto, atraves do codigo, e adiciona ao carrinho de compras.
    char cadMais = 1;
    int quantidade = 0;

    if(totalProdutos < 1){
        printf("\nNao existem produtos cadastrados ainda. Cadastre-os no menu a seguir.\n\n");
        menu();
    }

    do {
        Produto produtoEncontrado = pegarProdutoPorCodigo();
        
        if (produtoEncontrado.codigo != 0) {
            int indice = temNoCarrinho(produtoEncontrado.nome);
            if (indice != -1) {
                printf("Esse produto ja esta no carrinho. Atualizando quantidade.\n");
                printf("Quantidade adicional: ");
                scanf("%d", &quantidade);
                
                // Atualiza a quantidade e subtotal no carrinho
                carrinho[indice]->quantidade += quantidade;
                carrinho[indice]->subtotal += (produtoEncontrado.preco * quantidade);
                SystemClear();
                printf("\nQuantidade do produto '%s' atualizada com sucesso!\n\n", produtoEncontrado.nome);
            } else {
                // Se o produto não está no carrinho, solicita a quantidade
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                
                // Cria um novo item no carrinho
                Carrinho *itemCarrinho = (Carrinho *)calloc(1, sizeof(Carrinho));
                itemCarrinho->produto = produtoEncontrado;
                itemCarrinho->quantidade = quantidade;

                double subtotal = itemCarrinho->produto.preco * itemCarrinho->quantidade;
                itemCarrinho->subtotal = subtotal;

                // Adiciona o item ao carrinho
                carrinho[indiceCarrinho] = itemCarrinho;
                SystemClear();

                printf("\n%s adicionado ao carrinho com sucesso!\n\n", itemCarrinho->produto.nome);
                indiceCarrinho++;
            }
        } else {
            printf("\nProduto nao encontrado. Tente novamente.\n");
        }

        getchar(); 
        printf("Quer comprar mais produtos? [s/n]: ");
        scanf("%c", &cadMais);

        while (cadMais != 's' && cadMais != 'S' && cadMais != 'n' && cadMais != 'N') {
            getchar(); 
            printf("Caractere invalido! Quer comprar mais produtos? [s/n]: ");
            scanf("%c", &cadMais);
        }

    } while (cadMais == 's' || cadMais == 'S');
}

void visualizarCarrinho(){
    // visualiza os produtos adicionados ao carrinho, com suas respectivas quantidades.
    int i = 0;

    if (indiceCarrinho == 0)
    {
        printf("\nO carrinho esta vazio, adicione produtos nele.\n\n");
    }
    else
    {
        for (i = 0; i < indiceCarrinho; i++)
        {
            printf("\nProduto: %s\n", carrinho[i]->produto.nome);
            printf("Quantidade: %d\n", carrinho[i]->quantidade);
            printf("Preco unitario: R$%.2f\n", carrinho[i]->produto.preco);
            printf("Subtotal: R$%.2f\n\n", carrinho[i]->subtotal);
        }
    }
}

void fecharPedido()
{
    // calcula o valor total da compra, exibe uma fatura detalhada e limpar o carrinho depois de finalizar o pedido
    int i = 0;
    double total = 0;

    if(indiceCarrinho < 1){
        printf("\nAinda nao existem pedidos. Cadastre produtos e adicione-os no carrinho antes de fechar pedido.\n\n");
        menu();
    }

    for (i = 0; i < indiceCarrinho; i++)
    {
        total += carrinho[i]->subtotal;
    }

    printf("Total da compra: R$%.2f\n", total);

    printf("\nFatura detalhada:\n");
    for (i = 0; i < indiceCarrinho; i++)
    {
        printf("\n%s - Quantidade: %d - Subtotal: R$%.2f\n",
               carrinho[i]->produto.nome, carrinho[i]->quantidade, carrinho[i]->subtotal);
    }

    for (i = 0; i < indiceCarrinho; i++)
    {
        free(carrinho[i]);
    }

    indiceCarrinho = 0;
    printf("\nCarrinho esta vazio.\n");
}

void removerEspacos(char *str)
{ // remove espaços para validar os nomes dos produtos e garantir que nao sejam repetidos
    int start = 0;
    while (isspace(str[start]))
    {
        start++;
    }
    int end = strlen(str) - 1;
    while (end >= start && isspace(str[end]))
    {
        end--;
    }

    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

void removerCarrinho()
{   // remove um produto do carrinho
    if(indiceCarrinho<1){
        printf("\nNao existem produtos para serem removidos, o carrinho esta vazio.\n\n");
        menu();
    }

    char remMais;

    do
    {
        Produto produtoEncontrado = pegarProdutoPorCodigo();
        if (produtoEncontrado.codigo != 0)
        {
            Carrinho *itemCarrinho = (Carrinho *)calloc(1, sizeof(Carrinho));

            itemCarrinho->produto = produtoEncontrado;
            carrinho[indiceCarrinho] = itemCarrinho;

            printf("\n%s removido do carrinho com sucesso!\n\n", itemCarrinho->produto.nome);
            free(itemCarrinho);
            indiceCarrinho--;
        }

        if(indiceCarrinho<1){
            printf("\nNao existem produtos para serem removidos, o carrinho esta vazio.\n\n");
            menu();
        }

        getchar(); 
        printf("Quer remover mais produtos? [s/n]: ");
        scanf("%c", &remMais);

        while (remMais != 's' && remMais != 'S' && remMais != 'n' && remMais != 'N') {
            getchar(); 
            printf("Caractere invalido! Quer remover mais produtos? [s/n]: ");
            scanf("%c", &remMais);
        }
        

    } while (remMais == 's' || remMais =='S');
}

void atualizarNome() {
    // O usuario pode atualizar o nome de um produto ja cadastrado atraves do seu codigo
    int codigo;
    char novoNome[50];

    if (totalProdutos < 1) {
        printf("\nAinda nao existem produtos cadastrados. Cadastre-os no menu a seguir.\n\n");
        menu();
        return;
    }

    printf("Digite o codigo do produto que deseja renomear: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i]->codigo == codigo) {
            getchar(); 
            printf("Produto encontrado: %s\n", listaProdutos[i]->nome);
            printf("Digite o novo nome: ");
            scanf("%49[^\n]", novoNome);

            if (validaNome(novoNome)) {
                strcpy(listaProdutos[i]->nome, novoNome);
                SystemClear();
                printf("Nome atualizado com sucesso.\n");
            } else {
                printf("Esse nome já foi utilizado anteriormente. Nome invalido.\n");
            }
            return;
        }
    }

    // Caso nenhum produto seja encontrado com o código fornecido
    printf("Produto nao encontrado.\n");
}

Produto *cadastrarProduto(){
    // cadastro de novos produtos, com um codigo unico, nome e preço.
    Produto *produto = (Produto *)calloc(1, sizeof(Produto)); // alocaÃ§Ã£o da memÃ³ria para cadastrar o produto

    int codigo;
    char nome[50];
    float preco;

    puts("\n\nCadastro do produto");
    printf("Codigo: ");
    scanf("%d", &codigo);

    if (validaCodigo(codigo))
    {
        produto->codigo = codigo;
    }
    else
    {
        return NULL;
    }

    getchar();
   
    printf("Nome: ");
    scanf("%49[^\n]", nome);

    if (!validaNome(nome))
    {
        printf("Nome invalido. Por favor, insira um nome valido.\n\n");
        menu();
    }

    strcpy(produto->nome, nome);
    getchar();

    printf("Preco: ");
    scanf("%f", &preco);
    produto->preco = preco;

    listaProdutos[totalProdutos++] = produto;
    SystemClear();

    printf("\nProduto '%s' cadastrado com sucesso!\n\n\n", produto->nome);

    return produto;
}

Produto pegarProdutoPorCodigo(){
    // Retorna um produto a partir do codigo informado.
    int codComprarProduto = 0, i = 0;
    Produto produtoNaoEncontrado = {0, "", 0};

    printf("Digite o codigo do produto: ");
    scanf("%d", &codComprarProduto);

    for (i = 0; i <= totalProdutos; i++)
    {
        if (listaProdutos[i]->codigo == codComprarProduto)
        {
            return *listaProdutos[i];
        }
    }

    printf("\nProduto nao encontrado. Cadastre-o pelo menu.\n");
    return produtoNaoEncontrado;
}

bool validaCodigo(int codigo){
    // verifica se o codigo e unico
    int i = 0;

    for (i = 0; i < totalProdutos; i++){
        if (codigo == listaProdutos[i]->codigo)
        {
            printf("\nCodigo ja utilizado.\n");
            return false;
        }
    }
    return true;
}

bool validaNome(char *nome) {
    // verifica se o nome esta repetido
    removerEspacos(nome);
    
    if (strlen(nome) < 2) {
        printf("O nome deve ter mais de 1 caractere.\n");
        return false; 
    }

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(listaProdutos[i]->nome, nome) == 0) {
            printf("Produto com o nome '%s' ja existe.\n", nome);
            return false;
         }
    }

    return true; 
}

int temNoCarrinho(char *nome){
    // verifica se o produto esta no carrinho
    for (int i = 0; i < indiceCarrinho; i++)
    {

        if (strcmp(carrinho[i]->produto.nome, nome) == 0)
        {
            return i;
        }
    }
    return -1;
}
