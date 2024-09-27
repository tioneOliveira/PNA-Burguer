// Tione Augusto Gomes de Oliveira e Gabriel Hezequiel Hartmann
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class ItemMenu {
protected:
  string name;
  double price;
  double weight;
  string description;
  int prepTime;

public:
  ItemMenu() {
    name = " ";
    price = 0;
    weight = 0;
    description = " ";
    prepTime = 0;
  }
  ItemMenu(string name, double price, double weight, string description,
           double prepTime) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->description = description;
    this->prepTime = prepTime;
  }

  string getName() { return name; }
  void setName(string name) { this->name = name; }

  double getPrice() { return price; }
  void setPrice(double price) { this->price = price; }

  double getWeight() { return weight; }
  void setWeight(double weight) { this->weight = weight; }

  string getDescription() { return description; }
  void setDescription(string description) { this->description = description; }

  double getPrepTime() { return prepTime; }
  void setPrepTime(double prepTime) { this->prepTime = prepTime; }

  virtual void print() {
    cout << name << endl;
    cout << "\nDescrição: " << description << endl;
    cout << "\nPeso: " << weight << "g" << endl;
    cout << "Preço: " << price << endl;
    cout << "--------------------------\n" << endl;
  }
};
class Hamburger : public ItemMenu {
protected:
  string bread;
  vector<string> ingredients = {};

public:
  Hamburger() {
    name = "";
    price = 0;
    weight = 0.0;
    prepTime = 0;
    bread = " ";
    ingredients = {};
    description = " ";
    prepTime = 0;
  }
  Hamburger(string name, double price, double weight, string bread,
            vector<string> ingredients, string description, int prepTime) {
    this->name = name;
    this->price = price;
    this->weight = weight;
    this->bread = bread;
    this->ingredients = ingredients;
    this->description = description;
    this->prepTime = prepTime;
  }

  string getBread() { return bread; }
  void setBread(string bread) { this->bread = bread; }

  vector<string> getIngredients() { return ingredients; }
  void setIngredients(vector<string> ingredients) {
    this->ingredients = ingredients;
  }

  void print() {
    cout << name << endl;
    cout << "\nTipo de pão: " << bread << endl;
    cout << "Ingredientes: " << endl;
    for (int i = 0; i < ingredients.size(); i++) {
      cout << "    " << i + 1 << ": " << ingredients[i] << endl;
    }
    cout << "\nPeso: " << weight << "g" << endl;
    cout << "Preço: " << price << endl;
    cout << "--------------------------\n" << endl;
  }
};
class Drink : public ItemMenu {
protected:
  string type;

public:
  Drink() {
    name = "";
    price = 0;
    weight = 0.0;
    type = " ";
    description = " ";
    prepTime = 0;
  }
  Drink(string name, double price, double weight, string type,
        string description, int prepTime) {
    this->name = name;
    this->price = price;
    this->type = type;
    this->description = description;
    this->weight = weight;
    this->prepTime = prepTime;
  }

  string getType() { return type; }
  void setType(string type) { this->type = type; }

  void print() {
    cout << name << endl;
    cout << "\nTipo: " << type << endl;
    cout << "Descrição: " << description << endl;
    cout << "\nPeso: " << weight << "ml" << endl;
    cout << "Preço: " << price << endl;
    cout << "--------------------------\n" << endl;
  }
};
class Combos : public ItemMenu {
protected:
  vector<ItemMenu *> combo;

public:
  Combos() {
    name = " ";
    combo = {};
    price = 0;
    weight = 0.0;
    description = " ";
  }
  Combos(string name, string description, vector<ItemMenu *> combo) {
    this->name = name;
    this->combo = combo;
    this->description = description;
    for (int i = 0; i < combo.size(); i++) {
      price += combo[i]->getPrice();
    }
    price = price - price * 0.3;
    for (int i = 0; i < combo.size(); i++) {
      weight += combo[i]->getWeight();
    }
    for (int i = 0; i < combo.size(); i++) {
      prepTime += combo[i]->getPrepTime();
    }
  }

  void print() {
    cout << name << endl;
    cout << "\nDescrição: " << description << endl;
    cout << "\nItens: " << endl;
    for (int i = 0; i < combo.size(); i++) {
      cout << combo[i]->getName() << endl;
    }
    cout << "\nPeso: " << weight << "g" << endl;
    cout << "Preço: " << price << endl;
    cout << "--------------------------\n" << endl;
  }
};

class Cardapio {
private:
  vector<ItemMenu *> itens = {};

public:
  Cardapio() { itens = {}; }
  Cardapio(vector<ItemMenu *> itens) { this->itens = itens; }

  void addItem(ItemMenu *item) { itens.push_back(item); }

  void print() {
    cout << "Cardápio: " << endl;
    for (int i = 0; i < itens.size(); i++) {
      cout << i + 1 << ": ";
      itens[i]->print();
    }
  }
  vector<ItemMenu *> getItens() { return itens; }
};

