<h1 align="center">🧠 Ordenação Externa com Multi-Way Merge Sort + Max-Heap</h1>
<p align="center"><i>Projeto acadêmico da disciplina de Estruturas de Dados (GAC108) — 2025.1</i><br><b>Conversão de CSV para binário e ordenação eficiente em memória secundária</b></p>
<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++ Badge"/>
  <img src="https://img.shields.io/badge/Makefile-Automation-red.svg" alt="Makefile Badge"/>
  <img src="https://img.shields.io/badge/CSV-Binary%20Converter-yellowgreen.svg" alt="CSV Badge"/>
  <img src="https://img.shields.io/badge/Heap-Max--Heap-important.svg" alt="Heap Badge"/>
</p>

---

## 📘 Descrição
Este projeto tem como objetivo a conversão de arquivos `.csv` em arquivos binários e a ordenação dos registros com a técnica **Multi-Way Merge Sort**, utilizando uma **estrutura Max-Heap** para otimizar a fase de intercalação. O sistema simula a ordenação em **memória secundária**, ideal para cenários onde os dados excedem a capacidade de RAM.

---

## 📌 Funcionalidades
- 🔄 Conversão de arquivos `.csv` para `.bin`  
- 👁️ Impressão de registros binários (total ou parcial)  
- ➕ Inserção de novos registros no binário  
- 🧮 Ordenação externa usando **Multi-Way Merge Sort**  
- 📦 Otimização da intercalação com **Max-Heap**  
- 🧪 Validação e testes com dados reais de transferências de propriedades  

---

## 🧠 Técnicas Utilizadas
- Manipulação de arquivos binários em C++  
- Estrutura de dados **Max-Heap** para otimização de merge  
- **Divisão em runs** e criação de arquivos temporários  
- Ordenação eficiente com múltiplos arquivos abertos simultaneamente  
- Automação de compilação com `Makefile`  

---

## 📂 Estrutura do Projeto
```bash
projeto_final_ed/
├── binario.cpp                # Código-fonte principal
├── binario.out                # Executável gerado
├── Makefile                   # Script de compilação
├── property-transfer-*.csv    # Dados de entrada (exemplo)

🛠️ Como Executar

✅ Pré-requisitos
- Compilador C++ (g++ recomendado)
- Linux/macOS ou WSL no Windows
- `make` instalado (para usar o Makefile)

---

⚙️ Compilar o projeto

bash
make

▶️ Executar o programa

bash
./binario.out
