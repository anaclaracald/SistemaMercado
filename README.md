# Sistema de Mercado

Este projeto implementa um **Sistema de Mercado** simples em linguagem C, onde os usuários podem cadastrar produtos, adicioná-los a um carrinho de compras, visualizar o carrinho, fechar o pedido, entre outras funcionalidades. O sistema simula operações essenciais de um mercado, como listagem de produtos e cálculo de subtotais no carrinho.

## Requisitos

Para compilar e executar o sistema de mercado, é necessário ter:

- Um compilador de C (por exemplo, GCC)
- Sistema operacional compatível com `system("cls")` (pode ser adaptado para `system("clear")` em sistemas Unix)

## Instruções de Compilação

1. Baixe o código-fonte e salve em um arquivo, por exemplo, `sistema_mercado.c`.
2. Abra um terminal ou prompt de comando e navegue até o diretório onde o arquivo foi salvo.
3. Utilize o comando abaixo para compilar o código:

   ```sh
   gcc sistema_mercado.c -o sistema_mercado

## Funcionalidades Principais

- **Cadastro de Produtos**: Adiciona produtos ao sistema com um código único, nome e preço.
- **Listar Produtos**: Exibe todos os produtos cadastrados, mostrando código, nome e preço.
- **Comprar Produto**: Adiciona produtos ao carrinho de compras.
- **Visualizar Carrinho**: Exibe os produtos adicionados ao carrinho, com quantidades e subtotais.
- **Fechar Pedido**: Calcula o total da compra e gera uma fatura detalhada, além de esvaziar o carrinho.

## Funcionalidades extras

- **Remover Produto do Carrinho**: Remove produtos do carrinho de compras.
- **Renomear Produto**: Permite alterar o nome de um produto já cadastrado.
  
## Estrutura do Código

### Estruturas Utilizadas

- **Produto**: Representa um produto com código, nome e preço.
    ```c
    typedef struct _produto {
        int codigo;
        char nome[50];
        float preco;
    } Produto;
    ```

- **Carrinho**: Armazena o produto adicionado ao carrinho, sua quantidade e o subtotal do item.
    ```c
    typedef struct _carrinho {
        Produto produto;
        int quantidade;
        double subtotal;
    } Carrinho;
    ```

### Variáveis Globais

- **`int operacao`**: Armazena a operação escolhida no menu pelo usuário.
- **`int totalProdutos`**: Conta quantos produtos foram cadastrados no sistema.
- **`int indiceCarrinho`**: Indica a quantidade de produtos no carrinho de compras.
- **`Produto *listaProdutos[50]`**: Lista de produtos cadastrados.
- **`Carrinho *carrinho[50]`**: Lista dos produtos no carrinho de compras.

### Funções 

#### Sistema e Menu
- **`SystemClear()`**: Limpa a tela do console.
- **`menu()`**: Exibe o menu principal do sistema e gerencia as operações.

#### Cadastro e Gerenciamento de Produtos
- **`Produto *cadastrarProduto()`**: Permite o cadastro de novos produtos, verificando se o código já foi utilizado.
- **`void listarProdutos()`**: Exibe todos os produtos cadastrados com código, nome e preço.
- **`Produto pegarProdutoPorCodigo()`**: Retorna um produto pelo código informado.
- **`void atualizarNome()`**: Permite alterar o nome de um produto já cadastrado.

#### Carrinho de Compras
- **`void comprarProduto()`**: Adiciona produtos ao carrinho e atualiza a quantidade se o produto já estiver no carrinho.
- **`void visualizarCarrinho()`**: Exibe os produtos, quantidades e subtotais no carrinho.
- **`void removerCarrinho()`**: Remove produtos do carrinho.
- **`void fecharPedido()`**: Calcula o valor total da compra e gera uma fatura detalhada, além de limpar o carrinho.

### Funções Auxiliares

- **`bool validaCodigo(int codigo)`**: Verifica se o código do produto já existe.
- **`bool validaNome(char *nome)`**: Valida o nome do produto (não pode ser vazio ou já existente), também, valida se o usuário não digitou um espaço ao invés do nome.
- **`int temNoCarrinho(char *nome)`**: Verifica se o produto já está no carrinho.
- **`void removerEspacos(char *str)`**: Remove espaços em branco no início e no fim de uma string.

## Fluxo do Sistema

1. **Sair do sistema**: Fecha o sistema de mercado.
2. **Menu Inicial**: O usuário navega pelo menu e escolhe as operações desejadas.
3. **Cadastro de Produtos**: O usuário insere código, nome e preço para cadastrar novos produtos.
4. **Compra de Produtos**: O usuário adiciona produtos ao carrinho informando o código e a quantidade.
5. **Visualização do Carrinho**: Exibe os produtos no carrinho e seus detalhes (quantidade, preço, subtotal).
6. **Renomeação de produto**: Opção para renomear produto, solicita o código do produto e o novo nome.
7. **Remoção do Carrinho**: O usuário pode remover produtos do carrinho.
8. **Finalização do Pedido**: Calcula o total da compra e limpa o carrinho após a compra.

## Aplicabilidade

Este sistema pode ser aplicado como uma base para implementação de um software de ponto de venda (POS) em um mercado, supermercado ou loja. Ele realiza operações básicas de cadastro, compras e gerenciamento de carrinho, podendo ser expandido para incluir funcionalidades como autenticação de usuários, integração com bancos de dados ou sistemas de pagamento.

## Melhorias Futuras

- Implementar um banco de dados para persistir os produtos e pedidos.
- Adicionar suporte a diferentes formas de pagamento.
- Criar uma interface gráfica (GUI) para facilitar o uso do sistema.