class Pedido {
private:
  string cliente;
  Cardapio cardapio;
  vector<int> itens = {};
  string status;
  double price;
  double prepTime;

public:
  Pedido() {
    cliente = " ";
    cardapio = {};
    itens = {};
    status = " ";
    price = 0;
    prepTime = 0;
  }
  Pedido(string cliente, Cardapio cardapio, vector<int> itens) {
    this->cliente = cliente;
    this->cardapio = cardapio;
    this->itens = itens;
    this->status = "Aberto";
    for (int i = 0; i < itens.size(); i++) {
      price += cardapio.getItens()[itens[i] - 1]->getPrice();
      prepTime += cardapio.getItens()[itens[i] - 1]->getPrepTime();
    }
  }

  void setStatus(string status) { this->status = status; }

  void prepararPedido() {
    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    for (int i = 0; i < prepTime; i++) {
      cout << "Preparando pedido..." << endl;
      sleep_for(1ns);
      sleep_until(system_clock::now() + 1s);
    }
    cout << "\nPedido pronto!" << endl;
    setStatus("Pedido pronto!");
  }

  double getPrice() { return price; }
  int getPrepTime() { return prepTime; }
  void printPedido() {
    cout << "\nPedido de " << cliente << endl;
    for (int i = 0; i < itens.size(); i++) {
      cout << cardapio.getItens()[itens[i] - 1]->getName() << endl;
    }
    cout << "Preço: " << price << endl;
    cout << "Status: " << status << endl;
    cout << "Tempo de preparo: " << prepTime << " minutos\n" << endl;
  }
};

class Pagamento {
protected:
  double saldo;

public:
  Pagamento() { saldo = 0; }
  Pagamento(double saldo) { this->saldo = saldo; }
  void setSaldo(double saldo) { this->saldo = saldo; }

  void virtual pagar(Pedido pedido) {
    saldo -= pedido.getPrice();
    cout << "Pago com dinheiro!" << endl;
  }
};
class Pix : public Pagamento {
public:
  Pix() { saldo = 0; }
  Pix(double saldo) { this->saldo = saldo; }

  void pagar(Pedido pedido) {
    cout << "Leia o QR CODE: " << endl;
    cout << "imagine um qr code" << endl;
    saldo -= pedido.getPrice();
    cout << "Pago com Pix!" << endl;
  }
};
class Cartao : public Pagamento {
public:
  Cartao() { saldo = 0; }
  Cartao(double saldo) { this->saldo = saldo; }
  void pagar(Pedido pedido) {
    string senha = "";
    cout << "Passe o cartão: " << endl;
    cout << "imagine um cartão sendo passado" << endl;
    cout << "Digite sua senha" << endl;
    cin >> senha;
    saldo -= pedido.getPrice();
    cout << "Pago com cartão!" << endl;
  }
};

