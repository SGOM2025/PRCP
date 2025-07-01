# Problema de Rotulação Cartográfica de Pontos (PRCP)

Este projeto tem como objetivo a implementação de diferentes heurísticas e estratégias de vizinhança para resolver o **Problema de Rotulação Cartográfica de Pontos (PRCP)**, utilizando a linguagem C++.

## 🗺️ Descrição do Problema

O PRCP consiste em rotular pontos de interesse em um mapa sem causar sobreposição entre os rótulos, visando proporcionar uma visualização mais clara e legível. Quando as sobreposições são permitidas, o objetivo é **maximizar o número de pontos livres de conflitos (sem sobreposição)**.

Cada ponto possui múltiplas **posições candidatas** para inserção de seu rótulo, conforme uma padronização cartográfica comum. Os conflitos ocorrem quando dois rótulos, de pontos diferentes, se sobrepõem em determinadas posições.

### Exemplo ilustrativo:

- Se dois rótulos se sobrepõem: pontuação = 0
- Se ambos os rótulos estão livres: pontuação = 2 (um para cada ponto)

## 📄 Formato das Instâncias

Cada instância contém:

- Número de pontos `n`
- Número de posições candidatas por ponto `m`
- Para cada posição candidata:
  - Número de conflitos
  - Lista de posições conflitantes (por identificador)

## 🧠 Heurísticas Implementadas

O código base disponibiliza estruturas e funções auxiliares. A partir dele, foram implementados os seguintes métodos:

1. **Geração de solução vizinha**  
   - Troca a posição candidata de um ponto para uma nova aleatória.
   
2. **Heurística Construtiva Aleatória**  
   - Atribui aleatoriamente uma posição candidata para cada ponto.

3. **Heurística Construtiva Gulosa**  
   - Escolhe, para cada ponto, a posição com menor número de conflitos.

4. **Heurística Construtiva Aleatória Gulosa (GRASP-like)**  
   - Usa uma lista restrita de candidatos (LRC) com critérios de qualidade para balancear exploração e escolha gulosa.

## 📁 Estrutura dos Arquivos

- `main.cpp` – Arquivo principal com a implementação das heurísticas.
- `cabecalho.h` – Cabeçalhos e estruturas de dados.
- `instancias/` – Pasta contendo os arquivos de instância de teste.
- `README.md` – Este arquivo de descrição.

## ▶️ Execução

Compile o código com:

```bash
g++ main.cpp -o prcp
./prcp