/*Trabalho prático da disciplina Estruturas de Dados (GAC108)
Integrantes: Gabriel Henrique De Paula Santos - 202320596
Marina Barbosa Valim - 202410197 
Vitor Gabriel Firmino - 202320923
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <iomanip>

using namespace std;

const double VALOR_VAZIO_DOUBLE = -00001.0;

// Função para copiar string
void copiarStringSeguro(char *destino, const char *origem, size_t tamanho_destino)
{
    if (origem == nullptr)
    {
        destino[0] = '\0';
        return;
    }
    strncpy(destino, origem, tamanho_destino - 1);
    destino[tamanho_destino - 1] = '\0';
}

// Controle de exceção 
void lerStringSegura(const char *prompt, char *destino, int tamanhoMaximo)
{
    char entradaTemporaria[256]; 
    bool entradaValida = false;

    do
    {
        cout << prompt;
        cin.getline(entradaTemporaria, sizeof(entradaTemporaria));

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "ERRO!: Entrada muito longa. Tente novamente." << endl;
        }
        
        else if (strlen(entradaTemporaria) >= tamanhoMaximo)
        {
            cerr << "ERRO!: O valor inserido e muito longo (max " << tamanhoMaximo - 1 << " caracteres). Tente novamente." << endl;
        }

        else
        {
            entradaValida = true;
        }
    } while (!entradaValida);

    copiarStringSeguro(destino, entradaTemporaria, tamanhoMaximo);
}

double lerDoubleSeguro(const char *prompt)
{
    double valor;
    bool entradaValida = false;

    do
    {
        cout << prompt;
        cin >> valor;

        if (cin.fail())
        {
            cin.clear();                                        
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cerr << "ERRO!: Insira um numero valido." << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            entradaValida = true;
        }
    } while (!entradaValida);

    return valor;
}

// Função para ler um número inteiro de forma segura.
int lerInteiroSeguro(const char *prompt)
{
    int valor;
    bool entradaValida = false;

    do
    {
        cout << prompt;
        cin >> valor;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "ERRO!: Insira um numero inteiro valido." << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            entradaValida = true;
        }
    } while (!entradaValida);

    return valor;
}



// Extrai um campo de uma linha CSV
int extrairCampoCsv(const char *linha, int posicao_inicio, char delimitador, char *saida, int tamanho_saida)
{
    int pos_atual = posicao_inicio;
    int indice_saida = 0;
    bool temAspas = false;
    bool continuarLoop = true;

    if (linha[pos_atual] == '"')
    {
        temAspas = true;
        pos_atual++;
    }

    while (linha[pos_atual] != '\0' && continuarLoop)
    {
        if (temAspas)
        {
            if (linha[pos_atual] == '"')
            {
                if (linha[pos_atual + 1] == '"')
                {
                    if (indice_saida < tamanho_saida - 1)
                    {
                        saida[indice_saida++] = '"';
                    }
                    pos_atual += 2;
                }
                else
                {
                    temAspas = false;
                    pos_atual++;
                    continuarLoop = false;
                }
            }
            else
            {
                if (indice_saida < tamanho_saida - 1)
                {
                    saida[indice_saida++] = linha[pos_atual];
                }
                pos_atual++;
            }
        }
        else
        {
            if (linha[pos_atual] == delimitador)
            {
                continuarLoop = false;
            }
            else
            {
                if (indice_saida < tamanho_saida - 1)
                {
                    saida[indice_saida++] = linha[pos_atual];
                }
                pos_atual++;
            }
        }
    }
    saida[indice_saida] = '\0';

    if (linha[pos_atual] == delimitador)
    {
        pos_atual++;
    }
    return pos_atual;
}

// Converte uma string para double, tratando valores vazios ou "Not Provided"
double analisarCampoNumerico(const char *s)
{
    if (s == nullptr || s[0] == '\0' || strcmp(s, "Not Provided") == 0 || strcmp(s, "C") == 0 || strcmp(s, "P") == 0)
    {
        return VALOR_VAZIO_DOUBLE;
    }
    return atof(s);
}

// Converte uma string para int, tratando valores vazios
int analisarCampoInteiro(const char *s)
{
    if (s == nullptr || s[0] == '\0' || strcmp(s, "Not Provided") == 0)
    {
        return 0;
    }
    return atoi(s);
}

class EntradaDadosCsv
{
public:
    char referenciaSerie[50];
    double periodo;
    double valorDado;
    char status[10];
    char unidades[20];
    int magnitude;
    char assunto[50];
    char periodicidade[20];
    char grupo[50];
    char tituloSerie1[100];
    char tituloSerie2[100];
    char tituloSerie3[100];
    char tituloSerie4[100];
    char tituloSerie5[100];

    EntradaDadosCsv() : periodo(0.0), valorDado(VALOR_VAZIO_DOUBLE), magnitude(0)
    {
        referenciaSerie[0] = '\0';
        status[0] = '\0';
        unidades[0] = '\0';
        assunto[0] = '\0';
        periodicidade[0] = '\0';
        grupo[0] = '\0';
        tituloSerie1[0] = '\0';
        tituloSerie2[0] = '\0';
        tituloSerie3[0] = '\0';
        tituloSerie4[0] = '\0';
        tituloSerie5[0] = '\0';
    }

    // Exibe todo o conteúdo do registro
    void exibir() const
    {
        cout << referenciaSerie << ",";
        cout << fixed << setprecision(2) << periodo << ",";
        if (valorDado == VALOR_VAZIO_DOUBLE)
        {
            cout << ",";
        }
        else
        {
            cout << fixed << setprecision(2) << valorDado << ",";
        }
        cout << status << "," << unidades << "," << magnitude << ",";
        cout << assunto << "," << periodicidade << "," << grupo << ",";
        cout << tituloSerie1 << "," << tituloSerie2 << "," << tituloSerie3 << ",";
        cout << tituloSerie4 << "," << tituloSerie5;
    }

    static int compararDecrescente(const EntradaDadosCsv *A, const EntradaDadosCsv *B)
    {
        // Primeiro critério de ordenação será o período
        if (A->periodo > B->periodo)
        {
            return -1; // Período de A é maior, então A vem antes (decrescente).
        }
        if (A->periodo < B->periodo)
        {
            return 1; // Período de B é maior, então B vem antes.
        }

        // Caso os períodos forem iguais, então será usado referenciaSerie
        return -strcmp(A->referenciaSerie, B->referenciaSerie);
    }
};

struct NohHeap
{
    EntradaDadosCsv data;
    long indiceArq;
};

class MaxHeap
{
private:
    NohHeap *vetorHeap;
    int capacidade;
    int tamAtual;

    int pai(int i) { return (i - 1) / 2; }
    int filhoEsq(int i) { return (2 * i + 1); }
    int filhoDir(int i) { return (2 * i + 2); }

    void swap(NohHeap *x, NohHeap *y)
    {
        NohHeap temp = *x;
        *x = *y;
        *y = temp;
    }

    void corrigeDescendo(int i)
    {
        int l = filhoEsq(i);
        int r = filhoDir(i);
        int maior = i;

        if (l < tamAtual && EntradaDadosCsv::compararDecrescente(&vetorHeap[l].data, &vetorHeap[maior].data) < 0)
        {
            maior = l;
        }

        if (r < tamAtual && EntradaDadosCsv::compararDecrescente(&vetorHeap[r].data, &vetorHeap[maior].data) < 0)
        {
            maior = r;
        }

        if (maior != i)
        {
            swap(&vetorHeap[i], &vetorHeap[maior]);
            corrigeDescendo(maior);
        }
    }

    void corrigeSubindo(int i)
    {

        while (i != 0 && EntradaDadosCsv::compararDecrescente(&vetorHeap[i].data, &vetorHeap[pai(i)].data) < 0)
        {
            swap(&vetorHeap[i], &vetorHeap[pai(i)]);
            i = pai(i);
        }
    }

public:
    MaxHeap(int cap)
    {
        capacidade = cap;
        tamAtual = 0;
        vetorHeap = new (nothrow) NohHeap[capacidade];
        if (vetorHeap == nullptr)
        {
            cerr << "Falha na alocacao de memoria para o MaxHeap!" << endl;
        }
    }

    ~MaxHeap()
    {
        delete[] vetorHeap;
    }

    void insereNoh(NohHeap noh)
    {
        if (tamAtual == capacidade)
            return;
        tamAtual++;
        int i = tamAtual - 1;
        vetorHeap[i] = noh;
        corrigeSubindo(i);
    }

    NohHeap extraiRaiz()
    {
        if (tamAtual <= 0)
        {
            NohHeap noh_vazio;
            noh_vazio.indiceArq = -1;
            return noh_vazio;
        }
        if (tamAtual == 1)
        {
            tamAtual--;
            return vetorHeap[0];
        }
        NohHeap raiz = vetorHeap[0];
        vetorHeap[0] = vetorHeap[tamAtual - 1];
        tamAtual--;
        corrigeDescendo(0);
        return raiz;
    }

    int obterTam() const
    {
        return tamAtual;
    }
};

class GerenciadorDadosBinarios
{
private:
    char nomeArquivoCsv[100];
    char nomeArquivoBinario[100];

    // Métodos para ordenação
    void intercalar(EntradaDadosCsv *arr, long esquerda, long meio, long direita);
    void ordenarIntercalacao(EntradaDadosCsv *arr, long esquerda, long direita);
    long dividirEOrdenarSubArquivos(const char *prefixo, char nomesSubArquivos[][100], int maxSubArquivos);
    void intercalarSubArquivosOrdenados(char nomesSubArquivos[][100], long numSubArquivos);

    EntradaDadosCsv criarNovaEntrada();
    long obterTotalRegistros();

public:
    GerenciadorDadosBinarios(const char *csvFname, const char *binFname)
    {
        copiarStringSeguro(nomeArquivoCsv, csvFname, sizeof(nomeArquivoCsv));
        copiarStringSeguro(nomeArquivoBinario, binFname, sizeof(nomeArquivoBinario));
    }

    void converterCsvParaBinario();
    void imprimirArquivoBinario(long posInicial, long posFinal);
    void adicionarRegistroEmPosicao(long posicao);
    void alterarRegistroEmPosicao(long posicao);
    void trocarRegistros(long pos1, long pos2);
    void ordenarArquivoBinario(const char *nomeSubarqTemp);
    void exibirMenuEExecutar();
};

void GerenciadorDadosBinarios::converterCsvParaBinario()
{
    ifstream arquivoEntrada(nomeArquivoCsv);
    ofstream arquivoSaida(nomeArquivoBinario, ios::binary);

    if (!arquivoEntrada.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir o arquivo CSV: " << nomeArquivoCsv << endl;
        return;
    }
    if (!arquivoSaida.is_open())
    {
        cerr << "Erro: Nao foi possivel criar o arquivo binario: " << nomeArquivoBinario << endl;
        return;
    }

    char bufferLinha[1024];
    arquivoEntrada.getline(bufferLinha, sizeof(bufferLinha)); // Pula o cabeçalho

    while (arquivoEntrada.getline(bufferLinha, sizeof(bufferLinha)))
    {
        if (bufferLinha[0] == '\0')
            continue;

        EntradaDadosCsv entrada;
        int pos_atual = 0;
        char campoTemporario[200];

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.referenciaSerie));
        copiarStringSeguro(entrada.referenciaSerie, campoTemporario, sizeof(entrada.referenciaSerie));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(campoTemporario));
        entrada.periodo = analisarCampoNumerico(campoTemporario);

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(campoTemporario));
        entrada.valorDado = analisarCampoNumerico(campoTemporario);

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.status));
        copiarStringSeguro(entrada.status, campoTemporario, sizeof(entrada.status));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.unidades));
        copiarStringSeguro(entrada.unidades, campoTemporario, sizeof(entrada.unidades));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(campoTemporario));
        entrada.magnitude = analisarCampoInteiro(campoTemporario);

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.assunto));
        copiarStringSeguro(entrada.assunto, campoTemporario, sizeof(entrada.assunto));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.periodicidade));
        copiarStringSeguro(entrada.periodicidade, campoTemporario, sizeof(entrada.periodicidade));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.grupo));
        copiarStringSeguro(entrada.grupo, campoTemporario, sizeof(entrada.grupo));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.tituloSerie1));
        copiarStringSeguro(entrada.tituloSerie1, campoTemporario, sizeof(entrada.tituloSerie1));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.tituloSerie2));
        copiarStringSeguro(entrada.tituloSerie2, campoTemporario, sizeof(entrada.tituloSerie2));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.tituloSerie3));
        copiarStringSeguro(entrada.tituloSerie3, campoTemporario, sizeof(entrada.tituloSerie3));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, ',', campoTemporario, sizeof(entrada.tituloSerie4));
        copiarStringSeguro(entrada.tituloSerie4, campoTemporario, sizeof(entrada.tituloSerie4));

        pos_atual = extrairCampoCsv(bufferLinha, pos_atual, '\n', campoTemporario, sizeof(entrada.tituloSerie5));
        copiarStringSeguro(entrada.tituloSerie5, campoTemporario, sizeof(entrada.tituloSerie5));

        arquivoSaida.write(reinterpret_cast<char *>(&entrada), sizeof(EntradaDadosCsv));
    }

    arquivoEntrada.close();
    arquivoSaida.close();
    cout << "Conversao de CSV para binario concluida." << endl;
}

void GerenciadorDadosBinarios::imprimirArquivoBinario(long posInicial, long posFinal)
{
    ifstream arquivoBinario(nomeArquivoBinario, ios::binary);

    if (!arquivoBinario.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir o arquivo binario: " << nomeArquivoBinario << endl;
        return;
    }

    arquivoBinario.seekg(0, ios::end);
    long tamanhoArquivo = arquivoBinario.tellg();
    arquivoBinario.seekg(0, ios::beg);

    long numRegistros = tamanhoArquivo / sizeof(EntradaDadosCsv);

    long inicioReal = (posInicial < 0 || posInicial >= numRegistros) ? 0 : posInicial;
    long fimReal = (posFinal < 0 || posFinal >= numRegistros) ? numRegistros - 1 : posFinal;

    if (inicioReal > fimReal)
    {
        cerr << "Intervalo de impressao invalido." << endl;
        arquivoBinario.close();
        return;
    }

    arquivoBinario.seekg(inicioReal * sizeof(EntradaDadosCsv));

    EntradaDadosCsv entrada;
    bool continuarLeitura = true;

    for (long i = inicioReal; i <= fimReal && continuarLeitura; ++i)
    {
        if (arquivoBinario.read(reinterpret_cast<char *>(&entrada), sizeof(EntradaDadosCsv)))
        {
            cout << "Posicao " << i << ": ";
            entrada.exibir();
            cout << endl;
        }
        else
        {
            cerr << "Erro de leitura no registro " << i << endl;
            continuarLeitura = false;
        }
    }

    arquivoBinario.close();
}

long GerenciadorDadosBinarios::obterTotalRegistros()
{
    ifstream arquivo(nomeArquivoBinario, ios::binary | ios::ate);
    if (!arquivo.is_open())
    {
        return -1;
    }
    long tamanhoArquivo = arquivo.tellg();
    arquivo.close();
    return tamanhoArquivo / sizeof(EntradaDadosCsv);
}

EntradaDadosCsv GerenciadorDadosBinarios::criarNovaEntrada()
{
    EntradaDadosCsv novaEntrada;
    char bufferTemporario[256]; // Buffer para campos que podem ser vazios

    cout << "--- Inserir Novo Registro ---" << endl;

    lerStringSegura("Series_reference (max 49 chars): ", novaEntrada.referenciaSerie, sizeof(novaEntrada.referenciaSerie));

    novaEntrada.periodo = lerDoubleSeguro("Period (double): ");

    // Para o Data_value, permitimos que o usuário deixe em branco
    cout << "Data_value (double, deixe em branco para vazio): ";
    cin.getline(bufferTemporario, sizeof(bufferTemporario));
    novaEntrada.valorDado = analisarCampoNumerico(bufferTemporario);
    // Limpa estado de falha caso o usuário tenha digitado algo muito longo aqui
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    lerStringSegura("Status (max 9 chars): ", novaEntrada.status, sizeof(novaEntrada.status));
    lerStringSegura("Units (max 19 chars): ", novaEntrada.unidades, sizeof(novaEntrada.unidades));

    novaEntrada.magnitude = lerInteiroSeguro("Magnitude (int): ");

    lerStringSegura("Subject (max 49 chars): ", novaEntrada.assunto, sizeof(novaEntrada.assunto));
    lerStringSegura("Periodicity (max 19 chars): ", novaEntrada.periodicidade, sizeof(novaEntrada.periodicidade));
    lerStringSegura("Group (max 49 chars): ", novaEntrada.grupo, sizeof(novaEntrada.grupo));
    lerStringSegura("Series_title_1 (max 99 chars): ", novaEntrada.tituloSerie1, sizeof(novaEntrada.tituloSerie1));
    lerStringSegura("Series_title_2 (max 99 chars): ", novaEntrada.tituloSerie2, sizeof(novaEntrada.tituloSerie2));
    lerStringSegura("Series_title_3 (max 99 chars): ", novaEntrada.tituloSerie3, sizeof(novaEntrada.tituloSerie3));
    lerStringSegura("Series_title_4 (max 99 chars): ", novaEntrada.tituloSerie4, sizeof(novaEntrada.tituloSerie4));
    lerStringSegura("Series_title_5 (max 99 chars): ", novaEntrada.tituloSerie5, sizeof(novaEntrada.tituloSerie5));

    return novaEntrada;
}

void GerenciadorDadosBinarios::adicionarRegistroEmPosicao(long posicao)
{
    long totalRegistros = obterTotalRegistros();
    if (totalRegistros == -1)
    {
        cerr << "Erro ao acessar o arquivo binario." << endl;
        return;
    }

    if (posicao < 0 || posicao > totalRegistros)
    {
        cerr << "Posicao invalida para insercao. Deve estar entre 0 e " << totalRegistros << endl;
        return;
    }

    EntradaDadosCsv novaEntrada = criarNovaEntrada();

    char nomeTempArquivo[100];
    copiarStringSeguro(nomeTempArquivo, "temp_binario_insercao.bin", sizeof(nomeTempArquivo));

    ifstream arquivoOriginal(nomeArquivoBinario, ios::binary);
    ofstream arquivoTemporario(nomeTempArquivo, ios::binary);

    if (!arquivoOriginal.is_open() || !arquivoTemporario.is_open())
    {
        cerr << "Erro ao abrir arquivos para insercao." << endl;
        if (arquivoOriginal.is_open())
            arquivoOriginal.close();
        if (arquivoTemporario.is_open())
            arquivoTemporario.close();
        return;
    }

    EntradaDadosCsv registroLido;
    long i = 0;

    while (i < posicao && arquivoOriginal.read(reinterpret_cast<char *>(&registroLido), sizeof(EntradaDadosCsv)))
    {
        arquivoTemporario.write(reinterpret_cast<const char *>(&registroLido), sizeof(EntradaDadosCsv));
        i++;
    }

    arquivoTemporario.write(reinterpret_cast<const char *>(&novaEntrada), sizeof(EntradaDadosCsv));

    while (arquivoOriginal.read(reinterpret_cast<char *>(&registroLido), sizeof(EntradaDadosCsv)))
    {
        arquivoTemporario.write(reinterpret_cast<const char *>(&registroLido), sizeof(EntradaDadosCsv));
    }

    arquivoOriginal.close();
    arquivoTemporario.close();

    if (remove(nomeArquivoBinario) != 0)
    {
        cerr << "Erro ao remover o arquivo binario original para insercao." << endl;
        return;
    }
    if (rename(nomeTempArquivo, nomeArquivoBinario) != 0)
    {
        cerr << "Erro ao renomear o arquivo temporario para insercao." << endl;
        return;
    }

    cout << "Registro adicionado com sucesso na posicao " << posicao << "." << endl;
}

void GerenciadorDadosBinarios::alterarRegistroEmPosicao(long posicao)
{
    long totalRegistros = obterTotalRegistros();
    if (totalRegistros == -1)
    {
        cerr << "Erro ao acessar o arquivo binario." << endl;
        return;
    }

    if (posicao < 0 || posicao >= totalRegistros)
    {
        cerr << "Posicao invalida para alteracao. Deve estar entre 0 e " << totalRegistros - 1 << endl;
        return;
    }

    fstream arquivoBinario(nomeArquivoBinario, ios::binary | ios::in | ios::out);
    if (!arquivoBinario.is_open())
    {
        cerr << "Erro ao abrir o arquivo binario para alteracao." << endl;
        return;
    }

    arquivoBinario.seekg(posicao * sizeof(EntradaDadosCsv));

    EntradaDadosCsv registroAntigo;
    arquivoBinario.read(reinterpret_cast<char *>(&registroAntigo), sizeof(EntradaDadosCsv));
    arquivoBinario.seekp(posicao * sizeof(EntradaDadosCsv));

    cout << "Registro atual na posicao " << posicao << ":" << endl;
    registroAntigo.exibir();
    cout << endl;

    cout << "Por favor, insira os novos dados para o registro:" << endl;
    EntradaDadosCsv novoRegistro = criarNovaEntrada();

    arquivoBinario.write(reinterpret_cast<const char *>(&novoRegistro), sizeof(EntradaDadosCsv));

    arquivoBinario.close();
    cout << "Registro na posicao " << posicao << " alterado com sucesso." << endl;
}

void GerenciadorDadosBinarios::trocarRegistros(long pos1, long pos2)
{
    long totalRegistros = obterTotalRegistros();
    if (totalRegistros == -1)
    {
        cerr << "Erro ao acessar o arquivo binario." << endl;
        return;
    }

    if (pos1 < 0 || pos1 >= totalRegistros || pos2 < 0 || pos2 >= totalRegistros)
    {
        cerr << "Posicoes invalidas para troca. Devem estar entre 0 e " << totalRegistros - 1 << endl;
        return;
    }
    if (pos1 == pos2)
    {
        cout << "As posicoes sao as mesmas, nenhuma troca necessaria." << endl;
        return;
    }

    fstream arquivoBinario(nomeArquivoBinario, ios::binary | ios::in | ios::out);
    if (!arquivoBinario.is_open())
    {
        cerr << "Erro ao abrir o arquivo binario para troca." << endl;
        return;
    }

    EntradaDadosCsv registro1, registro2;

    arquivoBinario.seekg(pos1 * sizeof(EntradaDadosCsv));
    if (!arquivoBinario.read(reinterpret_cast<char *>(&registro1), sizeof(EntradaDadosCsv)))
    {
        cerr << "Erro ao ler registro da posicao " << pos1 << "." << endl;
        arquivoBinario.close();
        return;
    }

    arquivoBinario.seekg(pos2 * sizeof(EntradaDadosCsv));
    if (!arquivoBinario.read(reinterpret_cast<char *>(&registro2), sizeof(EntradaDadosCsv)))
    {
        cerr << "Erro ao ler registro da posicao " << pos2 << "." << endl;
        arquivoBinario.close();
        return;
    }

    arquivoBinario.seekp(pos1 * sizeof(EntradaDadosCsv));
    if (!arquivoBinario.write(reinterpret_cast<const char *>(&registro2), sizeof(EntradaDadosCsv)))
    {
        cerr << "Erro ao escrever registro na posicao " << pos1 << "." << endl;
        arquivoBinario.close();
        return;
    }

    arquivoBinario.seekp(pos2 * sizeof(EntradaDadosCsv));
    if (!arquivoBinario.write(reinterpret_cast<const char *>(&registro1), sizeof(EntradaDadosCsv)))
    {
        cerr << "Erro ao escrever registro na posicao " << pos2 << "." << endl;
        arquivoBinario.close();
        return;
    }

    arquivoBinario.close();
    cout << "Registros nas posicoes " << pos1 << " e " << pos2 << " trocados com sucesso." << endl;
}

void GerenciadorDadosBinarios::intercalar(EntradaDadosCsv *arr, long esquerda, long meio, long direita)
{
    long i, j, k;
    long n1 = meio - esquerda + 1;
    long n2 = direita - meio;

    EntradaDadosCsv *L = new (nothrow) EntradaDadosCsv[n1];
    EntradaDadosCsv *R = new (nothrow) EntradaDadosCsv[n2];

    if (L == nullptr || R == nullptr)
    {
        cerr << "Erro de alocacao de memoria na intercalacao!" << endl;
        delete[] L;
        delete[] R;
        return;
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;

    while (i < n1 && j < n2)
    {
        if (EntradaDadosCsv::compararDecrescente(&L[i], &R[j]) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void GerenciadorDadosBinarios::ordenarIntercalacao(EntradaDadosCsv *arr, long esquerda, long direita)
{
    if (esquerda < direita)
    {
        long meio = esquerda + (direita - esquerda) / 2;
        ordenarIntercalacao(arr, esquerda, meio);
        ordenarIntercalacao(arr, meio + 1, direita);
        intercalar(arr, esquerda, meio, direita);
    }
}

long GerenciadorDadosBinarios::dividirEOrdenarSubArquivos(const char *prefixo, char nomesSubArquivos[][100], int maxSubArquivos)
{
    ifstream arquivoEntrada(nomeArquivoBinario, ios::binary);
    if (!arquivoEntrada.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir o arquivo binario para ordenacao." << endl;
        return 0;
    }

    arquivoEntrada.seekg(0, ios::end);
    long tamanhoTotalArquivo = arquivoEntrada.tellg();
    long totalRegistros = tamanhoTotalArquivo / sizeof(EntradaDadosCsv);
    arquivoEntrada.seekg(0, ios::beg);

    const long MAX_REG = 5000;
    long indiceRegistroAtual = 0;
    int contadorSubArquivos = 0;

    while (indiceRegistroAtual < totalRegistros && contadorSubArquivos < maxSubArquivos)
    {
        long registrosParaLer = (totalRegistros - indiceRegistroAtual < MAX_REG) ? (totalRegistros - indiceRegistroAtual) : MAX_REG;

        EntradaDadosCsv *bloco = new (nothrow) EntradaDadosCsv[registrosParaLer];
        if (bloco == nullptr)
        {
            cerr << "Erro de alocacao de memoria para bloco!" << endl;
            arquivoEntrada.close();
            return contadorSubArquivos;
        }

        arquivoEntrada.read(reinterpret_cast<char *>(bloco), registrosParaLer * sizeof(EntradaDadosCsv));

        ordenarIntercalacao(bloco, 0, registrosParaLer - 1);

        sprintf(nomesSubArquivos[contadorSubArquivos], "subarquivos/%s%d.bin", prefixo, contadorSubArquivos);

        ofstream subArquivo(nomesSubArquivos[contadorSubArquivos], ios::binary);
        if (!subArquivo.is_open())
        {
            cerr << "Erro ao criar subarquivo: " << nomesSubArquivos[contadorSubArquivos] << endl;
            delete[] bloco;
            arquivoEntrada.close();
            return contadorSubArquivos;
        }
        subArquivo.write(reinterpret_cast<const char *>(bloco), registrosParaLer * sizeof(EntradaDadosCsv));
        subArquivo.close();

        delete[] bloco;
        indiceRegistroAtual += registrosParaLer;
        contadorSubArquivos++;
    }
    arquivoEntrada.close();
    return contadorSubArquivos;
}

void GerenciadorDadosBinarios::intercalarSubArquivosOrdenados(char nomesSubArquivos[][100], long numSubArquivos)
{
    if (numSubArquivos <= 0)
        return;

    ifstream *subArquivos = new (nothrow) ifstream[numSubArquivos];
    if (subArquivos == nullptr)
    {
        cerr << "Erro de alocacao de memoria para subArquivos!" << endl;
        return;
    }

    ofstream arquivoSaida(nomeArquivoBinario, ios::binary);
    if (!arquivoSaida.is_open())
    {
        cerr << "Erro ao criar arquivo de saida ordenado: " << nomeArquivoBinario << endl;
        delete[] subArquivos;
        return;
    }

    MaxHeap heap(numSubArquivos);

    for (long i = 0; i < numSubArquivos; ++i)
    {
        subArquivos[i].open(nomesSubArquivos[i], ios::binary);
        if (subArquivos[i].is_open())
        {
            EntradaDadosCsv entrada;
            if (subArquivos[i].read(reinterpret_cast<char *>(&entrada), sizeof(EntradaDadosCsv)))
            {
                NohHeap noh = {entrada, i};
                heap.insereNoh(noh);
            }
        }
    }

    while (heap.obterTam() > 0)
    {
        NohHeap raiz = heap.extraiRaiz();
        arquivoSaida.write(reinterpret_cast<const char *>(&raiz.data), sizeof(EntradaDadosCsv));

        long idcArq = raiz.indiceArq;
        EntradaDadosCsv proximaEntrada;

        if (subArquivos[idcArq].is_open() && subArquivos[idcArq].good())
        {
            if (subArquivos[idcArq].read(reinterpret_cast<char *>(&proximaEntrada), sizeof(EntradaDadosCsv)))
            {
                NohHeap novoNoh = {proximaEntrada, idcArq};
                heap.insereNoh(novoNoh);
            }
        }
    }

    for (long i = 0; i < numSubArquivos; ++i)
    {
        if (subArquivos[i].is_open())
        {
            subArquivos[i].close();
        }
    }
    arquivoSaida.close();
    delete[] subArquivos;
}

void GerenciadorDadosBinarios::ordenarArquivoBinario(const char *nomeSubarqTemp)
{

    system("mkdir -p subarquivos");
    cout << "Iniciando ordenacao do arquivo binario (decrescente)..." << endl;

    // Portabilidade Linux/Windows

    char nomesSubArquivos[500][100];
    long numSubArquivos = 0;

    numSubArquivos = dividirEOrdenarSubArquivos(nomeSubarqTemp, nomesSubArquivos, 500);

    if (numSubArquivos > 0)
    {
        if (remove(nomeArquivoBinario) != 0)
        {
            cerr << "Aviso: Nao foi possivel remover o arquivo principal original. Pode ser que nao exista ou esteja em uso." << endl;
        }
        intercalarSubArquivosOrdenados(nomesSubArquivos, numSubArquivos);

        for (int i = 0; i < numSubArquivos; ++i)
        {
            if (remove(nomesSubArquivos[i]) != 0)
            {
                cerr << "Aviso: Nao foi possivel remover subarquivo temporario: " << nomesSubArquivos[i] << endl;
            }
        }
        cout << "Ordenacao do arquivo binario concluida." << endl;
    }
    else
    {
        cout << "Nenhum registro para ordenar ou erro na criacao de subarquivos." << endl;
    }
}

void GerenciadorDadosBinarios::exibirMenuEExecutar()
{
    int opcao = -1;
    long posicao1, posicao2;

    cout.precision(2);

    while (opcao != 0)
    {
        cout << "=============================================================" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Converter CSV para Binario" << endl;
        cout << "2 - Imprimir registros do Binario (intervalo)" << endl;
        cout << "3 - Adicionar um registro no Binario em posicao especifica" << endl;
        cout << "4 - Alterar um registro no Binario em posicao especifica" << endl;
        cout << "5 - Trocar dois registros de posicao no Binario" << endl;
        cout << "6 - Ordenar arquivo Binario (Decrescente)" << endl;
        cout << "=============================================================" << endl;

        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << "=============================================================" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcao == 1)
        {
            cout << "Convertendo para binario..." << endl;
            converterCsvParaBinario();
        }
        else if (opcao == 2)
        {
            long total = obterTotalRegistros();
            if (total == -1)
            {
                cerr << "Nao foi possivel acessar o arquivo binario. Converta-o primeiro (Opcao 1)." << endl;
                continue;
            }
            cout << "Total de registros: " << total << endl;
            cout << "Posicao inicial para imprimir (0 para o inicio, -1 para todos): ";
            cin >> posicao1;
            cout << "Posicao final para imprimir (Max " << total - 1 << ", -1 para o final): ";
            cin >> posicao2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Imprimindo registros..." << endl;
            imprimirArquivoBinario(posicao1, posicao2);
        }
        else if (opcao == 3)
        {
            long total = obterTotalRegistros();
            if (total == -1)
            {
                cerr << "Nao foi possivel acessar o arquivo binario. Converta-o primeiro (Opcao 1)." << endl;
                continue;
            }
            cout << "Total de registros: " << total << endl;
            cout << "Digite a posicao onde deseja inserir o novo registro (0 a " << total << "): ";
            cin >> posicao1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            adicionarRegistroEmPosicao(posicao1);
        }
        else if (opcao == 4)
        {
            long total = obterTotalRegistros();
            if (total <= 0)
            {
                cerr << "Nenhum registro para alterar ou erro no arquivo. Converta-o primeiro (Opcao 1)." << endl;
                continue;
            }
            cout << "Total de registros: " << total << endl;
            cout << "Digite a posicao do registro a ser alterado (0 a " << total - 1 << "): ";
            cin >> posicao1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            alterarRegistroEmPosicao(posicao1);
        }
        else if (opcao == 5)
        {
            long total = obterTotalRegistros();
            if (total <= 1)
            {
                cerr << "Nao ha registros suficientes para trocar ou erro no arquivo. Converta-o primeiro (Opcao 1)." << endl;
                continue;
            }
            cout << "Total de registros: " << total << endl;
            cout << "Digite a primeira posicao para troca (0 a " << total - 1 << "): ";
            cin >> posicao1;
            cout << "Digite a segunda posicao para troca (0 a " << total - 1 << "): ";
            cin >> posicao2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            trocarRegistros(posicao1, posicao2);
        }
        else if (opcao == 6)
        {
            cout << "Ordenando registros (decrescente)..." << endl;
            ordenarArquivoBinario("subArquivoDecrescente");
        }
        else if (opcao == 0)
        {
            cout << "Saindo..." << endl;
        }
        else
        {
            cout << "Opcao nao encontrada..." << endl;
        }
    }
}

int main()
{
    GerenciadorDadosBinarios gerenciador("property-transfer-statistics-march-2022-quarter-csv.csv", "dados_ordenacao.bin");

    gerenciador.exibirMenuEExecutar();

    return 0;
}