int main() {
  ItemMenu batataFrita("Batata Frita da Casa", 15.00, 200,
                       "Batata frita com molho especial", 5);
  ItemMenu aneisDeCebola("Aneis de Cebola", 25.00, 300,
                         "Anéis tão perfeitos que nem Frodo o jogaria fora", 8);
  ItemMenu nuggets("Nuggets", 10.00, 200, "Não queira saber como é feito", 10);
  ItemMenu batata("Batata C&B", 20.00, 150,
                  "Batata com chedder e bacon, não questione", 10);

  Hamburger pnaBurguer(
      "PNA Burguer", 35.00, 500, "Pão 100% Italiano de Riozinho",
      {"Carne 100% de Jacaré", "Queijo", "Cebola",
       "Molho especial, Lagrimas dos Keynesianistas "},
      "Hamburguer 100% livre de imposto, tá tranquilo, tá sonegado!", 10);
  Hamburger hoppeBurguer(
      "Hoppe Burguer", 45.00, 600, "Pão de hambuerguer Americano",
      {"Carne 100% Águia Careca", "Queijo Americano", "Cebola Americana",
       "*solo de Freebird", "M4"},
      "Hamburguer tão Americano que você vai se sentir livre!", 15);
  Hamburger duploSimetrico(
      "Duplo Simetrico", 22.22, 222, "Pão Brioche",
      {"Blend 50% Bovino 50% Suíno", "Queijo Cheddar", "Alface", "Molho BBQ",
       "Molho QBB"},
      "Hamburguer espelhado no eixo x, os ingredientes são dispostos "
      "simetricamente no topo e na base do hamburguer, cada repetição dessa "
      "sequencia a quantidade é dividida pela metade numa progressão infinita "
      "que desafia a física, o diferencial da casa!",
      360);
  Hamburger desinteriaBurguer(
      "Desinteria Burguer", 64.19, 480, "Pão Australiano",
      {"Carne de Lagarto", "Alface Americana", "Cebola Caramelizada no Shoyu",
       "Mix de queijos Brie, gorgonzola, provolole e meia cura, tomate cereja "
       "confitado",
       "Molho especial da casa"},
      "Servido em duas finíssimas de pão australiano esmagadas na chapa, o "
      "Chico Buarque conta com duas fatias generosas de hamburguer de lagarto, "
      "cada uma com 180 gramas. A salada, crocante e firme, é composta por "
      "cebola caramelizada no shoyo, tomate cereja confitado e alface "
      "americana completamente industrializada. Adornado com um generoso mix "
      "de queijos, composto por brie, gorgonzola, provolone e meia cura, o "
      "sanduíche é inundado com um molho especial da casa.",
      20);

  Drink pnaCola("PNA-Cola", 5.00, 500, "Refrigerante",
                "Livre de açucar e de impostos!", 0);
  Drink pnaLimonada("PNA-Limonada", 5.00, 500, "Suco",
                    "Limonada de limões suiços, um paraíso tanto para o "
                    "paladar, quanto fiscal!",
                    2);
  Drink weissBier(
      "Weissbear", 20.00, 300, "Cerveja",
      "Cerveja com nome alemão pra cobrar caro, feito em Tramandaí!", 0);
  Drink apanhandoNoRodaViva(
      "Apanhando no Roda Viva", 21.00, 200, "Destilado",
      "Um fatal drink de Bloody Mary com molho de pimenta Carolina Reaper, a "
      "nostalgia não vivida de apanhar no Roda Viva!",
      5);

  Combos apanhandoAoVivoNoRodaViva(
      "Apanhando ao Vivo no Roda Viva",
      "A experiência de ser levado de volta no tempo. A nostalgia, tanto a boa "
      "quanto a ruim, de lutar contra o invencível. O combo"
      "Apanhando ao Vivo no Roda Viva te leva de volta a essa época. "
      "Te leva de volta à cadeira em que você estava amarrado, enquanto "
      "alicates beliscavam as pontas dos seus dedos, gentilmente separando a "
      "cutícula das suas unhas.",
      {&desinteriaBurguer, &apanhandoNoRodaViva, &batata});

  Cardapio cardapioLiberdade(
      {&pnaBurguer, &hoppeBurguer, &duploSimetrico, &desinteriaBurguer, &batata,
       &aneisDeCebola, &nuggets, &batataFrita, &pnaCola, &pnaLimonada,
       &weissBier, &apanhandoNoRodaViva, &apanhandoAoVivoNoRodaViva});

  cardapioLiberdade.print();

  Pagamento pagamento(1000000);
  Pix pix(1000000);
  Cartao cartao(1000000);

  int nPedidos = 0;
  int nItens = 0;
  double saldo = 0.0;

  vector<Pedido> pedidosDoDia;

  do {
    vector<int> pedido;
    string nome;
    cout << "Digite seu nome: " << endl;
    cin >> nome;
    do {
      cout << "Digite o números do item que deseja adicionar ao seu pedido:\n ";
      int item;
      cin >> item;
      pedido.push_back(item);

      nItens++;

      cout << "Deseja adicionar mais algum item? (1 - Sim, 2 - Não):\n ";
      int add;
      cin >> add;
      if (add == 2) {
        cout << "Aguarde...\n";
        break;
      }
    } while (true);
    Pedido pedidoLiberdade(nome, cardapioLiberdade, pedido);
    pedidoLiberdade.setStatus("Aguardando Pagamento...");
    pedidoLiberdade.printPedido();

    cout
        << "\nQual a forma de pagamento? (1 - Dinheiro, 2 - Pix, 3 - Cartão): ";
    int formaPagamento;
    cin >> formaPagamento;
    if (formaPagamento == 1) {
      pagamento.pagar(pedidoLiberdade);
      nPedidos++;
      saldo += pedidoLiberdade.getPrice();
      pedidoLiberdade.setStatus("Preparando...");
      pedidoLiberdade.printPedido();
      pedidoLiberdade.prepararPedido();
      pedidosDoDia.push_back(pedidoLiberdade);
    } else if (formaPagamento == 2) {
      pix.pagar(pedidoLiberdade);
      nPedidos++;
      saldo += pedidoLiberdade.getPrice();
      pedidoLiberdade.setStatus("Preparando...");
      pedidoLiberdade.printPedido();
      pedidoLiberdade.prepararPedido();
      pedidosDoDia.push_back(pedidoLiberdade);
    } else if (formaPagamento == 3) {
      cartao.pagar(pedidoLiberdade);
      nPedidos++;
      saldo += pedidoLiberdade.getPrice();
      pedidoLiberdade.setStatus("Preparando...");
      pedidoLiberdade.printPedido();
      pedidoLiberdade.prepararPedido();
      pedidosDoDia.push_back(pedidoLiberdade);
    } else
      cout << "ERRO" << endl;

    cout << "Deseja fazer outro pedido? (1 - Sim, 2 - Não)\n";
    int add;
    cin >> add;
    if (add == 2) {
      break;
    }

  } while (true);

  cout << "\nPedidos realizados: " << nPedidos << endl;
  cout << "Itens no vendidos: " << nItens << endl;
  cout << "Saldo: " << saldo << endl;

  for (int i = 0; i < pedidosDoDia.size(); i++) {
    pedidosDoDia[i].printPedido();
  }

  return 0;
};
