#include <iostream>
#include <map>
#include <string>
using namespace std;

// Estrutura que vai representar o produto
struct Produto {
    string nome;
    double preco;
    int quantidade;
};

// Classe que vai representar a Máquina de Venda
class MaquinaDeVenda {
private:
    map<int, Produto> produtos; // Mapa para guardar os produtos com seus IDs
    double faturamentoTotal; // Variável para guardar o faturamento total da máquina

public:
    MaquinaDeVenda() {
        faturamentoTotal = 0.0;
    }

    // Método para adicionar um novo produto à máquina
    void adicionarProduto(int id, string nome, double preco, int quantidade) {
        Produto produto;
        produto.nome = nome;
        produto.preco = preco;
        produto.quantidade = quantidade;
        produtos[id] = produto; // Adiciona o produto ao mapa de produtos
    }

    // Método para exibir os produtos disponíveis na máquina
    void exibirProdutos() {
        cout << "- Produtos Disponíveis -" << endl;
        for (const auto& par : produtos) {
            int id = par.first; // Pega o ID do produto
            const Produto& produto = par.second; // Pega o produto
            cout << "ID: " << id << ", Nome: " << produto.nome << ", Preço: R$" << produto.preco << ", Quantidade: " << produto.quantidade << endl;
        }
    }

    // Método para comprar um produto da máquina
    void comprarProduto(int idProduto, double valorInserido) {
        if (produtos.find(idProduto) != produtos.end()) { // Verifica se o produto existe
            Produto& produto = produtos[idProduto]; // Pega o produto do mapa
            if (produto.quantidade > 0) { // Verifica se ainda tem o produto
                if (valorInserido >= produto.preco) { // Verifica se o valor colocado é suficiente
                    cout << "Produto '" << produto.nome << "' comprado com sucesso!" << endl;
                    double troco = valorInserido - produto.preco; // Calcula o troco
                    cout << "Troco: R$" << troco << endl;
                    produto.quantidade--; // Diminui a quantidade do produto
                    faturamentoTotal += produto.preco; // Atualiza o faturamento total
                } else {
                    cout << "Valor insuficiente para comprar o produto." << endl;
                }
            } else {
                cout << "Produto esgotado." << endl;
            }
        } else {
            cout << "Produto não encontrado." << endl;
        }
    }

    // Método para exibir o faturamento total da máquina
    void exibirFaturamento() {
        double faturamentoRestante = 0.0;
        for (const auto& par : produtos) {
            const Produto& produto = par.second;
            faturamentoRestante += produto.preco * produto.quantidade;
        }

        cout << "Faturamento Total: R$" << faturamentoTotal << endl;
        cout << "Faturamento Restante: R$" << faturamentoRestante << endl;
    }

    // Método para repor produtos na máquina
    void reporProdutos() {
        cout << "- Repor Produtos -" << endl;
        cout << "Produtos Disponíveis:" << endl;
        exibirProdutos();
        cout << "Digite o ID do produto que deseja repor: ";
        int idProduto;
        cin >> idProduto;

        if (produtos.find(idProduto) != produtos.end()) { // Verifica se o produto existe
            Produto& produto = produtos[idProduto]; // Pega o produto do mapa
            cout << "Digite a quantidade a ser adicionada: ";
            int quantidade;
            cin >> quantidade;
            produto.quantidade += quantidade; // Aumenta a quantidade do produto
            cout << "Produto '" << produto.nome << "' reposto com sucesso!" << endl;
        } else {
            cout << "Produto não encontrado." << endl;
        }
    }
};

int main() {
    MaquinaDeVenda maquina;

    // Adicionando produtos na máquina
    maquina.adicionarProduto(1, "Água", 2.50, 3);
    maquina.adicionarProduto(2, "Refrigerante", 4.00, 5);
    maquina.adicionarProduto(3, "Suco", 3.00, 6);
    maquina.adicionarProduto(4, "Chá", 2.00, 2);
    maquina.adicionarProduto(5, "Bolacha", 1.50, 9);
    maquina.adicionarProduto(6, "Salgadinho", 3.50, 1);
    maquina.adicionarProduto(7, "Bolo", 5.00, 9);
    maquina.adicionarProduto(8, "Chocolate", 3.00, 4);
    maquina.adicionarProduto(9, "Torta", 6.00, 7);

    int opcao = -1;
    while (opcao != 0) {
        cout << "- Máquina de Venda -" << endl;
        cout << "Escolha o modo de operação:" << endl;
        cout << "1. Modo Usuário" << endl;
        cout << "2. Modo Administrador" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        if (opcao == 1) {
            cout << "- Modo Usuário -" << endl;
            maquina.exibirProdutos();
            cout << "Digite o ID do produto que deseja comprar: ";
            int idProduto;
            cin >> idProduto;
            cout << "Digite o valor inserido: ";
            double valorInserido;
            cin >> valorInserido;
            maquina.comprarProduto(idProduto, valorInserido);
        } else if (opcao == 2) {
            cout << "Digite a senha: ";
            string senha;
            cin >> senha;
            if (senha == "123") {
                cout << "- Modo Administrador -" << endl;
                cout << "1. Repor Produtos" << endl;
                cout << "2. Inventário de Produtos" << endl;
                cout << "3. Faturamento Total" << endl;
                cout << "Escolha uma opção: ";
                int adminOpcao;
                cin >> adminOpcao;
                if (adminOpcao == 1) {
                    maquina.reporProdutos();
                } else if (adminOpcao == 2) {
                    maquina.exibirProdutos();
                } else if (adminOpcao == 3) {
                    maquina.exibirFaturamento();
                } else {
                    cout << "Opção inválida. Tente novamente." << endl;
                }
            } else {
                cout << "Senha incorreta. Acesso negado ao modo Administrador." << endl;
            }
        } else if (opcao == 0) {
            cout << "Saindo do programa..." << endl;
        } else {
            cout << "Opção inválida. Tente novamente." << endl;
        }

        cout << endl;
    }

    return 0;
}