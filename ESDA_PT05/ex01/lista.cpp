#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void imprime_lista(list<string> lst)
{
  list<string>::iterator it;

  for(it = lst.begin(); it != lst.end(); it++)
  {
    cout << *it << endl;
  }
}

int main()
{

  // a) criar a lista
  list<string> lst_jogos;

  // b) inserir jogos na lista
  ifstream file("arquivo.txt");
  string line;
  while(getline(file, line))
  {
    lst_jogos.push_back(line);
  }

  // c) imprimir tamanho da lista
  cout << "Foram carregados " << lst_jogos.size() << " jogos." << endl;

  // d) imprimir conteúdo da lista
  for(auto it = lst_jogos.begin(); it != lst_jogos.end(); it++){
    cout << "Pos " <<  distance(lst_jogos.begin(), it) << " -> " << *it << endl;
  }
  
  // e) ordenar lista e imprimir
  for(auto it = lst_jogos.begin(); it != lst_jogos.end(); it++){
    for(auto it2 = it; it2 != lst_jogos.end(); it2++){
      if(*it > *it2){
        string aux = *it;
        *it = *it2;
        *it2 = aux;
      }
    }
  }
  cout << "Lista Ordenada:" << endl;
  for (auto it = lst_jogos.begin(); it != lst_jogos.end(); it++){
    cout << "Pos " <<  distance(lst_jogos.begin(), it) << " -> " << *it << endl;
  }
  
  // f) remover "Mario Kart (Wii)" e imprimir
 for (auto it = lst_jogos.begin(); it != lst_jogos.end(); /* no increment here */) {
    if (*it == "Mario Kart (Wii)") {
        it = lst_jogos.erase(it); // Update iterator after erasing
    } else {
        ++it; // Increment iterator only if no element is erased
    }
  }

  cout << "Lista sem o jogo Mario Kart (Wii):" << endl;
  for (auto it = lst_jogos.begin(); it != lst_jogos.end(); it++) {
    cout << "Pos " << distance(lst_jogos.begin(), it) << " -> " << *it << endl;
  }
  // g) remover jogos PS2 e imprimir
  for (auto it = lst_jogos.begin(); it != lst_jogos.end(); /* no increment here */) {
      // Check if the current game contains "PS2"
      if (it->find("PS2") != string::npos) {
          it = lst_jogos.erase(it); // Update iterator after erasing
      } else {
          ++it; // Increment iterator only if no element is erased
      }
  }
  cout << "Lista sem jogos da PS2:" << endl;
  for (auto it = lst_jogos.begin(); it != lst_jogos.end(); it++) {
    cout << "Pos " << distance(lst_jogos.begin(), it) << " -> " << *it << endl;
  }
  return 0;
}