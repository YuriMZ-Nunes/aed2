
# Algoritmos e Estrutura de Dados II

Repositório com os algoritmos aprendidos na disciplina de AED II

## Dependências necessárias
- Compilador C++ [(check here)](https://en.cppreference.com/w/cpp/compiler_support)
    - GCC >= 11 OU
    - Clang >= 13 OU
    - MSVC >= 19 (VS >= 16.10)





## Como funciona

Este repositório contem apenas um programa com todos os algortmos aprendidos

Para rodar, clone o projeto 

```bash
    git clone https://github.com/YuriMZ-Nunes/aed2.git
```

Vá para o diretório do projeto

```bash
    cd aed2/grafoMelhorado
```
Compile os arquivos
```bash
    bash -c make 

    g++ -std=c++17 -Wall -Wextra -g -Iinclude -c -MMD src/dijikstra.cpp  -o src/dijikstra.o
    g++ -std=c++17 -Wall -Wextra -g -Iinclude -c -MMD src/graph.cpp  -o src/    graph.o
    g++ -std=c++17 -Wall -Wextra -g -Iinclude -c -MMD src/main.cpp  -o src/main.o
    g++ -std=c++17 -Wall -Wextra -g -Iinclude -o output/main src/dijikstra.o src/graph.o src/main.o  -Llib
```
Execute
```bash
    ./output/main
```

